// function forwarder

//#pragma comment(linker, "/export:D3D11CreateDevice=d3d11_ex.D3D11CreateDevice")
//#pragma comment(linker, "/export:D3D11CreateDeviceAndSwapChain=d3d11_ex.D3D11CreateDeviceAndSwapChain")
#pragma comment(linker, "/export:D3D11CoreCreateDevice=d3d11_ex.D3D11CoreCreateDevice")
#pragma comment(linker, "/export:D3D11CoreCreateLayeredDevice=d3d11_ex.D3D11CoreCreateLayeredDevice")
#pragma comment(linker, "/export:D3D11CoreRegisterLayers=d3d11_ex.D3D11CoreRegisterLayers")
//#pragma comment(linker, "/export:D3D11CreateDeviceAndSwapChain=d3d11_ex.D3D11CreateDeviceAndSwapChain")


// #pragma comment(linker, "/export:D3DPERF_BeginEvent=d3d9ex.D3DPERF_BeginEvent")
// #pragma comment(linker, "/export:D3DPERF_EndEvent=d3d9ex.D3DPERF_EndEvent")
// #pragma comment(linker, "/export:D3DPERF_SetMarker=d3d9ex.D3DPERF_SetMarker")

#include "xd3d9.h"
#include "xDirect3D9.h"
#include "xDirect3D9Ex.h"
#include "xVirtualApp.h"
#include "xDXGIFactory1.h"
#include "Logger.h"
#include "xDirect3D11.h"
#include "xD3D11DeviceContext.h"

typedef HRESULT (WINAPI* PFN_D3D11_CREATE_DEVICE)( __in_opt IDXGIAdapter*, 
	D3D_DRIVER_TYPE, HMODULE, UINT, 
	__in_ecount_opt( FeatureLevels ) CONST D3D_FEATURE_LEVEL*, 
	UINT FeatureLevels, UINT, __out_opt ID3D11Device**, 
	__out_opt D3D_FEATURE_LEVEL*, __out_opt ID3D11DeviceContext** );

typedef HRESULT (WINAPI* PFN_D3D11_CREATE_DEVICE_AND_SWAP_CHAIN)( __in_opt IDXGIAdapter*, 
	D3D_DRIVER_TYPE, HMODULE, UINT, 
	__in_ecount_opt( FeatureLevels ) CONST D3D_FEATURE_LEVEL*, 
	UINT FeatureLevels, UINT, __in_opt CONST DXGI_SWAP_CHAIN_DESC*, 
	__out_opt IDXGISwapChain**, __out_opt ID3D11Device**, 
	__out_opt D3D_FEATURE_LEVEL*, __out_opt ID3D11DeviceContext** );


LPDIRECT3DCREATE9EX g_Direct3DCreate9Ex = NULL;
LPDIRECT3DCREATE9 g_Direct3DCreate9 = NULL;
PFN_D3D11_CREATE_DEVICE g_Direct3DCreate11 = NULL;
HMODULE g_handle;
xDirect3D9* g_api;
xDirect3D9Ex* g_apiEx;
xGlobalEnv* gEnv = NULL;

extern "C" __declspec(dllexport) HRESULT __stdcall D3D11CreateDevice(
	IDXGIAdapter* pAdapter,
	D3D_DRIVER_TYPE DriverType,
	HMODULE Software,
	UINT Flags,
	CONST D3D_FEATURE_LEVEL* pFeatureLevels,
	UINT FeatureLevels,
	UINT SDKVersion,
	ID3D11Device** ppDevice,
	D3D_FEATURE_LEVEL* pFeatureLevel,
	ID3D11DeviceContext** ppImmediateContext )
{
	// get into my own program! haha!
	char systemDir[256];
	char systemDirEx[256];
	GetSystemDirectoryA(systemDir, 256);
	strcpy(systemDirEx, systemDir);
	strcat(systemDir, "\\d3d11.dll");

	//strcat(systemDirEx, "\\d3d9ex.dll");
	//CopyFile( systemDir, systemDirEx, FALSE );
	//CopyFile( systemDirEx, systemDir, FALSE );
	g_handle = LoadLibraryExA( systemDir, NULL, LOAD_WITH_ALTERED_SEARCH_PATH );
	//g_handle = LoadLibrary("d3d9.dll");
	g_Direct3DCreate11 = (PFN_D3D11_CREATE_DEVICE)GetProcAddress( g_handle, "D3D11CreateDevice" );



	gEnv = new xGlobalEnv;
	g_vApp = new xVirtualApp();

	gEnv->logger->LogE("Create Device11, Injected.");
	//MessageBox(NULL, "成功注入！！！", "哈哈", MB_OK);

	ID3D11Device* pDevice = NULL;
	ID3D11DeviceContext* pImmediateContext= NULL;

	HRESULT ert = g_Direct3DCreate11(pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels, SDKVersion, &pDevice, pFeatureLevel, &pImmediateContext);

	xD3D11Device* device = new xD3D11Device( pDevice );
	xD3D11DeviceContext* context = new xD3D11DeviceContext(pImmediateContext);

	device->m_deviceContex = pImmediateContext;


	*ppDevice = device;
	*ppImmediateContext = context;

	return ert;
}
typedef HRESULT     (WINAPI * LPCREATEDXGIFACTORY)(REFIID, void ** );

extern "C" __declspec(dllexport) HRESULT __stdcall CreateDXGIFactory(REFIID riid, void **ppFactory)
{
	// get into my own program! haha!
	char systemDir[256];
	char systemDirEx[256];
	GetSystemDirectoryA(systemDir, 256);
	strcpy(systemDirEx, systemDir);
	strcat(systemDir, "\\dxgi.dll");

	g_handle = LoadLibraryExA( systemDir, NULL, LOAD_WITH_ALTERED_SEARCH_PATH );
	LPCREATEDXGIFACTORY pDynamicCreateDXGIFactory = (LPCREATEDXGIFACTORY)GetProcAddress( g_handle, "CreateDXGIFactory" );

	MessageBox(NULL, "CreateDXGIFactory", "哈哈", MB_OK);

	return pDynamicCreateDXGIFactory(riid,ppFactory);
}

extern "C" __declspec(dllexport) HRESULT __stdcall CreateDXGIFactory1(REFIID riid, void **ppFactory)
{
	// get into my own program! haha!
	char systemDir[256];
	char systemDirEx[256];
	GetSystemDirectoryA(systemDir, 256);
	strcpy(systemDirEx, systemDir);
	strcat(systemDir, "\\dxgi.dll");

	g_handle = LoadLibraryExA( systemDir, NULL, LOAD_WITH_ALTERED_SEARCH_PATH );
	LPCREATEDXGIFACTORY pDynamicCreateDXGIFactory = (LPCREATEDXGIFACTORY)GetProcAddress( g_handle, "CreateDXGIFactory1" );

	//MessageBox(NULL, "CreateDXGIFactory1", "哈哈", MB_OK);

	IDXGIFactory1* dxgi_factory = NULL;

	HRESULT ret = pDynamicCreateDXGIFactory(riid,(void**)&dxgi_factory);

	if(!gEnv)
	{
		gEnv = new xGlobalEnv;
	}
	if(!g_vApp)
	{
		g_vApp = new xVirtualApp();
	}
	
	xDXGIFactory1* dxgi_wrap = new xDXGIFactory1(dxgi_factory);


	(*ppFactory) = dxgi_wrap;

	return ret;
}

extern "C" __declspec(dllexport)  HRESULT __stdcall D3D11CreateDeviceAndSwapChain(
	IDXGIAdapter* pAdapter,
	D3D_DRIVER_TYPE DriverType,
	HMODULE Software,
	UINT Flags,
	CONST D3D_FEATURE_LEVEL* pFeatureLevels,
	UINT FeatureLevels,
	UINT SDKVersion,
	CONST DXGI_SWAP_CHAIN_DESC* pSwapChainDesc,
	IDXGISwapChain** ppSwapChain,
	ID3D11Device** ppDevice,
	D3D_FEATURE_LEVEL* pFeatureLevel,
	ID3D11DeviceContext** ppImmediateContext )
{
	gEnv->logger->Log("CreateSwapChain & Device");

	return S_OK;
}
//////////////////////////////////////////////////////////////////////////
// HAND MAKE EXP FUNC
extern "C" __declspec(dllexport) IDirect3D9* __stdcall Direct3DCreate9(UINT SDKVersion)
{
	// get into my own program! haha!
	char systemDir[256];
	char systemDirEx[256];
	GetSystemDirectoryA(systemDir, 256);
	strcpy(systemDirEx, systemDir);
	
	// 判断要不要load d3d9d.dll
	char app[255] = "debug";
	char key[255] = "debug_runtime";
	char buffer[255];
	GetConfig(app, key, buffer);
	if ( strstr( buffer, "true" ) )
	{
		strcat(systemDir, "\\d3d9d.dll");
	}
	else
	{
		strcat(systemDir, "\\d3d9.dll");
	}

 	//strcat(systemDirEx, "\\d3d9ex.dll");
 	//CopyFile( systemDir, systemDirEx, FALSE );
 	//CopyFile( systemDirEx, systemDir, FALSE );
	g_handle = LoadLibraryExA( systemDir, NULL, LOAD_WITH_ALTERED_SEARCH_PATH );
	//g_handle = LoadLibrary("d3d9.dll");
	g_Direct3DCreate9Ex = (LPDIRECT3DCREATE9EX)GetProcAddress( g_handle, "Direct3DCreate9Ex" );
	g_Direct3DCreate9 = (LPDIRECT3DCREATE9)GetProcAddress( g_handle, "Direct3DCreate9" );

	OutputDebugString( "trojan d3d9.dll here.\n" );
	
	g_api = new xDirect3D9(SDKVersion, g_Direct3DCreate9);
	gEnv = new xGlobalEnv;
	g_vApp = new xVirtualApp();

	return g_api;
}
// 
// extern "C" __declspec(dllexport) HRESULT __stdcall Direct3DCreate9Ex(UINT SDKVersion, IDirect3D9Ex** api)
// {
// 	// get into my own program! haha!
// 	char systemDir[256];
// 	char systemDirEx[256];
// 	GetSystemDirectoryA(systemDir, 256);
// 	strcpy(systemDirEx, systemDir);
// 	strcat(systemDir, "\\d3d9d.dll");
// 	//strcat(systemDirEx, "\\d3d9ex.dll");
// 	//CopyFile( systemDir, systemDirEx, FALSE );
// 	//CopyFile( systemDirEx, systemDir, FALSE );
// 	g_handle = LoadLibraryExA( systemDir, NULL, LOAD_WITH_ALTERED_SEARCH_PATH );
// 	//g_handle = LoadLibrary("d3d9.dll");
// 	g_Direct3DCreate9Ex = (LPDIRECT3DCREATE9EX)GetProcAddress( g_handle, "Direct3DCreate9Ex" );
// 	g_Direct3DCreate9 = (LPDIRECT3DCREATE9)GetProcAddress( g_handle, "Direct3DCreate9" );
// 
// 	OutputDebugString( "trojan d3d9.dll here.\n" );
// 
// 	g_apiEx = new xDirect3D9Ex(SDKVersion, g_Direct3DCreate9Ex);
// 	gEnv = new xGlobalEnv;
// 
// 	*api = reinterpret_cast<IDirect3D9Ex*>(g_apiEx);
// 
// 	return S_OK;
// }
#if 1

//////////////////////////////////////////////////////////////////////////
typedef int (WINAPI *LPD3DPERF_BeginEvent)( D3DCOLOR, LPCWSTR);
extern "C" __declspec(dllexport) int __stdcall D3DPERF_BeginEvent( D3DCOLOR col, LPCWSTR wszName )
{
	LPD3DPERF_BeginEvent func = (LPD3DPERF_BeginEvent)GetProcAddress( g_handle, "D3DPERF_BeginEvent" );
	if (func)
	{
		return func(col, wszName);
	}
	return 0;
}
typedef int (WINAPI *LPD3DPERF_EndEvent)();
extern "C" __declspec(dllexport)int __stdcall D3DPERF_EndEvent( void )
{
	LPD3DPERF_EndEvent func = (LPD3DPERF_EndEvent)GetProcAddress( g_handle, "D3DPERF_EndEvent" );
	if (func)
	{
		return func();
	}
	return 0;
}
typedef void (WINAPI *LPD3DPERF_SetMarker)( D3DCOLOR, LPCWSTR);
extern "C" __declspec(dllexport) void __stdcall D3DPERF_SetMarker( D3DCOLOR col, LPCWSTR wszName )
{
	LPD3DPERF_SetMarker func = (LPD3DPERF_SetMarker)GetProcAddress( g_handle, "D3DPERF_SetMarker" );
	if (func)
	{
		func(col, wszName);
	}
}
extern "C" __declspec(dllexport) void __stdcall D3DPERF_SetRegion( D3DCOLOR col, LPCWSTR wszName )
{
	LPD3DPERF_SetMarker func = (LPD3DPERF_SetMarker)GetProcAddress( g_handle, "D3DPERF_SetRegion" );
	if (func)
	{
		func(col, wszName);
	}
}
typedef BOOL (WINAPI *LPD3DPERF_QueryRepeatFrame)();
extern "C" __declspec(dllexport) BOOL __stdcall D3DPERF_QueryRepeatFrame( void )
{
	LPD3DPERF_QueryRepeatFrame func = (LPD3DPERF_QueryRepeatFrame)GetProcAddress( g_handle, "D3DPERF_QueryRepeatFrame" );
	if (func)
	{
		return func();
	}
	return 0;
}
typedef void (WINAPI *LPD3DPERF_SetOptions)( DWORD dwOptions );
extern "C" __declspec(dllexport) void __stdcall D3DPERF_SetOptions( DWORD dwOptions )
{
	LPD3DPERF_SetOptions func = (LPD3DPERF_SetOptions)GetProcAddress( g_handle, "D3DPERF_SetOptions" );
	if (func)
	{
		func(dwOptions);
	}
}
typedef DWORD (WINAPI *LPD3DPERF_GetStatus)();
extern "C" __declspec(dllexport) DWORD __stdcall D3DPERF_GetStatus( void )
{
	LPD3DPERF_GetStatus func = (LPD3DPERF_GetStatus)GetProcAddress( g_handle, "D3DPERF_GetStatus" );
	if (func)
	{
		return func();
	}
	return 0;
}


#endif
