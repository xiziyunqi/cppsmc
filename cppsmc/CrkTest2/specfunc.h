#ifndef __SPECFUNC_H__
#define __SPECFUNC_H__

const int nMovCodeLength = 10;

extern unsigned long slStartSignVar;
extern unsigned long slEndSignVar;

int CalcRegCode(const char *pszUserName, char *pCodeBuf, int nbufSize);

#endif //__SPECFUNC_H__