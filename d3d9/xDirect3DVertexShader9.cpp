#include "xDirect3DVertexShader9.h"
#include "xAPICallMonitor.h"

xDirect3DVertexShader9::xDirect3DVertexShader9( IDirect3DVertexShader9* vs):xDirect3DResourceBase(eDRT_VertexShader, (res_index)this, (res_index)vs)
{
	m_vertexShader = vs;

	m_vertexShader->GetFunction( NULL, &m_memUsage );
}

STDMETHODIMP xDirect3DVertexShader9::QueryInterface( THIS_ REFIID riid, void** ppvObj )
{
	STDMETHODIMP hr;
	hr = m_vertexShader->QueryInterface( riid, ppvObj );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DVertexShader9::GetDevice( THIS_ IDirect3DDevice9** ppDevice )
{
	STDMETHODIMP hr;
	hr = m_vertexShader->GetDevice( ppDevice );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DVertexShader9::GetFunction( THIS_ void* pData,UINT* pSizeOfData )
{
	STDMETHODIMP hr;
	hr = m_vertexShader->GetFunction( pData , pSizeOfData );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

ULONG xDirect3DVertexShader9::Release ( THIS )
{
	ULONG hr;
	hr = m_vertexShader->Release(  );
	if (hr == 0)
	{
		delete this;
	}
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

ULONG xDirect3DVertexShader9::AddRef ( THIS )
{
	ULONG hr;
	hr = m_vertexShader->AddRef(  );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}


