//////////////////////////////////////////////////////////////////////////
//
// yikaiming (C) 2014
// gkENGINE Source File 
//
// Name:   	xDXGISwapChain.h
// Desc:	
// 	
// 
// Author:  gameKnife
// Date:	2015/2/17
// 
//////////////////////////////////////////////////////////////////////////

#ifndef _xDXGISwapChain_h_
#define _xDXGISwapChain_h_

#include "DXGI.h"

class xDXGISwapChain : public IDXGISwapChain
{
public:
	xDXGISwapChain(IDXGISwapChain* dev)
	{
		m_device = dev;
	}
	virtual ~xDXGISwapChain()
	{

	}
	IDXGISwapChain* m_device;
public:
	virtual HRESULT STDMETHODCALLTYPE Present( 
		UINT SyncInterval,
		UINT Flags);

	virtual HRESULT STDMETHODCALLTYPE GetBuffer( 
		UINT Buffer,
		
		REFIID riid,
		
		void **ppSurface);

	virtual HRESULT STDMETHODCALLTYPE SetFullscreenState( 
		BOOL Fullscreen,
		
		IDXGIOutput *pTarget);

	virtual HRESULT STDMETHODCALLTYPE GetFullscreenState( 
		
		BOOL *pFullscreen,
		
		IDXGIOutput **ppTarget);

	virtual HRESULT STDMETHODCALLTYPE GetDesc( 
		
		DXGI_SWAP_CHAIN_DESC *pDesc);

	virtual HRESULT STDMETHODCALLTYPE ResizeBuffers( 
		UINT BufferCount,
		UINT Width,
		UINT Height,
		DXGI_FORMAT NewFormat,
		UINT SwapChainFlags);

	virtual HRESULT STDMETHODCALLTYPE ResizeTarget( 
		
		const DXGI_MODE_DESC *pNewTargetParameters);

	virtual HRESULT STDMETHODCALLTYPE GetContainingOutput( 
		
		IDXGIOutput **ppOutput);

	virtual HRESULT STDMETHODCALLTYPE GetFrameStatistics( 
		
		DXGI_FRAME_STATISTICS *pStats);

	virtual HRESULT STDMETHODCALLTYPE GetLastPresentCount( 
		
		UINT *pLastPresentCount);

	//////////////////////////////////////////////////////////////////////////

	virtual HRESULT STDMETHODCALLTYPE GetDevice( 
		REFIID riid,
		void **ppDevice);

	//////////////////////////////////////////////////////////////////////////

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
