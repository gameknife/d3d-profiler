#ifndef xd3d9_h__
#define xd3d9_h__

#define SR_ALIGN

#include <Windows.h>

#include <assert.h>
#include <iostream>

#include <memory>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <algorithm>
#include <functional>
#include <string>

//#include <hash_map>

#include "d3d9.h"
#include "d3d11.h"

#include "math_def.h"

typedef unsigned int uint32;
typedef unsigned int res_index;
//#include "xMath.h"

#pragma warning(disable:4229)



typedef HRESULT (WINAPI *LPDIRECT3DCREATE9EX)( UINT, IDirect3D9Ex**);
typedef IDirect3D9* (WINAPI *LPDIRECT3DCREATE9)( UINT );

extern LPDIRECT3DCREATE9EX g_Direct3DCreate9Ex;
extern LPDIRECT3DCREATE9 g_Direct3DCreate9;

class xVirtualApp;
class xProfiler;
class xTimer;
class xInputManager;
struct xDirect3DResourceManager;

//////////////////////////////////////////////////////////////////////////
// xD3D Object
class xDirect3DTexture9;
class xDirect3DVertexBuffer9;
class xDirect3DVertexShader9;
class xDirect3DPixelShader9;
class xDirect3DIndexBuffer9;
class xDirect3DDevice9;
class xDirect3DVertexDeclaration9;
class xDirect3DSurface9;
class xDirect3DVolume9;
class xDirect3DVolumeTexture9;
class xD3D11Device;
class xD3D11DeviceContext;

struct ILogger;
class xAuxrenderer;
class gkInGUI;
class xTextFlusher;
struct xModel;

extern xVirtualApp* g_vApp;
extern xProfiler* g_profiler;
extern xTimer* g_timer;
extern xDirect3DResourceManager g_resourceManager;
extern xInputManager g_inputManager;

struct xGlobalEnv
{
	HWND hwnd;
	ILogger* logger;
	xAuxrenderer* aux;
	gkInGUI* gui;
	xVirtualApp* app;
	xTextFlusher* textFlusher;

	int width;
	int height;
};

extern xGlobalEnv* gEnv;

struct PPVERT
{
	float4 post;
	float4 texcoord0;       // Texcoord for post-process source
	const static D3DVERTEXELEMENT9 Decl[3];
};

struct FIXEDVERT
{
	float4 post;
	DWORD texcoord0;       // d3dcolor
};

#define LOGFUNCENTRY //gEnv->logger->LogE(__FUNCTION__);

#define XUI_BG_BLACK float4(0.0, 0.0, 0.0, 0.85)
#define XUI_BG_NORMAL float4(0.1, 0.1, 0.1, 0.85)
#define XUI_BG_HOVER float4(0.1, 0.1, 0.1, 1.0)
#define XUI_BG_PRESSED float4(0.1, 0.1, 0.5, 1.0)

#define XUI_FG_NORMAL float4(1.0, 1.0, 1.0, 1.0)
#define XUI_FG_HIGHLIGHT float4(0.2, 0.2, 1.0, 1.0)

inline void GetConfig( const char* app, const char* key, char* buffer ) 
{
	char strExePath[MAX_PATH] = {0};
	char* strLastSlash = NULL;
	GetModuleFileNameA( NULL, strExePath, MAX_PATH );
	strExePath[MAX_PATH - 1] = 0;
	strLastSlash = strrchr( strExePath, L'\\' );
	if( strLastSlash )
		*strLastSlash = 0;
	strcat( strExePath, "\\d3d9_profile.ini");
	GetPrivateProfileString( app, key, "", buffer, 255, strExePath  );
}

inline std::string GetRootPath()
{
	char strExePath[MAX_PATH] = { 0 };
	char* strLastSlash = NULL;
	GetModuleFileNameA(NULL, strExePath, MAX_PATH);
	strExePath[MAX_PATH - 1] = 0;
	strLastSlash = strrchr(strExePath, L'\\');
	if (strLastSlash)
		*strLastSlash = 0;

	return strExePath;
}



#endif // xd3d9_h__