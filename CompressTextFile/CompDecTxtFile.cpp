#include "CompDecTxtFile.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <bitset>

#define ASCII_VALUE_a 97

bool CompressionFile::CompressFile(char* lpFileSrc, char* lpFileDest)
{
	//open file to write compressed data
	ofstream txtDestFile (lpFileDest);
	if (txtDestFile.is_open())
	{
		//open file to read data
		ifstream txtSrcFile(lpFileSrc);
		if (txtSrcFile.is_open())
		{
			int index = 7;
			char n = 0x0;
			bool flag = false;	// Empty file flag
			while (txtSrcFile)
			{
				char c;
				txtSrcFile.get(c);
				if (txtSrcFile)
					for (int i = 2; i >= 0; i--)
					{
						// Read offset where Ascii representation of char 'a' is the base
						if ((((bitset<8>((int)c - ASCII_VALUE_a)) >> i) &= 0x01) == 1)
							n |= 1 << index;
						if (--index < 0)
						{
							txtDestFile << n;
							index = 7;
							n &= 0x0;
							flag = true;
						}
					}
				else if (index != 7)
				{
					txtDestFile << n;
					txtDestFile << ++index;		//The last byte tell how much bits we NOT use in byte before last
				}
				else if (index == 7 && flag)
					txtDestFile << 0;
			}
			txtSrcFile.close();
		}
		else {
			cout << "Unable to open source file";
			return false;
		}
		txtDestFile.close();
	}
	else {
		cout << "Unable to open destination file";
		return false;
	}
	return true;
}

bool CompressionFile::DecompressFile(char* lpFileSrc, char* lpFileDest)
{
	//open file to write compressed data
	ofstream txtDestFile(lpFileDest);
	if (txtDestFile.is_open())
	{
		//open file to read data
		ifstream txtSrcFile(lpFileSrc);
		if (txtSrcFile.is_open())
		{
			// get length of file:
			txtSrcFile.seekg(0, txtSrcFile.end);
			int length = txtSrcFile.tellg();
			txtSrcFile.seekg(0, txtSrcFile.beg);

			int index = 2;
			char n = 0x0;
			while (length > 2)
			{
				char c;
				txtSrcFile.get(c);
				if (txtSrcFile)
				{
					for (int i = 7; i >= 0; i--)
					{
						if (((bitset<8>(c) >> i) &= 0x01) == 1)
							n |= 1 << index;
						if (--index < 0)
						{
							txtDestFile << (char)(ASCII_VALUE_a + (int)n);
							index = 2;
							n &= 0x0;
						}
					}
				}
				length--;
			}
			if(length == 2)
			{
				char c;
				int d;
				txtSrcFile.get(c);
				txtSrcFile >> d;
				for (int i = 7; i >= d; i--)
				{
					if (((bitset<8>(c) >> i) &= 0x01) == 1)
						n |= 1 << index;
					if (--index < 0)
					{
						index = 2;
						txtDestFile << (char)(ASCII_VALUE_a + (int)n); // Add base Ascii value ('a')
						n &= 0x0;
					}
				}
			}
			txtSrcFile.close();
		}
		else {
			cout << "Unable to open source file";
			return false;
		}
		txtDestFile.close();
	}
	else {
		cout << "Unable to open destination file";
		return false;
	}
	return true;
}