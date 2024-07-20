#include <iostream>
#include <windows.h>

using namespace std;

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // �����ӽ���
    if (!CreateProcess(
        NULL,           // ��ִ��ģ�������
        "cmd /C dir",   // �����У�������ִ�� dir ����Ϊ����
        NULL,           // ���̰�ȫ����
        NULL,           // �̰߳�ȫ����
        FALSE,          // �̳о��
        0,              // ������־
        NULL,           // ʹ�ø����̵Ļ���
        NULL,           // ʹ�ø����̵ĵ�ǰĿ¼
        &si,            // ָ�� STARTUPINFO �ṹ���ָ��
        &pi             // ָ�� PROCESS_INFORMATION �ṹ���ָ��
    )) {
        cerr << "CreateProcess ʧ�� (" << GetLastError() << ")." << endl;
        return 1;
    }

    // �����̵ȴ��ӽ��̽���
    cout << "���������ڵȴ��ӽ��̽���..." << endl;
    WaitForSingleObject(pi.hProcess, INFINITE);

    // ��ȡ�ӽ��̵��˳���
    DWORD exit_code;
    if (!GetExitCodeProcess(pi.hProcess, &exit_code)) {
        cerr << "GetExitCodeProcess ʧ�� (" << GetLastError() << ")." << endl;
        return 1;
    }

    if (exit_code == STILL_ACTIVE) {
        cout << "�ӽ����������С�" << endl;
    }
    else {
        cout << "�ӽ�����������������ֵ: " << exit_code << endl;
    }

    // �رս��̺��߳̾��
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    cout << "�������˳�..." << endl;
    return 0;
}

