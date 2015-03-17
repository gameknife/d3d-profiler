#ifndef xDirect3DResourceBase_h__
#define xDirect3DResourceBase_h__

#include "xd3d9.h"

enum EDirect3DResourceType
{
	eDRT_Texture2D = 0,
	eDRT_TextureCUBE,
	eDRT_TextureVolume,

	eDRT_Surface,
	eDRT_Volume,

	eDRT_VertexBuffer,
	eDRT_IndexBuffer,
	
	eDRT_VertexDeclaration,

	eDRT_VertexShader,
	eDRT_PixelShader,

	eDRT_Count,
};


struct xDirect3DResourceBase
{
	xDirect3DResourceBase(EDirect3DResourceType type, res_index xResIndex, res_index d3dIndex):m_type(type), m_resIndex(xResIndex), m_d3dIndex(d3dIndex) { AddResource(m_resIndex, m_d3dIndex);}
	virtual ~xDirect3DResourceBase() { DeleteResource(m_resIndex, m_d3dIndex);}

	void AddResource( res_index xRes, res_index d3dRes );
	void DeleteResource( res_index xRes, res_index d3dRes  );

	EDirect3DResourceType m_type;
	res_index m_resIndex;
	res_index m_d3dIndex;
};

typedef stdext::hash_map<res_index, res_index> xResourceLib;
typedef std::vector<xModel> xModelLib;
typedef std::vector<xDirect3DTexture9*> xTextureArray;

struct xDirect3DResourceManager
{
	xDirect3DTexture9*					getXTexMapping( res_index index );
	xDirect3DVertexBuffer9*				getXVBMapping( res_index index );
	xDirect3DVertexShader9*				getXVSMapping( res_index index );
	xDirect3DPixelShader9*				getXPSMapping( res_index index );
	xDirect3DVertexDeclaration9*		getXVCMapping( res_index index );
	xDirect3DSurface9*					getXSurfaceMapping( res_index index );
	xDirect3DVolume9*					getXVolumeMapping( res_index index );

	IDirect3DTexture9*					getD3DTexMapping( res_index index );
	IDirect3DVertexBuffer9*				getD3DVBMapping( res_index index );
	IDirect3DVertexShader9*				getD3DVSMapping( res_index index );
	IDirect3DPixelShader9*				getD3DPSMapping( res_index index );
	IDirect3DVertexDeclaration9*		getD3DVCMapping( res_index index );
	IDirect3DSurface9*					getD3DSurfaceMapping( res_index index );

	xDirect3DTexture9*					getXTexByIndex( uint32 index);
	xDirect3DVertexBuffer9*				getXVBByIndex( uint32 index );

	xDirect3DTexture9*					getTexAllByIndex( uint32 index);
	xDirect3DTexture9*					getTexRTByIndex( uint32 index);
	xDirect3DTexture9*					getTexGeneralByIndex( uint32 index);

	uint32								getTexAllCount() {return m_texAll.size();} 
	uint32								getTexRTCount() {return m_texRenderTarget.size();}
	uint32								getTexGeneralCount() {return m_texGeneral.size();}

	xModel*								getModelByIndex( uint32 index );
	xModel&								addModel( xModel& model );
	
	void								removeModelWithVB( xDirect3DVertexBuffer9* vb );
	void								removeModelWithIB( xDirect3DIndexBuffer9* ib );

	uint32								getModelCount();
	uint32								getTexCount();
	float								getTexMemUsage();
	float								getTexVMemUsage();

	float								getVBMemUsage();
	float								getVBVMemUsage();

	void								cleanAllMapping();
	void								reCalcMemUsage();

	void SortTexArray( xTextureArray &thisList );

	xResourceLib m_resLibs[eDRT_Count];
	xResourceLib m_resReflect[eDRT_Count];

	xTextureArray m_texAll;
	xTextureArray m_texGeneral;
	xTextureArray m_texRenderTarget;


	xModelLib m_models;

	float m_texMemUsage;
	float m_texMemUsageGPU;
	float m_vbMemUsage;
	float m_vbMemUsageGPU;
};

#endif // xDirect3DResourceBase_h__