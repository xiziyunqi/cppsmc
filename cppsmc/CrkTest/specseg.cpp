/*********************************************************************************
*  Author         : orbit                                                        *
*  Description    : 这个文件声明演示了如何将一个函数放在一个独立的代码段中       *
*                                                                                *
*  Date           : June 2, 2006                                                 *
*  Last-modified  : June 2, 2006                                                 *
*  Contact us     : inte2000@163.com,support@winmsg.com                          *
*  Web Page       : http://www.winmsg.com/cn/orbit.htm                           *
*                   http://blog.csdn.net/orbit/   (关于文件更新)                 *
*********************************************************************************/
#include "stdafx.h"
#include "specseg.h"
		

#pragma code_seg(".scode")

int CalcRegCode(const char *pszUserName, char *pCodeBuf, int nbufSize)
{
	if(!pszUserName || !pCodeBuf)
		return 0;

	int nLength = strlen(pszUserName);
	if(nLength <= 0 || nLength >= nbufSize)
		return 0;

	if(::IsBadReadPtr(pszUserName,nLength) || ::IsBadWritePtr(pCodeBuf,nbufSize))
		return 0;

	for(int i = 0; i < nLength; i++)
		pCodeBuf[i] = pszUserName[i] + 1;//为了演示，仅仅是作个移位变换

	pCodeBuf[nLength] = 0;

	return nLength;
}

#pragma code_seg()
#pragma comment(linker, "/SECTION:.scode,ERW")