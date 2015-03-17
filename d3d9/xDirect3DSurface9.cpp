#include "xDirect3DSurface9.h"
#include "xAPICallMonitor.h"

xDirect3DSurface9::xDirect3DSurface9( IDirect3DSurface9* surface ) : xDirect3DResourceBase( eDRT_Surface, (res_index)this, (res_index)surface  )
{
	m_surface = surface;
}

STDMETHODIMP xDirect3DSurface9::QueryInterface( THIS_ REFIID riid, void** ppvObj )
{
	STDMETHODIMP hr;
	hr = m_surface->QueryInterface( riid, ppvObj );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DSurface9::GetDevice( THIS_ IDirect3DDevice9** ppDevice )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_surface->GetDevice( ppDevice );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DSurface9::SetPrivateData( THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_surface->SetPrivateData( refguid, pData, SizeOfData, Flags );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DSurface9::GetPrivateData( THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_surface->GetPrivateData( refguid, pData, pSizeOfData );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DSurface9::FreePrivateData( THIS_ REFGUID refguid )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_surface->FreePrivateData( refguid );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DSurface9::GetContainer( THIS_ REFIID riid,void** ppContainer )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_surface->GetContainer( riid, ppContainer );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DSurface9::GetDesc( THIS_ D3DSURFACE_DESC *pDesc )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_surface->GetDesc( pDesc );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DSurface9::LockRect( THIS_ D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags )
{
	STDMETHODIMP hr;
	hr = m_surface->LockRect( pLockedRect, pRect, Flags );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DSurface9::UnlockRect( )
{
	STDMETHODIMP hr;
	hr = m_surface->UnlockRect(  );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DSurface9::GetDC( THIS_ HDC *phdc )
{
	STDMETHODIMP hr;
	hr = m_surface->GetDC( phdc );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DSurface9::ReleaseDC( THIS_ HDC hdc )
{
	STDMETHODIMP hr;
	hr = m_surface->ReleaseDC( hdc );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}



D3DRESOURCETYPE xDirect3DSurface9::GetType()
{
	D3DRESOURCETYPE hr;
	hr = m_surface->GetType();
	return hr;
}

void xDirect3DSurface9::PreLoad()
{
	m_surface->PreLoad();
}

DWORD xDirect3DSurface9::GetPriority()
{
	DWORD hr;
	hr = m_surface->GetPriority();
	return hr;
}

DWORD xDirect3DSurface9::SetPriority( DWORD PriorityNew )
{
	DWORD hr;
	hr = m_surface->SetPriority( PriorityNew );
	return hr;
}

ULONG xDirect3DSurface9::Release()
{
	ULONG hr;
	hr = m_surface->Release();
	// D3D RT始终会持有一个，所以引用计数到1就将其删除 [2/20/2013 YiKaiming]
	if (hr == 0)
	{
		// 可以调用xd3d内部的资源管理器来删除
		delete this;
	}
	return hr;
}

ULONG xDirect3DSurface9::AddRef()
{
	ULONG hr;
	hr = m_surface->AddRef();
	return hr;
}
