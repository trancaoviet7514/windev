#pragma once
#include "Library.h"


class ListView
{
	HWND hList;
	bool Col;
	HIMAGELIST hil;
public:
	friend class Disk;
	friend class OCung;
	friend class TreeView;

	void Create(HWND parent);

	void AddItemToList(WCHAR*, WIN32_FIND_DATA);
	void ResizeWindow(int, int, int, int);
	void CreateColDrive();
	void LoadThisPCToList();
	void CreateColFolder();
	void LoadDiskToList(int);
	void showList(WCHAR*);
	void DoubleClickItem(WCHAR *);
	HWND GetHWND();
	int getImageIcon(WCHAR *);
	ListView();
	~ListView();
};
extern ListView lv;