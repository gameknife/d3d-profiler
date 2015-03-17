#ifndef xDirect3DDevice9_h__
#define xDirect3DDevice9_h__

#include "xd3d9.h"

class xDirect3DTexture9;
typedef std::map<uint32, xDirect3DTexture9*> xTextureLib;

class xDirect3DDevice9 : public IDirect3DDevice9
{
public:
	xDirect3DDevice9() { m_device = NULL; }
	xDirect3DDevice9( IDirect3DDevice9* realDevice );
	~xDirect3DDevice9() {}

	virtual STDMETHODIMP QueryInterface( THIS_ REFIID riid, void** ppvObj );

	virtual STDMETHODIMP_(ULONG) AddRef( THIS );

	virtual STDMETHODIMP_(ULONG) Release( THIS );

	virtual STDMETHODIMP TestCooperativeLevel( THIS );

	virtual STDMETHODIMP_(UINT) GetAvailableTextureMem( THIS );

	virtual STDMETHODIMP EvictManagedResources( THIS );

	virtual STDMETHODIMP GetDirect3D( THIS_ IDirect3D9** ppD3D9 );

	virtual STDMETHODIMP GetDeviceCaps( THIS_ D3DCAPS9* pCaps );

	virtual STDMETHODIMP GetDisplayMode( THIS_ UINT iSwapChain,D3DDISPLAYMODE* pMode );

	virtual STDMETHODIMP GetCreationParameters( THIS_ D3DDEVICE_CREATION_PARAMETERS *pParameters );

	virtual STDMETHODIMP SetCursorProperties( THIS_ UINT XHotSpot,UINT YHotSpot,IDirect3DSurface9* pCursorBitmap );

	virtual STDMETHODIMP_(void) SetCursorPosition( THIS_ int X,int Y,DWORD Flags );

	virtual STDMETHODIMP_(BOOL) ShowCursor( THIS_ BOOL bShow );

	virtual STDMETHODIMP CreateAdditionalSwapChain( THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DSwapChain9** pSwapChain );

	virtual STDMETHODIMP GetSwapChain( THIS_ UINT iSwapChain,IDirect3DSwapChain9** pSwapChain );

	virtual STDMETHODIMP_(UINT) GetNumberOfSwapChains( THIS );

	virtual STDMETHODIMP Reset( THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters );

	virtual STDMETHODIMP Present( THIS_ CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion );

	virtual STDMETHODIMP GetBackBuffer( THIS_ UINT iSwapChain,UINT iBackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface9** ppBackBuffer );

	virtual STDMETHODIMP GetRasterStatus( THIS_ UINT iSwapChain,D3DRASTER_STATUS* pRasterStatus );

	virtual STDMETHODIMP SetDialogBoxMode( THIS_ BOOL bEnableDialogs );

	virtual STDMETHODIMP_(void) SetGammaRamp( THIS_ UINT iSwapChain,DWORD Flags,CONST D3DGAMMARAMP* pRamp );

	virtual STDMETHODIMP_(void) GetGammaRamp( THIS_ UINT iSwapChain,D3DGAMMARAMP* pRamp );

	virtual STDMETHODIMP CreateTexture( THIS_ UINT Width,UINT Height,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DTexture9** ppTexture,HANDLE* pSharedHandle );

	virtual STDMETHODIMP CreateVolumeTexture( THIS_ UINT Width,UINT Height,UINT Depth,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DVolumeTexture9** ppVolumeTexture,HANDLE* pSharedHandle );

	virtual STDMETHODIMP CreateCubeTexture( THIS_ UINT EdgeLength,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DCubeTexture9** ppCubeTexture,HANDLE* pSharedHandle );

	virtual STDMETHODIMP CreateVertexBuffer( THIS_ UINT Length,DWORD Usage,DWORD FVF,D3DPOOL Pool,IDirect3DVertexBuffer9** ppVertexBuffer,HANDLE* pSharedHandle );

	virtual STDMETHODIMP CreateIndexBuffer( THIS_ UINT Length,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DIndexBuffer9** ppIndexBuffer,HANDLE* pSharedHandle );

	virtual STDMETHODIMP CreateRenderTarget( THIS_ UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Lockable,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle );

	virtual STDMETHODIMP CreateDepthStencilSurface( THIS_ UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Discard,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle );

	virtual STDMETHODIMP UpdateSurface( THIS_ IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestinationSurface,CONST POINT* pDestPoint );

	virtual STDMETHODIMP UpdateTexture( THIS_ IDirect3DBaseTexture9* pSourceTexture,IDirect3DBaseTexture9* pDestinationTexture );

	virtual STDMETHODIMP GetRenderTargetData( THIS_ IDirect3DSurface9* pRenderTarget,IDirect3DSurface9* pDestSurface );

	virtual STDMETHODIMP GetFrontBufferData( THIS_ UINT iSwapChain,IDirect3DSurface9* pDestSurface );

	virtual STDMETHODIMP StretchRect( THIS_ IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestSurface,CONST RECT* pDestRect,D3DTEXTUREFILTERTYPE Filter );

	virtual STDMETHODIMP ColorFill( THIS_ IDirect3DSurface9* pSurface,CONST RECT* pRect,D3DCOLOR color );

	virtual STDMETHODIMP CreateOffscreenPlainSurface( THIS_ UINT Width,UINT Height,D3DFORMAT Format,D3DPOOL Pool,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle );

	virtual STDMETHODIMP SetRenderTarget( THIS_ DWORD RenderTargetIndex,IDirect3DSurface9* pRenderTarget );

	virtual STDMETHODIMP GetRenderTarget( THIS_ DWORD RenderTargetIndex,IDirect3DSurface9** ppRenderTarget );

	virtual STDMETHODIMP SetDepthStencilSurface( THIS_ IDirect3DSurface9* pNewZStencil );

	virtual STDMETHODIMP GetDepthStencilSurface( THIS_ IDirect3DSurface9** ppZStencilSurface );

	virtual STDMETHODIMP BeginScene( THIS );

	virtual STDMETHODIMP EndScene( THIS );

	virtual STDMETHODIMP Clear( THIS_ DWORD Count,CONST D3DRECT* pRects,DWORD Flags,D3DCOLOR Color,float Z,DWORD Stencil );

	virtual STDMETHODIMP SetTransform( THIS_ D3DTRANSFORMSTATETYPE State,CONST D3DMATRIX* pMatrix );

	virtual STDMETHODIMP GetTransform( THIS_ D3DTRANSFORMSTATETYPE State,D3DMATRIX* pMatrix );

	virtual STDMETHODIMP MultiplyTransform( THIS_ D3DTRANSFORMSTATETYPE,CONST D3DMATRIX* );

	virtual STDMETHODIMP SetViewport( THIS_ CONST D3DVIEWPORT9* pViewport );

	virtual STDMETHODIMP GetViewport( THIS_ D3DVIEWPORT9* pViewport );

	virtual STDMETHODIMP SetMaterial( THIS_ CONST D3DMATERIAL9* pMaterial );

	virtual STDMETHODIMP GetMaterial( THIS_ D3DMATERIAL9* pMaterial );

	virtual STDMETHODIMP SetLight( THIS_ DWORD Index,CONST D3DLIGHT9* );

	virtual STDMETHODIMP GetLight( THIS_ DWORD Index,D3DLIGHT9* );

	virtual STDMETHODIMP LightEnable( THIS_ DWORD Index,BOOL Enable );

	virtual STDMETHODIMP GetLightEnable( THIS_ DWORD Index,BOOL* pEnable );

	virtual STDMETHODIMP SetClipPlane( THIS_ DWORD Index,CONST float* pPlane );

	virtual STDMETHODIMP GetClipPlane( THIS_ DWORD Index,float* pPlane );

	virtual STDMETHODIMP SetRenderState( THIS_ D3DRENDERSTATETYPE State,DWORD Value );

	virtual STDMETHODIMP GetRenderState( THIS_ D3DRENDERSTATETYPE State,DWORD* pValue );

	virtual STDMETHODIMP CreateStateBlock( THIS_ D3DSTATEBLOCKTYPE Type,IDirect3DStateBlock9** ppSB );

	virtual STDMETHODIMP BeginStateBlock( THIS );

	virtual STDMETHODIMP EndStateBlock( THIS_ IDirect3DStateBlock9** ppSB );

	virtual STDMETHODIMP SetClipStatus( THIS_ CONST D3DCLIPSTATUS9* pClipStatus );

	virtual STDMETHODIMP GetClipStatus( THIS_ D3DCLIPSTATUS9* pClipStatus );

	virtual STDMETHODIMP GetTexture( THIS_ DWORD Stage,IDirect3DBaseTexture9** ppTexture );

	virtual STDMETHODIMP SetTexture( THIS_ DWORD Stage,IDirect3DBaseTexture9* pTexture );

	virtual STDMETHODIMP GetTextureStageState( THIS_ DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD* pValue );

	virtual STDMETHODIMP SetTextureStageState( THIS_ DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD Value );

	virtual STDMETHODIMP GetSamplerState( THIS_ DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD* pValue );

	virtual STDMETHODIMP SetSamplerState( THIS_ DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD Value );

	virtual STDMETHODIMP ValidateDevice( THIS_ DWORD* pNumPasses );

	virtual STDMETHODIMP SetPaletteEntries( THIS_ UINT PaletteNumber,CONST PALETTEENTRY* pEntries );

	virtual STDMETHODIMP GetPaletteEntries( THIS_ UINT PaletteNumber,PALETTEENTRY* pEntries );

	virtual STDMETHODIMP SetCurrentTexturePalette( THIS_ UINT PaletteNumber );

	virtual STDMETHODIMP GetCurrentTexturePalette( THIS_ UINT *PaletteNumber );

	virtual STDMETHODIMP SetScissorRect( THIS_ CONST RECT* pRect );

	virtual STDMETHODIMP GetScissorRect( THIS_ RECT* pRect );

	virtual STDMETHODIMP SetSoftwareVertexProcessing( THIS_ BOOL bSoftware );

	virtual STDMETHODIMP_(BOOL) GetSoftwareVertexProcessing( THIS );

	virtual STDMETHODIMP SetNPatchMode( THIS_ float nSegments );

	virtual STDMETHODIMP_(float) GetNPatchMode( THIS );

	virtual STDMETHODIMP DrawPrimitive( THIS_ D3DPRIMITIVETYPE PrimitiveType,UINT StartVertex,UINT PrimitiveCount );

	virtual STDMETHODIMP DrawIndexedPrimitive( THIS_ D3DPRIMITIVETYPE,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount );

	virtual STDMETHODIMP DrawPrimitiveUP( THIS_ D3DPRIMITIVETYPE PrimitiveType,UINT PrimitiveCount,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride );

	virtual STDMETHODIMP DrawIndexedPrimitiveUP( THIS_ D3DPRIMITIVETYPE PrimitiveType,UINT MinVertexIndex,UINT NumVertices,UINT PrimitiveCount,CONST void* pIndexData,D3DFORMAT IndexDataFormat,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride );

	virtual STDMETHODIMP ProcessVertices( THIS_ UINT SrcStartIndex,UINT DestIndex,UINT VertexCount,IDirect3DVertexBuffer9* pDestBuffer,IDirect3DVertexDeclaration9* pVertexDecl,DWORD Flags );

	virtual STDMETHODIMP CreateVertexDeclaration( THIS_ CONST D3DVERTEXELEMENT9* pVertexElements,IDirect3DVertexDeclaration9** ppDecl );

	virtual STDMETHODIMP SetVertexDeclaration( THIS_ IDirect3DVertexDeclaration9* pDecl );

	virtual STDMETHODIMP GetVertexDeclaration( THIS_ IDirect3DVertexDeclaration9** ppDecl );

	virtual STDMETHODIMP SetFVF( THIS_ DWORD FVF );

	virtual STDMETHODIMP GetFVF( THIS_ DWORD* pFVF );

	virtual STDMETHODIMP CreateVertexShader( THIS_ CONST DWORD* pFunction,IDirect3DVertexShader9** ppShader );

	virtual STDMETHODIMP SetVertexShader( THIS_ IDirect3DVertexShader9* pShader );

	virtual STDMETHODIMP GetVertexShader( THIS_ IDirect3DVertexShader9** ppShader );

	virtual STDMETHODIMP SetVertexShaderConstantF( THIS_ UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount );

	virtual STDMETHODIMP GetVertexShaderConstantF( THIS_ UINT StartRegister,float* pConstantData,UINT Vector4fCount );

	virtual STDMETHODIMP SetVertexShaderConstantI( THIS_ UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount );

	virtual STDMETHODIMP GetVertexShaderConstantI( THIS_ UINT StartRegister,int* pConstantData,UINT Vector4iCount );

	virtual STDMETHODIMP SetVertexShaderConstantB( THIS_ UINT StartRegister,CONST BOOL* pConstantData,UINT BoolCount );

	virtual STDMETHODIMP GetVertexShaderConstantB( THIS_ UINT StartRegister,BOOL* pConstantData,UINT BoolCount );

	virtual STDMETHODIMP SetStreamSource( THIS_ UINT StreamNumber,IDirect3DVertexBuffer9* pStreamData,UINT OffsetInBytes,UINT Stride );

	virtual STDMETHODIMP GetStreamSource( THIS_ UINT StreamNumber,IDirect3DVertexBuffer9** ppStreamData,UINT* pOffsetInBytes,UINT* pStride );

	virtual STDMETHODIMP SetStreamSourceFreq( THIS_ UINT StreamNumber,UINT Setting );

	virtual STDMETHODIMP GetStreamSourceFreq( THIS_ UINT StreamNumber,UINT* pSetting );

	virtual STDMETHODIMP SetIndices( THIS_ IDirect3DIndexBuffer9* pIndexData );

	virtual STDMETHODIMP GetIndices( THIS_ IDirect3DIndexBuffer9** ppIndexData );

	virtual STDMETHODIMP CreatePixelShader( THIS_ CONST DWORD* pFunction,IDirect3DPixelShader9** ppShader );

	virtual STDMETHODIMP SetPixelShader( THIS_ IDirect3DPixelShader9* pShader );

	virtual STDMETHODIMP GetPixelShader( THIS_ IDirect3DPixelShader9** ppShader );

	virtual STDMETHODIMP SetPixelShaderConstantF( THIS_ UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount );

	virtual STDMETHODIMP GetPixelShaderConstantF( THIS_ UINT StartRegister,float* pConstantData,UINT Vector4fCount );

	virtual STDMETHODIMP SetPixelShaderConstantI( THIS_ UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount );

	virtual STDMETHODIMP GetPixelShaderConstantI( THIS_ UINT StartRegister,int* pConstantData,UINT Vector4iCount );

	virtual STDMETHODIMP SetPixelShaderConstantB( THIS_ UINT StartRegister,CONST BOOL* pConstantData,UINT BoolCount );

	virtual STDMETHODIMP GetPixelShaderConstantB( THIS_ UINT StartRegister,BOOL* pConstantData,UINT BoolCount );

	virtual STDMETHODIMP DrawRectPatch( THIS_ UINT Handle,CONST float* pNumSegs,CONST D3DRECTPATCH_INFO* pRectPatchInfo );

	virtual STDMETHODIMP DrawTriPatch( THIS_ UINT Handle,CONST float* pNumSegs,CONST D3DTRIPATCH_INFO* pTriPatchInfo );

	virtual STDMETHODIMP DeletePatch( THIS_ UINT Handle );

	virtual STDMETHODIMP CreateQuery( THIS_ D3DQUERYTYPE Type,IDirect3DQuery9** ppQuery );

public:
	IDirect3DDevice9* m_device;

	xDirect3DVertexBuffer9* prevVB;
	uint32 prevStride;
	xDirect3DIndexBuffer9* prevIB;

	xDirect3DVertexDeclaration9* prevDecl;

	xDirect3DTexture9* m_texUnit[8];

};

#endif // xDirect3DDevice9_h__