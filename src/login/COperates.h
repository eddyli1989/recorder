//���ڽ�ֹ���������桢�������������ӿ����Զ�������һЩ����

#if !defined(AFX_EDITTEST_chinagfa_123456)
#define AFX_EDITTEST_chinagfa_123456

class COperates
{
public:
	

	COperates();

	void static DisableDesktop();//��ֹ�������

	void static EnableDesktop();//�����������

	void static DisableTaskMgr();//��ֹʹ�����������

	void static EnableTaskMgr();//����ʹ�����������

	void static AddAutoRun(LPSTR Pro);//���ض�·���µ�.exe������Ϊ�����Զ�������Proֵ�磺"D:\\TEST.exe"

	static void OpenRecorderControl();//��¼�ƿ��Ƴ���
};
#endif
