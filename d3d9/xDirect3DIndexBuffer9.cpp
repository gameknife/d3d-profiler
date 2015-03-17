#include "xDirect3DIndexBuffer9.h"
#include "xAPICallMonitor.h"

xDirect3DIndexBuffer9::xDirect3DIndexBuffer9( IDirect3DIndexBuffer9* realIB ):xDirect3DResourceBase(eDRT_IndexBuffer, (res_index)this, (res_index)realIB)
{
	m_indexBuffer = realIB;

	D3DINDEXBUFFER_DESC desc;
	m_indexBuffer->GetDesc( &desc );

	m_memUsage = desc.Size;
	m_memUsageGPU = desc.Size;

	switch(desc.Pool)
	{
	case D3DPOOL_DEFAULT:
		m_memUsage = 0;
		break;
	case D3DPOOL_SYSTEMMEM:
	case D3DPOOL_SCRATCH:
		m_memUsageGPU = 0;
		break;
	}

}

STDMETHODIMP xDirect3DIndexBuffer9::QueryInterface( THIS_ REFIID riid, void** ppvObj )
{
	STDMETHODIMP hr;
	hr = m_indexBuffer->QueryInterface( riid, ppvObj );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DIndexBuffer9::GetDevice( THIS_ IDirect3DDevice9** ppDevice )
{
	STDMETHODIMP hr;
	hr = m_indexBuffer->GetDevice(  ppDevice );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DIndexBuffer9::SetPrivateData( THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags )
{
	STDMETHODIMP hr;
	hr = m_indexBuffer->SetPrivateData(  refguid,  pData, SizeOfData, Flags );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DIndexBuffer9::GetPrivateData( THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData )
{
	STDMETHODIMP hr;
	hr = m_indexBuffer->GetPrivateData(  refguid, pData, pSizeOfData );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DIndexBuffer9::FreePrivateData( THIS_ REFGUID refguid )
{
	STDMETHODIMP hr;
	hr = m_indexBuffer->FreePrivateData(  refguid );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DIndexBuffer9::Lock( THIS_ UINT OffsetToLock,UINT SizeToLock,void** ppbData,DWORD Flags )
{
	FUNC_ENTER_TICK; STDMETHODIMP hr;
	hr = m_indexBuffer->Lock(  OffsetToLock, SizeToLock, ppbData, Flags );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DIndexBuffer9::Unlock( THIS )
{
	FUNC_ENTER_TICK; STDMETHODIMP hr;
	hr = m_indexBuffer->Unlock(  );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DIndexBuffer9::GetDesc( THIS_ D3DINDEXBUFFER_DESC *pDesc )
{
	STDMETHODIMP hr;
	hr = m_indexBuffer->GetDesc(  pDesc );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

D3DRESOURCETYPE xDirect3DIndexBuffer9::GetType( THIS )
{
	D3DRESOURCETYPE hr;
	hr = m_indexBuffer->GetType();
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

void xDirect3DIndexBuffer9::PreLoad( THIS )
{
	m_indexBuffer->PreLoad();
}

DWORD xDirect3DIndexBuffer9::GetPriority ( THIS )
{
	DWORD hr;
	hr = m_indexBuffer->GetPriority();
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

DWORD xDirect3DIndexBuffer9::SetPriority( THIS_ DWORD PriorityNew )
{
	DWORD hr;
	hr = m_indexBuffer->SetPriority( PriorityNew );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

ULONG xDirect3DIndexBuffer9::Release( THIS )
{
	ULONG hr;
	hr = m_indexBuffer->Release();
	if (hr == 0)
	{
		g_resourceManager.removeModelWithIB( this );
		delete this;
	}
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

ULONG xDirect3DIndexBuffer9::AddRef( THIS )
{
	ULONG hr;
	hr = m_indexBuffer->AddRef();
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}
