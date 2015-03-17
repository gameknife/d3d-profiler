#include "xDXGIFactory1.h"
#include "xDXGISwapChain.h"
#include "Logger.h"
#include "IDXGIAdpater1.h"
#include "xDirect3D11.h"
#include "xVirtualApp.h"

HRESULT STDMETHODCALLTYPE xDXGIFactory1::EnumAdapters(UINT Adapter, IDXGIAdapter **ppAdapter)
{
	//gEnv->logger->LogE("EnumA");
	return m_device->EnumAdapters(Adapter, ppAdapter);
}

HRESULT STDMETHODCALLTYPE xDXGIFactory1::MakeWindowAssociation(HWND WindowHandle, UINT Flags)
{
	gEnv->logger->LogE("MakeWindow");
	return m_device->MakeWindowAssociation(WindowHandle,Flags);
}

HRESULT STDMETHODCALLTYPE xDXGIFactory1::GetWindowAssociation(HWND *pWindowHandle)
{
	gEnv->logger->LogE("Getwindow");
	return m_device->GetWindowAssociation(pWindowHandle);
}

HRESULT STDMETHODCALLTYPE xDXGIFactory1::CreateSwapChain(IUnknown *pDevice, DXGI_SWAP_CHAIN_DESC *pDesc, IDXGISwapChain **ppSwapChain)
{
	gEnv->logger->LogE("CreateSwapChain");

	IDXGISwapChain* pSwpc = NULL;
	HRESULT ret = m_device->CreateSwapChain(pDevice, pDesc, &pSwpc);

	xDXGISwapChain* pSwpc_wrap = new xDXGISwapChain(pSwpc);

	*ppSwapChain = pSwpc_wrap;

	//////////////////////////////////////////////////////////////////////////
	// create the device from here

	ID3D11DeviceContext* tmp;
	((xD3D11Device*)pDevice)->GetImmediateContext( &tmp );

	g_vApp->OnInit( (xD3D11Device*)pDevice, (xD3D11DeviceContext*)tmp );

	return ret;
}

HRESULT STDMETHODCALLTYPE xDXGIFactory1::CreateSoftwareAdapter(HMODULE Module, IDXGIAdapter **ppAdapter)
{
	gEnv->logger->LogE("CreateSoftwareAdapter");
	return m_device->CreateSoftwareAdapter(Module, ppAdapter);
}

HRESULT STDMETHODCALLTYPE xDXGIFactory1::EnumAdapters1(UINT Adapter, IDXGIAdapter1 **ppAdapter)
{
	//gEnv->logger->LogE("EnumA1");
	IDXGIAdapter1* pAda;
	HRESULT ret = m_device->EnumAdapters1(Adapter, &pAda);

	xDXGIAdapter1* adpater1 = new xDXGIAdapter1( pAda );
	*ppAdapter = adpater1;

	return ret;
}

BOOL STDMETHODCALLTYPE xDXGIFactory1::IsCurrent(void)
{
	gEnv->logger->LogE("IsCurrent");
	return m_device->IsCurrent();
}

HRESULT STDMETHODCALLTYPE xDXGIFactory1::SetPrivateData(REFGUID Name, UINT DataSize, const void *pData)
{
	return m_device->SetPrivateData(Name, DataSize, pData);
}

HRESULT STDMETHODCALLTYPE xDXGIFactory1::SetPrivateDataInterface(REFGUID Name, const IUnknown *pUnknown)
{
	return m_device->SetPrivateDataInterface(Name, pUnknown);
}

HRESULT STDMETHODCALLTYPE xDXGIFactory1::GetPrivateData(REFGUID Name, UINT *pDataSize, void *pData)
{
	return m_device->GetPrivateData(Name, pDataSize, pData);
}

HRESULT STDMETHODCALLTYPE xDXGIFactory1::GetParent(REFIID riid, void **ppParent)
{
	gEnv->logger->LogE("xDXGIFactory1:GetParent");
	return m_device->GetParent(riid, ppParent);
}

HRESULT STDMETHODCALLTYPE xDXGIFactory1::QueryInterface(REFIID riid, void **ppvObject)
{
	gEnv->logger->LogE("xDXGIFactory1:QueryInterface");
	return m_device->QueryInterface(riid, ppvObject);
}

ULONG STDMETHODCALLTYPE xDXGIFactory1::AddRef(void)
{
	return m_device->AddRef();
}

ULONG STDMETHODCALLTYPE xDXGIFactory1::Release(void)
{
	return m_device->Release();
}
