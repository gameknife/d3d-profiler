#ifndef xDirect3DDevice9Ex_h__
#define xDirect3DDevice9Ex_h__

#include "xd3d9.h"
#include "xDirect3DDevice9.h"

class xDirect3DDevice9Ex : public xDirect3DDevice9
{
public:

	xDirect3DDevice9Ex( IDirect3DDevice9Ex* realDevice );
	~xDirect3DDevice9Ex() {}

	virtual STDMETHODIMP SetConvolutionMonoKernel( THIS_ UINT width,UINT height,float* rows,float* columns );

	virtual STDMETHODIMP ComposeRects( THIS_ IDirect3DSurface9* pSrc,IDirect3DSurface9* pDst,IDirect3DVertexBuffer9* pSrcRectDescs,UINT NumRects,IDirect3DVertexBuffer9* pDstRectDescs,D3DCOMPOSERECTSOP Operation,int Xoffset,int Yoffset );

	virtual STDMETHODIMP PresentEx( THIS_ CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion,DWORD dwFlags );

	virtual STDMETHODIMP GetGPUThreadPriority( THIS_ INT* pPriority );

	virtual STDMETHODIMP SetGPUThreadPriority( THIS_ INT Priority );

	virtual STDMETHODIMP WaitForVBlank( THIS_ UINT iSwapChain );

	virtual STDMETHODIMP CheckResourceResidency( THIS_ IDirect3DResource9** pResourceArray,UINT32 NumResources );

	virtual STDMETHODIMP SetMaximumFrameLatency( THIS_ UINT MaxLatency );

	virtual STDMETHODIMP GetMaximumFrameLatency( THIS_ UINT* pMaxLatency );

	virtual STDMETHODIMP CheckDeviceState( THIS_ HWND hDestinationWindow );

	virtual STDMETHODIMP CreateRenderTargetEx( THIS_ UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Lockable,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle,DWORD Usage );

	virtual STDMETHODIMP CreateOffscreenPlainSurfaceEx( THIS_ UINT Width,UINT Height,D3DFORMAT Format,D3DPOOL Pool,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle,DWORD Usage );

	virtual STDMETHODIMP CreateDepthStencilSurfaceEx( THIS_ UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Discard,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle,DWORD Usage );

	virtual STDMETHODIMP ResetEx( THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters,D3DDISPLAYMODEEX *pFullscreenDisplayMode );

	virtual STDMETHODIMP GetDisplayModeEx( THIS_ UINT iSwapChain,D3DDISPLAYMODEEX* pMode,D3DDISPLAYROTATION* pRotation );


	IDirect3DDevice9Ex* m_deviceEx;

};
#endif // xDirect3DDevice9Ex_h__