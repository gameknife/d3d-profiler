/// SharedMem.cpp
#include <windows.h>
#include <tchar.h>
#include "sharedmem.h"
TSharedMem::TSharedMem(const TCHAR* Name, int Size)
{
	FHandle = CreateFileMapping((HANDLE)0xFFFFFFFF,
		NULL, PAGE_READWRITE, 0, Size, Name);
	if (FHandle != NULL) {
		FCreated = GetLastError() == 0;
		FFileView = (BYTE*)MapViewOfFile(FHandle,
			FILE_MAP_WRITE, 0, 0, Size);
		if (FFileView && FCreated)
			ZeroMemory(FFileView, Size);
	}
	else
		FFileView = NULL;
}
TSharedMem::~TSharedMem()
{
	if (FFileView) UnmapViewOfFile(FFileView);
	if (FHandle) CloseHandle(FHandle);
}
bool TSharedMem::IsUnique()
{
	return FCreated;
}
BYTE * TSharedMem::Buffer()
{
	return FFileView;
}