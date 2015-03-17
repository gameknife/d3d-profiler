//////////////////////////////////////////////////////////////////////////
//
// yikaiming (C) 2014
// gkENGINE Source File 
//
// Name:   	IDXGIAdpater1.h
// Desc:	
// 	
// 
// Author:  gameKnife
// Date:	2015/2/17
// 
//////////////////////////////////////////////////////////////////////////

#ifndef _IDXGIAdpater1_h_
#define _IDXGIAdpater1_h_

#include "DXGI.h"

class xDXGIAdapter1 : public IDXGIAdapter1
{
public:
	xDXGIAdapter1( IDXGIAdapter1* dev )
	{
		m_device = dev;
	}

	virtual ~xDXGIAdapter1()
	{

	}

	IDXGIAdapter1* m_device;

public:
	virtual HRESULT STDMETHODCALLTYPE GetDesc1( 
		DXGI_ADAPTER_DESC1 *pDesc);

	virtual HRESULT STDMETHODCALLTYPE EnumOutputs( 
		UINT Output,
		IDXGIOutput **ppOutput);

	virtual HRESULT STDMETHODCALLTYPE GetDesc( 
		DXGI_ADAPTER_DESC *pDesc);

	virtual HRESULT STDMETHODCALLTYPE CheckInterfaceSupport( 
		REFGUID InterfaceName,
		LARGE_INTEGER *pUMDVersion);

	virtual HRESULT STDMETHODCALLTYPE SetPrivateData( 
		REFGUID Name,
		UINT DataSize,
		const void *pData);

	virtual HRESULT STDMETHODCALLTYPE SetPrivateDataInterface( 
		REFGUID Name,
		const IUnknown *pUnknown);

	virtual HRESULT STDMETHODCALLTYPE GetPrivateData( 
		REFGUID Name,
		UINT *pDataSize,
		void *pData);

	virtual HRESULT STDMETHODCALLTYPE GetParent( 
		REFIID riid,
		void **ppParent);

	virtual HRESULT STDMETHODCALLTYPE QueryInterface( 
		REFIID riid,
		void **ppvObject);

	virtual ULONG STDMETHODCALLTYPE AddRef( void);

	virtual ULONG STDMETHODCALLTYPE Release( void);
};
#endif
