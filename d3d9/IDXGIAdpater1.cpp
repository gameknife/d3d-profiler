#include "IDXGIAdpater1.h"
#include "Logger.h"
#include "xDXGIFactory1.h"

HRESULT STDMETHODCALLTYPE xDXGIAdapter1::GetDesc1(DXGI_ADAPTER_DESC1 *pDesc)
{
	return m_device->GetDesc1( pDesc);
}

HRESULT STDMETHODCALLTYPE xDXGIAdapter1::EnumOutputs(UINT Output, IDXGIOutput **ppOutput)
{
	return m_device->EnumOutputs( Output, ppOutput);
}

HRESULT STDMETHODCALLTYPE xDXGIAdapter1::GetDesc(DXGI_ADAPTER_DESC *pDesc)
{
	return m_device->GetDesc( pDesc);
}

HRESULT STDMETHODCALLTYPE xDXGIAdapter1::CheckInterfaceSupport(REFGUID InterfaceName, LARGE_INTEGER *pUMDVersion)
{
	return m_device->CheckInterfaceSupport( InterfaceName, pUMDVersion);
}

//////////////////////////////////////////////////////////////////////////


HRESULT STDMETHODCALLTYPE xDXGIAdapter1::SetPrivateData(REFGUID Name, UINT DataSize, const void *pData)
{
	return m_device->SetPrivateData(Name, DataSize, pData);
}

HRESULT STDMETHODCALLTYPE xDXGIAdapter1::SetPrivateDataInterface(REFGUID Name, const IUnknown *pUnknown)
{
	return m_device->SetPrivateDataInterface(Name, pUnknown);
}

HRESULT STDMETHODCALLTYPE xDXGIAdapter1::GetPrivateData(REFGUID Name, UINT *pDataSize, void *pData)
{
	return m_device->GetPrivateData(Name, pDataSize, pData);
}

HRESULT STDMETHODCALLTYPE xDXGIAdapter1::GetParent(REFIID riid, void **ppParent)
{
	gEnv->logger->LogE("xDXGIAdapter1:GetParent");

	if (riid == __uuidof(IDXGIFactory1))
	{
		gEnv->logger->LogE("xDXGIAdapter1:IDXGIFactory FROM HERE!!!!!!!!!!");
	}

	IDXGIFactory1* fact;
	HRESULT ret = m_device->GetParent(riid, (void**)&fact);
	xDXGIFactory1* factory = new xDXGIFactory1(fact);
	*ppParent = factory;

	return ret;
}

HRESULT STDMETHODCALLTYPE xDXGIAdapter1::QueryInterface(REFIID riid, void **ppvObject)
{
	gEnv->logger->LogE("xDXGIAdapter1:QueryInterface");
	return m_device->QueryInterface(riid, ppvObject);
}

ULONG STDMETHODCALLTYPE xDXGIAdapter1::AddRef(void)
{
	return m_device->AddRef();
}

ULONG STDMETHODCALLTYPE xDXGIAdapter1::Release(void)
{
	return m_device->Release();
}
