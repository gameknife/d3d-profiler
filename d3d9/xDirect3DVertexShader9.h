#ifndef xDirect3DVertexShader9_h__
#define xDirect3DVertexShader9_h__

#include "xd3d9.h"
#include "xDirect3DResourceBase.h"

class xDirect3DVertexShader9 : public IDirect3DVertexShader9, public xDirect3DResourceBase
{
public:
	xDirect3DVertexShader9( IDirect3DVertexShader9* vs );
	~xDirect3DVertexShader9(void) {}

	virtual STDMETHODIMP QueryInterface( THIS_ REFIID riid, void** ppvObj );

	virtual STDMETHODIMP_(ULONG) AddRef( THIS );

	virtual STDMETHODIMP_(ULONG) Release( THIS );

	virtual STDMETHODIMP GetDevice( THIS_ IDirect3DDevice9** ppDevice );

	virtual STDMETHODIMP GetFunction( THIS_ void*,UINT* pSizeOfData );

	IDirect3DVertexShader9* m_vertexShader;
	uint32 m_memUsage;
};

#endif // xDirect3DVertexShader9_h__