#include "xDirect3DVertexBuffer9.h"
#include "xAPICallMonitor.h"

xDirect3DVertexBuffer9::xDirect3DVertexBuffer9( IDirect3DVertexBuffer9* realVB ):xDirect3DResourceBase(eDRT_VertexBuffer, (res_index)this, (res_index)realVB)
{
	m_vertexBuffer = realVB;

	D3DVERTEXBUFFER_DESC desc;
	m_vertexBuffer->GetDesc(&desc);

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

xDirect3DVertexBuffer9::~xDirect3DVertexBuffer9()
{
}
STDMETHODIMP xDirect3DVertexBuffer9::QueryInterface( THIS_ REFIID riid, void** ppvObj )
{
	STDMETHODIMP hr;
	hr = m_vertexBuffer->QueryInterface( riid, ppvObj );
	return hr;
}

STDMETHODIMP xDirect3DVertexBuffer9::GetDevice( THIS_ IDirect3DDevice9** ppDevice )
{
	STDMETHODIMP hr;
	hr = m_vertexBuffer->GetDevice( ppDevice );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DVertexBuffer9::SetPrivateData( THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags )
{
	STDMETHODIMP hr;
	hr = m_vertexBuffer->SetPrivateData( refguid, pData, SizeOfData, Flags );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DVertexBuffer9::GetPrivateData( THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData )
{
	STDMETHODIMP hr;
	hr = m_vertexBuffer->GetPrivateData(  refguid, pData, pSizeOfData );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DVertexBuffer9::FreePrivateData( THIS_ REFGUID refguid )
{
	STDMETHODIMP hr;
	hr = m_vertexBuffer->FreePrivateData( refguid );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DVertexBuffer9::Lock( THIS_ UINT OffsetToLock,UINT SizeToLock,void** ppbData,DWORD Flags )
{
	FUNC_ENTER_TICK; STDMETHODIMP hr;
	hr = m_vertexBuffer->Lock(  OffsetToLock, SizeToLock, ppbData, Flags );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DVertexBuffer9::Unlock( THIS )
{
	FUNC_ENTER_TICK; STDMETHODIMP hr;
	hr = m_vertexBuffer->Unlock();
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DVertexBuffer9::GetDesc( THIS_ D3DVERTEXBUFFER_DESC *pDesc )
{
	STDMETHODIMP hr;
	hr = m_vertexBuffer->GetDesc( pDesc );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

D3DRESOURCETYPE xDirect3DVertexBuffer9::GetType( THIS )
{
	D3DRESOURCETYPE hr;
	hr = m_vertexBuffer->GetType();
	return hr;
}

void xDirect3DVertexBuffer9::PreLoad( THIS )
{
	m_vertexBuffer->PreLoad();
}

DWORD xDirect3DVertexBuffer9::GetPriority( THIS )
{
	DWORD hr;
	hr = m_vertexBuffer->GetPriority();
	return hr;
}

DWORD xDirect3DVertexBuffer9::SetPriority( THIS_ DWORD PriorityNew )
{
	DWORD hr;
	hr = m_vertexBuffer->SetPriority( PriorityNew );
	return hr;
}

ULONG xDirect3DVertexBuffer9::Release ( THIS )
{
	ULONG hr;
	hr = m_vertexBuffer->Release();
	if (hr == 0)
	{
		g_resourceManager.removeModelWithVB( this );
		delete this;
	}
	return hr;
}

ULONG xDirect3DVertexBuffer9::AddRef ( THIS )
{
	ULONG hr;
	hr = m_vertexBuffer->AddRef(   );
	return hr;
}





