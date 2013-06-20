#include<fstream>
#include<ctime>
#include<cstdio>
#include<cstdlib>

#include<direct.h>
#include<io.h>
#include<windows.h>
#include<assert.h>
#include<tchar.h>

#define ACCESS _taccess
#define MKDIR(a) _tmkdir((a))
#define MAX_LOG_LENGTH 1024
#define LOG_DIR "../log/"

using namespace std;
int  mkdirs(TCHAR * pDir) {
    int i = 0;
    int iRet;
    int iLen;
    TCHAR* pszDir;

    if(NULL == pDir) {
        return -1;
    }

    pszDir = _tcsdup(pDir);
    iLen = _tcslen(pszDir);

    // 创建中间目录
    for (i = 0;i < iLen;i ++) {
        if (pszDir[i] == '\\' || pszDir[i] == '/') {
            pszDir[i] = '\0';

            //如果不存在,创建
            iRet = ACCESS(pszDir,0);
            if (iRet != 0) {
                iRet = MKDIR(pszDir);
                if (iRet != 0) {
                    return -1;
                }
            }
            //支持linux,将所有\换成/
            pszDir[i] = '/';
        }
    }

    iRet = MKDIR(pszDir);
    free(pszDir);
    return iRet;
}

void today(TCHAR * day, UINT iLength) {
    assert(iLength > 10);
    time_t tnow;
    struct tm* now;
    time(&tnow);   //取得当前日期
    now = localtime(&tnow);   //
    _sntprintf(day, iLength, _T("%04d-%02d-%02d"),  \
        1900+now->tm_year, now->tm_mon+1, now->tm_mday);
}

void hour(TCHAR * hour, UINT iLength) {
    assert(iLength > 12);
    time_t tnow;
    struct tm* now;
    time(&tnow);   //取得当前日期
    now = localtime(&tnow);   //
    _sntprintf(hour, iLength, _T("%04d-%02d-%02d-%02d"),  \
        1900+now->tm_year, now->tm_mon+1, now->tm_mday, now->tm_hour);
}

void now(TCHAR *_now, UINT iLength) {
    assert(iLength > 18);
    time_t tnow;
    struct tm* now;
    time(&tnow);   //取得当前日期
    now = localtime(&tnow);   //
    _sntprintf(_now, iLength, _T("%04d-%02d-%02d %02d:%02d:%02d"),  \
        1900+now->tm_year, now->tm_mon+1, now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec);
}

ofstream* ready4log() {
    TCHAR path[MAX_PATH] = {0};
    TCHAR _today[MAX_PATH] = {0};
    today(_today, MAX_PATH);
    _sntprintf(path, MAX_PATH-1, _T("%s%s"), LOG_DIR, _today);
    if (ACCESS(path,6) != 0) {
         if ( mkdirs(path) != 0 )
             return NULL;
    }

    TCHAR file[MAX_PATH] = {0};
    TCHAR _hour[MAX_PATH] = {0};

    hour(_hour, MAX_PATH);
    _sntprintf(file, MAX_PATH-1, _T("%s/%s.log"), path, _hour);

    static ofstream fh(file,ofstream::app);
    static TCHAR preFile[MAX_PATH] = { 0 };

    if (_tcslen(preFile) == 0) {
        _tcsncpy(preFile, file, MAX_PATH);
    }
   if (_tcscmp(preFile, file) != 0) {
        //上个文件名和这个文件名不相等
        fh<< _T("close handle for:") <<  preFile << endl;
        fh.close();
        fh.open(file);
    }
    return &fh;
}



void log_info(const TCHAR * fmt,...) {
    va_list ap;
    ofstream *fh = ready4log();
    if (fh == NULL)
        return;
    TCHAR _log[2 * MAX_LOG_LENGTH] = {0};
    TCHAR _now[MAX_PATH] = {0};
    now(_now, MAX_PATH);
    TCHAR msg[MAX_LOG_LENGTH] = { 0 }; 

    va_start(ap, fmt);
    _vsntprintf(msg, sizeof(msg), fmt, ap);
    va_end(ap);

    _sntprintf(_log, 2 * MAX_LOG_LENGTH, _T("[INFO]%s:%s"), _now, msg);
    (*fh) << _log << endl;
}

void log_error(const TCHAR * fmt, ...) {
    va_list ap;
    ofstream *fh = ready4log();
    if (fh == NULL)
        return;
    TCHAR _log[2 * MAX_LOG_LENGTH] = {0};
    TCHAR _now[MAX_PATH] = {0};
    now(_now, MAX_PATH);
    TCHAR msg[MAX_LOG_LENGTH] = { 0 }; 

    va_start(ap, fmt);
    _vsntprintf(msg, sizeof(msg), fmt, ap);
    va_end(ap);

    _sntprintf(_log, 2 * MAX_LOG_LENGTH, _T("[ERROR]%s:%s"), _now, msg);
    (*fh) << _log << endl;
}


