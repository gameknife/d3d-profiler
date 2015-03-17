#ifndef xDirect3D9_h_
#define xDirect3D9_h_

#include "xd3d9.h"

class xDirect3D9 : public IDirect3D9
{
public:
	xDirect3D9() {m_api = NULL;}
	xDirect3D9(UINT SDKVersion, LPDIRECT3DCREATE9 func );
	~xDirect3D9(void);

	virtual STDMETHODIMP QueryInterface( THIS_ REFIID riid, void** ppvObj );

	virtual STDMETHODIMP_(ULONG) AddRef( THIS );

	virtual STDMETHODIMP_(ULONG) Release( THIS );

	virtual STDMETHODIMP RegisterSoftwareDevice( THIS_ void* pInitializeFunction );

	virtual STDMETHODIMP_(UINT) GetAdapterCount( THIS );

	virtual STDMETHODIMP GetAdapterIdentifier( THIS_ UINT Adapter,DWORD Flags,D3DADAPTER_IDENTIFIER9* pIdentifier );

	virtual STDMETHODIMP_(UINT) GetAdapterModeCount( THIS_ UINT Adapter,D3DFORMAT Format );

	virtual STDMETHODIMP EnumAdapterModes( THIS_ UINT Adapter,D3DFORMAT Format,UINT Mode,D3DDISPLAYMODE* pMode );

	virtual STDMETHODIMP GetAdapterDisplayMode( THIS_ UINT Adapter,D3DDISPLAYMODE* pMode );

	virtual STDMETHODIMP CheckDeviceType( THIS_ UINT Adapter,D3DDEVTYPE DevType,D3DFORMAT AdapterFormat,D3DFORMAT BackBufferFormat,BOOL bWindowed );

	virtual STDMETHODIMP CheckDeviceFormat( THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,DWORD Usage,D3DRESOURCETYPE RType,D3DFORMAT CheckFormat );

	virtual STDMETHODIMP CheckDeviceMultiSampleType( THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SurfaceFormat,BOOL Windowed,D3DMULTISAMPLE_TYPE MultiSampleType,DWORD* pQualityLevels );

	virtual STDMETHODIMP CheckDepthStencilMatch( THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,D3DFORMAT RenderTargetFormat,D3DFORMAT DepthStencilFormat );

	virtual STDMETHODIMP CheckDeviceFormatConversion( THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SourceFormat,D3DFORMAT TargetFormat );

	virtual STDMETHODIMP GetDeviceCaps( THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DCAPS9* pCaps );

	virtual STDMETHODIMP_(HMONITOR) GetAdapterMonitor( THIS_ UINT Adapter );

	virtual STDMETHODIMP CreateDevice( THIS_ UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DDevice9** ppReturnedDeviceInterface );

public:
	IDirect3D9* m_api;
	class xDirect3DDevice9* m_device;
};

#endif