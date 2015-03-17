#include "xDirect3DPixelShader9.h"
#include "xAPICallMonitor.h"

xDirect3DPixelShader9::xDirect3DPixelShader9( IDirect3DPixelShader9* ps ):xDirect3DResourceBase(eDRT_PixelShader, (res_index)this, (res_index)ps)
{
	m_pixelShader = ps;

	m_pixelShader->GetFunction( NULL, &m_memUsage );
}

STDMETHODIMP xDirect3DPixelShader9::QueryInterface( THIS_ REFIID riid, void** ppvObj )
{
	STDMETHODIMP hr;
	hr = m_pixelShader ->QueryInterface( riid, ppvObj );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DPixelShader9::GetDevice( THIS_ IDirect3DDevice9** ppDevice )
{
	STDMETHODIMP hr;
	hr = m_pixelShader ->GetDevice( ppDevice );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3DPixelShader9::GetFunction( THIS_ void* pdata,UINT* pSizeOfData )
{
	STDMETHODIMP hr;
	hr = m_pixelShader ->GetFunction(  pdata, pSizeOfData );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

ULONG xDirect3DPixelShader9::Release( THIS )
{
	ULONG hr;
	hr = m_pixelShader ->Release();
	if (hr == 0)
	{
		delete this;
	}
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

ULONG xDirect3DPixelShader9::AddRef( THIS )
{
	ULONG hr;
	hr = m_pixelShader ->AddRef();
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}
