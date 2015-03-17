#include "xD3D11DeviceContext.h"

void STDMETHODCALLTYPE xD3D11DeviceContext::VSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer *const *ppConstantBuffers)
{
	return m_device->VSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::PSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView *const *ppShaderResourceViews)
{
	return m_device->PSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::PSSetShader(ID3D11PixelShader *pPixelShader, ID3D11ClassInstance *const *ppClassInstances, UINT NumClassInstances)
{
	return m_device->PSSetShader(pPixelShader, ppClassInstances, NumClassInstances);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::PSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState *const *ppSamplers)
{
	return m_device->PSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::VSSetShader(ID3D11VertexShader *pVertexShader, ID3D11ClassInstance *const *ppClassInstances, UINT NumClassInstances)
{
	return m_device->VSSetShader(pVertexShader, ppClassInstances, NumClassInstances);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::DrawIndexed(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation)
{
	return m_device->DrawIndexed(IndexCount, StartIndexLocation, BaseVertexLocation);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::Draw(UINT VertexCount, UINT StartVertexLocation)
{
	return m_device->Draw(VertexCount, StartVertexLocation);
}

HRESULT STDMETHODCALLTYPE xD3D11DeviceContext::Map(ID3D11Resource *pResource, UINT Subresource, D3D11_MAP MapType, UINT MapFlags, D3D11_MAPPED_SUBRESOURCE *pMappedResource)
{
	return m_device->Map(pResource, Subresource, MapType, MapFlags, pMappedResource);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::Unmap(ID3D11Resource *pResource, UINT Subresource)
{
	return m_device->Unmap(pResource, Subresource);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::PSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer *const *ppConstantBuffers)
{
	return m_device->PSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::IASetInputLayout(ID3D11InputLayout *pInputLayout)
{
	return m_device->IASetInputLayout(pInputLayout);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::IASetVertexBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer *const *ppVertexBuffers, const UINT *pStrides, const UINT *pOffsets)
{
	return m_device->IASetVertexBuffers(StartSlot, NumBuffers, ppVertexBuffers, pStrides, pOffsets);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::IASetIndexBuffer(ID3D11Buffer *pIndexBuffer, DXGI_FORMAT Format, UINT Offset)
{
	return m_device->IASetIndexBuffer( pIndexBuffer, Format, Offset);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::DrawIndexedInstanced(UINT IndexCountPerInstance, UINT InstanceCount, UINT StartIndexLocation, INT BaseVertexLocation, UINT StartInstanceLocation)
{
	return m_device->DrawIndexedInstanced(IndexCountPerInstance, InstanceCount, StartIndexLocation, BaseVertexLocation, StartInstanceLocation);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::DrawInstanced(UINT VertexCountPerInstance, UINT InstanceCount, UINT StartVertexLocation, UINT StartInstanceLocation)
{
	return m_device->DrawInstanced(VertexCountPerInstance, InstanceCount, StartVertexLocation, StartInstanceLocation);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::GSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer *const *ppConstantBuffers)
{
	return m_device->GSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::GSSetShader(ID3D11GeometryShader *pShader, ID3D11ClassInstance *const *ppClassInstances, UINT NumClassInstances)
{
	return m_device->GSSetShader( pShader, ppClassInstances, NumClassInstances);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology)
{
	return m_device->IASetPrimitiveTopology(Topology);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::VSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView *const *ppShaderResourceViews)
{
	return m_device->VSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::VSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState *const *ppSamplers)
{
	return m_device->VSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::Begin(ID3D11Asynchronous *pAsync)
{
	return m_device->Begin( pAsync);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::End(ID3D11Asynchronous *pAsync)
{
	return m_device->End( pAsync);
}

HRESULT STDMETHODCALLTYPE xD3D11DeviceContext::GetData(ID3D11Asynchronous *pAsync, void *pData, UINT DataSize, UINT GetDataFlags)
{
	return m_device->GetData( pAsync, pData, DataSize, GetDataFlags);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::SetPredication(ID3D11Predicate *pPredicate, BOOL PredicateValue)
{
	return m_device->SetPredication(pPredicate, PredicateValue);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::GSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView *const *ppShaderResourceViews)
{
	return m_device->GSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::GSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState *const *ppSamplers)
{
	return m_device->GSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::OMSetRenderTargets(UINT NumViews, ID3D11RenderTargetView *const *ppRenderTargetViews, ID3D11DepthStencilView *pDepthStencilView)
{
	return m_device->OMSetRenderTargets(NumViews, ppRenderTargetViews, pDepthStencilView);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::OMSetRenderTargetsAndUnorderedAccessViews(UINT NumRTVs, ID3D11RenderTargetView *const *ppRenderTargetViews, ID3D11DepthStencilView *pDepthStencilView, UINT UAVStartSlot, UINT NumUAVs, ID3D11UnorderedAccessView *const *ppUnorderedAccessViews, const UINT *pUAVInitialCounts)
{
	return m_device->OMSetRenderTargetsAndUnorderedAccessViews(NumRTVs, ppRenderTargetViews, pDepthStencilView, UAVStartSlot, NumUAVs, ppUnorderedAccessViews, pUAVInitialCounts);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::OMSetBlendState(ID3D11BlendState *pBlendState, const FLOAT BlendFactor[ 4 ], UINT SampleMask)
{
	return m_device->OMSetBlendState(pBlendState, BlendFactor, SampleMask);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::OMSetDepthStencilState(ID3D11DepthStencilState *pDepthStencilState, UINT StencilRef)
{
	return m_device->OMSetDepthStencilState( pDepthStencilState, StencilRef);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::SOSetTargets(UINT NumBuffers, ID3D11Buffer *const *ppSOTargets, const UINT *pOffsets)
{
	return m_device->SOSetTargets(NumBuffers, ppSOTargets, pOffsets);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::DrawAuto(void)
{
	return m_device->DrawAuto();
}

void STDMETHODCALLTYPE xD3D11DeviceContext::DrawIndexedInstancedIndirect(ID3D11Buffer *pBufferForArgs, UINT AlignedByteOffsetForArgs)
{
	return m_device->DrawIndexedInstancedIndirect(pBufferForArgs, AlignedByteOffsetForArgs);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::DrawInstancedIndirect(ID3D11Buffer *pBufferForArgs, UINT AlignedByteOffsetForArgs)
{
	return m_device->DrawInstancedIndirect(pBufferForArgs, AlignedByteOffsetForArgs);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::Dispatch(UINT ThreadGroupCountX, UINT ThreadGroupCountY, UINT ThreadGroupCountZ)
{
	return m_device->Dispatch(ThreadGroupCountX, ThreadGroupCountY, ThreadGroupCountZ);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::DispatchIndirect(ID3D11Buffer *pBufferForArgs, UINT AlignedByteOffsetForArgs)
{
	return m_device->DispatchIndirect(pBufferForArgs, AlignedByteOffsetForArgs);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::RSSetState(ID3D11RasterizerState *pRasterizerState)
{
	return m_device->RSSetState(pRasterizerState);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::RSSetViewports(UINT NumViewports, const D3D11_VIEWPORT *pViewports)
{
	return m_device->RSSetViewports(NumViewports, pViewports);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::RSSetScissorRects(UINT NumRects, const D3D11_RECT *pRects)
{
	return m_device->RSSetScissorRects(NumRects, pRects);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::CopySubresourceRegion(ID3D11Resource *pDstResource, UINT DstSubresource, UINT DstX, UINT DstY, UINT DstZ, ID3D11Resource *pSrcResource, UINT SrcSubresource, const D3D11_BOX *pSrcBox)
{
	return m_device->CopySubresourceRegion(pDstResource, DstSubresource, DstX, DstY, DstZ, pSrcResource, SrcSubresource, pSrcBox);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::CopyResource(ID3D11Resource *pDstResource, ID3D11Resource *pSrcResource)
{
	return m_device->CopyResource(pDstResource, pSrcResource);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::UpdateSubresource(ID3D11Resource *pDstResource, UINT DstSubresource, const D3D11_BOX *pDstBox, const void *pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch)
{
	return m_device->UpdateSubresource(pDstResource, DstSubresource, pDstBox, pSrcData, SrcRowPitch, SrcDepthPitch);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::CopyStructureCount(ID3D11Buffer *pDstBuffer, UINT DstAlignedByteOffset, ID3D11UnorderedAccessView *pSrcView)
{
	return m_device->CopyStructureCount(pDstBuffer, DstAlignedByteOffset, pSrcView);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::ClearRenderTargetView(ID3D11RenderTargetView *pRenderTargetView, const FLOAT ColorRGBA[ 4 ])
{
	return m_device->ClearRenderTargetView( pRenderTargetView, ColorRGBA);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::ClearUnorderedAccessViewUint(ID3D11UnorderedAccessView *pUnorderedAccessView, const UINT Values[ 4 ])
{
	return m_device->ClearUnorderedAccessViewUint(pUnorderedAccessView, Values);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::ClearUnorderedAccessViewFloat(ID3D11UnorderedAccessView *pUnorderedAccessView, const FLOAT Values[ 4 ])
{
	return m_device->ClearUnorderedAccessViewFloat(pUnorderedAccessView, Values);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::ClearDepthStencilView(ID3D11DepthStencilView *pDepthStencilView, UINT ClearFlags, FLOAT Depth, UINT8 Stencil)
{
	return m_device->ClearDepthStencilView(pDepthStencilView, ClearFlags, Depth, Stencil);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::GenerateMips(ID3D11ShaderResourceView *pShaderResourceView)
{
	return m_device->GenerateMips(pShaderResourceView);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::SetResourceMinLOD(ID3D11Resource *pResource, FLOAT MinLOD)
{
	return m_device->SetResourceMinLOD(pResource, MinLOD);
}

FLOAT STDMETHODCALLTYPE xD3D11DeviceContext::GetResourceMinLOD(ID3D11Resource *pResource)
{
	return m_device->GetResourceMinLOD(pResource);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::ResolveSubresource(ID3D11Resource *pDstResource, UINT DstSubresource, ID3D11Resource *pSrcResource, UINT SrcSubresource, DXGI_FORMAT Format)
{
	return m_device->ResolveSubresource(pDstResource, DstSubresource, pSrcResource, SrcSubresource, Format);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::ExecuteCommandList(ID3D11CommandList *pCommandList, BOOL RestoreContextState)
{
	return m_device->ExecuteCommandList(pCommandList, RestoreContextState);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::HSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView *const *ppShaderResourceViews)
{
	return m_device->HSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::HSSetShader(ID3D11HullShader *pHullShader, ID3D11ClassInstance *const *ppClassInstances, UINT NumClassInstances)
{
	return m_device->HSSetShader(pHullShader, ppClassInstances, NumClassInstances);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::HSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState *const *ppSamplers)
{
	return m_device->HSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::HSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer *const *ppConstantBuffers)
{
	return m_device->HSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::DSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView *const *ppShaderResourceViews)
{
	return m_device->DSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::DSSetShader(ID3D11DomainShader *pDomainShader, ID3D11ClassInstance *const *ppClassInstances, UINT NumClassInstances)
{
	return m_device->DSSetShader(pDomainShader, ppClassInstances, NumClassInstances);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::DSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState *const *ppSamplers)
{
	return m_device->DSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::DSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer *const *ppConstantBuffers)
{
	return m_device->DSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::CSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView *const *ppShaderResourceViews)
{
	return m_device->CSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::CSSetUnorderedAccessViews(UINT StartSlot, UINT NumUAVs, ID3D11UnorderedAccessView *const *ppUnorderedAccessViews, const UINT *pUAVInitialCounts)
{
	return m_device->CSSetUnorderedAccessViews(StartSlot, NumUAVs, ppUnorderedAccessViews, pUAVInitialCounts);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::CSSetShader(ID3D11ComputeShader *pComputeShader, ID3D11ClassInstance *const *ppClassInstances, UINT NumClassInstances)
{
	return m_device->CSSetShader(pComputeShader, ppClassInstances, NumClassInstances);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::CSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState *const *ppSamplers)
{
	return m_device->CSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::CSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer *const *ppConstantBuffers)
{
	return m_device->CSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::VSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer **ppConstantBuffers)
{
	return m_device->VSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::PSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView **ppShaderResourceViews)
{
	return m_device->PSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::PSGetShader(ID3D11PixelShader **ppPixelShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances)
{
	return m_device->PSGetShader(ppPixelShader, ppClassInstances, pNumClassInstances);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::PSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState **ppSamplers)
{
	return m_device->PSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::VSGetShader(ID3D11VertexShader **ppVertexShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances)
{
	return m_device->VSGetShader( ppVertexShader, ppClassInstances, pNumClassInstances);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::PSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer **ppConstantBuffers)
{
	return m_device->PSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::IAGetInputLayout(ID3D11InputLayout **ppInputLayout)
{
	return m_device->IAGetInputLayout(ppInputLayout);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::IAGetVertexBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer **ppVertexBuffers, UINT *pStrides, UINT *pOffsets)
{
	return m_device->IAGetVertexBuffers(StartSlot, NumBuffers, ppVertexBuffers, pStrides, pOffsets);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::IAGetIndexBuffer(ID3D11Buffer **pIndexBuffer, DXGI_FORMAT *Format, UINT *Offset)
{
	return m_device->IAGetIndexBuffer(pIndexBuffer,  Format, Offset);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::GSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer **ppConstantBuffers)
{
	return m_device->GSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::GSGetShader(ID3D11GeometryShader **ppGeometryShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances)
{
	return m_device->GSGetShader( ppGeometryShader, ppClassInstances, pNumClassInstances);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::IAGetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY *pTopology)
{
	return m_device->IAGetPrimitiveTopology( pTopology);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::VSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView **ppShaderResourceViews)
{
	return m_device->VSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::VSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState **ppSamplers)
{
	return m_device->VSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::GetPredication(ID3D11Predicate **ppPredicate, BOOL *pPredicateValue)
{
	return m_device->GetPredication(ppPredicate, pPredicateValue);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::GSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView **ppShaderResourceViews)
{
	return m_device->GSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::GSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState **ppSamplers)
{
	return m_device->GSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::OMGetRenderTargets(UINT NumViews, ID3D11RenderTargetView **ppRenderTargetViews, ID3D11DepthStencilView **ppDepthStencilView)
{
	return m_device->OMGetRenderTargets(NumViews, ppRenderTargetViews, ppDepthStencilView);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::OMGetRenderTargetsAndUnorderedAccessViews(UINT NumRTVs, ID3D11RenderTargetView **ppRenderTargetViews, ID3D11DepthStencilView **ppDepthStencilView, UINT UAVStartSlot, UINT NumUAVs, ID3D11UnorderedAccessView **ppUnorderedAccessViews)
{
	return m_device->OMGetRenderTargetsAndUnorderedAccessViews(NumRTVs, ppRenderTargetViews, ppDepthStencilView, UAVStartSlot, NumUAVs, ppUnorderedAccessViews);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::OMGetBlendState(ID3D11BlendState **ppBlendState, FLOAT BlendFactor[ 4 ], UINT *pSampleMask)
{
	return m_device->OMGetBlendState(ppBlendState, BlendFactor, pSampleMask);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::OMGetDepthStencilState(ID3D11DepthStencilState **ppDepthStencilState, UINT *pStencilRef)
{
	return m_device->OMGetDepthStencilState(ppDepthStencilState, pStencilRef);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::SOGetTargets(UINT NumBuffers, ID3D11Buffer **ppSOTargets)
{
	return m_device->SOGetTargets(NumBuffers, ppSOTargets);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::RSGetState(ID3D11RasterizerState **ppRasterizerState)
{
	return m_device->RSGetState(ppRasterizerState);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::RSGetViewports(UINT *pNumViewports, D3D11_VIEWPORT *pViewports)
{
	return m_device->RSGetViewports(pNumViewports, pViewports);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::RSGetScissorRects(UINT *pNumRects, D3D11_RECT *pRects)
{
	return m_device->RSGetScissorRects(pNumRects, pRects);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::HSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView **ppShaderResourceViews)
{
	return m_device->HSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::HSGetShader(ID3D11HullShader **ppHullShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances)
{
	return m_device->HSGetShader(ppHullShader, ppClassInstances, pNumClassInstances);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::HSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState **ppSamplers)
{
	return m_device->HSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::HSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer **ppConstantBuffers)
{
	return m_device->HSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::DSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView **ppShaderResourceViews)
{
	return m_device->DSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::DSGetShader(ID3D11DomainShader **ppDomainShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances)
{
	return m_device->DSGetShader(ppDomainShader, ppClassInstances, pNumClassInstances);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::DSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState **ppSamplers)
{
	return m_device->DSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::DSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer **ppConstantBuffers)
{
	return m_device->DSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::CSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView **ppShaderResourceViews)
{
	return m_device->CSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::CSGetUnorderedAccessViews(UINT StartSlot, UINT NumUAVs, ID3D11UnorderedAccessView **ppUnorderedAccessViews)
{
	return m_device->CSGetUnorderedAccessViews(StartSlot, NumUAVs, ppUnorderedAccessViews);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::CSGetShader(ID3D11ComputeShader **ppComputeShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances)
{
	return m_device->CSGetShader( ppComputeShader, ppClassInstances, pNumClassInstances);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::CSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState **ppSamplers)
{
	return m_device->CSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::CSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer **ppConstantBuffers)
{
	return m_device->CSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void STDMETHODCALLTYPE xD3D11DeviceContext::ClearState(void)
{
	return m_device->ClearState();
}

void STDMETHODCALLTYPE xD3D11DeviceContext::Flush(void)
{
	return m_device->Flush();
}

D3D11_DEVICE_CONTEXT_TYPE STDMETHODCALLTYPE xD3D11DeviceContext::GetType(void)
{
	return m_device->GetType();
}

UINT STDMETHODCALLTYPE xD3D11DeviceContext::GetContextFlags(void)
{
	return m_device->GetContextFlags();
}

HRESULT STDMETHODCALLTYPE xD3D11DeviceContext::FinishCommandList(BOOL RestoreDeferredContextState, ID3D11CommandList **ppCommandList)
{
	return m_device->FinishCommandList(RestoreDeferredContextState, ppCommandList);
}

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

HRESULT STDMETHODCALLTYPE xD3D11DeviceContext::SetPrivateData(REFGUID Name, UINT DataSize, const void *pData)
{
	return m_device->SetPrivateData(Name, DataSize, pData);
}

HRESULT STDMETHODCALLTYPE xD3D11DeviceContext::SetPrivateDataInterface(REFGUID Name, const IUnknown *pUnknown)
{
	return m_device->SetPrivateDataInterface(Name, pUnknown);
}

HRESULT STDMETHODCALLTYPE xD3D11DeviceContext::GetPrivateData(REFGUID Name, UINT *pDataSize, void *pData)
{
	return m_device->GetPrivateData(Name, pDataSize, pData);
}

HRESULT STDMETHODCALLTYPE xD3D11DeviceContext::QueryInterface(REFIID riid, void **ppvObject)
{
	return m_device->QueryInterface(riid, ppvObject);
}

ULONG STDMETHODCALLTYPE xD3D11DeviceContext::AddRef(void)
{
	return m_device->AddRef();
}

ULONG STDMETHODCALLTYPE xD3D11DeviceContext::Release(void)
{
	return m_device->Release();
}

void STDMETHODCALLTYPE xD3D11DeviceContext::GetDevice(ID3D11Device **ppDevice)
{
	m_device->GetDevice(ppDevice);
}

