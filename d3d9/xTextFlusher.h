/**
  @file SrHwTextFlusher.h
  
  @author yikaiming

  更改日志 history
  ver:1.0
   
 */

#ifndef SrHwTextFlusher_h__
#define SrHwTextFlusher_h__
#include "xd3d9.h"
#include "..\dxsdk/Include/d3dx9.h"

//--------------------------------------------------------------------------------------
// Manages the insertion point when drawing text
//--------------------------------------------------------------------------------------
class xTextFlusher
{
public:
	xTextFlusher();
	~xTextFlusher();

	void    Init( IDirect3DDevice9* device );
	void	Destroy();

	void    Begin();

	HRESULT DrawFormattedTextLine( RECT& rc, DWORD dwFlags, DWORD color, bool big, const char* strMsg ,  ... );
	HRESULT DrawTextLine( RECT& rc, DWORD dwFlags,  DWORD color, const char* strMsg, bool big );

	void    End();

protected:
	ID3DXFont* m_pFont9;
	ID3DXSprite* m_pSprite9;
	ID3DXFont* m_pFont9Big;
};

#endif // SrHwTextFlusher_h__
