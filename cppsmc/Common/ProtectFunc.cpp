/*********************************************************************************
*  Author         : orbit                                                        *
*  Description    : ����ļ�������һЩ���ݽṹ��Ϊ�˼��ܴ�����̶�ʵ�ֵ�һЩ���� *
*                   ����                                                         *
*  Date           : March 8, 2005                                                *
*  Last-modified  : Sep 14, 2005                                                 *
*  Contact us     : inte2000@163.com,support@winmsg.com                          *
*  Web Page       : http://www.winmsg.com/cn/orbit.htm                           *
*                   http://blog.csdn.net/orbit/   (�����ļ�����)                 *
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
	//����DOSͷ����DOS stub���룬��λ��PE��־λ��
	DWORD Signature = *(DWORD *)(pszModuleBase + pDosHead->e_lfanew);
	if(Signature != IMAGE_NT_SIGNATURE) //"PE\0\0"
		return false;

	//��λ��PE header
	pPEHead = (IMAGE_FILE_HEADER *)(pszModuleBase + pDosHead->e_lfanew + sizeof(DWORD));
	int nSizeofOptionHeader;
	if(pPEHead->SizeOfOptionalHeader == 0)
		nSizeofOptionHeader = sizeof(IMAGE_OPTIONAL_HEADER);
	else
		nSizeofOptionHeader = pPEHead->SizeOfOptionalHeader;

	bool bFind = false;
	//����PE header��Option Header����λ��Section��λ��
	pSection = (IMAGE_SECTION_HEADER *)((unsigned char *)pPEHead + sizeof(IMAGE_FILE_HEADER) + nSizeofOptionHeader);
	for(int i = 0; i < pPEHead->NumberOfSections; i++)
	{
		if(!strncmp(szSecName, (const char*)pSection[i].Name,IMAGE_SIZEOF_SHORT_NAME)) //�Ƚ϶�����
		{
			*ppPos = (void *)(pszModuleBase + pSection[i].VirtualAddress);//����ʵ�����ַ
			*lpSize = pSection[i].SizeOfRawData;//���δ�С
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
	//����DOSͷ����DOS stub���룬��λ��PE��־λ��
	DWORD Signature = *(DWORD *)(pszModuleBase + pDosHead->e_lfanew);
	if(Signature != IMAGE_NT_SIGNATURE) //"PE\0\0"
		return -1;

	unsigned char *pszVA = (unsigned char *)pVA;
	int nFileOffset = -1;

	//��λ��PE header
	pPEHead = (IMAGE_FILE_HEADER *)(pszModuleBase + pDosHead->e_lfanew + sizeof(DWORD));
	int nSizeofOptionHeader;
	if(pPEHead->SizeOfOptionalHeader == 0)
		nSizeofOptionHeader = sizeof(IMAGE_OPTIONAL_HEADER);
	else
		nSizeofOptionHeader = pPEHead->SizeOfOptionalHeader;

	//����PE header��Option Header����λ��Section��λ��
	pSection = (IMAGE_SECTION_HEADER *)((unsigned char *)pPEHead + sizeof(IMAGE_FILE_HEADER) + nSizeofOptionHeader);
	for(int i = 0; i < pPEHead->NumberOfSections; i++)
	{
		if(!strncmp(".text", (const char*)pSection[i].Name,5)) //�Ƚ϶�����
		{
			//�����ļ�ƫ���� = �����ڴ������ַ - (������ڴ������ַ - ����ε��ļ�ƫ��)
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
		if((*pAddr == 0xC7) && (*(pAddr + 1) == 0x05))//����movָ��
		{
			unsigned long *Loc = (unsigned long *)((unsigned char*)pAddr + 2);
			if(*Loc == (unsigned long)pTagLoc)//�˴�������*Loc����ȫ�־�̬�����ĵ�ַ
			{
				unsigned long *Val = (unsigned long *)((unsigned char*)pAddr + 6);
				if(*Val == lTagValue)//�˴�������*Val���ǳ���lTagValueֵ
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

/*���м򵥵������ܣ�����Ϊ����ʾ*/
bool EncryptBlock(void *pStartAddr, int nLength, unsigned char cMask)
{
	return XorBlock(pStartAddr,nLength,cMask);
}

bool DecryptBlock(void *pStartAddr, int nLength, unsigned char cMask)
{
	return XorBlock(pStartAddr,nLength,cMask);
}
