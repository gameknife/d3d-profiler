#include "xDirect3DCubeTexture9.h"
#include "xAPICallMonitor.h"
#include "xDirect3DSurface9.h"

xDirect3DCubeTexture9::xDirect3DCubeTexture9( IDirect3DCubeTexture9* cubemap ):xDirect3DResourceBase( eDRT_TextureCUBE, (res_index)this, (res_index)cubemap )
{
	m_cubeTexture = cubemap;
}

STDMETHODIMP xDirect3DCubeTexture9::QueryInterface( THIS_ REFIID riid, void** ppvObj )
{
	STDMETHODIMP hr;
	hr = m_cubeTexture->QueryInterface( riid, ppvObj );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DCubeTexture9::GetDevice( THIS_ IDirect3DDevice9** ppDevice )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_cubeTexture->GetDevice( ppDevice );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DCubeTexture9::SetPrivateData( THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_cubeTexture->SetPrivateData( refguid, pData, SizeOfData, Flags );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DCubeTexture9::GetPrivateData( THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_cubeTexture->GetPrivateData( refguid, pData, pSizeOfData );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DCubeTexture9::FreePrivateData( THIS_ REFGUID refguid )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_cubeTexture->FreePrivateData( refguid );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DCubeTexture9::SetAutoGenFilterType( THIS_ D3DTEXTUREFILTERTYPE FilterType )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_cubeTexture->SetAutoGenFilterType( FilterType );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DCubeTexture9::GetLevelDesc( THIS_ UINT Level,D3DSURFACE_DESC *pDesc )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_cubeTexture->GetLevelDesc( Level, pDesc );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DCubeTexture9::GetCubeMapSurface( THIS_ D3DCUBEMAP_FACES FaceType,UINT Level,IDirect3DSurface9** ppCubeMapSurface )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_cubeTexture->GetCubeMapSurface( FaceType, Level, ppCubeMapSurface );

	// create x surface if need [2/20/2013 YiKaiming]
// 	if (SUCCEEDED( hr ))
// 	{
// 		xDirect3DSurface9* mySurf = g_resourceManager.getXSurfaceMapping( (res_index)(*ppCubeMapSurface) );
// 		if (!mySurf)
// 		{
// 			mySurf = new xDirect3DSurface9( *ppCubeMapSurface );
// 		}
// 		*ppCubeMapSurface = mySurf;
// 	}


	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DCubeTexture9::LockRect( THIS_ D3DCUBEMAP_FACES FaceType,UINT Level,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags )
{
	// Lock还是放过屏蔽
	STDMETHODIMP hr;
	hr = m_cubeTexture->LockRect( FaceType, Level, pLockedRect, pRect, Flags );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DCubeTexture9::UnlockRect( THIS_ D3DCUBEMAP_FACES FaceType,UINT Level )
{
	STDMETHODIMP hr;
	hr = m_cubeTexture->UnlockRect( FaceType, Level );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DCubeTexture9::AddDirtyRect( THIS_ D3DCUBEMAP_FACES FaceType,CONST RECT* pDirtyRect )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_cubeTexture->AddDirtyRect( FaceType, pDirtyRect );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

void xDirect3DCubeTexture9::GenerateMipSubLevels()
{
	m_cubeTexture->GenerateMipSubLevels();
}

D3DTEXTUREFILTERTYPE xDirect3DCubeTexture9::GetAutoGenFilterType()
{
	D3DTEXTUREFILTERTYPE hr;
	hr = m_cubeTexture->GetAutoGenFilterType();
	return hr;
}

DWORD xDirect3DCubeTexture9::GetLevelCount()
{
	DWORD hr;
	hr = m_cubeTexture->GetLevelCount();
	return hr;
}

DWORD xDirect3DCubeTexture9::GetLOD()
{
	DWORD hr;
	hr = m_cubeTexture->GetLOD();
	return hr;
}

DWORD xDirect3DCubeTexture9::SetLOD( DWORD LODNew )
{
	DWORD hr;
	hr = m_cubeTexture->SetLOD( LODNew );
	return hr;
}

D3DRESOURCETYPE xDirect3DCubeTexture9::GetType()
{
	D3DRESOURCETYPE hr;
	hr = m_cubeTexture->GetType();
	return hr;
}

void xDirect3DCubeTexture9::PreLoad()
{
	m_cubeTexture->PreLoad();
}

DWORD xDirect3DCubeTexture9::GetPriority()
{
	DWORD hr;
	hr = m_cubeTexture->GetPriority();
	return hr;
}

DWORD xDirect3DCubeTexture9::SetPriority( DWORD PriorityNew )
{
	DWORD hr;
	hr = m_cubeTexture->SetPriority( PriorityNew );
	return hr;
}

ULONG xDirect3DCubeTexture9::Release()
{
	ULONG hr;
	hr = m_cubeTexture->Release();
	if (hr == 0)
	{
		// 可以调用xd3d内部的资源管理器来删除
		delete this;
	}
	return hr;
}

ULONG xDirect3DCubeTexture9::AddRef()
{
	ULONG hr;
	hr = m_cubeTexture->AddRef();
	return hr;
}

