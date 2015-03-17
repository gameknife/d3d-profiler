#include "xd3d9.h"
#include "xDirect3DResourceBase.h"

class xDirect3DVolume9 : public IDirect3DVolume9, public xDirect3DResourceBase
{
public:
	xDirect3DVolume9( IDirect3DVolume9* volume );
	~xDirect3DVolume9() {}

	virtual STDMETHODIMP QueryInterface( THIS_ REFIID riid, void** ppvObj );

	virtual STDMETHODIMP_(ULONG) AddRef( THIS );

	virtual STDMETHODIMP_(ULONG) Release( THIS );

	virtual STDMETHODIMP GetDevice( THIS_ IDirect3DDevice9** ppDevice );

	virtual STDMETHODIMP SetPrivateData( THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags );

	virtual STDMETHODIMP GetPrivateData( THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData );

	virtual STDMETHODIMP FreePrivateData( THIS_ REFGUID refguid );

	virtual STDMETHODIMP GetContainer( THIS_ REFIID riid,void** ppContainer );

	virtual STDMETHODIMP GetDesc( THIS_ D3DVOLUME_DESC *pDesc );

	virtual STDMETHODIMP LockBox( THIS_ D3DLOCKED_BOX * pLockedVolume,CONST D3DBOX* pBox,DWORD Flags );

	virtual STDMETHODIMP UnlockBox( THIS );


	IDirect3DVolume9* m_volume;

};

class xDirect3DVolumeTexture9 : public IDirect3DVolumeTexture9, public xDirect3DResourceBase
{
public:

	xDirect3DVolumeTexture9( IDirect3DVolumeTexture9* volumeTex );
	~xDirect3DVolumeTexture9() {}

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

	virtual STDMETHODIMP GetLevelDesc( THIS_ UINT Level,D3DVOLUME_DESC *pDesc );

	virtual STDMETHODIMP GetVolumeLevel( THIS_ UINT Level,IDirect3DVolume9** ppVolumeLevel );

	virtual STDMETHODIMP LockBox( THIS_ UINT Level,D3DLOCKED_BOX* pLockedVolume,CONST D3DBOX* pBox,DWORD Flags );

	virtual STDMETHODIMP UnlockBox( THIS_ UINT Level );

	virtual STDMETHODIMP AddDirtyBox( THIS_ CONST D3DBOX* pDirtyBox );

	IDirect3DVolumeTexture9* m_volumeTexture;
};