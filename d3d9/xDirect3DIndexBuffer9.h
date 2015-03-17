#ifndef xDirect3DIndexBuffer9_h__
#define xDirect3DIndexBuffer9_h__

#include "xd3d9.h"
#include "xDirect3DResourceBase.h"

class xDirect3DIndexBuffer9 : public IDirect3DIndexBuffer9, public xDirect3DResourceBase
{
public:
	xDirect3DIndexBuffer9(IDirect3DIndexBuffer9* realIB);
	~xDirect3DIndexBuffer9() {}


	virtual STDMETHODIMP QueryInterface( THIS_ REFIID riid, void** ppvObj );

	virtual STDMETHODIMP_(ULONG) AddRef( THIS );

	virtual STDMETHODIMP_(ULONG) Release( THIS );

	virtual STDMETHODIMP GetDevice( THIS_ IDirect3DDevice9** ppDevice );

	virtual STDMETHODIMP SetPrivateData( THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags );

	virtual STDMETHODIMP GetPrivateData( THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData );

	virtual STDMETHODIMP FreePrivateData( THIS_ REFGUID refguid );

	virtual STDMETHODIMP_(DWORD) SetPriority( THIS_ DWORD PriorityNew );

	virtual STDMETHODIMP_(DWORD) GetPriority( THIS );

	virtual STDMETHODIMP_(void) PreLoad( THIS );

	virtual STDMETHODIMP_(D3DRESOURCETYPE) GetType( THIS );

	virtual STDMETHODIMP Lock( THIS_ UINT OffsetToLock,UINT SizeToLock,void** ppbData,DWORD Flags );

	virtual STDMETHODIMP Unlock( THIS );

	virtual STDMETHODIMP GetDesc( THIS_ D3DINDEXBUFFER_DESC *pDesc );

	IDirect3DIndexBuffer9* m_indexBuffer;

	uint32 m_memUsage;
	uint32 m_memUsageGPU;
};

#endif // xDirect3DIndexBuffer9_h__