#include "stdafx.h"
#include "specfunc.h"

unsigned long slStartSignVar = 0;
unsigned long slEndSignVar = 0;

int CalcRegCode(const char *pszUserName, char *pCodeBuf, int nbufSize)
{
	if(!pszUserName || !pCodeBuf)
		return 0;

	slStartSignVar = 0x5A5A5A5A;//����鿪ʼ������������

	int nLength = strlen(pszUserName);
	if(nLength <= 0 || nLength >= nbufSize)
		return 0;

	if(::IsBadReadPtr(pszUserName,nLength) || ::IsBadWritePtr(pCodeBuf,nbufSize))
		return 0;

	for(int i = 0; i < nLength; i++)
		pCodeBuf[i] = pszUserName[i] + 1;//Ϊ����ʾ��������������λ�任

	pCodeBuf[nLength] = 0;

	slEndSignVar = 0x61616161;//��������������������

	return nLength;
}
