#pragma once

#include "gtest/gtest.h"
#include "..\ReadDicomFileLib\WriteDicomToJpeg.h"

class WriteDicomToJpegUnitTestCase : public testing::Test
{
public:

    WriteDicomToJpegUnitTestCase() = default;
    ~WriteDicomToJpegUnitTestCase() override {}

private:
    WriteDicomToJpegUnitTestCase(const WriteDicomToJpegUnitTestCase&) = delete;
    const WriteDicomToJpegUnitTestCase& operator=(const WriteDicomToJpegUnitTestCase&) = delete;

};
