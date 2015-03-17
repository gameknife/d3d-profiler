#include "xAuxRenderer.h"
#include "xDirect3DDevice9.h"
#include "xVirtualApp.h"
#include "xTextFlusher.h"

void xAuxrenderer::RenderScreenBox2D( const float2& pos, const float2& wh, const float4& color )
{
	FIXEDVERT quad[4];

	quad[0].post = float4(  -0.5f + pos.x,	-0.5f + pos.y,						0.01f, 1.0f );
	quad[1].post = float4(  -0.5f + pos.x,	pos.y + wh.y - 0.5f,				0.01f, 1.0f );	
	quad[2].post = float4(  pos.x + wh.x - 0.5f,	-0.5 + pos.y,				0.01f, 1.0f );	
	quad[3].post = float4(  pos.x + wh.x - 0.5f,	pos.y + wh.y - 0.5f,		0.01f, 1.0f );

	// screenTC
	quad[0].texcoord0 = color.packRGBA();
	quad[1].texcoord0 = color.packRGBA();
	quad[2].texcoord0 = color.packRGBA();
	quad[3].texcoord0 = color.packRGBA();

	m_2dverts.push_back( quad[0] );
	m_2dverts.push_back( quad[1] );
	m_2dverts.push_back( quad[2] );
	m_2dverts.push_back( quad[1] );
	m_2dverts.push_back( quad[2] );
	m_2dverts.push_back( quad[3] );
}

void xAuxrenderer::Flush()
{
	if ( !m_2dverts.empty() )
	{
		gEnv->app->SetRenderStateSaving(D3DRS_ZENABLE, FALSE);
		gEnv->app->SetRenderStateSaving(D3DRS_ALPHATESTENABLE, FALSE);
		gEnv->app->SetRenderStateSaving(D3DRS_ALPHABLENDENABLE, TRUE);
		gEnv->app->SetRenderStateSaving(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		gEnv->app->SetRenderStateSaving(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		gEnv->app->SetRenderStateSaving(D3DRS_LIGHTING, FALSE);
				
		if (m_device_dx9)
		{
			m_device_dx9->SetTexture(0, NULL);
			m_device_dx9->SetVertexDeclaration( gEnv->app->m_decl9fixed );
			m_device_dx9->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_2dverts.size() / 3, m_2dverts.data(), sizeof(FIXEDVERT) );
		}

		if (m_device_dx11)
		{
			//m_device_dx11->
		}

		gEnv->app->SetRenderStateSaving(D3DRS_ALPHABLENDENABLE, FALSE);
		gEnv->app->SetRenderStateSaving(D3DRS_ZENABLE, TRUE);
	}

	m_2dverts.clear();

	if (m_device_dx9)
	{
// 		if ( !m_renderTexts.empty() )
// 		{
// 			gEnv->textFlusher->Begin();
// 
// 			for ( uint32 i =0; i < m_renderTexts.size(); ++i)
// 			{
// 				RECT rc;
// 				rc.top = m_renderTexts[i].posy;
// 				rc.left = m_renderTexts[i].posx;
// 
// 				gEnv->textFlusher->DrawTextLine( rc, m_renderTexts[i].alignment, m_renderTexts[i].color, m_renderTexts[i].text, 1 );
// 			}
// 
// 			gEnv->textFlusher->End();
// 		}
	}


	m_renderTexts.clear();
}

void xAuxrenderer::RenderText( const char* text, const float2& pos, uint32 alignment, const float4& color )
{
	STextRenderInfo info;
	strcpy( info.text, text );
	info.posx = pos.x;
	info.posy = pos.y;

	info.alignment = alignment;
	info.color = color.packRGBA();

	m_renderTexts.push_back( info );
}
