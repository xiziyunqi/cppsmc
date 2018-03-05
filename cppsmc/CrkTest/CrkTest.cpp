// CrkTest.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"

#include "specseg.h"
#include "ProtectFunc.h"

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	char szBuff[128];

	void *pSecAddr = NULL;
	DWORD dwSecSize = 0;
	HMODULE hImageBase = ::GetModuleHandle(NULL);

	try
	{
		bool bFind = GetSectionPointer((void *)hImageBase,".scode",&pSecAddr,&dwSecSize);
		if(!bFind || !pSecAddr)
			throw "Not find special section!";

		//注意，解密和加密函数也是重要的函数，这两个函数的调用最好放在距离CalcRegCode()函数调用
		//远一点的位置，避免被发现
		DecryptBlock(pSecAddr,dwSecSize,0x5A);//首先解密代码段

		CalcRegCode("system",szBuff,128);//调用注册码计算函数
		
		EncryptBlock(pSecAddr,dwSecSize,0x5A);//调用后加密代码段

		::MessageBox(NULL,szBuff,_T("OK"),MB_OK);
	}
	catch(const char *pszError)
	{
		//处理代码段查找异常
		::MessageBox(NULL,pszError,_T("Error"),MB_OK);
	}
	catch(...)
	{
		//处理其它异常，比如对代码修改或加密不正确造成的异常
		::MessageBox(NULL,_T("Unknown exception"),_T("Error"),MB_OK);
	}



	return 0;
}


