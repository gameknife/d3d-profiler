#ifndef xDirect3DTexture9_h__
#define xDirect3DTexture9_h__

#include "xd3d9.h"
#include "xDirect3DResourceBase.h"

class xDirect3DTexture9 : public IDirect3DTexture9, public xDirect3DResourceBase
{
public:
	xDirect3DTexture9( IDirect3DTexture9* realTexture );
	~xDirect3DTexture9();

	virtual STDMETHODIMP QueryInterface( THIS_ REFIID riid, void** ppvObj );

	virtual STDMETHODIMP_(ULONG) AddRef( THIS );

	virtual STDMETHODIMP_(ULONG) Release( THIS );

	virtual STDMETHODIMP GetDevice( THIS_ IDirect3DDevice9** ppDevice );

	virtual STDMETHODIMP SetPrivateData( THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags );

	virtual STDMETHODIMP GetPrivateData( THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData );

	virtual STDMETHODIMP FreePrivateData( THIS_ REFGUID refguid );

	virtual STDMETHODIMP_(DWORD) SetPriority( THIS_ DWORD PriorityNew );

	virtual STDMETHODIMP_(DWORD) GetPriority( THIS );

	virtual STDMETHODIMP_(void) PreLoad( THIS );

	virtual STDMETHODIMP_(D3DRESOURCETYPE) GetType( THIS );

	virtual STDMETHODIMP_(DWORD) SetLOD( THIS_ DWORD LODNew );

	virtual STDMETHODIMP_(DWORD) GetLOD( THIS );

	virtual STDMETHODIMP_(DWORD) GetLevelCount( THIS );

	virtual STDMETHODIMP SetAutoGenFilterType( THIS_ D3DTEXTUREFILTERTYPE FilterType );

	virtual STDMETHODIMP_(D3DTEXTUREFILTERTYPE) GetAutoGenFilterType( THIS );

	virtual STDMETHODIMP_(void) GenerateMipSubLevels( THIS );

	virtual STDMETHODIMP GetLevelDesc( THIS_ UINT Level,D3DSURFACE_DESC *pDesc );

	virtual STDMETHODIMP GetSurfaceLevel( THIS_ UINT Level,IDirect3DSurface9** ppSurfaceLevel );

	virtual STDMETHODIMP LockRect( THIS_ UINT Level,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags );

	virtual STDMETHODIMP UnlockRect( THIS_ UINT Level );

	virtual STDMETHODIMP AddDirtyRect( THIS_ CONST RECT* pDirtyRect );

public:
	IDirect3DTexture9* m_realTexture;
	uint32 m_width;
	uint32 m_height;
	uint32 m_level;
	uint32 m_pool;
	uint32 m_format;
	uint32 m_memUsageGPU;
	uint32 m_memUsage;
	uint32 m_rt;
};

#endif // xDirect3DTexture9_h__