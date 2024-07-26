#pragma once

#include <iostream>
#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dcfilefo.h"
#include "dcmtk/dcmdata/dctk.h"

class ReadDICOMFile
{
public:
	void loadDicomAndReadTags(const char* fileName);
	const char* printTagNames[4];
private:
	int tagCount = 0;
	char* readTag(const char* tagName, const DcmTagKey& tagKey, DcmFileFormat& fileformat);
};

