#if !defined(AFX_Recorder_CNoteFile_123456)
#define AFX_Recorder_CNoteFile_123456

#define NoteFile_PATH "../config/NoteFile.ini"
#define StartNote_PATH "../deps/StartNote.exe"			//StartNote����·��
#define EndNote_PATH "../deps/EndNote.exe"				//EndNote����·��
#define KeyNote_PATH "../deps/KeyNote.exe"				//KeyNote����·��

class CNoteFile
{
public:
	CNoteFile();

	//��ĳ�������Ŀ�ʼʱ���¼��NoteFile�У�NoteFile���ڹ̶�·����
	static void WriteOperationToNote(const char *Operation);

	//��StartNote����
	static void OpenStartNote();

	//��KeyNote����
	static void OpenKeyNote();

	//��EndNote����
	static void OpenEndNote();
};

#endif