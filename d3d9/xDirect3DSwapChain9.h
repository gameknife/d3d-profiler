#ifndef xDirect3DSwapChain9_h__
#define xDirect3DSwapChain9_h__

#include "xd3d9.h"

class xDirect3DSwapChain9 : public IDirect3DSwapChain9
{
public:
	xDirect3DSwapChain9(IDirect3DSwapChain9* chain);
	~xDirect3DSwapChain9(void) {}

	virtual STDMETHODIMP QueryInterface( THIS_ REFIID riid, void** ppvObj );

	virtual STDMETHODIMP_(ULONG) AddRef( THIS );

	virtual STDMETHODIMP_(ULONG) Release( THIS );

	virtual STDMETHODIMP Present( THIS_ CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion,DWORD dwFlags );

	virtual STDMETHODIMP GetFrontBufferData( THIS_ IDirect3DSurface9* pDestSurface );

	virtual STDMETHODIMP GetBackBuffer( THIS_ UINT iBackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface9** ppBackBuffer );

	virtual STDMETHODIMP GetRasterStatus( THIS_ D3DRASTER_STATUS* pRasterStatus );

	virtual STDMETHODIMP GetDisplayMode( THIS_ D3DDISPLAYMODE* pMode );

	virtual STDMETHODIMP GetDevice( THIS_ IDirect3DDevice9** ppDevice );

	virtual STDMETHODIMP GetPresentParameters( THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters );

public:
	IDirect3DSwapChain9* m_swapchain;

};

#endif // xDirect3DSwapChain9_h__