#ifndef SharedMem_h__
#define SharedMem_h__

/// SharedMem.h
class TSharedMem
{
private:
	bool FCreated;
	BYTE *FFileView;
	HANDLE FHandle;
public:
	TSharedMem(const TCHAR* Name, int Size);
	~TSharedMem();
	bool IsUnique();
	BYTE *Buffer();
};
/// end of SharedMem.h

#endif // SharedMem_h__