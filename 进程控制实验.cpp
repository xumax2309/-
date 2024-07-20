#include <iostream>
#include <windows.h>

using namespace std;

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // 创建子进程
    if (!CreateProcess(
        NULL,           // 可执行模块的名称
        "cmd /C dir",   // 命令行（这里以执行 dir 命令为例）
        NULL,           // 进程安全属性
        NULL,           // 线程安全属性
        FALSE,          // 继承句柄
        0,              // 创建标志
        NULL,           // 使用父进程的环境
        NULL,           // 使用父进程的当前目录
        &si,            // 指向 STARTUPINFO 结构体的指针
        &pi             // 指向 PROCESS_INFORMATION 结构体的指针
    )) {
        cerr << "CreateProcess 失败 (" << GetLastError() << ")." << endl;
        return 1;
    }

    // 父进程等待子进程结束
    cout << "父进程正在等待子进程结束..." << endl;
    WaitForSingleObject(pi.hProcess, INFINITE);

    // 获取子进程的退出码
    DWORD exit_code;
    if (!GetExitCodeProcess(pi.hProcess, &exit_code)) {
        cerr << "GetExitCodeProcess 失败 (" << GetLastError() << ")." << endl;
        return 1;
    }

    if (exit_code == STILL_ACTIVE) {
        cout << "子进程仍在运行。" << endl;
    }
    else {
        cout << "子进程正常结束，返回值: " << exit_code << endl;
    }

    // 关闭进程和线程句柄
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    cout << "父进程退出..." << endl;
    return 0;
}

