#include "xDirect3DVertexDeclaration9.h"
#include "xAPICallMonitor.h"


xDirect3DVertexDeclaration9::xDirect3DVertexDeclaration9( IDirect3DVertexDeclaration9* decl ):xDirect3DResourceBase(eDRT_VertexDeclaration, (res_index)this, (res_index)decl)
{
	m_decl = decl;
}

STDMETHODIMP xDirect3DVertexDeclaration9::QueryInterface( THIS_ REFIID riid, void** ppvObj )
{
	STDMETHODIMP hr;
	hr = m_decl->QueryInterface( riid, ppvObj );
	CHECKCALL(hr, __FUNCTION__);
	return hr;
}

STDMETHODIMP xDirect3DVertexDeclaration9::GetDevice( THIS_ IDirect3DDevice9** ppDevice )
{
	STDMETHODIMP hr;
	hr = m_decl->GetDevice( ppDevice );
	CHECKCALL(hr, __FUNCTION__);
	return hr;
}

STDMETHODIMP xDirect3DVertexDeclaration9::GetDeclaration( THIS_ D3DVERTEXELEMENT9* pElement,UINT* pNumElements )
{
	STDMETHODIMP hr;
	hr = m_decl->GetDeclaration( pElement, pNumElements );
	CHECKCALL(hr, __FUNCTION__);
	return hr;
}

ULONG xDirect3DVertexDeclaration9::Release( THIS )
{
	ULONG hr;
	hr = m_decl->Release(   );
	if (hr == 0)
	{
		delete this;
	}
	return hr;
}

ULONG xDirect3DVertexDeclaration9::AddRef( THIS )
{
	ULONG hr;
	hr = m_decl->AddRef(   );
	return hr;
}

