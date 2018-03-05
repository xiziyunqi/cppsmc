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

		//ע�⣬���ܺͼ��ܺ���Ҳ����Ҫ�ĺ����������������ĵ�����÷��ھ���CalcRegCode()��������
		//Զһ���λ�ã����ⱻ����
		DecryptBlock(pSecAddr,dwSecSize,0x5A);//���Ƚ��ܴ����

		CalcRegCode("system",szBuff,128);//����ע������㺯��
		
		EncryptBlock(pSecAddr,dwSecSize,0x5A);//���ú���ܴ����

		::MessageBox(NULL,szBuff,_T("OK"),MB_OK);
	}
	catch(const char *pszError)
	{
		//�������β����쳣
		::MessageBox(NULL,pszError,_T("Error"),MB_OK);
	}
	catch(...)
	{
		//���������쳣������Դ����޸Ļ���ܲ���ȷ��ɵ��쳣
		::MessageBox(NULL,_T("Unknown exception"),_T("Error"),MB_OK);
	}



	return 0;
}


