#include "xTextFlusher.h"
#include "stdio.h"

#ifdef _M_X64
#pragma comment(lib,"../dxsdk/lib/x64/d3dx9.lib") 
#else
#pragma comment(lib,"../dxsdk/lib/x86/d3dx9.lib") 
#endif




xTextFlusher::xTextFlusher()
{
}

xTextFlusher::~xTextFlusher()
{
}

void xTextFlusher::Init( IDirect3DDevice9* device )
{
	D3DXCreateFont( device, 12, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		"Consolas", &m_pFont9 );

	D3DXCreateFont( device, 14, 0, FW_NORMAL, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		"Consolas", &m_pFont9Big );

	D3DXCreateSprite( device, &m_pSprite9 );
}

void xTextFlusher::Destroy()
{
	m_pFont9->Release();
	m_pFont9Big->Release();
	m_pSprite9->Release();
}

HRESULT xTextFlusher::DrawFormattedTextLine( RECT& rc, DWORD dwFlags, DWORD color, bool big, const char* strMsg, ... )
{
	char strBuffer[512];

	va_list args;
	va_start( args, strMsg );
	vsprintf_s( strBuffer, 512, strMsg, args );
	strBuffer[511] = L'\0';
	va_end( args );

	return DrawTextLine( rc, dwFlags, color, strBuffer, big );
}


HRESULT xTextFlusher::DrawTextLine( RECT& rc, DWORD dwFlags, DWORD color, const char* strMsg, bool big)
{
	HRESULT hr;
	if( m_pFont9Big && big )
	{
		HDC dc = m_pFont9Big->GetDC();
		SIZE sz;
		GetTextExtentPoint32( dc, strMsg, strlen(strMsg), &sz );

		int width = sz.cx;
		int height = sz.cy;

		if ( dwFlags & DT_CENTER )
		{
			rc.left -= width / 2;
		}

		if ( dwFlags & DT_VCENTER )
		{
			rc.top -= height / 2;
		}

		hr = m_pFont9Big->DrawText( m_pSprite9, strMsg, -1, &rc, DT_NOCLIP, color | 0xff000000 );
	}
	else if ( m_pFont9)
	{
		HDC dc = m_pFont9->GetDC();
		SIZE sz;
		GetTextExtentPoint32( dc, strMsg, strlen(strMsg), &sz );

		int width = sz.cx;
		int height = sz.cy;

		if ( dwFlags & DT_CENTER )
		{
			rc.left -= width / 2;
		}

		if ( dwFlags & DT_VCENTER )
		{
			rc.top -= height / 2;
		}

		hr = m_pFont9->DrawText( m_pSprite9, strMsg, -1, &rc, DT_NOCLIP, color | 0xff000000 );
	}
	if( FAILED( hr ) )
	{

	}

	return S_OK;
}


//--------------------------------------------------------------------------------------
void xTextFlusher::Begin()
{
	if( m_pSprite9 )
		m_pSprite9->Begin( D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE );
}
void xTextFlusher::End()
{
	if( m_pSprite9 )
		m_pSprite9->End();
}


