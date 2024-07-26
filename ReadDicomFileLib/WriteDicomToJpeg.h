#pragma once

#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

#include "dcmtk/dcmdata/dctk.h"          /* for various dcmdata headers */
#include "dcmtk/dcmdata/cmdlnarg.h"      /* for prepareCmdLineArgs */
#include "dcmtk/dcmdata/dcuid.h"         /* for dcmtk version name */
#include "dcmtk/dcmdata/dcrledrg.h"      /* for DcmRLEDecoderRegistration */

#include "dcmtk/dcmimgle/dcmimage.h"     /* for DicomImage */
#include "dcmtk/dcmimgle/digsdfn.h"      /* for DiGSDFunction */
#include "dcmtk/dcmimgle/diciefn.h"      /* for DiCIELABFunction */

#include "dcmtk/ofstd/ofconapp.h"        /* for OFConsoleApplication */
#include "dcmtk/ofstd/ofcmdln.h"         /* for OFCommandLine */

#include "dcmtk/dcmimage/diregist.h"     /* include to support color images */
#include "dcmtk/ofstd/ofstd.h"           /* for OFStandard */

#include "dcmtk/dcmjpeg/djdecode.h"      /* for dcmjpeg decoders */
#include "dcmtk/dcmjpeg/dipijpeg.h"      /* for dcmimage JPEG plugin */

#include "dcmtk/dcmjpls/djdecode.h"      /* for dcmjpls decoders */

class WriteDicomToJpeg
{
public:
	WriteDicomToJpeg(const char* in_fname, const char* out_fname);
	~WriteDicomToJpeg();
	int saveDicomImageInJPEG();
private:

	E_FileReadMode      opt_readMode = ERM_autoDetect;    /* default: fileformat or dataset */
	E_TransferSyntax    opt_transferSyntax = EXS_Unknown; /* default: xfer syntax recognition */

	unsigned long       opt_compatibilityMode = CIF_MayDetachPixelData | CIF_TakeOverExternalDataset;
	OFCmdUnsignedInt    opt_frameCount = 1;               /* default: one frame */
	OFCmdUnsignedInt    opt_frame = 1;                    /* default: first frame */

	const char* opt_ifname = nullptr;
	const char* opt_ofname = nullptr;
};

