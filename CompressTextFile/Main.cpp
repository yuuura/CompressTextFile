#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include "CompDecTxtFile.h"
using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		cerr << "Usage: " << argv[0] << " Source Destination -c		- To compress" << endl;
		cerr << "Usage: " << argv[0] << " Source Destination -d		- To Decompress" << endl;
		return 1;
	}
	
	CompressionFile compDecFile;

	if ((string)argv[3] == "-c" || (string)argv[3] == "-C")
	{
		if (compDecFile.CompressFile(argv[1], argv[2]))
			cout << "Compression completed successfuly!" << endl;
		else cout << "Error occured in compression process!" << endl;
	}
	else if ((string)argv[3] == "-d" || (string)argv[3] == "-D")
	{
		if(compDecFile.DecompressFile(argv[1], argv[2]))
			cout << "Decompression completed successfuly!" << endl;
		else cout << "Error occured in decompression process!" << endl;
	}
	return 0;
}