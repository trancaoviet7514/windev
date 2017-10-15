#pragma once
#include <Windows.h>
#include <CommCtrl.h>
#include <time.h>
#include "ListView.h"
#include <Shellapi.h>
#include "TreeView.h"
#include "Disk.h"
#pragma comment(lib,"comctl32.lib")

#define ID_HTREEVIEW   1000
#define ID_HLISTVIEW   1001
#define ID_BUTTON 1002

extern HINSTANCE hins;
extern HWND hWnd;
extern HICON icon;
extern HWND button;
extern LPWSTR stringname;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM MyRegisterClass(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
WCHAR* Convert(long long nSize);
WCHAR* ConvertDate(WIN32_FIND_DATA fd);
WCHAR* GetType(WIN32_FIND_DATA fd);
LPWSTR FindParentString(LPWSTR chid);

