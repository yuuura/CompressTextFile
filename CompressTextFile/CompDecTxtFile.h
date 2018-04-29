#pragma once

#include <string>
using namespace std;

class CompressionFile
{
public:
	bool CompressFile(char* lpFileSrc, char* lpFileDest);
	bool DecompressFile(char* lpFileSrc, char* lpFileDest);
};