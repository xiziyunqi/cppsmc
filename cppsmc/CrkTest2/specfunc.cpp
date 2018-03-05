#include "stdafx.h"
#include "specfunc.h"

unsigned long slStartSignVar = 0;
unsigned long slEndSignVar = 0;

int CalcRegCode(const char *pszUserName, char *pCodeBuf, int nbufSize)
{
	if(!pszUserName || !pCodeBuf)
		return 0;

	slStartSignVar = 0x5A5A5A5A;//代码块开始特征代码序列

	int nLength = strlen(pszUserName);
	if(nLength <= 0 || nLength >= nbufSize)
		return 0;

	if(::IsBadReadPtr(pszUserName,nLength) || ::IsBadWritePtr(pCodeBuf,nbufSize))
		return 0;

	for(int i = 0; i < nLength; i++)
		pCodeBuf[i] = pszUserName[i] + 1;//为了演示，仅仅是作个移位变换

	pCodeBuf[nLength] = 0;

	slEndSignVar = 0x61616161;//代码块结束特征代码序列

	return nLength;
}
