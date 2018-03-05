#include "stdafx.h"
#include "specfunc.h"
		

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

void CalcRegCodeEnd()
{
}