/*********************************************************************************
*  Author         : orbit                                                        *
*  Description    : 这个文件是加密工具软件CryptExe.exe的一部分，对于这个文件和   *
*                   CryptExe.exe工具可以自由使用，但是请保留最初的版权声明       *                                                             *
*  Date           : July 12, 2005                                                *
*  Last-modified  : July 12, 2005                                                *
*  Contact us     : inte2000@163.com,support@winmsg.com                          *
*  Web Page       : http://www.winmsg.com/cn/orbit.htm                           *
*                   http://blog.csdn.net/orbit/   (关于文件更新)                 *
*********************************************************************************/
#include "stdafx.h"
#include "ProtectFunc.h"

void ShowBanner()
{
	cout << endl;
	cout << "CryptExe - Encrypt the code block of executable file" << endl;
	cout << "Version 1.0 - Copyright (C) Orbit Studio 2005" << endl;
	cout << endl;
}

void ShowHelpMessage()
{
	cerr << "Usage:  " << endl;
	cerr << "  CryptExe <ExeFileName> <StartPosition> <BlockLength> [\"MatchCodeTag\"]" << endl;
	cerr << "\t ExeFileName   : Full file name of executable file" << endl;
	cerr << "\t StartPosition : The start offset position of code you want encrypt" << endl;
	cerr << "\t BlockLength   : Length of code block" << endl;
	cerr << "\t MatchCodeTag  : Not support this version" << endl;
	cerr << "\t help or ?     : Show this usage message" << endl;
	cerr << "Example: " << endl;
	cerr << "  CryptExe c:\\test\\crktest.exe 123800 128" << endl;
	cerr << endl;
}

int main(int argc, char* argv[])
{
	ShowBanner();

	if(argc < 4)
	{
		ShowHelpMessage();
		return 0;
	}

	unsigned long lfileOffset = 0;
	int nBlockLen = 0;
	string strFileName;
	fstream file;
	char *pBuf = NULL;

	try
	{
		strFileName = argv[1];
		istringstream strmOffset(argv[2]);
		strmOffset >> lfileOffset;

		istringstream strmLength(argv[3]);
		strmLength >> nBlockLen;

		pBuf = new char[nBlockLen];
		if(!pBuf)
		{
			throw string("Fail to allocate memory!");
		}

		file.open(strFileName.c_str(), ios_base::in | ios_base::out | ios_base::binary);
		if(!file)
		{
			delete[] pBuf;
			throw string("Fail to open file!");
		}

		file.seekg(0,ios_base::end);
		ios::pos_type size = file.tellp();
		if((lfileOffset + nBlockLen) > size)
		{
			file.close();
			delete[] pBuf;
			throw string("File size dismatch your offset position!");
		}

		file.seekg(lfileOffset,ios_base::beg);
		ios::pos_type mark = file.tellp();
		
		file.read(pBuf,nBlockLen);

		EncryptBlock(pBuf,nBlockLen,0x5A);

		file.seekp(mark);
		file.write(pBuf,nBlockLen);

		file.close();
		delete[] pBuf;
		cout << "File modified successfully!" << endl;
	}
	catch(exception& e)
	{
		cerr << "Exception : " << e.what() << endl;
	}
	catch(string& str)
	{
		cerr << "Exception : " << str << endl;
	}
	catch(...)
	{
		cerr << "Unknown Error !" << endl;
	}

	return 0;
}
