#include<windows.h>
#include<stdio.h>
#include "CNoteFile.h"

CNoteFile::CNoteFile()
{
}

//将某个动作的开始时间记录在NoteFile中，NoteFile放在固定路径中
void CNoteFile::WriteOperationToNote(const char *Operation)
{
	SYSTEMTIME st;
	GetLocalTime(&st);//获取系统当前时间
	char Time[20];
	if((st.wHour<10)&&(st.wMinute<10))
		sprintf(Time,"0%d:0%d",st.wHour,st.wMinute);//格式化系统时间作为键名
	if((st.wHour>10)&&(st.wMinute<10))
		sprintf(Time,"%d:0%d",st.wHour,st.wMinute);//格式化系统时间作为键名
	if((st.wHour<10)&&(st.wMinute>10))
		sprintf(Time,"0%d:%d",st.wHour,st.wMinute);//格式化系统时间作为键名
	if((st.wHour>10)&&(st.wMinute>10))
		sprintf(Time,"%d:%d",st.wHour,st.wMinute);//格式化系统时间作为键名
	::WritePrivateProfileString("动作",Operation,Time,NoteFile_PATH);
}

//打开StartNote程序
void CNoteFile::OpenStartNote()
{
	HINSTANCE hRet = 0;
    hRet = ShellExecute(NULL, "open", StartNote_PATH, NULL, NULL, SW_SHOW);
    if((int)hRet <= 32)
    {
      MessageBox(NULL,"打开StartNote程序失败！",NULL,MB_OK);
      PostQuitMessage(0);
    }
}

//打开KeyNote程序
void CNoteFile::OpenKeyNote()
{
	HINSTANCE hRet2 = 0;
	hRet2 = ShellExecute(NULL, "open", KeyNote_PATH, NULL, NULL, SW_SHOW);
	if((int)hRet2 <= 32)
	{
		MessageBox(NULL,"打开KeyNote程序失败！",NULL,MB_OK);
		PostQuitMessage(0);	
	}
}

//打开EndNote程序
void CNoteFile::OpenEndNote()
{
	HINSTANCE hRet1 = 0;
    hRet1 = ShellExecute(NULL, "open", EndNote_PATH, NULL, NULL, SW_SHOW);
    if((int)hRet1 <= 32)
    {
      MessageBox(NULL,"打开EndNote程序失败！",NULL,MB_OK);
      PostQuitMessage(0);
    }
}