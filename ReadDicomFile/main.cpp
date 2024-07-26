
#include <filesystem>
#include <iostream>
#include <direct.h>  
#include "ReadDICOMFile.h"
#include "WriteDicomToJpeg.h"
int main()
{
    const char* in_fname = "E:\\nitesh\\DICOM\\327.dcm";
    const char* out_fname = "E:\\nitesh\\DICOM\\327dcm.jpeg";

    ReadDICOMFile readDicomFile;
    readDicomFile.loadDicomAndReadTags(in_fname);

    std::cout << "PatientName" << " : " << readDicomFile.printTagNames[0] << std::endl;
    std::cout << "Modality" << " : " << readDicomFile.printTagNames[1] << std::endl;
    std::cout << "Image Height" << " : " << readDicomFile.printTagNames[2] << std::endl;
    std::cout << "Image Width" << " : " << readDicomFile.printTagNames[3] << std::endl;


    WriteDicomToJpeg writeDicomFile(in_fname, out_fname);
    writeDicomFile.saveDicomImageInJPEG();

    return getchar();
}