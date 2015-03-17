//////////////////////////////////////////////////////////////////////////
//
// yikaiming (C) 2014
// gkENGINE Source File 
//
// Name:   	xDXGIFactory1.h
// Desc:	
// 	
// 
// Author:  gameKnife
// Date:	2015/2/17
// 
//////////////////////////////////////////////////////////////////////////

#ifndef _xDXGIFactory1_h_
#define _xDXGIFactory1_h_

#include "DXGI.h"

class xDXGIFactory1 : public IDXGIFactory1
{
public:
	xDXGIFactory1(IDXGIFactory1* dev)
	{
		m_device = dev;
	}
	virtual ~xDXGIFactory1()
	{

	}
	IDXGIFactory1* m_device;
public:
	virtual HRESULT STDMETHODCALLTYPE EnumAdapters( 
		UINT Adapter,
		IDXGIAdapter **ppAdapter);

	virtual HRESULT STDMETHODCALLTYPE MakeWindowAssociation( 
		HWND WindowHandle,
		UINT Flags);

	virtual HRESULT STDMETHODCALLTYPE GetWindowAssociation( 
		HWND *pWindowHandle);

	virtual HRESULT STDMETHODCALLTYPE CreateSwapChain( 
		
		IUnknown *pDevice,
		
		DXGI_SWAP_CHAIN_DESC *pDesc,
		
		IDXGISwapChain **ppSwapChain);

	virtual HRESULT STDMETHODCALLTYPE CreateSoftwareAdapter( 
		HMODULE Module,
		
		IDXGIAdapter **ppAdapter);

	virtual HRESULT STDMETHODCALLTYPE EnumAdapters1( 
		UINT Adapter,
		
		IDXGIAdapter1 **ppAdapter);

	virtual BOOL STDMETHODCALLTYPE IsCurrent( void);

	//////////////////////////////////////////////////////////////////////////
	// dxgiobject

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

