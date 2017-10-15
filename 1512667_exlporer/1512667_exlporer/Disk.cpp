#include "Disk.h"


Drive::Drive()
{
	cung = new WCHAR[3];
	cung[0] = 0;
	cung[1] = L':';
	cung[2] = 0;
	free = 0;
	total = 0;
	Loai = new WCHAR[15];
}
void Drive::Add(WCHAR ten)
{
	cung[0] = ten;
	Type();
	Size();
}
Drive::~Drive()
{
	delete[] cung;
	delete[] Loai;
}
void Drive::Type()
{
	int kieu = GetDriveType(cung);
	switch (kieu)
	{
	case DRIVE_UNKNOWN:
	case DRIVE_NO_ROOT_DIR:
		wcscpy(Loai, L"Unknow");
		break;
	case DRIVE_REMOVABLE:
		wcscpy(Loai, L"Removable Disk");
		break;
	case DRIVE_FIXED:
		wcscpy(Loai, L"Local Disk");
		break;
	case DRIVE_REMOTE:
		wcscpy(Loai, L"Remote Drive");
		break;
	case DRIVE_CDROM:
		wcscpy(Loai, L"CD Drive");
		break;
	case DRIVE_RAMDISK:
		wcscpy(Loai, L"Ram Disk");
		break;
	}
}
void Drive::Size()
{
	WCHAR a[4];
	wsprintf(a, L"%s", cung);
	SHGetDiskFreeSpaceEx(a, NULL, (PULARGE_INTEGER)&total, (PULARGE_INTEGER)&free);
}
Disk::Disk()
{
	NumDisk = 0;
}
void Disk::GetDiskFromSystem()
{
	WCHAR str[26 * 4 + 1];
	GetLogicalDriveStrings(26 * 4 + 1, str);
	for (int i = 0; str[i] != 0; i = i + 4) {
		this->HardDisk[NumDisk++].Add(str[i]);
	}
}
Disk::~Disk()
{
}
