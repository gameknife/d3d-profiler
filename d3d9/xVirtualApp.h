#ifndef xVirtualApp_h__
#define xVirtualApp_h__

#include "xd3d9.h"
#include "InputManager.h"
#include "SrCamera.h"

class xDirect3DDevice9;

class xVirtualApp : public IInputEventListener
{
public:
	xVirtualApp();
	~xVirtualApp();
	void OnInit( xDirect3DDevice9* device );
	void OnInit( xD3D11Device* device, xD3D11DeviceContext* context );
	void OnUpdate();

	void UpdateStaticBanner();

	void UpdateResourceGUI(); 
	void UpdateProfileGUI();

	void OnDestroy();

	void OnReset( xDirect3DDevice9* device );
	void OnLost();

	void DisplayTexture( xDirect3DTexture9* texture, float4& region, float2& repeat );
	void DisplayTexture( xDirect3DTexture9* texture, float centralWidth );
	void DisplayTexture( xDirect3DTexture9* texture, float2& start, float2& limit );
	void DisplayModel( xModel* model, float scale );

	virtual bool OnInputEvent( const SInputEvent &event );

	void SetRenderStateSaving( D3DRENDERSTATETYPE type, DWORD value );

	void BackupState();
	void RestoreState();

	xDirect3DDevice9* m_device_dx9;
	xD3D11Device* m_device_dx11;
	xD3D11DeviceContext* m_device_context_dx11;

public:
	IDirect3DSurface9* m_backbuffer;

	IDirect3DVertexDeclaration9* m_decl9;
	IDirect3DVertexDeclaration9* m_decl9fixed;

	DWORD m_backupState[D3DRS_BLENDOPALPHA];

	char* m_testForAlloc;


	bool m_drag_mode;

	float m_horizon_angle;
	float m_vertical_angle;

	SrCamera m_vCam;


};

#endif // xVirtualApp_h__