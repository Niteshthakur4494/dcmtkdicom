#include "pch.h"
#include "WriteDicomToJpeg.h"

using namespace std;

WriteDicomToJpeg::WriteDicomToJpeg(const char* in_fname, const char* out_fname)
{
	opt_ifname = in_fname;
	opt_ofname = out_fname;
}

WriteDicomToJpeg::~WriteDicomToJpeg()
{
	opt_ifname = nullptr;
	opt_ofname = nullptr;
}

int WriteDicomToJpeg::saveDicomImageInJPEG()
{
	// JPEG parameters
	OFCmdUnsignedInt    opt_quality = 100;                 /* default: 90% JPEG quality */
	E_SubSampling       opt_sampling = ESS_422;           /* default: 4:2:2 sub-sampling */
	E_DecompressionColorSpaceConversion opt_decompCSconversion = EDC_photometricInterpretation;
	OFBool              opt_predictor6WorkaroundEnable = OFFalse;
	OFBool              opt_cornellWorkaroundEnable = OFFalse;
	OFBool              opt_forceSingleFragmentPerFrame = OFFalse;

	/* make sure data dictionary is loaded */
	if (!dcmDataDict.isDictionaryLoaded())
	{
		cerr << "no data dictionary loaded, check environment variable: "
			<< DCM_DICT_ENVIRONMENT_VARIABLE << endl;
	}

	// open inputfile
	if ((opt_ifname == NULL) || (strlen(opt_ifname) == 0))
	{
		cerr << "invalid filename: <empty string>" << endl;
		return 1;
	}

	// register JPEG decompression codecs
	DJDecoderRegistration::registerCodecs(opt_decompCSconversion, EUC_default,
		EPC_default, opt_predictor6WorkaroundEnable, opt_cornellWorkaroundEnable,
		opt_forceSingleFragmentPerFrame);

	OFCondition error = EC_Normal;

	cout << "reading input file " << opt_ifname << endl;

	DcmFileFormat* fileformat = new DcmFileFormat();

	OFCondition cond = fileformat->loadFile(opt_ifname, opt_transferSyntax, EGL_withoutGL, DCM_MaxReadLength, opt_readMode);
	if (error.bad())
	{
		cerr << error.text() << ": reading file: " << opt_ifname << endl;
		return 1;
	}

	cout << "preparing pixel data" << endl;

	DcmDataset* dataset = fileformat->getDataset();
	E_TransferSyntax xfer = dataset->getOriginalXfer();

	Sint32 frameCount;
	if (dataset->findAndGetSint32(DCM_NumberOfFrames, frameCount).bad())
		frameCount = 1;
	if ((opt_frameCount == 0) || ((opt_frame == 1) && (opt_frameCount == OFstatic_cast(Uint32, frameCount))))
	{
		// since we process all frames anyway, decompress the complete pixel data (if required)
		opt_compatibilityMode |= CIF_DecompressCompletePixelData;
	}
	if ((frameCount > 1) && !(opt_compatibilityMode & CIF_DecompressCompletePixelData))
	{
		// use partial read access to pixel data (only in case of multiple frames, but not for all frames)
		opt_compatibilityMode |= CIF_UsePartialAccessToPixelData;
	}

	DicomImage* di = new DicomImage(fileformat, xfer, opt_compatibilityMode, opt_frame - 1, opt_frameCount);
	if (di == NULL)
	{
		cout << "Out of memory" << endl;
		return 1;
	}

	if (di->getStatus() != EIS_Normal)
	{
		cout << DicomImage::getString(di->getStatus()) << endl;
		return 1;
	}

	cout << "activating VOI window min-max algorithm" << endl;
	if (!di->setMinMaxWindow(0))
		cout << "cannot compute min/max VOI window" << endl;

	int result = 0;
	FILE* ofile = NULL;
	OFString ofname;
	unsigned int fcount = OFstatic_cast(unsigned int, ((opt_frameCount > 0) && (opt_frameCount <= di->getFrameCount())) ? opt_frameCount : di->getFrameCount());
	const char* ofext = "jpg";

	if (fcount < opt_frameCount)
	{
		cout << "cannot select " << opt_frameCount << " frames, limiting to "
			<< fcount << " frames" << endl;
	}

	for (unsigned int frame = 0; frame < fcount; frame++)
	{
		if (opt_ofname)
		{
			/* output to file */
			ofname.assign(opt_ofname);
			cout << "writing frame " << (opt_frame + frame) << " to " << ofname << endl;
			ofile = fopen(ofname.c_str(), "wb");
			if (ofile == NULL)
			{
				cerr << "cannot create file " << ofname << endl;
				return 1;
			}
		}
		else {
			/* output to stdout */
			ofile = stdout;
			cout << "writing frame " << (opt_frame + frame) << " to stdout" << endl;
		}

		/* initialize JPEG plugin */
		DiJPEGPlugin plugin;
		plugin.setQuality(OFstatic_cast(unsigned int, opt_quality));
		plugin.setSampling(opt_sampling);
		result = di->writePluginFormat(&plugin, ofile, frame);

		if (opt_ofname)
			fclose(ofile);

		if (!result)
		{
			cout << "cannot write frame" << endl;
			return 1;
		}
	}

	delete di;

	cout << "conversion successful" << endl;

	// deregister global codecs
	DJDecoderRegistration::cleanup();

	return 0;
}
