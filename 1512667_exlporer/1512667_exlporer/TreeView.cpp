#include "TreeView.h"


TreeView::TreeView()
{
}
TreeView::~TreeView()
{
}

void TreeView::Create(HWND parent)
{
	hTree = CreateWindow(WC_TREEVIEW, L"", WS_VISIBLE | WS_CHILD | WS_BORDER | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS, 0, 0, 200, 750, parent, (HMENU)ID_HTREEVIEW, hins, NULL);
	this->hil = ImageList_Create(16, 16, ILC_COLOR16 | ILC_MASK, 0, 0);
	ImageList_AddIcon(this->hil, ExtractIcon(hins, L"%SystemRoot%\\system32\\shell32.dll", 3));
	ImageList_AddIcon(this->hil, ExtractIcon(hins, L"%SystemRoot%\\system32\\shell32.dll", 68 * 4));
	SendMessage(hTree, TVM_SETIMAGELIST, 0, (LPARAM)hil);
	CreateThisPC();
	addDriveToPC();
}
void TreeView::ResizeWindow(int x, int y, int w, int h)
{
	MoveWindow(this->hTree, x, y, w, h, TRUE);
}
HWND TreeView::GetHWND()
{

	return hTree;
}
void TreeView::CreateThisPC()
{
	WCHAR *s = new WCHAR[8];
	wcscpy(s, L"This PC");
	TVINSERTSTRUCT tv;
	tv.hInsertAfter = TVI_FIRST;
	tv.item.cchTextMax = 8;
	tv.item.iImage = 1;
	tv.item.iSelectedImage = 1;
	tv.item.lParam = (LPARAM)s;
	tv.item.pszText = s;
	tv.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	tv.hParent = TVI_ROOT;
	pc = (HTREEITEM)SendMessage(hTree, TVM_INSERTITEM, 0, (LPARAM)&tv);
}

HTREEITEM TreeView::addItem(WCHAR *link, WCHAR* s, HTREEITEM cha)
{
	int icon = getImageIcon(link);
	TVINSERTSTRUCT tv;
	tv.hInsertAfter = cha;
	tv.item.cchTextMax = 255;
	tv.item.iImage = icon;
	tv.item.iSelectedImage = icon;
	tv.item.lParam = (LPARAM)link;
	tv.item.pszText = s;
	tv.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	tv.hParent = cha;
	return (HTREEITEM)SendMessage(this->hTree, TVM_INSERTITEM, 0, (LPARAM)&tv);
}
void TreeView::addDriveToPC()
{
	for (int i = 0; i < disk.NumDisk; i++)
	{
		HTREEITEM drive = addItem(disk.HardDisk[i].cung, disk.HardDisk[i].cung, pc);
		CheckFolderHaveChid(disk.HardDisk[i].cung, drive);
	}
}
void TreeView::LoadItemFromFolderToTree(WCHAR* parent, HTREEITEM cha)
{
	WIN32_FIND_DATA fd;
	WCHAR folder[MAX_PATH];
	wsprintf(folder, L"%s\\*.*", parent);
	HANDLE hFind = FindFirstFile(folder, &fd);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do {
			if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && (fd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) == false)
			{
				if (wcscmp(fd.cFileName, L".") && wcscmp(fd.cFileName, L".."))
				{
					WCHAR *child = new WCHAR[wcslen(parent) + wcslen(fd.cFileName) + 2];
					wsprintf(child, L"%s\\%s", parent, fd.cFileName);
					HTREEITEM con = addItem(child, fd.cFileName, cha);
					CheckFolderHaveChid(child, con);
				}
			}
		} while (FindNextFile(hFind, &fd));
		FindClose(hFind);
	}
}
bool TreeView::CheckFolderHaveChid(WCHAR *parent, HTREEITEM cha)
{
	WIN32_FIND_DATA fd;
	WCHAR folder[MAX_PATH];
	wsprintf(folder, L"%s\\*.*", parent);
	HANDLE hFind = FindFirstFile(folder, &fd);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do {
			if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && (fd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) == false)
			{
				if (wcscmp(fd.cFileName, L".") && wcscmp(fd.cFileName, L".."))
				{
					WCHAR *child = new WCHAR[8];
					wcscpy(child, L"ItemCon");
					addItem(child, fd.cFileName, cha);
					return true;
				}
			}
		} while (FindNextFile(hFind, &fd));
		FindClose(hFind);
	}
	return false;
}
WCHAR* TreeView::getPatch(HTREEITEM itemcanlay)
{
	TVITEMEX tv;
	tv.mask = TVIF_PARAM;
	tv.hItem = itemcanlay;
	TreeView_GetItem(this->hTree, &tv);
	return (WCHAR*)tv.lParam;
}
void TreeView::Impact(HTREEITEM itemnew)
{
	if (itemnew == this->pc)
		return;
	HTREEITEM con = TreeView_GetChild(this->hTree, itemnew);
	WCHAR *link = getPatch(con);
	if (!wcscmp(link, L"ItemCon"))
	{
		TreeView_DeleteItem(this->hTree, con);
		LoadItemFromFolderToTree(getPatch(itemnew), itemnew);
	}
}
void TreeView::Open()
{
	HTREEITEM h = this->getItemClicked();
	TreeView_Expand(this->hTree, h, TVE_EXPAND);
}
HTREEITEM TreeView::getItemClicked()
{
	return TreeView_GetNextItem(this->hTree, NULL, TVGN_CARET);
}
int TreeView::getImageIcon(WCHAR * link)
{
	WORD a = 0;
	int len = wcslen(link);
	if (len == 2)
		return ImageList_AddIcon(this->hil, ExtractAssociatedIconW(hins, link, &a));
	return 0;
}