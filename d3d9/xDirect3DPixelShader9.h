#ifndef xDirect3DPixelShader9_h__
#define xDirect3DPixelShader9_h__

#include "xd3d9.h"
#include "xDirect3DResourceBase.h"

class xDirect3DPixelShader9 : public IDirect3DPixelShader9, public xDirect3DResourceBase
{
public:
	xDirect3DPixelShader9( IDirect3DPixelShader9* ps );
	~xDirect3DPixelShader9(void) {}

	virtual STDMETHODIMP QueryInterface( THIS_ REFIID riid, void** ppvObj );

	virtual STDMETHODIMP_(ULONG) AddRef( THIS );

	virtual STDMETHODIMP_(ULONG) Release( THIS );

	virtual STDMETHODIMP GetDevice( THIS_ IDirect3DDevice9** ppDevice );

	virtual STDMETHODIMP GetFunction( THIS_ void*,UINT* pSizeOfData );

	IDirect3DPixelShader9* m_pixelShader;
	uint32 m_memUsage;
};

#endif // xDirect3DPixelShader9_h__