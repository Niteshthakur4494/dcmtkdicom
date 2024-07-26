
#include "ReadDicomFileUnitTestCase.h"

TEST_F(ReadDicomFileUnitTestCase, ReadDicomTagsWhenFileLoadedSuccessfully) {
	const char* in_fname = "E:\\nitesh\\DICOM\\327.dcm";

	readDicomFile.loadDicomAndReadTags(in_fname);
	std::string patientName(readDicomFile.printTagNames[0]);
	std::string modality(readDicomFile.printTagNames[1]);
	std::string imgHeight(readDicomFile.printTagNames[2]);
	std::string imgWidth(readDicomFile.printTagNames[3]);

	EXPECT_EQ("BRUNER^HUEY", patientName);
	EXPECT_EQ("CT", modality);
	EXPECT_EQ("512", imgHeight);
	EXPECT_EQ("512", imgWidth);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}