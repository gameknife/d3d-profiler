#include "xDirect3DDevice9.h"
#include "xDirect3DTexture9.h"
#include "xAPICallMonitor.h"
#include "xVirtualApp.h"
#include "xProfiler.h"
#include "timer.h"
#include "xDirect3DSwapChain9.h"
#include "xDirect3DVertexBuffer9.h"
#include "xDirect3DIndexBuffer9.h"
#include "xDirect3DVertexShader9.h"
#include "xDirect3DPixelShader9.h"
#include "xModel.h"
#include "xDirect3DVertexDeclaration9.h"
#include "xDirect3DCubeTexture9.h"
#include "xDirect3DSurface9.h"
#include "xDirect3DQuery9.h"
#include "xDirect3DVolume9.h"

STDMETHODIMP xDirect3DDevice9::QueryInterface( THIS_ REFIID riid, void** ppvObj )
{
	STDMETHODIMP hr;
	hr = m_device->QueryInterface( riid, ppvObj );
	/*CHECKCALL( hr, __FUNCTION__ );*/ return hr;
}

STDMETHODIMP xDirect3DDevice9::TestCooperativeLevel( THIS )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->TestCooperativeLevel();
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::EvictManagedResources( THIS )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->EvictManagedResources();
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::GetDirect3D( THIS_ IDirect3D9** ppD3D9 )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->GetDirect3D( ppD3D9 );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::GetDeviceCaps( THIS_ D3DCAPS9* pCaps )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->GetDeviceCaps( pCaps );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::GetDisplayMode( THIS_ UINT iSwapChain,D3DDISPLAYMODE* pMode )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->GetDisplayMode( iSwapChain, pMode );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::GetCreationParameters( THIS_ D3DDEVICE_CREATION_PARAMETERS *pParameters )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->GetCreationParameters( pParameters );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::SetCursorProperties( THIS_ UINT XHotSpot,UINT YHotSpot,IDirect3DSurface9* pCursorBitmap )
{
	FUNC_ENTER; STDMETHODIMP hr;
	IDirect3DSurface9* realSurf = g_resourceManager.getD3DSurfaceMapping( (res_index)pCursorBitmap );
	if (realSurf)
	{
		hr = m_device->SetCursorProperties( XHotSpot, YHotSpot, realSurf );
	}
	else
	{
		hr = m_device->SetCursorProperties( XHotSpot, YHotSpot, pCursorBitmap );
	}
	
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::CreateAdditionalSwapChain( THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DSwapChain9** pSwapChain )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->CreateAdditionalSwapChain(  pPresentationParameters, pSwapChain );

	xDirect3DSwapChain9* ourChain = new xDirect3DSwapChain9( *pSwapChain );
	*pSwapChain = ourChain;

	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::GetSwapChain( THIS_ UINT iSwapChain,IDirect3DSwapChain9** pSwapChain )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->GetSwapChain(   iSwapChain, pSwapChain );

	xDirect3DSwapChain9* ourChain = new xDirect3DSwapChain9( *pSwapChain );
	*pSwapChain = ourChain;

	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::Reset( THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters )
{
	FUNC_ENTER; STDMETHODIMP hr;

	g_vApp->OnLost();

	Sleep(50);

	hr = m_device->Reset( pPresentationParameters );

	gEnv->width = pPresentationParameters->BackBufferWidth;
	gEnv->height = pPresentationParameters->BackBufferHeight;

	if ( SUCCEEDED(hr) )
	{
		g_vApp->OnReset( this );
	}	

	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::Present( THIS_ CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion )
{
	FUNC_ENTER_TICK; STDMETHODIMP hr;

	if ( pSourceRect != NULL )
	{
		gEnv->width = pSourceRect->right - pSourceRect->left;
		gEnv->height = pSourceRect->bottom - pSourceRect->top;
	}

	g_vApp->OnUpdate();

	hr = m_device->Present(   pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion );

	memset( m_texUnit, 0, sizeof(m_texUnit));

	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::GetBackBuffer( THIS_ UINT iSwapChain,UINT iBackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface9** ppBackBuffer )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->GetBackBuffer(  iSwapChain, iBackBuffer, Type, ppBackBuffer );
	// 这里取出RT,有必要创建surface [2/20/2013 YiKaiming]
	// 不知道对于同一个surface, D3D RT会不会返回不同的内存地址？ 跟一下
	if ( SUCCEEDED(hr) && ppBackBuffer )
	{
		xDirect3DSurface9* mySurf = g_resourceManager.getXSurfaceMapping( (res_index)(*ppBackBuffer) );
		if (!mySurf)
		{
			mySurf = new xDirect3DSurface9( *ppBackBuffer );
		}
		*ppBackBuffer = mySurf;
	}



	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::GetRasterStatus( THIS_ UINT iSwapChain,D3DRASTER_STATUS* pRasterStatus )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->GetRasterStatus( iSwapChain, pRasterStatus );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::SetDialogBoxMode( THIS_ BOOL bEnableDialogs )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->SetDialogBoxMode( bEnableDialogs );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::CreateTexture( THIS_ UINT Width,UINT Height,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DTexture9** ppTexture,HANDLE* pSharedHandle )
{
	FUNC_ENTER; STDMETHODIMP hr;
	//IDirect3DTexture9* realTexture;
	hr = m_device->CreateTexture( Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle );
	if ( SUCCEEDED(hr) && ppTexture )
	{
		//realTexture->AddRef();
		xDirect3DTexture9* xTexture = new xDirect3DTexture9( *ppTexture );
		*ppTexture = xTexture;		
	}
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::CreateVolumeTexture( THIS_ UINT Width,UINT Height,UINT Depth,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DVolumeTexture9** ppVolumeTexture,HANDLE* pSharedHandle )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->CreateVolumeTexture(  Width, Height, Depth, Levels, Usage, Format, Pool, ppVolumeTexture, pSharedHandle );
	if ( SUCCEEDED(hr) && ppVolumeTexture )
	{
		xDirect3DVolumeTexture9* xTexture = new xDirect3DVolumeTexture9( *ppVolumeTexture );
		*ppVolumeTexture = xTexture;
	}

	
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::CreateCubeTexture( THIS_ UINT EdgeLength,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DCubeTexture9** ppCubeTexture,HANDLE* pSharedHandle )
{
	FUNC_ENTER; STDMETHODIMP hr;
	
	hr = m_device->CreateCubeTexture(  EdgeLength, Levels, Usage, Format, Pool, ppCubeTexture, pSharedHandle );
	if ( SUCCEEDED(hr) && ppCubeTexture )
	{
		xDirect3DCubeTexture9* xTexture = new xDirect3DCubeTexture9( *ppCubeTexture );
		*ppCubeTexture = xTexture;
	}

	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::CreateVertexBuffer( THIS_ UINT Length,DWORD Usage,DWORD FVF,D3DPOOL Pool,IDirect3DVertexBuffer9** ppVertexBuffer,HANDLE* pSharedHandle )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->CreateVertexBuffer(  Length, Usage, FVF, Pool, ppVertexBuffer, pSharedHandle );
	if ( SUCCEEDED(hr) && ppVertexBuffer )
	{
		xDirect3DVertexBuffer9* myVB = new xDirect3DVertexBuffer9( *ppVertexBuffer );
		*ppVertexBuffer = myVB;
	}
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::CreateIndexBuffer( THIS_ UINT Length,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DIndexBuffer9** ppIndexBuffer,HANDLE* pSharedHandle )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->CreateIndexBuffer(  Length, Usage, Format, Pool, ppIndexBuffer, pSharedHandle );
	if ( SUCCEEDED(hr) && ppIndexBuffer )
	{
		xDirect3DIndexBuffer9* myIB = new xDirect3DIndexBuffer9( *ppIndexBuffer );
		*ppIndexBuffer = myIB;
	}
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::CreateRenderTarget( THIS_ UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Lockable,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->CreateRenderTarget(  Width, Height, Format, MultiSample, MultisampleQuality, Lockable, ppSurface, pSharedHandle );
	// Create这里，也是，有必要创建SURFACE [2/20/2013 YiKaiming]
// 	if ( SUCCEEDED(hr) && ppSurface )
// 	{
// 		xDirect3DSurface9* mySurf = g_resourceManager.getXSurfaceMapping( (res_index)(*ppSurface) );
// 		if (!mySurf)
// 		{
// 			mySurf = new xDirect3DSurface9( *ppSurface );
// 		}
// 		*ppSurface = mySurf;
// 	}


	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::CreateDepthStencilSurface( THIS_ UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Discard,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->CreateDepthStencilSurface(   Width, Height, Format, MultiSample, MultisampleQuality, Discard, ppSurface, pSharedHandle );
	// Create这里，也是，有必要创建SURFACE [2/20/2013 YiKaiming]
// 	if ( SUCCEEDED(hr) && ppSurface )
// 	{
// 		xDirect3DSurface9* mySurf = g_resourceManager.getXSurfaceMapping( (res_index)(*ppSurface) );
// 		if (!mySurf)
// 		{
// 			mySurf = new xDirect3DSurface9( *ppSurface );
// 		}
// 		*ppSurface = mySurf;
// 	}
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::UpdateSurface(  IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestinationSurface,CONST POINT* pDestPoint )
{
	FUNC_ENTER; STDMETHODIMP hr;
	IDirect3DSurface9* src = pSourceSurface;
	IDirect3DSurface9* dst = pDestinationSurface;

	IDirect3DSurface9* realSrc = g_resourceManager.getD3DSurfaceMapping( (res_index)pSourceSurface );
	if ( realSrc )
	{
		src = realSrc;
	}
	IDirect3DSurface9* realDst = g_resourceManager.getD3DSurfaceMapping( (res_index)pDestinationSurface );
	if( realDst )
	{
		dst = realDst;
	}

	hr = m_device->UpdateSurface(  src, pSourceRect, dst, pDestPoint );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::UpdateTexture( THIS_ IDirect3DBaseTexture9* pSourceTexture,IDirect3DBaseTexture9* pDestinationTexture )
{
	FUNC_ENTER; STDMETHODIMP hr;
	// here important [2/7/2013 Kaiming]
	IDirect3DBaseTexture9* src = pSourceTexture;
	IDirect3DBaseTexture9* dst = pDestinationTexture;

	IDirect3DTexture9* realSrc = g_resourceManager.getD3DTexMapping( (res_index)pSourceTexture );
	if ( realSrc )
	{
		src = realSrc;
	}
	IDirect3DTexture9* realDst = g_resourceManager.getD3DTexMapping( (res_index)pDestinationTexture );
	if( realDst )
	{
		dst = realDst;
	}

	hr = m_device->UpdateTexture(   src, dst );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::GetRenderTargetData( THIS_ IDirect3DSurface9* pRenderTarget,IDirect3DSurface9* pDestSurface )
{
	FUNC_ENTER; STDMETHODIMP hr;

	// here important [2/7/2013 Kaiming]
	IDirect3DSurface9* src = pRenderTarget;
	IDirect3DSurface9* dst = pDestSurface;

	IDirect3DSurface9* realSrc = g_resourceManager.getD3DSurfaceMapping( (res_index)pRenderTarget );
	if ( realSrc )
	{
		src = realSrc;
	}
	IDirect3DSurface9* realDst = g_resourceManager.getD3DSurfaceMapping( (res_index)pDestSurface );
	if( realDst )
	{
		dst = realDst;
	}

	hr = m_device->GetRenderTargetData(   src, dst );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::GetFrontBufferData( THIS_ UINT iSwapChain,IDirect3DSurface9* pDestSurface )
{
	FUNC_ENTER; STDMETHODIMP hr;
	IDirect3DSurface9* mySurf = g_resourceManager.getD3DSurfaceMapping( (res_index)pDestSurface );
	if ( mySurf )
	{
		hr = m_device->GetFrontBufferData(  iSwapChain, mySurf );
	}
	else
	{
		hr = m_device->GetFrontBufferData(  iSwapChain, pDestSurface );
	}
	
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::StretchRect( THIS_ IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestSurface,CONST RECT* pDestRect,D3DTEXTUREFILTERTYPE Filter )
{
	FUNC_ENTER; STDMETHODIMP hr;
	// here important [2/7/2013 Kaiming]
	IDirect3DSurface9* src = pSourceSurface;
	IDirect3DSurface9* dst = pDestSurface;

	IDirect3DSurface9* realSrc = g_resourceManager.getD3DSurfaceMapping( (res_index)pSourceSurface );
	if ( realSrc )
	{
		src = realSrc;
	}
	IDirect3DSurface9* realDst = g_resourceManager.getD3DSurfaceMapping( (res_index)pDestSurface );
	if( realDst )
	{
		dst = realDst;
	}
	hr = m_device->StretchRect(  src,  pSourceRect, dst, pDestRect, Filter );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::ColorFill( THIS_ IDirect3DSurface9* pSurface,CONST RECT* pRect,D3DCOLOR color )
{
	FUNC_ENTER; STDMETHODIMP hr;
	IDirect3DSurface9* mySurf = g_resourceManager.getD3DSurfaceMapping( (res_index)pSurface );
	if ( mySurf )
	{
		hr = m_device->ColorFill(   mySurf,  pRect, color );
	}
	else
	{
		hr = m_device->ColorFill(   pSurface,  pRect, color );
	}	
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::CreateOffscreenPlainSurface( THIS_ UINT Width,UINT Height,D3DFORMAT Format,D3DPOOL Pool,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->CreateOffscreenPlainSurface(  Width, Height, Format, Pool, ppSurface, pSharedHandle );
	// Create这里，也是，有必要创建SURFACE [2/20/2013 YiKaiming]
// 	if ( SUCCEEDED(hr) && ppSurface )
// 	{
// 		xDirect3DSurface9* mySurf = g_resourceManager.getXSurfaceMapping( (res_index)(*ppSurface) );
// 		if (!mySurf)
// 		{
// 			mySurf = new xDirect3DSurface9( *ppSurface );
// 		}
// 		*ppSurface = mySurf;
// 	}
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::SetRenderTarget( THIS_ DWORD RenderTargetIndex,IDirect3DSurface9* pRenderTarget )
{
	FUNC_ENTER; STDMETHODIMP hr;
	// 如果在res_manager能找到，就用自己的 [2/20/2013 YiKaiming]
	IDirect3DSurface9* mySurf = g_resourceManager.getD3DSurfaceMapping( (res_index)pRenderTarget );
	if ( mySurf )
	{
		hr = m_device->SetRenderTarget( RenderTargetIndex, mySurf );
	}
	else
	{
		hr = m_device->SetRenderTarget( RenderTargetIndex, pRenderTarget );
	}
	
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::GetRenderTarget( THIS_ DWORD RenderTargetIndex,IDirect3DSurface9** ppRenderTarget )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->GetRenderTarget(  RenderTargetIndex, ppRenderTarget );

	// 这里是也需要创建, 先跟一下 [2/20/2013 YiKaiming]
	if ( SUCCEEDED(hr) && ppRenderTarget )
	{
		xDirect3DSurface9* mySurf = g_resourceManager.getXSurfaceMapping( (res_index)(*ppRenderTarget) );
		if (!mySurf)
		{
			mySurf = new xDirect3DSurface9( *ppRenderTarget );
		}
		*ppRenderTarget = mySurf;
	}

// 	xDirect3DSurface9* mySurf = g_resourceManager.getXSurfaceMapping( (res_index)(*ppRenderTarget) );
// 	if (mySurf)
// 	{
// 		*ppRenderTarget = mySurf;
// 	}

	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::SetDepthStencilSurface( THIS_ IDirect3DSurface9* pNewZStencil )
{
	FUNC_ENTER; STDMETHODIMP hr;

	IDirect3DSurface9* mySurf = g_resourceManager.getD3DSurfaceMapping( (res_index)pNewZStencil );
	if (mySurf)
	{
		hr = m_device->SetDepthStencilSurface(  mySurf );
	}
	else
	{
		hr = m_device->SetDepthStencilSurface(  pNewZStencil );
	}

	
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::GetDepthStencilSurface( THIS_ IDirect3DSurface9** ppZStencilSurface )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->GetDepthStencilSurface( ppZStencilSurface );

	// 这里是也需要创建, 先跟一下 [2/20/2013 YiKaiming]
	if ( SUCCEEDED(hr) && ppZStencilSurface )
	{
		xDirect3DSurface9* mySurf = g_resourceManager.getXSurfaceMapping( (res_index)(*ppZStencilSurface) );
		if (!mySurf)
		{
			mySurf = new xDirect3DSurface9( *ppZStencilSurface );
		}
		*ppZStencilSurface = mySurf;
	}

	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::BeginScene( THIS )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->BeginScene(  );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::EndScene( THIS )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->EndScene(  );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::Clear( THIS_ DWORD Count,CONST D3DRECT* pRects,DWORD Flags,D3DCOLOR Color,float Z,DWORD Stencil )
{
	FUNC_ENTER_TICK; STDMETHODIMP hr;
	hr = m_device->Clear(  Count,  pRects, Flags, Color, Z, Stencil );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::SetTransform( THIS_ D3DTRANSFORMSTATETYPE State,CONST D3DMATRIX* pMatrix )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->SetTransform(  State,  pMatrix );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::GetTransform( THIS_ D3DTRANSFORMSTATETYPE State,D3DMATRIX* pMatrix )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->GetTransform(  State, pMatrix );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::MultiplyTransform( THIS_ D3DTRANSFORMSTATETYPE State,CONST D3DMATRIX* pMatrix )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->MultiplyTransform(  State, pMatrix );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::SetViewport( THIS_ CONST D3DVIEWPORT9* pViewport )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->SetViewport(  pViewport );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::GetViewport( THIS_ D3DVIEWPORT9* pViewport )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->GetViewport( pViewport );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::SetMaterial( THIS_ CONST D3DMATERIAL9* pMaterial )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->SetMaterial(    pMaterial );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::GetMaterial( THIS_ D3DMATERIAL9* pMaterial )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->GetMaterial(   pMaterial );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::SetLight( THIS_ DWORD Index,CONST D3DLIGHT9* light )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->SetLight(   Index, light );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::GetLight( THIS_ DWORD Index,D3DLIGHT9* light)
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->GetLight(   Index, light);
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::LightEnable( THIS_ DWORD Index,BOOL Enable )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->LightEnable(   Index, Enable );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::GetLightEnable( THIS_ DWORD Index,BOOL* pEnable )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->GetLightEnable(   Index, pEnable );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::SetClipPlane( THIS_ DWORD Index,CONST float* pPlane )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->SetClipPlane(   Index,  pPlane );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::GetClipPlane( THIS_ DWORD Index,float* pPlane )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->GetClipPlane(   Index, pPlane );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::SetRenderState( THIS_ D3DRENDERSTATETYPE State,DWORD Value )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->SetRenderState(   State, Value );
	if (SUCCEEDED(hr))
	{
		g_profiler->setIncrement(ePe_StateChangeCount);
	}
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::GetRenderState( THIS_ D3DRENDERSTATETYPE State,DWORD* pValue )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->GetRenderState(   State, pValue );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::CreateStateBlock( THIS_ D3DSTATEBLOCKTYPE Type,IDirect3DStateBlock9** ppSB )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->CreateStateBlock(   Type, ppSB );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::BeginStateBlock( THIS )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->BeginStateBlock(  );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::EndStateBlock( THIS_ IDirect3DStateBlock9** ppSB )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->EndStateBlock(  ppSB );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::SetClipStatus( THIS_ CONST D3DCLIPSTATUS9* pClipStatus )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->SetClipStatus(   pClipStatus );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::GetClipStatus( THIS_ D3DCLIPSTATUS9* pClipStatus )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->GetClipStatus(   pClipStatus );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::GetTexture( THIS_ DWORD Stage,IDirect3DBaseTexture9** ppTexture )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->GetTexture(  Stage, ppTexture );

	xDirect3DTexture9* xres = g_resourceManager.getXTexMapping( (res_index)(*ppTexture) );
	if (xres)
	{
		*ppTexture = xres;
	}	

	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::SetTexture( THIS_ DWORD Stage,IDirect3DBaseTexture9* pTexture )
{
	FUNC_ENTER; STDMETHODIMP hr;

	if (Stage >= 0 && Stage <= 7)
	{
		m_texUnit[Stage] = (xDirect3DTexture9*)pTexture;
	}
	
	IDirect3DTexture9* d3dres = g_resourceManager.getD3DTexMapping((res_index)pTexture);
	if (d3dres)
	{
		hr = m_device->SetTexture( Stage, d3dres );
	}
	else
	{
		hr = m_device->SetTexture( Stage, pTexture );
	}
	
	if (SUCCEEDED(hr))
	{
		g_profiler->setIncrement(ePe_SetTextureCount);
	}

	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::GetTextureStageState( THIS_ DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD* pValue )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->GetTextureStageState(   Stage,Type, pValue );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::SetTextureStageState( THIS_ DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD Value )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->SetTextureStageState(   Stage, Type, Value );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::GetSamplerState( THIS_ DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD* pValue )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->GetSamplerState(   Sampler, Type, pValue );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::SetSamplerState( THIS_ DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD Value )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->SetSamplerState(   Sampler, Type, Value );
	if (SUCCEEDED(hr))
	{
		g_profiler->setIncrement(ePe_StateChangeCount);
	}
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::ValidateDevice( THIS_ DWORD* pNumPasses )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->ValidateDevice(   pNumPasses );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::SetPaletteEntries( THIS_ UINT PaletteNumber,CONST PALETTEENTRY* pEntries )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->SetPaletteEntries(   PaletteNumber,  pEntries );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::GetPaletteEntries( THIS_ UINT PaletteNumber,PALETTEENTRY* pEntries )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->GetPaletteEntries(   PaletteNumber, pEntries );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::SetCurrentTexturePalette( THIS_ UINT PaletteNumber )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->SetCurrentTexturePalette( PaletteNumber );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::GetCurrentTexturePalette( THIS_ UINT *PaletteNumber )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->GetCurrentTexturePalette( PaletteNumber );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::SetScissorRect( THIS_ CONST RECT* pRect )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->SetScissorRect( pRect );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::GetScissorRect( THIS_ RECT* pRect )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->GetScissorRect(  pRect );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::SetSoftwareVertexProcessing( THIS_ BOOL bSoftware )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->SetSoftwareVertexProcessing(  bSoftware );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::SetNPatchMode( THIS_ float nSegments )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->SetNPatchMode(  nSegments );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::DrawPrimitive( THIS_ D3DPRIMITIVETYPE PrimitiveType,UINT StartVertex,UINT PrimitiveCount )
{
	FUNC_ENTER; STDMETHODIMP hr;
	LONGLONG tickprev = g_timer->getRealTick();
	hr = m_device->DrawPrimitive(   PrimitiveType, StartVertex, PrimitiveCount );
	tickprev = g_timer->getRealTick() - tickprev;
	if( SUCCEEDED(hr) )
	{
		g_profiler->setIncrement(ePe_DPCount);
		g_profiler->setIncrement( ePe_DPTickCount, tickprev );
	}
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::DrawIndexedPrimitive( THIS_ D3DPRIMITIVETYPE PrimitiveType,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount )
{
	FUNC_ENTER; STDMETHODIMP hr;

	LONGLONG tickprev = g_timer->getRealTick();
	hr = m_device->DrawIndexedPrimitive( PrimitiveType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount );
	tickprev = g_timer->getRealTick() - tickprev;

	if( SUCCEEDED(hr) )
	{
		xModel model;
		model.vb = prevVB;
		model.ib = prevIB;
		model.decl = prevDecl;
		model.stride = prevStride;

		model.numVerts = NumVertices;
		model.primCount = primCount;

		switch( PrimitiveType )
		{
		case D3DPT_TRIANGLELIST:
			model.type = eMT_TriList;
			break;
		case D3DPT_TRIANGLESTRIP:
			model.type = eMT_TriSptrip;
			break;

		default:
			model.type = eMT_Count;

		}

		xModel& mdl = g_resourceManager.addModel( model );


		for (int i=0; i < 8; ++i)
		{
			mdl.SetTexUnit( i, m_texUnit[i] );
		}

		g_profiler->setIncrement(ePe_DIPCount);
		g_profiler->setIncrement( ePe_DPTickCount, tickprev );
	}
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::DrawPrimitiveUP( THIS_ D3DPRIMITIVETYPE PrimitiveType,UINT PrimitiveCount,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride )
{
	FUNC_ENTER; STDMETHODIMP hr;

	LONGLONG tickprev = g_timer->getRealTick();
	hr = m_device->DrawPrimitiveUP( PrimitiveType, PrimitiveCount,  pVertexStreamZeroData, VertexStreamZeroStride );
	tickprev = g_timer->getRealTick() - tickprev;

	if( SUCCEEDED(hr) )
	{
		g_profiler->setIncrement(ePe_DPUCount);
		g_profiler->setIncrement( ePe_DPTickCount, tickprev );
	}
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::DrawIndexedPrimitiveUP( THIS_ D3DPRIMITIVETYPE PrimitiveType,UINT MinVertexIndex,UINT NumVertices,UINT PrimitiveCount,CONST void* pIndexData,D3DFORMAT IndexDataFormat,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride )
{
	FUNC_ENTER; STDMETHODIMP hr;
	LONGLONG tickprev = g_timer->getRealTick();
	hr = m_device->DrawIndexedPrimitiveUP(   PrimitiveType, MinVertexIndex, NumVertices, PrimitiveCount,  pIndexData, IndexDataFormat,  pVertexStreamZeroData, VertexStreamZeroStride );
	tickprev = g_timer->getRealTick() - tickprev;

	if( SUCCEEDED(hr) )
	{
		g_profiler->setIncrement(ePe_DIPUCount);
		g_profiler->setIncrement( ePe_DPTickCount, tickprev );
	}
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::ProcessVertices( THIS_ UINT SrcStartIndex,UINT DestIndex,UINT VertexCount,IDirect3DVertexBuffer9* pDestBuffer,IDirect3DVertexDeclaration9* pVertexDecl,DWORD Flags )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->ProcessVertices(   SrcStartIndex, DestIndex, VertexCount, pDestBuffer, pVertexDecl, Flags );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::CreateVertexDeclaration( THIS_ CONST D3DVERTEXELEMENT9* pVertexElements,IDirect3DVertexDeclaration9** ppDecl )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->CreateVertexDeclaration( pVertexElements, ppDecl );

	xDirect3DVertexDeclaration9* decl = new xDirect3DVertexDeclaration9( *ppDecl );
	*ppDecl = decl;
	
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::SetVertexDeclaration( THIS_ IDirect3DVertexDeclaration9* pDecl )
{
	FUNC_ENTER; STDMETHODIMP hr;
	
	IDirect3DVertexDeclaration9* myDecl = g_resourceManager.getD3DVCMapping( (res_index)pDecl );
	if (myDecl)
	{
		prevDecl = (xDirect3DVertexDeclaration9*)pDecl;
		hr = m_device->SetVertexDeclaration(  myDecl );
	}
	else
	{
		hr = m_device->SetVertexDeclaration(  pDecl );
	}
	
	

	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::GetVertexDeclaration( THIS_ IDirect3DVertexDeclaration9** ppDecl )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->GetVertexDeclaration(  ppDecl );
	xDirect3DVertexDeclaration9* myDecl = g_resourceManager.getXVCMapping( (res_index)(*ppDecl) );
	if (myDecl)
	{
		*ppDecl = myDecl;
	}
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::SetFVF( THIS_ DWORD FVF )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->SetFVF(   FVF );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::GetFVF( THIS_ DWORD* pFVF )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->GetFVF(   pFVF );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::CreateVertexShader( THIS_ CONST DWORD* pFunction,IDirect3DVertexShader9** ppShader )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->CreateVertexShader(    pFunction, ppShader );

	if ( SUCCEEDED(hr) && ppShader)
	{
		xDirect3DVertexShader9* myVS = new xDirect3DVertexShader9( *ppShader );
		*ppShader = myVS;
	}

	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::SetVertexShader( THIS_ IDirect3DVertexShader9* pShader )
{
	FUNC_ENTER; STDMETHODIMP hr;
	IDirect3DVertexShader9* d3dshader = g_resourceManager.getD3DVSMapping( (res_index)pShader );
	if (d3dshader)
	{
		hr = m_device->SetVertexShader(  d3dshader );
	}
	else
	{
		hr = m_device->SetVertexShader(  pShader );
	}
	
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::GetVertexShader( THIS_ IDirect3DVertexShader9** ppShader )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->GetVertexShader(  ppShader );
	xDirect3DVertexShader9* xshader = g_resourceManager.getXVSMapping( (res_index)(*ppShader) );
	if (xshader)
	{
		*ppShader = xshader;
	}

	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::SetVertexShaderConstantF( THIS_ UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->SetVertexShaderConstantF(   StartRegister,  pConstantData, Vector4fCount );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::GetVertexShaderConstantF( THIS_ UINT StartRegister,float* pConstantData,UINT Vector4fCount )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->GetVertexShaderConstantF(   StartRegister, pConstantData, Vector4fCount );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::SetVertexShaderConstantI( THIS_ UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->SetVertexShaderConstantI(   StartRegister,  pConstantData, Vector4iCount );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::GetVertexShaderConstantI( THIS_ UINT StartRegister,int* pConstantData,UINT Vector4iCount )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->GetVertexShaderConstantI(   StartRegister, pConstantData, Vector4iCount );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::SetVertexShaderConstantB( THIS_ UINT StartRegister,CONST BOOL* pConstantData,UINT BoolCount )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->SetVertexShaderConstantB(   StartRegister,  pConstantData, BoolCount );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::GetVertexShaderConstantB( THIS_ UINT StartRegister,BOOL* pConstantData,UINT BoolCount )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->GetVertexShaderConstantB(   StartRegister, pConstantData, BoolCount );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::SetStreamSource( THIS_ UINT StreamNumber,IDirect3DVertexBuffer9* pStreamData,UINT OffsetInBytes,UINT Stride )
{
	FUNC_ENTER; STDMETHODIMP hr;
	
	IDirect3DVertexBuffer9* realVB = g_resourceManager.getD3DVBMapping( (res_index)pStreamData );
	if (realVB)
	{
		prevVB = (xDirect3DVertexBuffer9*)pStreamData;
		prevStride = Stride;
		hr = m_device->SetStreamSource(   StreamNumber, realVB, OffsetInBytes, Stride );
	}
	else
	{
		hr = m_device->SetStreamSource(   StreamNumber, pStreamData, OffsetInBytes, Stride );
	}


	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::GetStreamSource( THIS_ UINT StreamNumber,IDirect3DVertexBuffer9** ppStreamData,UINT* pOffsetInBytes,UINT* pStride )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->GetStreamSource(   StreamNumber, ppStreamData, pOffsetInBytes, pStride );

	xDirect3DVertexBuffer9* xres = g_resourceManager.getXVBMapping( (res_index)(*ppStreamData) );
	if (xres)
	{
		*ppStreamData = xres;
	}

	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::SetStreamSourceFreq( THIS_ UINT StreamNumber,UINT Setting )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->SetStreamSourceFreq(  StreamNumber, Setting );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::GetStreamSourceFreq( THIS_ UINT StreamNumber,UINT* pSetting )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->GetStreamSourceFreq(  StreamNumber, pSetting );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::SetIndices( THIS_ IDirect3DIndexBuffer9* pIndexData )
{
	FUNC_ENTER; STDMETHODIMP hr;

	xDirect3DIndexBuffer9* myIB = static_cast<xDirect3DIndexBuffer9*>(pIndexData);
	if (myIB)
	{
		prevIB = myIB;
		hr = m_device->SetIndices(  myIB->m_indexBuffer );
	}
	else
	{
		hr = m_device->SetIndices(  pIndexData );
	}	
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::GetIndices( THIS_ IDirect3DIndexBuffer9** ppIndexData )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->GetIndices(  ppIndexData );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::CreatePixelShader( THIS_ CONST DWORD* pFunction,IDirect3DPixelShader9** ppShader )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->CreatePixelShader(    pFunction, ppShader );

	if ( SUCCEEDED(hr) && ppShader)
	{
		xDirect3DPixelShader9* myPS = new xDirect3DPixelShader9( *ppShader );
		*ppShader = myPS;
	}

	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::SetPixelShader( THIS_ IDirect3DPixelShader9* pShader )
{
	FUNC_ENTER; STDMETHODIMP hr;

	IDirect3DPixelShader9* realPS = g_resourceManager.getD3DPSMapping( (res_index)pShader);
	if (realPS)
	{
		hr = m_device->SetPixelShader(  realPS );
	}
	else
	{
		hr = m_device->SetPixelShader(  pShader );
	}

	
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::GetPixelShader( THIS_ IDirect3DPixelShader9** ppShader )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->GetPixelShader(  ppShader );
	xDirect3DPixelShader9* myPS = g_resourceManager.getXPSMapping( (res_index)(*ppShader) );
	if (myPS)
	{
		*ppShader = myPS;
	}	

	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::SetPixelShaderConstantF( THIS_ UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->SetPixelShaderConstantF(   StartRegister,  pConstantData, Vector4fCount );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::GetPixelShaderConstantF( THIS_ UINT StartRegister,float* pConstantData,UINT Vector4fCount )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->GetPixelShaderConstantF(   StartRegister, pConstantData, Vector4fCount );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::SetPixelShaderConstantI( THIS_ UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->SetPixelShaderConstantI(   StartRegister,  pConstantData, Vector4iCount );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::GetPixelShaderConstantI( THIS_ UINT StartRegister,int* pConstantData,UINT Vector4iCount )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->GetPixelShaderConstantI(   StartRegister, pConstantData, Vector4iCount );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::SetPixelShaderConstantB( THIS_ UINT StartRegister,CONST BOOL* pConstantData,UINT BoolCount )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->SetPixelShaderConstantB(  StartRegister, pConstantData, BoolCount );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::GetPixelShaderConstantB( THIS_ UINT StartRegister,BOOL* pConstantData,UINT BoolCount )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->GetPixelShaderConstantB( StartRegister, pConstantData, BoolCount );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::DrawRectPatch( THIS_ UINT Handle,CONST float* pNumSegs,CONST D3DRECTPATCH_INFO* pRectPatchInfo )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->DrawRectPatch( Handle, pNumSegs, pRectPatchInfo );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::DrawTriPatch( THIS_ UINT Handle,CONST float* pNumSegs,CONST D3DTRIPATCH_INFO* pTriPatchInfo )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->DrawTriPatch(  Handle, pNumSegs,  pTriPatchInfo );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::DeletePatch( THIS_ UINT Handle )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->DeletePatch( Handle );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DDevice9::CreateQuery( THIS_ D3DQUERYTYPE Type,IDirect3DQuery9** ppQuery )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_device->CreateQuery( Type, ppQuery );

	if ( SUCCEEDED(hr) && ppQuery )
	{
		xDirect3DQuery9* myQuery = new xDirect3DQuery9( *ppQuery );
		*ppQuery = myQuery;
	}


	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

float xDirect3DDevice9::GetNPatchMode( THIS )
{
	float hr;
	hr = m_device->GetNPatchMode();
	return hr;
}

BOOL xDirect3DDevice9::GetSoftwareVertexProcessing ( THIS )
{
	BOOL hr;
	hr = m_device->GetSoftwareVertexProcessing();
	return hr;
}

void xDirect3DDevice9::GetGammaRamp( THIS_ UINT iSwapChain,D3DGAMMARAMP* pRamp )
{
	m_device->GetGammaRamp(iSwapChain, pRamp );
}

void xDirect3DDevice9::SetGammaRamp( THIS_ UINT iSwapChain,DWORD Flags,CONST D3DGAMMARAMP* pRamp )
{
	m_device->SetGammaRamp( iSwapChain, Flags, pRamp );
}

UINT xDirect3DDevice9::GetNumberOfSwapChains( THIS )
{
	UINT hr;
	hr = m_device->GetNumberOfSwapChains();
	return hr;
}

BOOL xDirect3DDevice9::ShowCursor( THIS_ BOOL bShow )
{
	BOOL hr;
	hr = m_device->ShowCursor( bShow );
	return hr;
}

void xDirect3DDevice9::SetCursorPosition( THIS_ int X,int Y,DWORD Flags )
{
	m_device->SetCursorPosition( X, Y, Flags );
}

UINT xDirect3DDevice9::GetAvailableTextureMem( THIS )
{
	UINT hr;
	hr = m_device->GetAvailableTextureMem();
	return hr;
}

ULONG xDirect3DDevice9::Release( THIS )
{
	ULONG hr;

	//g_vApp.OnLost();
	//g_vApp.OnDestroy();

	hr = m_device->Release();

	if (hr == 0)
	{
		delete this;
	}

	return hr;
}

ULONG xDirect3DDevice9::AddRef( THIS )
{
	ULONG hr;
	hr = m_device->AddRef( );
	return hr;
}

xDirect3DDevice9::xDirect3DDevice9( IDirect3DDevice9* realDevice )
{
	m_device = realDevice;

	prevVB = NULL;
	prevIB = NULL;

	g_vApp->OnInit(this);
	g_vApp->OnReset(this);

	memset( m_texUnit, 0, sizeof(m_texUnit));
}
