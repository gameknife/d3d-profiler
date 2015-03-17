#include "xDirect3D9Ex.h"
#include "xDirect3DDevice9Ex.h"
#include "xAPICallMonitor.h"

STDMETHODIMP xDirect3D9Ex::EnumAdapterModesEx( THIS_ UINT Adapter,CONST D3DDISPLAYMODEFILTER* pFilter,UINT Mode,D3DDISPLAYMODEEX* pMode )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_apiEx->EnumAdapterModesEx( Adapter, pFilter, Mode, pMode );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3D9Ex::GetAdapterDisplayModeEx( THIS_ UINT Adapter,D3DDISPLAYMODEEX* pMode,D3DDISPLAYROTATION* pRotation )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_apiEx->GetAdapterDisplayModeEx( Adapter, pMode, pRotation );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3D9Ex::CreateDeviceEx( THIS_ UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,D3DDISPLAYMODEEX* pFullscreenDisplayMode,IDirect3DDevice9Ex** ppReturnedDeviceInterface )
{
	FUNC_ENTER; STDMETHODIMP hr;

	gEnv->hwnd = hFocusWindow;

	hr = m_apiEx->CreateDeviceEx( Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, pFullscreenDisplayMode, ppReturnedDeviceInterface );
	if (SUCCEEDED( hr ))
	{
		m_device = new xDirect3DDevice9Ex( *ppReturnedDeviceInterface );
		*ppReturnedDeviceInterface = reinterpret_cast<IDirect3DDevice9Ex*>(m_device);
		
		gEnv->width = pPresentationParameters->BackBufferWidth;
		gEnv->height = pPresentationParameters->BackBufferHeight;
	}

	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

STDMETHODIMP xDirect3D9Ex::GetAdapterLUID( THIS_ UINT Adapter,LUID * pLUID )
{
	FUNC_ENTER; STDMETHODIMP hr;
	hr = m_apiEx->GetAdapterLUID( Adapter, pLUID );
	CHECKCALL( hr, __FUNCTION__ ); return hr;
}

UINT xDirect3D9Ex::GetAdapterModeCountEx( THIS_ UINT Adapter,CONST D3DDISPLAYMODEFILTER* pFilter )
{
	UINT hr;
	hr = m_apiEx->GetAdapterModeCountEx( Adapter, pFilter );
	return hr;
}

xDirect3D9Ex::xDirect3D9Ex( UINT SDKVersion, LPDIRECT3DCREATE9EX func )
{
	HRESULT hr = func(SDKVersion, &m_apiEx);
	if (SUCCEEDED(hr))
	{
		m_api = m_apiEx;
	}
}
