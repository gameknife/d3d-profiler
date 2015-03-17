#include "xDirect3D9.h"
#include "xDirect3DDevice9.h"
#include "xAPICallMonitor.h"

STDMETHODIMP xDirect3D9::QueryInterface( THIS_ REFIID riid, void** ppvObj )
{
	STDMETHODIMP hr;
	hr = m_api->QueryInterface( riid, ppvObj );
	return hr;
}

STDMETHODIMP xDirect3D9::RegisterSoftwareDevice( THIS_ void* pInitializeFunction )
{
	STDMETHODIMP hr;
	hr = m_api->RegisterSoftwareDevice( pInitializeFunction );
	CHECKCALL( hr, __FUNCTION__ );return hr;
}

STDMETHODIMP xDirect3D9::GetAdapterIdentifier( THIS_ UINT Adapter,DWORD Flags,D3DADAPTER_IDENTIFIER9* pIdentifier )
{
	STDMETHODIMP hr;
	hr = m_api->GetAdapterIdentifier(Adapter, Flags, pIdentifier );
	CHECKCALL( hr, __FUNCTION__ );return hr;
}

STDMETHODIMP xDirect3D9::EnumAdapterModes( THIS_ UINT Adapter,D3DFORMAT Format,UINT Mode,D3DDISPLAYMODE* pMode )
{
	STDMETHODIMP hr;
	hr = m_api->EnumAdapterModes( Adapter, Format, Mode, pMode );
	CHECKCALL( hr, __FUNCTION__ );return hr;
}

STDMETHODIMP xDirect3D9::GetAdapterDisplayMode( THIS_ UINT Adapter,D3DDISPLAYMODE* pMode )
{
	STDMETHODIMP hr;
	hr = m_api->GetAdapterDisplayMode( Adapter, pMode );
	CHECKCALL( hr, __FUNCTION__ );return hr;
}

STDMETHODIMP xDirect3D9::CheckDeviceType( THIS_ UINT Adapter,D3DDEVTYPE DevType,D3DFORMAT AdapterFormat,D3DFORMAT BackBufferFormat,BOOL bWindowed )
{
	STDMETHODIMP hr;
	hr = m_api->CheckDeviceType( Adapter, DevType, AdapterFormat, BackBufferFormat, bWindowed );
	CHECKCALL( hr, __FUNCTION__ );return hr;
}

STDMETHODIMP xDirect3D9::CheckDeviceFormat( THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,DWORD Usage,D3DRESOURCETYPE RType,D3DFORMAT CheckFormat )
{
	STDMETHODIMP hr;
	hr = m_api->CheckDeviceFormat(  Adapter, DeviceType, AdapterFormat, Usage, RType, CheckFormat );
	CHECKCALL( hr, __FUNCTION__ );return hr;
}

STDMETHODIMP xDirect3D9::CheckDeviceMultiSampleType( THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SurfaceFormat,BOOL Windowed,D3DMULTISAMPLE_TYPE MultiSampleType,DWORD* pQualityLevels )
{
	STDMETHODIMP hr;
	hr = m_api->CheckDeviceMultiSampleType(  Adapter, DeviceType, SurfaceFormat, Windowed, MultiSampleType, pQualityLevels );
	CHECKCALL( hr, __FUNCTION__ );return hr;
}

STDMETHODIMP xDirect3D9::CheckDepthStencilMatch( THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,D3DFORMAT RenderTargetFormat,D3DFORMAT DepthStencilFormat )
{
	STDMETHODIMP hr;
	hr = m_api->CheckDepthStencilMatch( Adapter, DeviceType, AdapterFormat, RenderTargetFormat, DepthStencilFormat );
	CHECKCALL( hr, __FUNCTION__ );return hr;
}

STDMETHODIMP xDirect3D9::CheckDeviceFormatConversion( THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SourceFormat,D3DFORMAT TargetFormat )
{
	STDMETHODIMP hr;
	hr = m_api->CheckDeviceFormatConversion(  Adapter, DeviceType, SourceFormat, TargetFormat );
	CHECKCALL( hr, __FUNCTION__ );return hr;
}

STDMETHODIMP xDirect3D9::GetDeviceCaps( THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DCAPS9* pCaps )
{
	STDMETHODIMP hr;
	hr = m_api->GetDeviceCaps(   Adapter, DeviceType, pCaps );
	CHECKCALL( hr, __FUNCTION__ );return hr;
}

UINT xDirect3D9::GetAdapterModeCount( THIS_ UINT Adapter,D3DFORMAT Format )
{
	UINT hr;
	hr = m_api->GetAdapterModeCount( Adapter, Format );
	return hr;
}

UINT xDirect3D9::GetAdapterCount()
{
	UINT hr;
	hr = m_api->GetAdapterCount();
	return hr;
}

ULONG xDirect3D9::Release()
{
	ULONG hr;
	hr = m_api->Release();
	return hr;
}

ULONG xDirect3D9::AddRef()
{
	ULONG hr;
	hr = m_api->AddRef();
	return hr;
}

xDirect3D9::xDirect3D9( UINT SDKVersion, LPDIRECT3DCREATE9 func )
{
	m_api = func(SDKVersion);
}

xDirect3D9::~xDirect3D9( void )
{
	
}

STDMETHODIMP xDirect3D9::CreateDevice( THIS_ UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DDevice9** ppReturnedDeviceInterface )
{
	STDMETHODIMP hr;
	IDirect3DDevice9* realDevice;

	gEnv->hwnd = hFocusWindow;

	hr = m_api->CreateDevice( Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, &realDevice );

	m_device = new xDirect3DDevice9( realDevice );
	*ppReturnedDeviceInterface = m_device;	

	gEnv->width = pPresentationParameters->BackBufferWidth;
	gEnv->height = pPresentationParameters->BackBufferHeight;

	CHECKCALL( hr, __FUNCTION__ );
	return hr;
}

HMONITOR xDirect3D9::GetAdapterMonitor( THIS_ UINT Adapter )
{
	HMONITOR hr;
	hr = m_api->GetAdapterMonitor( Adapter );
	return hr;
}
