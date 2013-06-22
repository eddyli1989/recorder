#if !defined(AFX_Recorder_CNoteFile_123456)
#define AFX_Recorder_CNoteFile_123456

#define NoteFile_PATH "../config/NoteFile.ini"
#define StartNote_PATH "../deps/StartNote.exe"			//StartNote程序路径
#define EndNote_PATH "../deps/EndNote.exe"				//EndNote程序路径
#define KeyNote_PATH "../deps/KeyNote.exe"				//KeyNote程序路径

class CNoteFile
{
public:
	CNoteFile();

	//将某个动作的开始时间记录在NoteFile中，NoteFile放在固定路径中
	static void WriteOperationToNote(const char *Operation);

	//打开StartNote程序
	static void OpenStartNote();

	//打开KeyNote程序
	static void OpenKeyNote();

	//打开EndNote程序
	static void OpenEndNote();
};

#endif