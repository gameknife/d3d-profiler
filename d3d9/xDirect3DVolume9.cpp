#include "xDirect3DVolume9.h"
#include "xAPICallMonitor.h"


xDirect3DVolume9::xDirect3DVolume9( IDirect3DVolume9* volume ) : xDirect3DResourceBase( eDRT_Volume, (res_index)this, (res_index)volume )
{
	m_volume = volume;
}

STDMETHODIMP xDirect3DVolume9::QueryInterface( THIS_ REFIID riid, void** ppvObj )
{
	STDMETHODIMP hr;
	hr = m_volume->QueryInterface( riid, ppvObj );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DVolume9::GetDevice( THIS_ IDirect3DDevice9** ppDevice )
{
	STDMETHODIMP hr;
	hr = m_volume->GetDevice( ppDevice );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DVolume9::SetPrivateData( THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags )
{
	STDMETHODIMP hr;
	hr = m_volume->SetPrivateData( refguid, pData, SizeOfData, Flags );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DVolume9::GetPrivateData( THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData )
{
	STDMETHODIMP hr;
	hr = m_volume->GetPrivateData( refguid, pData, pSizeOfData );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DVolume9::FreePrivateData( THIS_ REFGUID refguid )
{
	STDMETHODIMP hr;
	hr = m_volume->FreePrivateData( refguid );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DVolume9::GetContainer( THIS_ REFIID riid,void** ppContainer )
{
	STDMETHODIMP hr;
	hr = m_volume->GetContainer(  riid, ppContainer );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DVolume9::GetDesc( THIS_ D3DVOLUME_DESC *pDesc )
{
	STDMETHODIMP hr;
	hr = m_volume->GetDesc( pDesc );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DVolume9::LockBox( THIS_ D3DLOCKED_BOX * pLockedVolume,CONST D3DBOX* pBox,DWORD Flags )
{
	STDMETHODIMP hr;
	hr = m_volume->LockBox( pLockedVolume, pBox, Flags );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DVolume9::UnlockBox( THIS )
{
	STDMETHODIMP hr;
	hr = m_volume->UnlockBox( );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

ULONG xDirect3DVolume9::Release()
{
	ULONG hr;
	hr = m_volume->Release( );
	return hr;
}

ULONG xDirect3DVolume9::AddRef()
{
	ULONG hr;
	hr = m_volume->AddRef();
	return hr;
}


xDirect3DVolumeTexture9::xDirect3DVolumeTexture9( IDirect3DVolumeTexture9* volumeTex ) : xDirect3DResourceBase( eDRT_TextureVolume, (res_index)this, (res_index)volumeTex )
{
	m_volumeTexture = volumeTex;
}

STDMETHODIMP xDirect3DVolumeTexture9::QueryInterface( THIS_ REFIID riid, void** ppvObj )
{
	STDMETHODIMP hr;
	hr = m_volumeTexture->QueryInterface( riid,  ppvObj );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DVolumeTexture9::GetDevice( THIS_ IDirect3DDevice9** ppDevice )
{
	STDMETHODIMP hr;
	hr = m_volumeTexture->GetDevice(   ppDevice );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DVolumeTexture9::SetPrivateData( THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags )
{
	STDMETHODIMP hr;
	hr = m_volumeTexture->SetPrivateData(   refguid,  pData, SizeOfData, Flags );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DVolumeTexture9::GetPrivateData( THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData )
{
	STDMETHODIMP hr;
	hr = m_volumeTexture->GetPrivateData(   refguid, pData, pSizeOfData );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DVolumeTexture9::FreePrivateData( THIS_ REFGUID refguid )
{
	STDMETHODIMP hr;
	hr = m_volumeTexture->FreePrivateData(  refguid );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DVolumeTexture9::SetAutoGenFilterType( THIS_ D3DTEXTUREFILTERTYPE FilterType )
{
	STDMETHODIMP hr;
	hr = m_volumeTexture->SetAutoGenFilterType(  FilterType );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DVolumeTexture9::GetLevelDesc( THIS_ UINT Level,D3DVOLUME_DESC *pDesc )
{
	STDMETHODIMP hr;
	hr = m_volumeTexture->GetLevelDesc(  Level, pDesc );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DVolumeTexture9::GetVolumeLevel( THIS_ UINT Level,IDirect3DVolume9** ppVolumeLevel )
{
	STDMETHODIMP hr;
	hr = m_volumeTexture->GetVolumeLevel(  Level, ppVolumeLevel );
	if ( SUCCEEDED(hr) )
	{
		xDirect3DVolume9* myVolume = g_resourceManager.getXVolumeMapping( (res_index)(*ppVolumeLevel) );
		if (!myVolume)
		{
			myVolume = new xDirect3DVolume9( *ppVolumeLevel );
		}
		*ppVolumeLevel = myVolume;
	}
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DVolumeTexture9::LockBox( THIS_ UINT Level,D3DLOCKED_BOX* pLockedVolume,CONST D3DBOX* pBox,DWORD Flags )
{
	STDMETHODIMP hr;
	hr = m_volumeTexture->LockBox(  Level, pLockedVolume,  pBox, Flags );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DVolumeTexture9::UnlockBox( THIS_ UINT Level )
{
	STDMETHODIMP hr;
	hr = m_volumeTexture->UnlockBox(  Level );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DVolumeTexture9::AddDirtyBox( THIS_ CONST D3DBOX* pDirtyBox )
{
	STDMETHODIMP hr;
	hr = m_volumeTexture->AddDirtyBox(   pDirtyBox );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

void xDirect3DVolumeTexture9::GenerateMipSubLevels( )
{
	m_volumeTexture->GenerateMipSubLevels();
}

D3DTEXTUREFILTERTYPE xDirect3DVolumeTexture9::GetAutoGenFilterType()
{
	D3DTEXTUREFILTERTYPE hr;
	hr = m_volumeTexture->GetAutoGenFilterType();
	return hr;
}

DWORD xDirect3DVolumeTexture9::GetLevelCount()
{
	DWORD hr;
	hr = m_volumeTexture->GetLevelCount();
	return hr;
}

DWORD xDirect3DVolumeTexture9::GetLOD()
{
	DWORD hr;
	hr = m_volumeTexture->GetLOD();
	return hr;
}

DWORD xDirect3DVolumeTexture9::SetLOD( DWORD LODNew )
{
	DWORD hr;
	hr = m_volumeTexture->SetLOD( LODNew );
	return hr;
}

D3DRESOURCETYPE xDirect3DVolumeTexture9::GetType()
{
	D3DRESOURCETYPE hr;
	hr = m_volumeTexture->GetType();
	return hr;
}

void xDirect3DVolumeTexture9::PreLoad()
{
	m_volumeTexture->PreLoad();
}

DWORD xDirect3DVolumeTexture9::GetPriority()
{
	DWORD hr;
	hr = m_volumeTexture->GetPriority();
	return hr;
}

DWORD xDirect3DVolumeTexture9::SetPriority( DWORD PriorityNew )
{
	DWORD hr;
	hr = m_volumeTexture->SetPriority( PriorityNew );
	return hr;
}

ULONG xDirect3DVolumeTexture9::Release()
{
	ULONG hr;
	hr = m_volumeTexture->Release();
	return hr;
}

ULONG xDirect3DVolumeTexture9::AddRef()
{
	ULONG hr;
	hr = m_volumeTexture->AddRef();
	return hr;
}
