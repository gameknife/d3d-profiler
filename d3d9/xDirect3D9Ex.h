#ifndef xDirect3D9Ex_h__
#define xDirect3D9Ex_h__

#include "xd3d9.h"
#include "xDirect3D9.h"

class xDirect3D9Ex : public xDirect3D9//, public IDirect3D9Ex
{
public:
	xDirect3D9Ex( UINT SDKVersion, LPDIRECT3DCREATE9EX func );
	~xDirect3D9Ex() {}
	virtual STDMETHODIMP_(UINT) GetAdapterModeCountEx( THIS_ UINT Adapter,CONST D3DDISPLAYMODEFILTER* pFilter );

	virtual STDMETHODIMP EnumAdapterModesEx( THIS_ UINT Adapter,CONST D3DDISPLAYMODEFILTER* pFilter,UINT Mode,D3DDISPLAYMODEEX* pMode );

	virtual STDMETHODIMP GetAdapterDisplayModeEx( THIS_ UINT Adapter,D3DDISPLAYMODEEX* pMode,D3DDISPLAYROTATION* pRotation );

	virtual STDMETHODIMP CreateDeviceEx( THIS_ UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,D3DDISPLAYMODEEX* pFullscreenDisplayMode,IDirect3DDevice9Ex** ppReturnedDeviceInterface );

	virtual STDMETHODIMP GetAdapterLUID( THIS_ UINT Adapter,LUID * pLUID );

	IDirect3D9Ex* m_apiEx;
};
#endif // xDirect3D9Ex_h__