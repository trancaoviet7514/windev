#pragma once
#include "Library.h"
class TreeView
{
	HWND hTree;
	HTREEITEM pc;
	HIMAGELIST hil;
public:
	friend class Disk;
	friend class List;
	friend class Driver;

	void LoadItemFromFolderToTree(WCHAR*, HTREEITEM);
	bool CheckFolderHaveChid(WCHAR *, HTREEITEM);
	void Create(HWND parent);
	void ResizeWindow(int, int, int, int);
	void CreateThisPC();
	void addDriveToPC();
	HTREEITEM addItem(WCHAR *, WCHAR*, HTREEITEM);
	HWND GetHWND();
	void Impact(HTREEITEM);
	WCHAR * getPatch(HTREEITEM);
	HTREEITEM getItemClicked();
	int getImageIcon(WCHAR*);
	void Open();
	~TreeView();
	TreeView();
};
extern TreeView tv;
