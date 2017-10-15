#include "Library.h"

HWND hWnd;
HWND button;
HWND hstatic;
HINSTANCE hins;
Disk disk;
TreeView tv;
ListView lv;
LPWSTR stringname;
HICON icon;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	hins = hInstance;
	icon = ExtractIcon(hInstance, L"%SystemRoot%\\system32\\shell32.dll", 36 * 4 + 2);
	MyRegisterClass(hInstance);
	if (!InitInstance(hInstance, nCmdShow))
		return FALSE;
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT mes, WPARAM wparam, LPARAM lparam)
{

	NMHDR *nmh;
	int index;
	LVITEM lvi;
	LPNMTREEVIEW pnmtv;
	HTREEITEM htvitem;
	switch (mes)
	{
	case WM_NOTIFY:
		nmh = (LPNMHDR)lparam;
		switch (nmh->code)
		{
		case NM_DBLCLK:
			switch (nmh->idFrom)
			{
			case ID_HLISTVIEW:
				index = SendMessage(lv.GetHWND(), LVM_GETNEXTITEM, -1, LVNI_SELECTED);
				if (index == -1)
					break;
				lvi.iItem = index;
				ListView_GetItem(lv.GetHWND(), (LVITEM*)&lvi);
				stringname = (WCHAR*)lvi.lParam;
				lv.DoubleClickItem(stringname);
				break;
			}
			break;
		case TVN_ITEMEXPANDED:
			pnmtv = (LPNMTREEVIEW)lparam;
			tv.Impact(pnmtv->itemNew.hItem);
			break;
		case TVN_SELCHANGED:
			tv.Open();
			stringname = tv.getPatch(tv.getItemClicked());
			lv.DoubleClickItem(stringname);
			break;
		}
		break;
	case WM_COMMAND:
		if (LOWORD(wparam) == ID_BUTTON)
		{
			if (wcscmp(stringname, L"This PC")) {
				stringname = FindParentString(stringname);
			}
			lv.DoubleClickItem(stringname);
		}
		break;
	case WM_CREATE:

		InitCommonControls();
		disk.GetDiskFromSystem();
		stringname = L"This PC";

		tv.Create(hwnd);
		lv.Create(hwnd);

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, mes, wparam, lparam);
}
