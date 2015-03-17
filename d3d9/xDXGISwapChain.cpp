#include "xDXGISwapChain.h"
#include "Logger.h"
#include "xVirtualApp.h"

HRESULT STDMETHODCALLTYPE xDXGISwapChain::Present(UINT SyncInterval, UINT Flags)
{
	//gEnv->logger->Log("present");
	if(gEnv->app)
	{
		gEnv->app->OnUpdate();
	}
	return m_device->Present(SyncInterval, Flags);
}

HRESULT STDMETHODCALLTYPE xDXGISwapChain::GetBuffer(UINT Buffer, REFIID riid, void **ppSurface)
{
	return m_device->GetBuffer(Buffer, riid, ppSurface);
}

HRESULT STDMETHODCALLTYPE xDXGISwapChain::SetFullscreenState(BOOL Fullscreen, IDXGIOutput *pTarget)
{
	return m_device->SetFullscreenState(Fullscreen, pTarget);
}

HRESULT STDMETHODCALLTYPE xDXGISwapChain::GetFullscreenState(BOOL *pFullscreen, IDXGIOutput **ppTarget)
{
	return m_device->GetFullscreenState(pFullscreen, ppTarget);
}

HRESULT STDMETHODCALLTYPE xDXGISwapChain::GetDesc(DXGI_SWAP_CHAIN_DESC *pDesc)
{
	return m_device->GetDesc(pDesc);
}

HRESULT STDMETHODCALLTYPE xDXGISwapChain::ResizeBuffers(UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
	return m_device->ResizeBuffers(BufferCount, Width, Height, NewFormat, SwapChainFlags);
}

HRESULT STDMETHODCALLTYPE xDXGISwapChain::ResizeTarget(const DXGI_MODE_DESC *pNewTargetParameters)
{
	return m_device->ResizeTarget(pNewTargetParameters);
}

HRESULT STDMETHODCALLTYPE xDXGISwapChain::GetContainingOutput(IDXGIOutput **ppOutput)
{
	return m_device->GetContainingOutput( ppOutput);
}

HRESULT STDMETHODCALLTYPE xDXGISwapChain::GetFrameStatistics(DXGI_FRAME_STATISTICS *pStats)
{
	return m_device->GetFrameStatistics( pStats);
}

HRESULT STDMETHODCALLTYPE xDXGISwapChain::GetLastPresentCount(UINT *pLastPresentCount)
{
	return m_device->GetLastPresentCount( pLastPresentCount);
}

//////////////////////////////////////////////////////////////////////////

HRESULT STDMETHODCALLTYPE xDXGISwapChain::SetPrivateData(REFGUID Name, UINT DataSize, const void *pData)
{
	return m_device->SetPrivateData(Name, DataSize, pData);
}

HRESULT STDMETHODCALLTYPE xDXGISwapChain::SetPrivateDataInterface(REFGUID Name, const IUnknown *pUnknown)
{
	return m_device->SetPrivateDataInterface(Name, pUnknown);
}

HRESULT STDMETHODCALLTYPE xDXGISwapChain::GetPrivateData(REFGUID Name, UINT *pDataSize, void *pData)
{
	return m_device->GetPrivateData(Name, pDataSize, pData);
}

HRESULT STDMETHODCALLTYPE xDXGISwapChain::GetParent(REFIID riid, void **ppParent)
{
	return m_device->GetParent(riid, ppParent);
}

HRESULT STDMETHODCALLTYPE xDXGISwapChain::QueryInterface(REFIID riid, void **ppvObject)
{
	return m_device->QueryInterface(riid, ppvObject);
}

ULONG STDMETHODCALLTYPE xDXGISwapChain::AddRef(void)
{
	return m_device->AddRef();
}

ULONG STDMETHODCALLTYPE xDXGISwapChain::Release(void)
{
	return m_device->Release();
}

HRESULT STDMETHODCALLTYPE xDXGISwapChain::GetDevice(REFIID riid, void **ppDevice)
{
	return m_device->GetDevice(riid, ppDevice);
}
