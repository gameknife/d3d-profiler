#ifndef xDirect3DVertexBuffer9_h__
#define xDirect3DVertexBuffer9_h__

#include "xd3d9.h"
#include "xDirect3DResourceBase.h"

class xDirect3DVertexBuffer9 : public IDirect3DVertexBuffer9, public xDirect3DResourceBase
{
public:
	xDirect3DVertexBuffer9(IDirect3DVertexBuffer9* realVB);
	~xDirect3DVertexBuffer9();

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

	virtual STDMETHODIMP GetDesc( THIS_ D3DVERTEXBUFFER_DESC *pDesc );

public:
	IDirect3DVertexBuffer9* m_vertexBuffer;

	uint32 m_memUsage;
	uint32 m_memUsageGPU;
};
#endif // xDirect3DVertexBuffer9_h__