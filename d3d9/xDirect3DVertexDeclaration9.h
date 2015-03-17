#ifndef xDirect3DVertexDeclaration9_h__
#define xDirect3DVertexDeclaration9_h__

#include "xd3d9.h"
#include "xDirect3DResourceBase.h"

class xDirect3DVertexDeclaration9 : public IDirect3DVertexDeclaration9, public xDirect3DResourceBase
{
public:
	xDirect3DVertexDeclaration9( IDirect3DVertexDeclaration9* decl );
	~xDirect3DVertexDeclaration9() {}
	virtual STDMETHODIMP QueryInterface( THIS_ REFIID riid, void** ppvObj );

	virtual STDMETHODIMP_(ULONG) AddRef( THIS );

	virtual STDMETHODIMP_(ULONG) Release( THIS );

	virtual STDMETHODIMP GetDevice( THIS_ IDirect3DDevice9** ppDevice );

	virtual STDMETHODIMP GetDeclaration( THIS_ D3DVERTEXELEMENT9* pElement,UINT* pNumElements );

	IDirect3DVertexDeclaration9* m_decl;
};

#endif // xDirect3DVertexDeclaration9_h__