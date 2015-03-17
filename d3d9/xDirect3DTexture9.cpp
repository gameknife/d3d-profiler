#include "xDirect3DTexture9.h"
#include "xAPICallMonitor.h"
#include "xDirect3DSurface9.h"
#include "xDirect3DResourceHelper.h"


xDirect3DTexture9::xDirect3DTexture9( IDirect3DTexture9* realTexture ):xDirect3DResourceBase(eDRT_Texture2D, (res_index)this, (res_index)realTexture)
{
	m_realTexture = realTexture;

	D3DSURFACE_DESC desc;
	m_realTexture->GetLevelDesc( 0, &desc );
	m_level = m_realTexture->GetLevelCount();
	m_width = desc.Width;
	m_height = desc.Height;
	m_pool = desc.Pool;
	m_format = desc.Format;

	// 这里可以计算一下内存占用 [2/20/2013 YiKaiming]
	uint32 memSizeOfLevel0 = m_width * m_height * BitsPerPixel( desc.Format ) / 8;
	if ( !(desc.Usage & D3DUSAGE_AUTOGENMIPMAP) && m_level > 1 )
	{
		uint32 memThisLevel = memSizeOfLevel0 / 4;
		while( memThisLevel > 0)
		{
			memSizeOfLevel0 += memThisLevel;
			memThisLevel = memThisLevel / 4;
		}
	}

	m_memUsage = memSizeOfLevel0;
	m_memUsageGPU = memSizeOfLevel0;

	switch( m_pool )
	{
	case D3DPOOL_DEFAULT:
		m_memUsage = 0;
		break;
	case D3DPOOL_SYSTEMMEM:
	case D3DPOOL_SCRATCH:
		m_memUsageGPU = 0;
		break;
	}

	m_rt = false;
	if (desc.Usage & D3DUSAGE_DEPTHSTENCIL || desc.Usage & D3DUSAGE_RENDERTARGET)
	{
		m_rt = true;
	}

	g_resourceManager.reCalcMemUsage();
}

xDirect3DTexture9::~xDirect3DTexture9()
{
}


STDMETHODIMP xDirect3DTexture9::QueryInterface( THIS_ REFIID riid, void** ppvObj )
{
	STDMETHODIMP hr;
	hr = m_realTexture->QueryInterface( riid, ppvObj );
	CHECKCALL(hr, __FUNCTION__);
	return hr;
}

STDMETHODIMP xDirect3DTexture9::GetDevice( THIS_ IDirect3DDevice9** ppDevice )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_realTexture->GetDevice(   ppDevice );
	CHECKCALL(hr, __FUNCTION__);
	return hr;
}

STDMETHODIMP xDirect3DTexture9::SetPrivateData( THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_realTexture->SetPrivateData(   refguid, pData, SizeOfData, Flags );
	CHECKCALL(hr, __FUNCTION__);
	return hr;
}

STDMETHODIMP xDirect3DTexture9::GetPrivateData( THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_realTexture->GetPrivateData(   refguid, pData, pSizeOfData );
	CHECKCALL(hr, __FUNCTION__);
	return hr;
}

STDMETHODIMP xDirect3DTexture9::FreePrivateData( THIS_ REFGUID refguid )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_realTexture->FreePrivateData(  refguid );
	CHECKCALL(hr, __FUNCTION__);
	return hr;
}

STDMETHODIMP xDirect3DTexture9::SetAutoGenFilterType( THIS_ D3DTEXTUREFILTERTYPE FilterType )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_realTexture->SetAutoGenFilterType(   FilterType );
	CHECKCALL(hr, __FUNCTION__);
	return hr;
}

STDMETHODIMP xDirect3DTexture9::GetLevelDesc( THIS_ UINT Level,D3DSURFACE_DESC *pDesc )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_realTexture->GetLevelDesc(   Level, pDesc );
	CHECKCALL(hr, __FUNCTION__);
	return hr;
}

STDMETHODIMP xDirect3DTexture9::GetSurfaceLevel( THIS_ UINT Level,IDirect3DSurface9** ppSurfaceLevel )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_realTexture->GetSurfaceLevel(   Level, ppSurfaceLevel );

// 	if (SUCCEEDED( hr ) && ppSurfaceLevel)
// 	{
// 		// create x surface if need [2/20/2013 YiKaiming]
// 		xDirect3DSurface9* mySurf = g_resourceManager.getXSurfaceMapping( (res_index)(*ppSurfaceLevel) );
// 		if (!mySurf)
// 		{
// 			mySurf = new xDirect3DSurface9( *ppSurfaceLevel );
// 		}
// 		*ppSurfaceLevel = mySurf;
// 	}

	CHECKCALL(hr, __FUNCTION__);
	return hr;
}

STDMETHODIMP xDirect3DTexture9::LockRect( THIS_ UINT Level,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags )
{
	FUNC_ENTER_TICK; STDMETHODIMP hr;
	hr = m_realTexture->LockRect(   Level, pLockedRect,  pRect, Flags );
	CHECKCALL(hr, __FUNCTION__);
	return hr;
}

STDMETHODIMP xDirect3DTexture9::UnlockRect( THIS_ UINT Level )
{
	FUNC_ENTER_TICK; STDMETHODIMP hr;
	hr = m_realTexture->UnlockRect(   Level );
	CHECKCALL(hr, __FUNCTION__);
	return hr;
}

STDMETHODIMP xDirect3DTexture9::AddDirtyRect( THIS_ CONST RECT* pDirtyRect )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_realTexture->AddDirtyRect(    pDirtyRect );
	CHECKCALL(hr, __FUNCTION__);
	return hr;
}

void xDirect3DTexture9::GenerateMipSubLevels ( THIS )
{
	m_realTexture->GenerateMipSubLevels();
}

D3DTEXTUREFILTERTYPE xDirect3DTexture9::GetAutoGenFilterType( THIS )
{
	D3DTEXTUREFILTERTYPE hr;
	hr = m_realTexture->GetAutoGenFilterType();
	return hr;
}

DWORD xDirect3DTexture9::GetLevelCount( THIS )
{
	DWORD hr;
	hr = m_realTexture->GetLevelCount();
	return hr;
}

DWORD xDirect3DTexture9::GetLOD( THIS )
{
	DWORD hr;
	hr = m_realTexture->GetLOD( );
	return hr;
}

DWORD xDirect3DTexture9::SetLOD( THIS_ DWORD LODNew )
{
	DWORD hr;
	hr = m_realTexture->SetLOD( LODNew );
	return hr;
}

D3DRESOURCETYPE xDirect3DTexture9::GetType( THIS )
{
	D3DRESOURCETYPE hr;
	hr = m_realTexture->GetType();
	return hr;
}

void xDirect3DTexture9::PreLoad( THIS )
{
	m_realTexture->PreLoad( );
}

DWORD xDirect3DTexture9::GetPriority( THIS )
{
	DWORD hr;
	hr = m_realTexture->GetPriority( );
	return hr;
}

DWORD xDirect3DTexture9::SetPriority( THIS_ DWORD PriorityNew )
{
	DWORD hr;
	hr = m_realTexture->SetPriority( PriorityNew );
	return hr;
}

ULONG xDirect3DTexture9::Release( THIS )
{
	ULONG hr;
	hr = m_realTexture->Release();
	if (hr == 0)
	{
		// 可以调用xd3d内部的资源管理器来删除
		delete this;
		g_resourceManager.reCalcMemUsage();
	}
	return hr;
}

ULONG xDirect3DTexture9::AddRef( THIS )
{
	ULONG hr;
	hr = m_realTexture->AddRef();
	return hr;
}

