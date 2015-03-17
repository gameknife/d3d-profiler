#include "xDirect3DQuery9.h"
#include "xAPICallMonitor.h"

xDirect3DQuery9::xDirect3DQuery9( IDirect3DQuery9* query )
{
	m_query = query;
}

STDMETHODIMP xDirect3DQuery9::QueryInterface( THIS_ REFIID riid, void** ppvObj )
{
	STDMETHODIMP hr;
	hr = m_query->QueryInterface( riid, ppvObj );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DQuery9::GetDevice( THIS_ IDirect3DDevice9** ppDevice )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_query->GetDevice( ppDevice );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DQuery9::Issue( THIS_ DWORD dwIssueFlags )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_query->Issue( dwIssueFlags );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DQuery9::GetData( THIS_ void* pData,DWORD dwSize,DWORD dwGetDataFlags )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_query->GetData( pData, dwSize, dwGetDataFlags );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

DWORD xDirect3DQuery9::GetDataSize()
{
	DWORD hr;
	hr = m_query->GetDataSize();
	return hr;
}

D3DQUERYTYPE xDirect3DQuery9::GetType()
{
	D3DQUERYTYPE hr;
	hr = m_query->GetType();
	return hr;
}

ULONG xDirect3DQuery9::Release()
{
	ULONG hr;
	hr = m_query->Release();
// 	if (hr == 0)
// 	{
// 		delete this;
// 	}
	return hr;
}

ULONG xDirect3DQuery9::AddRef()
{
	ULONG hr;
	hr = m_query->AddRef();
	return hr;
}

