#include "xDirect3D11.h"
#include "Logger.h"
#include "xD3D11DeviceContext.h"

HRESULT STDMETHODCALLTYPE xD3D11Device::CreateBuffer(const D3D11_BUFFER_DESC *pDesc, const D3D11_SUBRESOURCE_DATA *pInitialData, ID3D11Buffer **ppBuffer)
{
	return m_device->CreateBuffer(pDesc, pInitialData, ppBuffer);
}

HRESULT STDMETHODCALLTYPE xD3D11Device::CreateTexture1D(const D3D11_TEXTURE1D_DESC *pDesc, const D3D11_SUBRESOURCE_DATA *pInitialData, ID3D11Texture1D **ppTexture1D)
{
	return m_device->CreateTexture1D(pDesc, pInitialData, ppTexture1D);
}

HRESULT STDMETHODCALLTYPE xD3D11Device::CreateTexture2D(const D3D11_TEXTURE2D_DESC *pDesc, const D3D11_SUBRESOURCE_DATA *pInitialData, ID3D11Texture2D **ppTexture2D)
{
	return m_device->CreateTexture2D(pDesc, pInitialData, ppTexture2D);
}

HRESULT STDMETHODCALLTYPE xD3D11Device::CreateTexture3D(const D3D11_TEXTURE3D_DESC *pDesc, const D3D11_SUBRESOURCE_DATA *pInitialData, ID3D11Texture3D **ppTexture3D)
{
	return m_device->CreateTexture3D(pDesc, pInitialData, ppTexture3D);
}

HRESULT STDMETHODCALLTYPE xD3D11Device::CreateShaderResourceView(ID3D11Resource *pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC *pDesc, ID3D11ShaderResourceView **ppSRView)
{
	return m_device->CreateShaderResourceView(pResource, pDesc, ppSRView);
}

HRESULT STDMETHODCALLTYPE xD3D11Device::CreateUnorderedAccessView(ID3D11Resource *pResource, const D3D11_UNORDERED_ACCESS_VIEW_DESC *pDesc, ID3D11UnorderedAccessView **ppUAView)
{
	return m_device->CreateUnorderedAccessView(pResource, pDesc, ppUAView);
}

HRESULT STDMETHODCALLTYPE xD3D11Device::CreateRenderTargetView(ID3D11Resource *pResource, const D3D11_RENDER_TARGET_VIEW_DESC *pDesc, ID3D11RenderTargetView **ppRTView)
{
	//gEnv->logger->LogE("Create Tex");
	return m_device->CreateRenderTargetView(pResource, pDesc, ppRTView);
}

HRESULT STDMETHODCALLTYPE xD3D11Device::CreateDepthStencilView(ID3D11Resource *pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC *pDesc, ID3D11DepthStencilView **ppDepthStencilView)
{
	return m_device->CreateDepthStencilView(pResource, pDesc, ppDepthStencilView);
}

HRESULT STDMETHODCALLTYPE xD3D11Device::CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC *pInputElementDescs, UINT NumElements, const void *pShaderBytecodeWithInputSignature, SIZE_T BytecodeLength, ID3D11InputLayout **ppInputLayout)
{
	return m_device->CreateInputLayout(pInputElementDescs, NumElements, pShaderBytecodeWithInputSignature, BytecodeLength, ppInputLayout);
}

HRESULT STDMETHODCALLTYPE xD3D11Device::CreateVertexShader(const void *pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11VertexShader **ppVertexShader)
{
	return m_device->CreateVertexShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppVertexShader);
}

HRESULT STDMETHODCALLTYPE xD3D11Device::CreateGeometryShader(const void *pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11GeometryShader **ppGeometryShader)
{
	return m_device->CreateGeometryShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppGeometryShader);
}

HRESULT STDMETHODCALLTYPE xD3D11Device::CreateGeometryShaderWithStreamOutput(const void *pShaderBytecode, SIZE_T BytecodeLength, const D3D11_SO_DECLARATION_ENTRY *pSODeclaration, UINT NumEntries, const UINT *pBufferStrides, UINT NumStrides, UINT RasterizedStream, ID3D11ClassLinkage *pClassLinkage, ID3D11GeometryShader **ppGeometryShader)
{
	return m_device->CreateGeometryShaderWithStreamOutput(pShaderBytecode, BytecodeLength, pSODeclaration, NumEntries, pBufferStrides, NumStrides, RasterizedStream, pClassLinkage, ppGeometryShader);
}

HRESULT STDMETHODCALLTYPE xD3D11Device::CreatePixelShader(const void *pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11PixelShader **ppPixelShader)
{
	return m_device->CreatePixelShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppPixelShader);
}

HRESULT STDMETHODCALLTYPE xD3D11Device::CreateHullShader(const void *pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11HullShader **ppHullShader)
{
	return m_device->CreateHullShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppHullShader);
}

HRESULT STDMETHODCALLTYPE xD3D11Device::CreateDomainShader(const void *pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11DomainShader **ppDomainShader)
{
	return m_device->CreateDomainShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppDomainShader);
}

HRESULT STDMETHODCALLTYPE xD3D11Device::CreateComputeShader(const void *pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11ComputeShader **ppComputeShader)
{
	return m_device->CreateComputeShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppComputeShader);
}

HRESULT STDMETHODCALLTYPE xD3D11Device::CreateClassLinkage(ID3D11ClassLinkage **ppLinkage)
{
	return m_device->CreateClassLinkage(ppLinkage);
}

HRESULT STDMETHODCALLTYPE xD3D11Device::CreateBlendState(const D3D11_BLEND_DESC *pBlendStateDesc, ID3D11BlendState **ppBlendState)
{
	return m_device->CreateBlendState( pBlendStateDesc, ppBlendState);
}

HRESULT STDMETHODCALLTYPE xD3D11Device::CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC *pDepthStencilDesc, ID3D11DepthStencilState **ppDepthStencilState)
{
	return m_device->CreateDepthStencilState(pDepthStencilDesc, ppDepthStencilState);
}

HRESULT STDMETHODCALLTYPE xD3D11Device::CreateRasterizerState(const D3D11_RASTERIZER_DESC *pRasterizerDesc, ID3D11RasterizerState **ppRasterizerState)
{
	return m_device->CreateRasterizerState(pRasterizerDesc, ppRasterizerState);
}

HRESULT STDMETHODCALLTYPE xD3D11Device::CreateSamplerState(const D3D11_SAMPLER_DESC *pSamplerDesc, ID3D11SamplerState **ppSamplerState)
{
	return m_device->CreateSamplerState( pSamplerDesc, ppSamplerState);
}

HRESULT STDMETHODCALLTYPE xD3D11Device::CreateQuery(const D3D11_QUERY_DESC *pQueryDesc, ID3D11Query **ppQuery)
{
	return m_device->CreateQuery( pQueryDesc, ppQuery);
}

HRESULT STDMETHODCALLTYPE xD3D11Device::CreatePredicate(const D3D11_QUERY_DESC *pPredicateDesc, ID3D11Predicate **ppPredicate)
{
	return m_device->CreatePredicate( pPredicateDesc, ppPredicate);
}

HRESULT STDMETHODCALLTYPE xD3D11Device::CreateCounter(const D3D11_COUNTER_DESC *pCounterDesc, ID3D11Counter **ppCounter)
{
	return m_device->CreateCounter(pCounterDesc, ppCounter);
}

HRESULT STDMETHODCALLTYPE xD3D11Device::CreateDeferredContext(UINT ContextFlags, ID3D11DeviceContext **ppDeferredContext)
{
	return m_device->CreateDeferredContext( ContextFlags, ppDeferredContext);
}

HRESULT STDMETHODCALLTYPE xD3D11Device::OpenSharedResource(HANDLE hResource, REFIID ReturnedInterface, void **ppResource)
{
	return m_device->OpenSharedResource(hResource, ReturnedInterface, ppResource);
}

HRESULT STDMETHODCALLTYPE xD3D11Device::CheckFormatSupport(DXGI_FORMAT Format, UINT *pFormatSupport)
{
	return m_device->CheckFormatSupport( Format,  pFormatSupport);
}

HRESULT STDMETHODCALLTYPE xD3D11Device::CheckMultisampleQualityLevels(DXGI_FORMAT Format, UINT SampleCount, UINT *pNumQualityLevels)
{
	return m_device->CheckMultisampleQualityLevels( Format,  SampleCount, pNumQualityLevels);
}

void STDMETHODCALLTYPE xD3D11Device::CheckCounterInfo(D3D11_COUNTER_INFO *pCounterInfo)
{
	return m_device->CheckCounterInfo( pCounterInfo);
}

HRESULT STDMETHODCALLTYPE xD3D11Device::CheckCounter(const D3D11_COUNTER_DESC *pDesc, D3D11_COUNTER_TYPE *pType, UINT *pActiveCounters, LPSTR szName, UINT *pNameLength, LPSTR szUnits, UINT *pUnitsLength, LPSTR szDescription, UINT *pDescriptionLength)
{
	return m_device->CheckCounter( pDesc, pType, pActiveCounters, szName, pNameLength, szUnits, pUnitsLength, szDescription, pDescriptionLength);
}

HRESULT STDMETHODCALLTYPE xD3D11Device::CheckFeatureSupport(D3D11_FEATURE Feature, void *pFeatureSupportData, UINT FeatureSupportDataSize)
{
	return m_device->CheckFeatureSupport( Feature, pFeatureSupportData, FeatureSupportDataSize);
}

HRESULT STDMETHODCALLTYPE xD3D11Device::GetPrivateData(REFGUID guid, UINT *pDataSize, void *pData)
{
	return m_device->GetPrivateData( guid, pDataSize, pData);
}

HRESULT STDMETHODCALLTYPE xD3D11Device::SetPrivateData(REFGUID guid, UINT DataSize, const void *pData)
{
	return m_device->SetPrivateData( guid, DataSize, pData);
}

HRESULT STDMETHODCALLTYPE xD3D11Device::SetPrivateDataInterface(REFGUID guid, const IUnknown *pData)
{
	return m_device->SetPrivateDataInterface( guid,pData);
}

D3D_FEATURE_LEVEL STDMETHODCALLTYPE xD3D11Device::GetFeatureLevel(void)
{
	return m_device->GetFeatureLevel();
}

UINT STDMETHODCALLTYPE xD3D11Device::GetCreationFlags(void)
{
	return m_device->GetCreationFlags();
}

HRESULT STDMETHODCALLTYPE xD3D11Device::GetDeviceRemovedReason(void)
{
	return m_device->GetDeviceRemovedReason();
}

xD3D11DeviceContext* gcont = NULL;

void STDMETHODCALLTYPE xD3D11Device::GetImmediateContext(ID3D11DeviceContext **ppImmediateContext)
{
	ID3D11DeviceContext* cont11;
	m_device->GetImmediateContext(&cont11);

	if(!gcont)
	{
		gcont = new xD3D11DeviceContext(cont11);
	}

	*ppImmediateContext = gcont;
}

HRESULT STDMETHODCALLTYPE xD3D11Device::SetExceptionMode(UINT RaiseFlags)
{
	return m_device->SetExceptionMode(RaiseFlags);
}

UINT STDMETHODCALLTYPE xD3D11Device::GetExceptionMode(void)
{
	return m_device->GetExceptionMode();
}

HRESULT STDMETHODCALLTYPE xD3D11Device::QueryInterface(REFIID riid, void **ppvObject)
{
	return m_device->QueryInterface(riid, ppvObject);
}

ULONG STDMETHODCALLTYPE xD3D11Device::AddRef(void)
{
	return m_device->AddRef();
}

ULONG STDMETHODCALLTYPE xD3D11Device::Release(void)
{
	return m_device->Release();
}