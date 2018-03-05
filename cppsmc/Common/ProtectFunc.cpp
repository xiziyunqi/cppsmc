/*********************************************************************************
*  Author         : orbit                                                        *
*  Description    : 这个文件声明了一些数据结构和为了加密传输过程而实现的一些处理 *
*                   函数                                                         *
*  Date           : March 8, 2005                                                *
*  Last-modified  : Sep 14, 2005                                                 *
*  Contact us     : inte2000@163.com,support@winmsg.com                          *
*  Web Page       : http://www.winmsg.com/cn/orbit.htm                           *
*                   http://blog.csdn.net/orbit/   (关于文件更新)                 *
*********************************************************************************/
#include "stdafx.h"
#include "ProtectFunc.h"

#ifdef _WINDOWS
bool GetSectionPointer(void *pModuleBase,const char *lpszSection,void** ppPos,LPDWORD lpSize)
{
	IMAGE_DOS_HEADER *pDosHead;
	IMAGE_FILE_HEADER *pPEHead;
	IMAGE_SECTION_HEADER *pSection;

	*ppPos = NULL;
	*lpSize = 0;

	if(::IsBadReadPtr(pModuleBase,sizeof(IMAGE_DOS_HEADER)) || ::IsBadReadPtr(lpszSection,8))
		return false;

	if(strlen(lpszSection) >= 16)
		return false;

	char szSecName[16];
	memset(szSecName,0,16);
	strncpy(szSecName,lpszSection,IMAGE_SIZEOF_SHORT_NAME);

	unsigned char *pszModuleBase = (unsigned char *)pModuleBase;
	pDosHead = (IMAGE_DOS_HEADER *)pszModuleBase;
	//跳过DOS头不和DOS stub代码，定位到PE标志位置
	DWORD Signature = *(DWORD *)(pszModuleBase + pDosHead->e_lfanew);
	if(Signature != IMAGE_NT_SIGNATURE) //"PE\0\0"
		return false;

	//定位到PE header
	pPEHead = (IMAGE_FILE_HEADER *)(pszModuleBase + pDosHead->e_lfanew + sizeof(DWORD));
	int nSizeofOptionHeader;
	if(pPEHead->SizeOfOptionalHeader == 0)
		nSizeofOptionHeader = sizeof(IMAGE_OPTIONAL_HEADER);
	else
		nSizeofOptionHeader = pPEHead->SizeOfOptionalHeader;

	bool bFind = false;
	//跳过PE header和Option Header，定位到Section表位置
	pSection = (IMAGE_SECTION_HEADER *)((unsigned char *)pPEHead + sizeof(IMAGE_FILE_HEADER) + nSizeofOptionHeader);
	for(int i = 0; i < pPEHead->NumberOfSections; i++)
	{
		if(!strncmp(szSecName, (const char*)pSection[i].Name,IMAGE_SIZEOF_SHORT_NAME)) //比较段名称
		{
			*ppPos = (void *)(pszModuleBase + pSection[i].VirtualAddress);//计算实际虚地址
			*lpSize = pSection[i].SizeOfRawData;//整段大小
			bFind = true;
			break;
		}
	}

	return bFind;
}

int VAtoFileOffset(void *pModuleBase,void *pVA)
{
	IMAGE_DOS_HEADER *pDosHead;
	IMAGE_FILE_HEADER *pPEHead;
	IMAGE_SECTION_HEADER *pSection;

	if(::IsBadReadPtr(pModuleBase,sizeof(IMAGE_DOS_HEADER)) || ::IsBadReadPtr(pVA,4))
		return -1;

	unsigned char *pszModuleBase = (unsigned char *)pModuleBase;
	pDosHead = (IMAGE_DOS_HEADER *)pszModuleBase;
	//跳过DOS头不和DOS stub代码，定位到PE标志位置
	DWORD Signature = *(DWORD *)(pszModuleBase + pDosHead->e_lfanew);
	if(Signature != IMAGE_NT_SIGNATURE) //"PE\0\0"
		return -1;

	unsigned char *pszVA = (unsigned char *)pVA;
	int nFileOffset = -1;

	//定位到PE header
	pPEHead = (IMAGE_FILE_HEADER *)(pszModuleBase + pDosHead->e_lfanew + sizeof(DWORD));
	int nSizeofOptionHeader;
	if(pPEHead->SizeOfOptionalHeader == 0)
		nSizeofOptionHeader = sizeof(IMAGE_OPTIONAL_HEADER);
	else
		nSizeofOptionHeader = pPEHead->SizeOfOptionalHeader;

	//跳过PE header和Option Header，定位到Section表位置
	pSection = (IMAGE_SECTION_HEADER *)((unsigned char *)pPEHead + sizeof(IMAGE_FILE_HEADER) + nSizeofOptionHeader);
	for(int i = 0; i < pPEHead->NumberOfSections; i++)
	{
		if(!strncmp(".text", (const char*)pSection[i].Name,5)) //比较段名称
		{
			//代码文件偏移量 = 代码内存虚拟地址 - (代码段内存虚拟地址 - 代码段的文件偏移)
			nFileOffset = pszVA - (pszModuleBase + pSection[i].VirtualAddress - pSection[i].PointerToRawData);
			break;
		}
	}

	return nFileOffset;
}

#endif

int FindCodeTag(void *pStartAddr, unsigned long *pTagLoc, unsigned long lTagValue, int nSerachLength)
{
	int nPos = -1;
	int i = 0;
	unsigned char *pAddr = (unsigned char *)pStartAddr;
	while(i < nSerachLength)
	{
		if((*pAddr == 0xC7) && (*(pAddr + 1) == 0x05))//查找mov指令
		{
			unsigned long *Loc = (unsigned long *)((unsigned char*)pAddr + 2);
			if(*Loc == (unsigned long)pTagLoc)//此处的数据*Loc就是全局静态变量的地址
			{
				unsigned long *Val = (unsigned long *)((unsigned char*)pAddr + 6);
				if(*Val == lTagValue)//此处的数据*Val就是常数lTagValue值
				{
					nPos = i;
					break;//find begin tag
				}
			}
		}
		pAddr++;
		i++;
	}

	return nPos;
}

static bool XorBlock(void *pStartAddr, int nLength, unsigned char cMask)
{
	if(!pStartAddr || nLength <= 0)
		return false;

	unsigned char *p = (unsigned char *)pStartAddr;
	for(int i = 0; i < nLength; i++)
	{
		*p++ ^= cMask;
	}

	return true;
}

/*进行简单的异或加密，仅仅为了演示*/
bool EncryptBlock(void *pStartAddr, int nLength, unsigned char cMask)
{
	return XorBlock(pStartAddr,nLength,cMask);
}

bool DecryptBlock(void *pStartAddr, int nLength, unsigned char cMask)
{
	return XorBlock(pStartAddr,nLength,cMask);
}
