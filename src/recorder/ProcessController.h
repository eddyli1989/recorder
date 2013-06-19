/**
 *@auth shineli 
 *@date 2013-06-19
 *@ver 1.0
 *@desc win32 process control
 */

#include<windows.h>
class ProcessController  {

    public:
	BOOL FindProcess(TCHAR * szExeFile, UINT iLength);
}
