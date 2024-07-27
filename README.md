# DCMTK DICOM

================================
DCMTK DICOM TOOLKIT INSTALLATION
================================

PRE-REQUISITES
==============

Please download the official release of DICOM toolkit (DCMTK) version 3.6.7[https://dicom.offis.de/download/dcmtk/dcmtk367/] source. The DCMTK toolkit needs to be compiled with a C++ compiler. We recommend using the Microsoft Visual Studio 2019 C++ compiler.

To build and compile, download the CMake latest version and then run CMake, in this program we should establish the path of the source code and the path of the folder in which the project that we will use to install DCMTK will be generated. Next, click on the “Configure” button. This will prompt you to select the version of Visual Studio for which the project will be generated. Choose “Visual Studio 16 2019” if that is the version installed on your computer. Be sure to explicitly set the Optional platform for the generator field to x64; do not leave it empty.

This project builds with flag /MT or MTd.

The above process is for the same to build Google Test, please download the latest version.

