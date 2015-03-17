#ifndef xAuxRenderer_h__
#define xAuxRenderer_h__

#include "xd3d9.h"

typedef std::vector<FIXEDVERT> xVertsForFlush;

struct STextRenderInfo
{
	TCHAR text[512];
	int posx;
	int posy;
	//const IgkFont* font;
	uint32 alignment;
	uint32 color;
};

typedef std::vector<STextRenderInfo> xRenderTexts;

class xAuxrenderer
{
public:
	xAuxrenderer( xDirect3DDevice9* device  ):m_device_dx9(device) {m_device_dx11 = NULL;}
	xAuxrenderer( xD3D11Device* device  ):m_device_dx11(device) {m_device_dx9 = NULL;}


	void RenderScreenBox2D( const float2& pos, const float2& wh, const float4& color );
	void RenderText( const char* text, const float2& pos, uint32 alignment, const float4& color );
	void Flush();
	
private:
	xDirect3DDevice9* m_device_dx9;
	xD3D11Device* m_device_dx11;
	xVertsForFlush m_2dverts;
	xRenderTexts m_renderTexts;
};
#endif // xAuxRenderer_h__