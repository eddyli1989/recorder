#include<windows.h>
#include<stdio.h>
#include "CNoteFile.h"

CNoteFile::CNoteFile()
{
}

//��ĳ�������Ŀ�ʼʱ���¼��NoteFile�У�NoteFile���ڹ̶�·����
void CNoteFile::WriteOperationToNote(const char *Operation)
{
	SYSTEMTIME st;
	GetLocalTime(&st);//��ȡϵͳ��ǰʱ��
	char Time[20];
	if((st.wHour<10)&&(st.wMinute<10))
		sprintf(Time,"0%d:0%d",st.wHour,st.wMinute);//��ʽ��ϵͳʱ����Ϊ����
	if((st.wHour>10)&&(st.wMinute<10))
		sprintf(Time,"%d:0%d",st.wHour,st.wMinute);//��ʽ��ϵͳʱ����Ϊ����
	if((st.wHour<10)&&(st.wMinute>10))
		sprintf(Time,"0%d:%d",st.wHour,st.wMinute);//��ʽ��ϵͳʱ����Ϊ����
	if((st.wHour>10)&&(st.wMinute>10))
		sprintf(Time,"%d:%d",st.wHour,st.wMinute);//��ʽ��ϵͳʱ����Ϊ����
	::WritePrivateProfileString("����",Operation,Time,NoteFile_PATH);
}

//��StartNote����
void CNoteFile::OpenStartNote()
{
	HINSTANCE hRet = 0;
    hRet = ShellExecute(NULL, "open", StartNote_PATH, NULL, NULL, SW_SHOW);
    if((int)hRet <= 32)
    {
      MessageBox(NULL,"��StartNote����ʧ�ܣ�",NULL,MB_OK);
      PostQuitMessage(0);
    }
}

//��KeyNote����
void CNoteFile::OpenKeyNote()
{
	HINSTANCE hRet2 = 0;
	hRet2 = ShellExecute(NULL, "open", KeyNote_PATH, NULL, NULL, SW_SHOW);
	if((int)hRet2 <= 32)
	{
		MessageBox(NULL,"��KeyNote����ʧ�ܣ�",NULL,MB_OK);
		PostQuitMessage(0);	
	}
}

//��EndNote����
void CNoteFile::OpenEndNote()
{
	HINSTANCE hRet1 = 0;
    hRet1 = ShellExecute(NULL, "open", EndNote_PATH, NULL, NULL, SW_SHOW);
    if((int)hRet1 <= 32)
    {
      MessageBox(NULL,"��EndNote����ʧ�ܣ�",NULL,MB_OK);
      PostQuitMessage(0);
    }
}