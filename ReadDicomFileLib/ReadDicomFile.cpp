#include "pch.h"
#include "ReadDicomFile.h"

using namespace std;

void ReadDICOMFile::loadDicomAndReadTags(const char* fileName)
{
    DcmFileFormat fileformat;
    OFCondition status = fileformat.loadFile(fileName);

    if (status.good())
    {
        printTagNames[tagCount++] = readTag("PatientName", DCM_PatientName, fileformat);
        printTagNames[tagCount++] = readTag("Modality", DCM_Modality, fileformat);
        printTagNames[tagCount++] = readTag("Rows", DCM_Rows, fileformat);
        printTagNames[tagCount++] = readTag("Columns", DCM_Columns, fileformat);
    }
    else
        cerr << "Error: cannot read DICOM file (" << status.text() << ")" << endl;
}

char* ReadDICOMFile::readTag(const char* tagName, const DcmTagKey& tagKey, DcmFileFormat& fileformat)
{
    OFString value;
    if (fileformat.getDataset()->findAndGetOFString(tagKey, value).good())
    {
        size_t buflen = strlen(value.c_str()) + 1;
        char* buf = OFstatic_cast(char*, malloc(buflen));
        OFStandard::strlcpy(buf, value.c_str(), buflen);
        return buf;
    }
    else
        cerr << "Error: cannot access " << tagName << endl;
    return nullptr;
}
