
#include "WriteDicomToJpegUnitTestCase.h"
#include "gtest/internal/gtest-filepath.h"

TEST_F(WriteDicomToJpegUnitTestCase, ReadDicomTagsWhenFileLoadedSuccessfully) {
	const char* in_fname = "E:\\nitesh\\DICOM\\327.dcm";
	const char* out_fname = "E:\\nitesh\\DICOM\\327dcm.jpeg";
	WriteDicomToJpeg writeDicomFile(in_fname, out_fname);
	writeDicomFile.saveDicomImageInJPEG();

	const std::string filename(out_fname);
	auto isExists = testing::internal::FilePath(filename);
	auto inValidFile = testing::internal::FilePath("3274dcm.jpeg");

	// Check if the file exists
	EXPECT_TRUE(isExists.FileOrDirectoryExists());

	// Check if the file does not exist
	EXPECT_FALSE(inValidFile.FileOrDirectoryExists());
}