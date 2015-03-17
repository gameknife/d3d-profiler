#include "xVirtualApp.h"
#include "xTextFlusher.h"
#include "xDirect3DDevice9.h"
#include "timer.h"
#include "xProfiler.h"
#include "xDirect3DResourceBase.h"
#include "xDirect3DTexture9.h"
#include "InputManager.h"
#include "Logger.h"
#include "xAuxRenderer.h"
#include "xInGUI.h"
#include "xModel.h"
#include "xAPICallMonitor.h"

xVirtualApp* g_vApp;
xTimer* g_timer;
xProfiler* g_profiler = NULL;
xInputManager g_inputManager;

const D3DVERTEXELEMENT9 PPVERT::Decl[3] =
{
	{ 0, 0,  D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITIONT, 0 },
	{ 0, 16, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,  0 },
	D3DDECL_END()
};

const D3DVERTEXELEMENT9 FixedDecl[3] =
{
	{ 0, 0,  D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITIONT, 0 },
	{ 0, 16, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,  0 },
	D3DDECL_END()
};

xVirtualApp::xVirtualApp():m_vCam( float3(0,0,0), Quat::CreateIdentity(), 60.0, 0.1, 4000.0  )
{
	gEnv->logger = new xLogger;
	m_drag_mode = false;

	m_horizon_angle = 0;
	m_vertical_angle = 0;


	m_device_dx11 = NULL;
	m_device_dx9 = NULL;
}

xVirtualApp::~xVirtualApp()
{

}

void xVirtualApp::OnInit( xD3D11Device* device, xD3D11DeviceContext* context )
{
	m_device_dx11 = device;
	m_device_context_dx11 = context;

	g_timer = new xTimer;
	g_timer->Init();
	g_profiler = new xProfiler;

	gEnv->app = this;

	g_inputManager.Init( gEnv->hwnd );

	gEnv->aux = new xAuxrenderer( m_device_dx9 );
	gEnv->gui = new gkInGUI;
	gEnv->gui->Init();

	g_inputManager.AddListener( this );
}

void xVirtualApp::OnInit( xDirect3DDevice9* device )
{
	m_device_dx9 = device;

	g_timer = new xTimer;
	g_timer->Init();
	g_profiler = new xProfiler;
	m_backbuffer = NULL;
	
	gEnv->app = this;

	m_testForAlloc = 0;
	g_inputManager.Init( gEnv->hwnd );
	gEnv->aux = new xAuxrenderer( m_device_dx9 );
	gEnv->gui = new gkInGUI;
	gEnv->gui->Init();

	g_inputManager.AddListener( this );
}

void xVirtualApp::OnUpdate()
{
	static float now = 0;
	g_profiler->IncreaseTime(ePe_ProfilerCostTime, now);
	now = g_timer->getRealTime();

	//////////////////////////////////////////////////////////////////////////
	// MUTE NOT AFFECT HERE!!!
	xAPICallMonitor::s_tmpUnMuteAll = true;

	BackupState();

	//////////////////////////////////////////////////////////////////////////

	g_timer->Update();

	g_inputManager.Update();

	float frameTime = g_timer->getElapsedTime();
	g_profiler->IncreaseTime(ePe_FrameTime, frameTime);
	
	RECT rc;
	rc.left = 10;
	rc.top = 10;

	IDirect3DVertexShader9* vs;
	IDirect3DPixelShader9* ps;

	if (m_device_dx9)
	{
		//////////////////////////////////////////////////////////////////////////
		// X GUI DRAW
		m_device_dx9->BeginScene();
		SetRenderStateSaving( D3DRS_CULLMODE, D3DCULL_NONE );
		SetRenderStateSaving( D3DRS_STENCILENABLE, FALSE );
		SetRenderStateSaving( D3DRS_ALPHATESTENABLE, FALSE );
		SetRenderStateSaving( D3DRS_SCISSORTESTENABLE, FALSE );

		m_device_dx9->Clear( 0, NULL, D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0, 1.0f, 0L );
		m_device_dx9->GetVertexShader( &vs );
		m_device_dx9->GetPixelShader( &ps );
		m_device_dx9->SetVertexShader( NULL );
		m_device_dx9->SetPixelShader( NULL );
	}

	// Draw GUI
	gEnv->aux->Flush();

	UpdateStaticBanner();

	static int s_guiMode = 0;
	if( gEnv->gui->gkGUIButton( "STATS", float2(0, gEnv->height - 50), 100, 50, float4(1,1,1,1), (s_guiMode == 0)? XUI_BG_PRESSED : XUI_BG_NORMAL ) )
	{
		s_guiMode = 0;
	}
	else if( gEnv->gui->gkGUIButton( "PROFILE", float2(101, gEnv->height - 50), 100, 50, float4(1,1,1,1), (s_guiMode == 1)? XUI_BG_PRESSED : XUI_BG_NORMAL ) )
	{
		s_guiMode = 1;
	}
	else if (gEnv->gui->gkGUIButton( "RESOURCE", float2(202, gEnv->height - 50), 100, 50, float4(1,1,1,1), (s_guiMode == 2)? XUI_BG_PRESSED : XUI_BG_NORMAL ) )
	{
		s_guiMode = 2;
	}



	switch(s_guiMode)
	{
	case 1:
		UpdateProfileGUI();
		break;
	case 2:
		UpdateResourceGUI();
		break;
	}

	if (m_device_dx9)
	{
		m_device_dx9->SetVertexShader( vs );
		m_device_dx9->SetPixelShader( ps );

		m_device_dx9->EndScene();
	}

	//////////////////////////////////////////////////////////////////////////

	g_profiler->Update();	

	char buffer[256];
	sprintf(buffer, "[xD3D9 Trojan] FPS: %.1f | FrameTime: %.2fms | Profiler Cost: %.2fms",
		1.f / g_profiler->getAverageTime(ePe_FrameTime),
		g_profiler->getAverageTime(ePe_FrameTime) * 1000.f,
		g_profiler->getAverageTime(ePe_ProfilerCostTime) * 1000.f );
	gEnv->logger->LogE(buffer);

	RestoreState();

	xAPICallMonitor::s_tmpUnMuteAll = false;

	now = g_timer->getRealTime() - now;

	xAPICallMonitor::Update();
}

void xVirtualApp::OnDestroy()
{
	delete g_profiler;
	delete g_timer;
	
	delete gEnv->logger;
	delete gEnv->aux;

	gEnv->gui->Shutdown();

	delete gEnv->gui;

	g_inputManager.Destroy();
}

void xVirtualApp::OnReset( xDirect3DDevice9* device )
{
	gEnv->textFlusher = new xTextFlusher;
	gEnv->textFlusher->Init( device->m_device );
	device->CreateVertexDeclaration( PPVERT::Decl, &m_decl9 );
	device->CreateVertexDeclaration( FixedDecl, &m_decl9fixed );
}

void xVirtualApp::OnLost()
{
	if (gEnv->textFlusher)
	{
		gEnv->textFlusher->Destroy();
		delete gEnv->textFlusher;
		gEnv->textFlusher = NULL;
	}

	if (m_decl9)
	{
		m_decl9->Release();
		m_decl9 = NULL;
	}

	if (m_decl9fixed)
	{
		m_decl9fixed->Release();
		m_decl9fixed = NULL;
	}

	//g_resourceManager.cleanAllMapping();
}


void xVirtualApp::DisplayTexture( xDirect3DTexture9* texture, float width )
{
	float totalWidth = gEnv->width;
	float totalHeight = gEnv->height;
	float halfWidth = totalWidth * 0.5f;
	float halfHeight = totalHeight * 0.5f;
	float centralWidth = width * 0.5f;
	DisplayTexture( texture, float4( (halfWidth - centralWidth) / totalWidth , (halfHeight - centralWidth) / totalHeight,
		(halfWidth + centralWidth) / totalWidth, (halfHeight + centralWidth) / totalHeight ), float2(1,1) );
}


void xVirtualApp::DisplayTexture( xDirect3DTexture9* texture, float2& start, float2& limit )
{
	float totalWidth = gEnv->width;
	float totalHeight = gEnv->height;
	float realWidth = texture->m_width;
	float realHeight = texture->m_height;

	float aspect = texture->m_width / (float)(texture->m_height);
	//if ( texture->m_height > limit.y )
	{
		realHeight = limit.y;
		realWidth = realHeight * aspect;
	}

	if ( realWidth > limit.x )
	{
		realWidth = limit.x;
		realHeight = realWidth / aspect;
	}

	DisplayTexture( texture, float4( start.x / totalWidth , start.y / totalHeight,
		( start.x + realWidth) / totalWidth, (start.y + realHeight) / totalHeight ), float2(1,1) );
}


void xVirtualApp::DisplayTexture( xDirect3DTexture9* texture, float4& region, float2& repeat )
{
		IDirect3DTexture9* realTex = g_resourceManager.getD3DTexMapping( (res_index)texture );
		if (realTex)
		{
			m_device_dx9->SetVertexDeclaration( m_decl9 );

			float texWidth = (float)gEnv->width;
			float texHeight = (float)gEnv->height;

			// Render a screen-sized quad
			PPVERT quad[4];

			quad[0].post = float4(  -0.5f + region.x * texWidth, -0.5f + region.y * texHeight,		0.0f, 1.0f );
			quad[1].post = float4(  -0.5f + region.x * texWidth, region.w * texHeight - 0.5f,		0.0f, 1.0f );	
			quad[2].post = float4(   region.z * texWidth - 0.5f, -0.5 + region.y * texHeight,		0.0f, 1.0f );	
			quad[3].post = float4(  region.z * texWidth - 0.5f,	region.w * texHeight - 0.5f,		0.0f, 1.0f );

			// screenTC
			quad[0].texcoord0 = float4( 0.0f,	0.0f, 0.0f, 0.0f );
			quad[1].texcoord0 = float4( 0.0f,	1.0f, 0.0f, repeat.y );
			quad[2].texcoord0 = float4( 1.0f,	0.0f, repeat.x, 0.0f );
			quad[3].texcoord0 = float4( 1.0f,	1.0f, repeat.x, repeat.y );

			m_device_dx9->SetTexture( 0, realTex );

			SetRenderStateSaving(D3DRS_ZENABLE, FALSE);
			
			SetRenderStateSaving(D3DRS_ALPHATESTENABLE, FALSE);
			SetRenderStateSaving(D3DRS_ALPHABLENDENABLE, TRUE);
			SetRenderStateSaving(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			SetRenderStateSaving(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			SetRenderStateSaving(D3DRS_LIGHTING, FALSE);

			m_device_dx9->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, quad, sizeof(PPVERT) );

			SetRenderStateSaving(D3DRS_ALPHABLENDENABLE, FALSE);
			
		}
}

bool xVirtualApp::OnInputEvent( const SInputEvent &event )
{
	switch(event.keyId)
	{
	case eKI_Mouse1:
		if (event.state == eIS_Down)
		{
			m_drag_mode = true;
		}
		else if (event.state == eIS_Released)
		{
			m_drag_mode = false;
		}
		break;
	case eKI_MouseX:
		if (event.state == eIS_Changed)
		{
			if(m_drag_mode)
			{
				//m_horizon_angle += event.value * 0.002;
				m_vCam.Rotate( 0, -event.value * 0.002 );
				//m_vCam.Rotate( event.value * 0.002, 0 );
			}
		}
		break;
	case eKI_MouseY:
		if (event.state == eIS_Changed)
		{
			if(m_drag_mode)
			{
				

				m_vCam.Rotate( -event.value * 0.002, 0 );
			}
		}
		break;
	}
	return false;
}

float get_angle_by_2pi( float x )
{
	return x - (2.0 * SR_PI) * floorf(x / (2.0 * SR_PI));
}

void xVirtualApp::DisplayModel( xModel* model, float scale )
{
	if (model)
	{
		IDirect3DVertexBuffer9* vb = (IDirect3DVertexBuffer9*)model->vb;
		IDirect3DIndexBuffer9* ib = (IDirect3DIndexBuffer9*)model->ib;
		IDirect3DVertexDeclaration9* decl = (IDirect3DVertexDeclaration9*)model->decl;


		float3 pos = model->m_box.center();

		float rad = model->m_box.radius();

		rad = 10.0f / rad;

		D3DXMATRIX world;
		D3DXMatrixIdentity( &world );
		D3DXMatrixScaling( &world, scale * rad, scale * rad, scale * rad );

		m_device_dx9->SetTransform( D3DTS_WORLD, &world );


		m_vCam.setPos( float3(0,0,0));
		m_vCam.Move( float3(0,0,-10));

		float44 viewmat = m_vCam.getViewMatrix();
		m_device_dx9->SetTransform( D3DTS_VIEW, (D3DXMATRIX*)&viewmat );

// 		D3DXMATRIX view;
// 		D3DXVECTOR3 at(0,0,0);
// 		D3DXVECTOR3 eye(x,y,z);
// 		D3DXVECTOR3 up(0,1,0);
// 		D3DXMatrixLookAtLH( &view, &eye, &at, &up );
// 		m_device->SetTransform( D3DTS_VIEW, &view );


		D3DXMATRIX proj;
		D3DXMatrixPerspectiveFovLH( &proj, 45.f / 2 * SR_PI, gEnv->width / (float)gEnv->height, 0.25f, 1000.f );
		m_device_dx9->SetTransform( D3DTS_PROJECTION, &proj );

		m_device_dx9->SetVertexDeclaration( decl );
		m_device_dx9->SetStreamSource( 0, vb, 0, model->stride );
		m_device_dx9->SetIndices( ib );

		m_device_dx9->SetVertexShader( NULL );
		m_device_dx9->SetPixelShader( NULL );

		//SetRenderStateSaving(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

		m_device_dx9->SetTexture(0, model->texUnit[0]);

		m_device_dx9->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, model->numVerts, 0, model->primCount );

		//SetRenderStateSaving(D3DRS_FILLMODE, D3DFILL_SOLID);

	}
}

void xVirtualApp::UpdateResourceGUI()
{
	{
		static int showMode = 0;
		switch ( showMode )
		{
		case 0:
			{
				if ( gEnv->gui->gkGUIButton( "show null", float2(gEnv->width / 2 - 50, gEnv->height - 100), 100, 50, float4(1,1,1,1), XUI_BG_NORMAL ) )
				{
					showMode++;
					showMode %= 4;
				}
			}
			break;
		case 1:
			{
				if ( gEnv->gui->gkGUIButton( "show texture", float2(gEnv->width / 2 - 50, gEnv->height - 100), 100, 50, float4(1,1,1,1), XUI_BG_NORMAL ) )
				{
					showMode++;
					showMode %= 4;
				}
			}
			break;
		case 2:
			{
				if ( gEnv->gui->gkGUIButton( "show mesh", float2(gEnv->width / 2 - 50, gEnv->height - 100), 100, 50, float4(1,1,1,1), XUI_BG_NORMAL ) )
				{
					showMode++;
					showMode %= 4;
				}
			}
			break;
		case 3:
			{
				if ( gEnv->gui->gkGUIButton( "show model", float2(gEnv->width / 2 - 50, gEnv->height - 100), 100, 50, float4(1,1,1,1), XUI_BG_NORMAL ) )
				{
					showMode++;
					showMode %= 4;
				}
			}
			break;
		}



		static uint32 showIndex = 0;
		if ( gEnv->gui->gkGUIButton( "<-", float2(gEnv->width / 2 - 100, gEnv->height - 100), 40, 50, float4(1,1,1,1), XUI_BG_NORMAL ) )
		{
			showIndex--;
		}

		if ( gEnv->gui->gkGUIButton( "->", float2(gEnv->width / 2 + 60, gEnv->height - 100), 40, 50, float4(1,1,1,1), XUI_BG_NORMAL ) )
		{
			showIndex++;
		}

		switch(showMode)
		{
		case 1:
			{
				static int texShowTab = 0;

				//////////////////////////////////////////////////////////////////////////
				// draw tabs
				if ( gEnv->gui->gkGUIButton( "All", float2(20, 80), 80, 20, float4(1,1,1,1), (texShowTab == 0)? XUI_BG_PRESSED : XUI_BG_NORMAL ) )
				{
					texShowTab = 0;
					showIndex = 0;
				}
				if ( gEnv->gui->gkGUIButton( "General", float2(101, 80), 80, 20, float4(1,1,1,1), (texShowTab == 1)? XUI_BG_PRESSED : XUI_BG_NORMAL ) )
				{
					texShowTab = 1;
					showIndex = 0;
				}
				if ( gEnv->gui->gkGUIButton( "RT", float2(182, 80), 80, 20, float4(1,1,1,1), (texShowTab == 2)? XUI_BG_PRESSED : XUI_BG_NORMAL ) )
				{
					texShowTab = 2;
					showIndex = 0;
				}

				//////////////////////////////////////////////////////////////////////////
				// draw the texture list
				char buffer[255];
				for ( uint32 count = 0; count < 30; ++count)
				{
					xDirect3DTexture9* tex;
					switch( texShowTab )
					{
					case 0:
						tex = g_resourceManager.getTexAllByIndex(showIndex - 1 + count);
						break;
					case 2:
						tex = g_resourceManager.getTexRTByIndex(showIndex - 1 + count);
						break;
					default:
						tex = g_resourceManager.getTexGeneralByIndex(showIndex - 1 + count);
						break;
					}
					
					if ( tex )
					{
						sprintf( buffer, "%.1fMB | %x", tex->m_memUsageGPU / 1024.f / 1024.f, (res_index)(tex->m_realTexture)  );
						if ( count == 1)
						{
							gEnv->aux->RenderText( buffer, float2( 25, 135 + count * 15 ), NULL, XUI_FG_HIGHLIGHT );
						}
						else
						{
							gEnv->aux->RenderText( buffer, float2( 25, 135 + count * 15 ), NULL, XUI_FG_NORMAL );
						}						
					}					
				}
				sprintf( buffer, "%d of %d", showIndex, g_resourceManager.getTexCount() );
				gEnv->aux->RenderText( buffer, float2( 25, 105 ), NULL, XUI_FG_NORMAL );

				gEnv->aux->RenderScreenBox2D( float2(20, 100), float2(300, 30), XUI_BG_PRESSED);
				gEnv->aux->RenderScreenBox2D( float2(20, 130), float2(300, 470), XUI_BG_BLACK);


				//////////////////////////////////////////////////////////////////////////
				// draw tex info
				char poolbuffer[128];
				char formatbuffer[128];
				
				xDirect3DTexture9* tex;
				switch( texShowTab )
				{
				case 0:
					tex = g_resourceManager.getTexAllByIndex(showIndex);
					break;
				case 2:
					tex = g_resourceManager.getTexRTByIndex(showIndex);
					break;
				default:
					tex = g_resourceManager.getTexGeneralByIndex(showIndex);
					break;
				}

				if (tex)
				{
					switch( tex->m_pool )
					{
					case D3DPOOL_MANAGED:
						strcpy(poolbuffer, "MANAGED");
						break;
					case D3DPOOL_DEFAULT:
						strcpy(poolbuffer, "DEFAULT");
						break;
					case D3DPOOL_SYSTEMMEM:
						strcpy(poolbuffer, "SYSTEMMEM");
						break;
					default:
						strcpy(poolbuffer, "UNKNOWN");
					}

					switch( tex->m_format )
					{
					case D3DFMT_DXT1:
						strcpy(formatbuffer, "DXT1");
						break;
					case D3DFMT_DXT3:
						strcpy(formatbuffer, "DXT3");
						break;
					case D3DFMT_DXT5:
						strcpy(formatbuffer, "DXT5");
						break;
					case D3DFMT_A8R8G8B8:
						strcpy(formatbuffer, "ARGB8");
						break;
					case D3DFMT_A16B16G16R16F:
						strcpy(formatbuffer, "ABGR16F");
						break;
					case D3DFMT_A32B32G32R32F:
						strcpy(formatbuffer, "ABGR32F");
						break;
					case D3DFMT_R16F:
						strcpy(formatbuffer, "R16F");
						break;
					case D3DFMT_R32F:
						strcpy(formatbuffer, "R32F");
						break;
					case D3DFMT_G16R16F:
						strcpy(formatbuffer, "G16R16F");
						break;
					default:
						strcpy(formatbuffer, "UNCOMPRESS");
					}

					sprintf( buffer, "addr:%x size:%d x %d pool:%s fmt:%s mem:%.1fMB mips:%d", (res_index)(tex->m_realTexture), tex->m_width, tex->m_height, poolbuffer, formatbuffer, tex->m_memUsageGPU / 1024.f / 1024.f, tex->m_level );
					gEnv->aux->RenderText( buffer, float2( 350, 110 ), NULL, XUI_FG_NORMAL );
					gEnv->aux->RenderScreenBox2D( float2(325, 100), float2(gEnv->width - 340, 30), XUI_BG_PRESSED);
					gEnv->aux->RenderScreenBox2D( float2(325, 130), float2(gEnv->width - 340, 470), float4(0,0,0,1));
					//DisplayTexture( tex, 256 );

					DisplayTexture( tex, float2( 350, 140 ), float2( gEnv->width - 380, 440 ));
				}

			}
			break;

		case 2:
			{
				//////////////////////////////////////////////////////////////////////////
				// draw the texture list
				char buffer[255];
				for ( uint32 count = 0; count < 30; ++count)
				{
					xModel* tex;
					
					tex = g_resourceManager.getModelByIndex(showIndex - 1 + count);
					

					if ( tex )
					{
						sprintf( buffer, "%d face | %x", tex->primCount, (res_index)(tex)  );
						if ( count == 1)
						{
							gEnv->aux->RenderText( buffer, float2( 25, 135 + count * 15 ), NULL, XUI_FG_HIGHLIGHT );
						}
						else
						{
							gEnv->aux->RenderText( buffer, float2( 25, 135 + count * 15 ), NULL, XUI_FG_NORMAL );
						}						
					}					
				}
				sprintf( buffer, "%d of %d", showIndex, g_resourceManager.getModelCount() );
				gEnv->aux->RenderText( buffer, float2( 25, 105 ), NULL, XUI_FG_NORMAL );

				gEnv->aux->RenderScreenBox2D( float2(20, 100), float2(300, 30), XUI_BG_PRESSED);
				gEnv->aux->RenderScreenBox2D( float2(20, 130), float2(300, 470), XUI_BG_BLACK);

				char poolbuffer[128];
				xModel* tex = g_resourceManager.getModelByIndex(showIndex);
				if (tex)
				{
					static float scaling = 1;
					if ( gEnv->gui->gkGUIButton( "[ - ]", float2(gEnv->width / 2 - 100, gEnv->height * 0.5f + 50), 20, 30, float4(1,1,1,1), XUI_BG_NORMAL ) )
					{
						scaling*= 0.5f;
					}

					if ( gEnv->gui->gkGUIButton( "[ + ]", float2(gEnv->width / 2 + 60, gEnv->height * 0.5f + 50), 20, 30, float4(1,1,1,1), XUI_BG_NORMAL ) )
					{
						scaling*= 2.0f;
					}

					sprintf( buffer, "scale: %.1f", scaling );

					gEnv->aux->RenderText( buffer, float2( gEnv->width * 0.5f, gEnv->height * 0.5f + 65 ), DT_CENTER | DT_VCENTER, float4(1,1,1,1) );
					gEnv->aux->RenderScreenBox2D( float2(gEnv->width * 0.5f - 200, gEnv->height * 0.5f - 300), float2(400, 400), XUI_BG_NORMAL);
					DisplayModel( tex, scaling );
				}

			}
			break;
		}
	}
}

struct xFuncCostSorter
{
	xCostElement m_element;
	const char* m_str;

	xFuncCostSorter(xCostElement& tick, const char* str):m_element(tick), m_str(str) {}

	bool operator < ( const xFuncCostSorter& other)
	{
		if ( m_element.tickPerFrame > other.m_element.tickPerFrame)
		{
			return true;
		}
		return false;
	}
};

void xVirtualApp::UpdateProfileGUI()
{
	int posy = 100;

	static bool mute_all = false;
	if ( gEnv->gui->gkGUIButton( "ÆÁ±ÎËùÓÐD3DAPI", float2(5, posy), 150, 50, float4(1,1,1,1), mute_all? XUI_BG_PRESSED : XUI_BG_NORMAL ) )
	{
		mute_all = !mute_all;
		xAPICallMonitor::MuteAll(mute_all);
	}

	static bool mute_dp = false;
	posy += 51;
	if ( gEnv->gui->gkGUIButton( "ÆÁ±Î DP", float2(5, posy), 150, 50, float4(1,1,1,1), mute_dp? XUI_BG_PRESSED : XUI_BG_NORMAL ) )
	{
		mute_dp = !mute_dp;
		xAPICallMonitor::MuteCall( "xDirect3DDevice9::DrawIndexedPrimitive", mute_dp);
		xAPICallMonitor::MuteCall( "xDirect3DDevice9::DrawPrimitive", mute_dp);
	}

	static bool mute_ssc = false;
	posy += 51;
	if ( gEnv->gui->gkGUIButton( "ÆÁ±Î SetShaderConst", float2(5, posy), 150, 50, float4(1,1,1,1), mute_ssc? XUI_BG_PRESSED : XUI_BG_NORMAL ) )
	{
		mute_ssc = !mute_ssc;
		xAPICallMonitor::MuteCall( "xDirect3DDevice9::SetPixelShaderConstantB", mute_ssc);
		xAPICallMonitor::MuteCall( "xDirect3DDevice9::SetPixelShaderConstantF", mute_ssc);
		xAPICallMonitor::MuteCall( "xDirect3DDevice9::SetPixelShaderConstantI", mute_ssc);
		xAPICallMonitor::MuteCall( "xDirect3DDevice9::SetVertexShaderConstantB", mute_ssc);
		xAPICallMonitor::MuteCall( "xDirect3DDevice9::SetVertexShaderConstantF", mute_ssc);
		xAPICallMonitor::MuteCall( "xDirect3DDevice9::SetVertexShaderConstantI", mute_ssc);
	}
	
	static bool mute_tex = false;
	posy += 51;
	if ( gEnv->gui->gkGUIButton( "ÆÁ±Î Texture", float2(5, posy), 150, 50, float4(1,1,1,1), mute_tex? XUI_BG_PRESSED : XUI_BG_NORMAL ) )
	{
		mute_tex = !mute_tex;
		xAPICallMonitor::MuteCall( "xDirect3DDevice9::SetTexture", mute_tex);
		xAPICallMonitor::MuteCall( "xDirect3DDevice9::SetTextureStageState", mute_tex);
		xAPICallMonitor::MuteCall( "xDirect3DDevice9::SetSamplerState", mute_tex);
	}

	//////////////////////////////////////////////////////////////////////////
	// custom func
	{
		static bool mute_custom1 = false;
		posy = 100;
		if ( gEnv->gui->gkGUIButton( "ÆÁ±Î Custom1", float2(gEnv->width - 155, posy), 150, 50, float4(1,1,1,1), mute_custom1? XUI_BG_PRESSED : XUI_BG_NORMAL ) )
		{
			mute_custom1 = !mute_custom1;
			char app[255] = "mute_api";
			char key[255] = "custom1";
			char buffer[255];
			GetConfig(app, key, buffer);
			xAPICallMonitor::MuteCall( buffer, mute_custom1);
		}
	}

	{
		static bool mute_custom1 = false;
		posy += 51;
		if ( gEnv->gui->gkGUIButton( "ÆÁ±Î Custom2", float2(gEnv->width - 155, posy), 150, 50, float4(1,1,1,1), mute_custom1? XUI_BG_PRESSED : XUI_BG_NORMAL ) )
		{
			mute_custom1 = !mute_custom1;
			char app[255] = "mute_api";
			char key[255] = "custom2";
			char buffer[255];
			GetConfig(app, key, buffer);
			xAPICallMonitor::MuteCall( buffer, mute_custom1);
		}
	}

	{
		static bool mute_custom1 = false;
		posy += 51;
		if ( gEnv->gui->gkGUIButton( "ÆÁ±Î Custom3", float2(gEnv->width - 155, posy), 150, 50, float4(1,1,1,1), mute_custom1? XUI_BG_PRESSED : XUI_BG_NORMAL ) )
		{
			mute_custom1 = !mute_custom1;
			char app[255] = "mute_api";
			char key[255] = "custom3";
			char buffer[255];
			GetConfig(app, key, buffer);
			xAPICallMonitor::MuteCall( buffer, mute_custom1);
		}
	}

	{
		static bool mute_custom1 = false;
		posy += 51;
		if ( gEnv->gui->gkGUIButton( "ÆÁ±Î Custom4", float2(gEnv->width - 155, posy), 150, 50, float4(1,1,1,1), mute_custom1? XUI_BG_PRESSED : XUI_BG_NORMAL ) )
		{
			mute_custom1 = !mute_custom1;
			char app[255] = "mute_api";
			char key[255] = "custom4";
			char buffer[255];
			GetConfig(app, key, buffer);
			xAPICallMonitor::MuteCall( buffer, mute_custom1);
		}
	}

	{
		if ( gEnv->gui->gkGUIButton( "D3DAPIºÄÊ±Í³¼Æ", float2(160, 100), 150, 20, float4(1,1,1,1), xAPICallMonitor::s_funcTicking? XUI_BG_PRESSED : XUI_BG_NORMAL ) )
		{
			xAPICallMonitor::s_funcTicking = !xAPICallMonitor::s_funcTicking;
		}

		if (xAPICallMonitor::s_funcTicking)
		{
			//////////////////////////////////////////////////////////////////////////
			// profile top 20 function

			// 1. push into a list
			std::list<xFuncCostSorter> tickList;
			xCostMap::iterator it = xAPICallMonitor::s_costMap.begin();
			for (; it != xAPICallMonitor::s_costMap.end(); ++it)
			{
				tickList.push_back( xFuncCostSorter( it->second, it->first.data() ) );
				//tickList.push_back( xFuncCostSorter( it->second, it->first. ) );
			}

			// 2. sort list
			tickList.sort();
			// 
			// 3. Draw Top 35
			uint32 count = 0;
			uint32 freq = g_timer->getRealFreq();
			{
				std::list<xFuncCostSorter>::iterator it = tickList.begin();
				for (; it != tickList.end(); ++it)
				{
					float dptime = it->m_element.tickPerFrame / (float)freq;
					char buffer[255];
					sprintf( buffer, "%.2fms | %5d | %s", dptime * 1000.f, it->m_element.countPerFrame, it->m_str );
					gEnv->aux->RenderText( buffer, float2( 170, 125 + count * 15 ), NULL, float4(1,1,1,1) );

					if (++count > 25)
					{
						break;
					}
				}
			}

			gEnv->aux->RenderScreenBox2D( float2(160, 120), float2(450, 450), XUI_BG_NORMAL);
		}
	}

}

void xVirtualApp::UpdateStaticBanner()
{
	// »­×´Ì¬Í³¼ÆÀ¸
	gEnv->aux->RenderScreenBox2D( float2(0,0), float2(gEnv->width, 70), XUI_BG_NORMAL);

	// ÐÅÏ¢Êä³ö
	char buffer[256];
	sprintf(buffer, "[xD3D9 Trojan] FPS: %.1f | FrameTime: %.2fms | Profiler Cost: %.2fms",
		1.f / g_profiler->getAverageTime(ePe_FrameTime),
		g_profiler->getAverageTime(ePe_FrameTime) * 1000.f,
		g_profiler->getAverageTime(ePe_ProfilerCostTime) * 1000.f );
	gEnv->aux->RenderText( buffer, float2(5,5), 0, float4(1,1,1,1) );
	sprintf(buffer, "DP: %d | DIP: %d | DPU: %d | DIPU: %d | [CPU Ticks: %d]",
		g_profiler->getCount(ePe_DPCount), 
		g_profiler->getCount(ePe_DIPCount),
		g_profiler->getCount(ePe_DPUCount),
		g_profiler->getCount(ePe_DIPUCount),
		g_profiler->getCount(ePe_DPTickCount));
	gEnv->aux->RenderText( buffer, float2(5,20), 0, float4(1,1,1,1) );
	sprintf(buffer, "StateChange: %d | SetTexture: %d",
		g_profiler->getCount(ePe_StateChangeCount), 
		g_profiler->getCount(ePe_SetTextureCount));
	gEnv->aux->RenderText( buffer, float2(5,35), 0, float4(1,1,1,1) );

	sprintf(buffer, "Tex: %d (RAM: %.2fMB | VRAM: %.2fMB) | Model: %d (RAM: %.2fMB | VRAM: %.2fMB)",
		g_resourceManager.getTexCount(),
		g_resourceManager.getTexMemUsage(),
		g_resourceManager.getTexVMemUsage(),
		g_resourceManager.getModelCount(),
		g_resourceManager.getVBMemUsage(),
		g_resourceManager.getVBVMemUsage()		
		);
	gEnv->aux->RenderText( buffer, float2(5,50), 0, float4(1,1,1,1) );
}

void xVirtualApp::BackupState()
{
	for (uint32 i=0; i < D3DRS_BLENDOPALPHA; ++i)
	{
		m_backupState[i] = -1;
	}
}

void xVirtualApp::RestoreState()
{
	if(m_device_dx9)
	{
		for (uint32 i=0; i < D3DRS_BLENDOPALPHA; ++i)
		{
			if (m_backupState[i] != -1)
			{
				m_device_dx9->m_device->SetRenderState( (D3DRENDERSTATETYPE)i, m_backupState[i] );
			}
		}
	}
}

void xVirtualApp::SetRenderStateSaving( D3DRENDERSTATETYPE type, DWORD value )
{
	if(m_device_dx9)
	{
		if ( m_backupState[type] == -1)
		{
			m_device_dx9->m_device->GetRenderState( type, &(m_backupState[type]) );
		}

		m_device_dx9->m_device->SetRenderState(type, value);
	}

}



