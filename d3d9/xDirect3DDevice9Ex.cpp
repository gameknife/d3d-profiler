#include "xDirect3DDevice9Ex.h"
#include "xVirtualApp.h"
#include "xAPICallMonitor.h"


xDirect3DDevice9Ex::xDirect3DDevice9Ex( IDirect3DDevice9Ex* realDevice )
{
	m_deviceEx = realDevice;
	m_device = m_deviceEx;

	prevVB = NULL;
	prevIB = NULL;

	g_vApp->OnInit(this);
	g_vApp->OnReset(this);
}

STDMETHODIMP xDirect3DDevice9Ex::SetConvolutionMonoKernel( THIS_ UINT width,UINT height,float* rows,float* columns )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_deviceEx->SetConvolutionMonoKernel( width, height, rows, columns );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9Ex::ComposeRects( THIS_ IDirect3DSurface9* pSrc,IDirect3DSurface9* pDst,IDirect3DVertexBuffer9* pSrcRectDescs,UINT NumRects,IDirect3DVertexBuffer9* pDstRectDescs,D3DCOMPOSERECTSOP Operation,int Xoffset,int Yoffset )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_deviceEx->ComposeRects(   pSrc, pDst, pSrcRectDescs, NumRects, pDstRectDescs, Operation, Xoffset, Yoffset );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9Ex::PresentEx( THIS_ CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion,DWORD dwFlags )
{
	STDMETHODIMP hr;

	// should call virtualapp update here [2/20/2013 YiKaiming]
	if ( pSourceRect != NULL )
	{
		gEnv->width = pSourceRect->right - pSourceRect->left;
		gEnv->height = pSourceRect->bottom - pSourceRect->top;
	}

	g_vApp->OnUpdate();

	hr = m_deviceEx->PresentEx(  pSourceRect,  pDestRect, hDestWindowOverride,  pDirtyRegion, dwFlags );
	

	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9Ex::GetGPUThreadPriority( THIS_ INT* pPriority )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_deviceEx->GetGPUThreadPriority( pPriority );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9Ex::SetGPUThreadPriority( THIS_ INT Priority )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_deviceEx->SetGPUThreadPriority( Priority );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9Ex::WaitForVBlank( THIS_ UINT iSwapChain )
{
	STDMETHODIMP hr;
	hr = m_deviceEx->WaitForVBlank( iSwapChain );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9Ex::CheckResourceResidency( THIS_ IDirect3DResource9** pResourceArray,UINT32 NumResources )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_deviceEx->CheckResourceResidency( pResourceArray, NumResources );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9Ex::SetMaximumFrameLatency( THIS_ UINT MaxLatency )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_deviceEx->SetMaximumFrameLatency( MaxLatency );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9Ex::GetMaximumFrameLatency( THIS_ UINT* pMaxLatency )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_deviceEx->GetMaximumFrameLatency( pMaxLatency );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9Ex::CheckDeviceState( THIS_ HWND hDestinationWindow )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_deviceEx->CheckDeviceState( hDestinationWindow );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9Ex::CreateRenderTargetEx( THIS_ UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Lockable,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle,DWORD Usage )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_deviceEx->CreateRenderTargetEx( Width, Height, Format, MultiSample, MultisampleQuality, Lockable, ppSurface, pSharedHandle, Usage );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9Ex::CreateOffscreenPlainSurfaceEx( THIS_ UINT Width,UINT Height,D3DFORMAT Format,D3DPOOL Pool,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle,DWORD Usage )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_deviceEx->CreateOffscreenPlainSurfaceEx( Width, Height, Format, Pool, ppSurface, pSharedHandle, Usage );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9Ex::CreateDepthStencilSurfaceEx( THIS_ UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Discard,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle,DWORD Usage )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_deviceEx->CreateDepthStencilSurfaceEx( Width, Height, Format, MultiSample, MultisampleQuality, Discard, ppSurface, pSharedHandle, Usage );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9Ex::ResetEx( THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters,D3DDISPLAYMODEEX *pFullscreenDisplayMode )
{
	FUNC_ENTER; STDMETHODIMP hr;
	g_vApp->OnLost();

	//Sleep(50);

	hr = m_deviceEx->ResetEx( pPresentationParameters, pFullscreenDisplayMode );

	gEnv->width = pPresentationParameters->BackBufferWidth;
	gEnv->height = pPresentationParameters->BackBufferHeight;

	if ( SUCCEEDED(hr) )
	{
		g_vApp->OnReset( this );
	}	
		
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9Ex::GetDisplayModeEx( THIS_ UINT iSwapChain,D3DDISPLAYMODEEX* pMode,D3DDISPLAYROTATION* pRotation )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_deviceEx->GetDisplayModeEx( iSwapChain, pMode, pRotation );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}
