//关于禁止、允许桌面、任务管理器和添加开机自动启动的一些操作

#if !defined(AFX_EDITTEST_chinagfa_123456)
#define AFX_EDITTEST_chinagfa_123456

class COperates
{
public:
	

	COperates();

	void static DisableDesktop();//禁止桌面操作

	void static EnableDesktop();//允许桌面操作

	void static DisableTaskMgr();//禁止使用任务管理器

	void static EnableTaskMgr();//允许使用任务管理器

	void static AddAutoRun(LPSTR Pro);//将特定路径下的.exe程序设为开机自动启动，Pro值如："D:\\TEST.exe"

	static void OpenRecorderControl();//打开录制控制程序
};
#endif
