#include "ListView.h"



ListView::ListView()
{
	Col = true;
}
ListView::~ListView()
{
}

void ListView::Create(HWND parent)
{
	this->hList = CreateWindow(WC_LISTVIEW, L"ListView", WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_ICON, 200, 0, 650, 750, parent, (HMENU)ID_HLISTVIEW, hins, NULL);
	this->hil = ImageList_Create(32, 32, ILC_COLOR32 | ILC_MASK, 0, 0);
	ImageList_AddIcon(this->hil, ExtractIcon(hins, L"%SystemRoot%\\system32\\shell32.dll", 3));
	ListView_SetImageList(this->hList, this->hil, LVSIL_SMALL);
	this->CreateColDrive();
	this->LoadThisPCToList();
}
void ListView::CreateColFolder()
{
	LVCOLUMN cot;
	cot.cx = 250;
	cot.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_FMT;
	cot.fmt = LVCFMT_LEFT;
	cot.pszText = L"Name";
	ListView_InsertColumn(this->hList, 0, &cot);
	cot.cx = 170;
	cot.pszText = L"Date modified";
	ListView_InsertColumn(this->hList, 1, &cot);
	cot.cx = 120;
	cot.pszText = L"Type";
	ListView_InsertColumn(this->hList, 2, &cot);
	cot.cx = 100;
	cot.pszText = L"Size";
	ListView_InsertColumn(this->hList, 3, &cot);
}
void ListView::CreateColDrive()
{
	LVCOLUMN cot;
	cot.cx = 250;
	cot.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_FMT;
	cot.fmt = LVCFMT_LEFT;
	cot.pszText = L"Name";
	ListView_InsertColumn(this->hList, 0, &cot);
	cot.cx = 170;
	cot.pszText = L"Type";
	ListView_InsertColumn(this->hList, 1, &cot);
	cot.cx = 120;
	cot.pszText = L"Total Size";
	ListView_InsertColumn(this->hList, 2, &cot);
	cot.cx = 100;
	cot.pszText = L"Free Space";
	ListView_InsertColumn(this->hList, 3, &cot);
}
void ListView::ResizeWindow(int x, int y, int w, int h)
{
	MoveWindow(this->hList, x, y, w, h, TRUE);
}
HWND ListView::GetHWND()
{
	return hList;
}
void ListView::LoadDiskToList(int index)
{
	LVITEM m;
	m.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
	m.iSubItem = 0;
	m.pszText = disk.HardDisk[index].cung;
	m.iImage = getImageIcon(disk.HardDisk[index].cung);
	m.lParam = (LPARAM)disk.HardDisk[index].cung;
	m.cchTextMax = 2;
	m.iItem = index;
	ListView_InsertItem(this->hList, &m);
	ListView_SetItemText(this->hList, index, 1, disk.HardDisk[index].Loai);
	ListView_SetItemText(this->hList, index, 2, Convert(disk.HardDisk[index].total));
	ListView_SetItemText(this->hList, index, 3, Convert(disk.HardDisk[index].free));
}
void ListView::LoadThisPCToList()
{
	for (int i = 0; i < disk.NumDisk; i++)
		LoadDiskToList(i);
}
void ListView::showList(WCHAR *parent)
{

	if (Col == true)
	{
		Col = false;
		for (int i = 0; i < 4; i++)
			ListView_DeleteColumn(this->hList, 0);
		CreateColFolder();
	}
	WIN32_FIND_DATA fd;
	WCHAR folder[MAX_PATH];
	wsprintf(folder, L"%s\\*.*", parent);
	HANDLE hFind = FindFirstFile(folder, &fd);
	if (hFind == INVALID_HANDLE_VALUE)
		return;
	do
	{
		if (!(fd.dwFileAttributes&FILE_ATTRIBUTE_HIDDEN))
		{
			if (wcscmp(fd.cFileName, L".") && wcscmp(fd.cFileName, L".."))
			{
				WCHAR *child = new WCHAR[wcslen(parent) + wcslen(fd.cFileName) + 2];
				wsprintf(child, L"%s\\%s", parent, fd.cFileName);
				AddItemToList(child, fd);
			}
		}
	} while (FindNextFile(hFind, &fd));
	FindClose(hFind);
}

void ListView::AddItemToList(WCHAR* link, WIN32_FIND_DATA da)
{
	LVITEM m;
	m.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
	m.iSubItem = 0;
	m.pszText = da.cFileName;
	m.iImage = getImageIcon(link);
	m.lParam = (LPARAM)link;
	m.cchTextMax = 100;
	m.iItem = 0;
	ListView_InsertItem(this->hList, &m);
	ListView_SetItemText(hList, 0, 1, ConvertDate(da));
	ListView_SetItemText(hList, 0, 2, GetType(da));
	ListView_SetItemText(hList, 0, 3, Convert(da.nFileSizeLow));
}
void ListView::DoubleClickItem(WCHAR * link)
{
	if (!wcscmp(link, L"This PC"))
	{
		EnableWindow(button, FALSE);
		ListView_DeleteAllItems(this->hList);
		this->Col = true;
		for (int i = 0; i < 4; i++)
			ListView_DeleteColumn(this->hList, 0);
		CreateColDrive();
		LoadThisPCToList();
		return;
	}
	WIN32_FIND_DATA fd;
	GetFileAttributesEx(link, GetFileExInfoStandard, &fd);
	if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
	{
		if (IsWindowEnabled(button) == false)
			EnableWindow(button, TRUE);

		ListView_DeleteAllItems(this->hList);
		showList(link);
	}
	else
		ShellExecute(0, L"open", link, 0, 0, 1);
}
int ListView::getImageIcon(WCHAR * duongdan)
{

	WORD a = 0;
	int len = wcslen(duongdan);
	if (len == 2)
		return ImageList_AddIcon(hil, ExtractAssociatedIconW(hins, duongdan, &a));
	WCHAR * link = new WCHAR[1000];
	wcscpy(link, duongdan);
	link[len] = 0;
	int vt = wcsrchr(link, L'.') - link;
	if (vt < 0 || vt >= len)
		return 0;
	WCHAR *duoi = new WCHAR[len - vt + 1];
	for (int i = 0; i < len - vt; i++)
		duoi[i] = link[vt + i];
	duoi[len - vt] = 0;
	if (!wcsicmp(duoi, L".htm") || !wcsicmp(duoi, L".html"))
		return ImageList_AddIcon(hil, ExtractIcon(hins, L"%SystemRoot%\\system32\\shell32.dll", 55 * 4));
	return ImageList_AddIcon(hil, ExtractAssociatedIconW(hins, link, &a));

}