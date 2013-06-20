/**
 *@auth shineli
 *@date 2013-06-19
 *@ver 1.0
 *@desc win32 process control
 */
#include<windows.h>
#include<vector>
#include<string>
using namespace std;

class ProcessController  {
    public:
      BOOL FindProcess(const TCHAR * szExeFile);
      BOOL FindProcessInList(vector<string> &list);
};
