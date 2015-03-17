#include "xDirect3DSwapChain9.h"
#include "xVirtualApp.h"
#include "xAPICallMonitor.h"

xDirect3DSwapChain9::xDirect3DSwapChain9( IDirect3DSwapChain9* chain )
{
	m_swapchain = chain;
}

STDMETHODIMP xDirect3DSwapChain9::QueryInterface( THIS_ REFIID riid, void** ppvObj )
{
	STDMETHODIMP hr;
	hr = m_swapchain->QueryInterface(  riid, ppvObj );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DSwapChain9::Present( THIS_ CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion,DWORD dwFlags )
{
	FUNC_ENTER_TICK; STDMETHODIMP hr;

	g_vApp->OnUpdate();

	hr = m_swapchain->Present( pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion, dwFlags );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DSwapChain9::GetFrontBufferData( THIS_ IDirect3DSurface9* pDestSurface )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_swapchain->GetFrontBufferData(  pDestSurface );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DSwapChain9::GetBackBuffer( THIS_ UINT iBackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface9** ppBackBuffer )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_swapchain->GetBackBuffer(   iBackBuffer, Type, ppBackBuffer );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DSwapChain9::GetRasterStatus( THIS_ D3DRASTER_STATUS* pRasterStatus )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_swapchain->GetRasterStatus( pRasterStatus );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DSwapChain9::GetDisplayMode( THIS_ D3DDISPLAYMODE* pMode )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_swapchain->GetDisplayMode( pMode );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DSwapChain9::GetDevice( THIS_ IDirect3DDevice9** ppDevice )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_swapchain->GetDevice( ppDevice );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DSwapChain9::GetPresentParameters( THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_swapchain->GetPresentParameters( pPresentationParameters );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

ULONG xDirect3DSwapChain9::Release( THIS )
{
	ULONG hr;
	hr = m_swapchain->Release();
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

ULONG xDirect3DSwapChain9::AddRef( THIS )
{
	ULONG hr;
	hr = m_swapchain->AddRef();
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}
