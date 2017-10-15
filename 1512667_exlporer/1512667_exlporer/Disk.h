#pragma once
#include "Library.h"

extern Disk disk;
class Drive
{
	WCHAR *cung;
	long long total;
	long long  free;
	WCHAR* Loai;
public:

	friend class TreeView;
	friend class ListView;
	friend class Disk;
	Drive();
	~Drive();
	void Add(WCHAR);
	void Size();
	void Type();
};

class Disk
{

	int NumDisk;
	Drive HardDisk[26];

public:

	friend class ListView;
	friend class Drive;
	friend class TreeView;
	void GetDiskFromSystem();
	Disk();
	~Disk();
};