#ifndef xDirect3DCubeTexture9_h__
#define xDirect3DCubeTexture9_h__

#include "xd3d9.h"
#include "xDirect3DResourceBase.h"

class xDirect3DCubeTexture9 : public IDirect3DCubeTexture9, public xDirect3DResourceBase
{
public:

	xDirect3DCubeTexture9( IDirect3DCubeTexture9* cubemap );
	~xDirect3DCubeTexture9() {}

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

	virtual STDMETHODIMP GetCubeMapSurface( THIS_ D3DCUBEMAP_FACES FaceType,UINT Level,IDirect3DSurface9** ppCubeMapSurface );

	virtual STDMETHODIMP LockRect( THIS_ D3DCUBEMAP_FACES FaceType,UINT Level,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags );

	virtual STDMETHODIMP UnlockRect( THIS_ D3DCUBEMAP_FACES FaceType,UINT Level );

	virtual STDMETHODIMP AddDirtyRect( THIS_ D3DCUBEMAP_FACES FaceType,CONST RECT* pDirtyRect );


	IDirect3DCubeTexture9* m_cubeTexture;
};
#endif // xDirect3DCubeTexture9_h__