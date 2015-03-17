#ifndef xDirect3DSurface9_h__
#define xDirect3DSurface9_h__


#include "xd3d9.h"
#include "xDirect3DResourceBase.h"

class xDirect3DSurface9 : public IDirect3DSurface9, public xDirect3DResourceBase
{
public:

	xDirect3DSurface9(IDirect3DSurface9* surface);
	~xDirect3DSurface9() {}


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

	virtual STDMETHODIMP GetContainer( THIS_ REFIID riid,void** ppContainer );

	virtual STDMETHODIMP GetDesc( THIS_ D3DSURFACE_DESC *pDesc );

	virtual STDMETHODIMP LockRect( THIS_ D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags );

	virtual STDMETHODIMP UnlockRect( THIS );

	virtual STDMETHODIMP GetDC( THIS_ HDC *phdc );

	virtual STDMETHODIMP ReleaseDC( THIS_ HDC hdc );

	IDirect3DSurface9* m_surface;

};
#endif // xDirect3DSurface9_h__
