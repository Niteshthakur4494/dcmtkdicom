#pragma once

#include "gtest/gtest.h"
#include "..\ReadDicomFileLib\ReadDicomFile.h"

class ReadDicomFileUnitTestCase : public testing::Test
{
public:

    ReadDicomFileUnitTestCase() = default;
    ~ReadDicomFileUnitTestCase() override {}
    ReadDICOMFile readDicomFile;

private:
    ReadDicomFileUnitTestCase(const ReadDicomFileUnitTestCase&) = delete;
    const ReadDicomFileUnitTestCase& operator=(const ReadDicomFileUnitTestCase&) = delete;

};