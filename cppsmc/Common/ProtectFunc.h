/*********************************************************************************
*  Author         : orbit                                                        *
*  Description    : ����ļ�������һЩ���ݽṹ��Ϊ�˼��ܴ�����̶�ʵ�ֵ�һЩ���� *
*                   ����(For HttpAdmin Project)                                  *
*  Date           : March 8, 2005                                                *
*  Last-modified  : Sep 14, 2005                                                 *
*  Contact us     : inte2000@163.com,support@winmsg.com                          *
*  Web Page       : http://www.winmsg.com/cn/orbit.htm                           *
*                   http://blog.csdn.net/orbit/   (�����ļ�����)                 *
*********************************************************************************/
#ifndef __PROTECTFUNC_H__
#define __PROTECTFUNC_H__

#ifdef _WINDOWS
bool GetSectionPointer(void *pModuleBase,const char *lpszSection,void** ppPos,LPDWORD lpSize);
int VAtoFileOffset(void *pModuleBase,void *pVA);
#endif

int FindCodeTag(void *pStartAddr, unsigned long *pTagLoc, unsigned long lTagValue, int nSerachLength);
bool EncryptBlock(void *pStartAddr, int nLength, unsigned char cMask);
bool DecryptBlock(void *pStartAddr, int nLength, unsigned char cMask);

/*
#define DIB_HEADER_MARKER   ((WORD) ('M' << 8) | 'B')

bool GetDataFromBitmapEncapsulation(const void *pEncapsulation, void *pDataBuf, int nBufSize, int& nDataSize);
bool EncapsulationDataToBitmap(const void *pData, int nDataSize, void *pEncapsulation, int& nEncapsulationSize);
*/


#endif //__PROTECTFUNC_H__