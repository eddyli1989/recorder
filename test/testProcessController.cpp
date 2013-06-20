#include"../src/recorder/ProcessController.h"
#include<stdio.h>
#include<vector>
#include<string>
using namespace std;

int main() {
    ProcessController controller;
    controller.FindProcess("QQ.exe");
    vector<string> list;
    list.push_back(string("QQ.exe"));
    list.push_back(string("GitHub.exe"));
    controller.FindProcessInList(list);
    return 0;
}
