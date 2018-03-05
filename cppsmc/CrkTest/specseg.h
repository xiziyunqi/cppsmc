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
#ifndef __SPECSEG_H__
#define __SPECSEG_H__

int CalcRegCode(const char *pszUserName, char *pCodeBuf, int nbufSize);

#endif //__SPECSEG_H__