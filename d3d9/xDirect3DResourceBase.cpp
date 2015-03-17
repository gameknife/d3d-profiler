#include "xDirect3DResourceBase.h"
#include "xModel.h"
#include "xDirect3DVertexDeclaration9.h"
#include "xDirect3DTexture9.h"
#include "xDirect3DVertexBuffer9.h"
#include "xDirect3DVolume9.h"

xDirect3DResourceManager g_resourceManager;

void xDirect3DResourceBase::AddResource( res_index xRes, res_index d3dRes )
{
	{
		xResourceLib& lib = g_resourceManager.m_resLibs[m_type];
		xResourceLib::iterator it = lib.find( xRes );
		if ( it != lib.end())
		{
			// 居然还有一样地址的资源
			if ( it->second )
			{
				assert(0);
			}

			it->second = d3dRes;

		}
		else
		{
			lib.insert( xResourceLib::value_type( xRes, d3dRes) );
		}
	}

	{
		xResourceLib& lib = g_resourceManager.m_resReflect[m_type];
		xResourceLib::iterator it = lib.find( d3dRes );
		if ( it != lib.end())
		{
			// 居然还有一样地址的资源
			if ( it->second )
			{
				assert(0);
			}

			it->second = xRes;

		}
		else
		{
			lib.insert( xResourceLib::value_type( d3dRes, xRes) );
		}
	}
}

void xDirect3DResourceBase::DeleteResource( res_index xRes, res_index d3dRes )
{
	{
		xResourceLib& lib = g_resourceManager.m_resLibs[m_type];
		xResourceLib::iterator it = lib.find( xRes );
		if ( it != lib.end())
		{
			// 找到了，erase然后return
			lib.erase(it);
		}
	}

	{
		xResourceLib& lib = g_resourceManager.m_resReflect[m_type];
		xResourceLib::iterator it = lib.find( d3dRes );
		if ( it != lib.end())
		{
			// 找到了，erase然后return
			lib.erase(it);
		}
	}
}

IDirect3DTexture9* xDirect3DResourceManager::getD3DTexMapping( res_index index )
{
	IDirect3DTexture9* hr = NULL;
	xResourceLib& lib = g_resourceManager.m_resLibs[eDRT_Texture2D];
	xResourceLib::iterator it = lib.find( index );
	if (it != lib.end())
	{
		hr = reinterpret_cast<IDirect3DTexture9*>( it->second );
	}
	else
	{
		// 没找到，从cubeMap里面找[2/19/2013 YiKaiming]
		xResourceLib& lib = g_resourceManager.m_resLibs[eDRT_TextureCUBE];
		xResourceLib::iterator it = lib.find( index );
		if (it != lib.end())
		{
			hr = reinterpret_cast<IDirect3DTexture9*>( it->second );
		}
		else
		{
			// 没找到，从volume里面找 [2/20/2013 YiKaiming]
			xResourceLib& lib = g_resourceManager.m_resLibs[eDRT_TextureVolume];
			xResourceLib::iterator it = lib.find( index );
			if (it != lib.end())
			{
				hr = reinterpret_cast<IDirect3DTexture9*>( it->second );
			}
		}
	}

	return hr;
}

IDirect3DVertexBuffer9* xDirect3DResourceManager::getD3DVBMapping( res_index index )
{
	IDirect3DVertexBuffer9* hr = NULL;
	xResourceLib& lib = g_resourceManager.m_resLibs[eDRT_VertexBuffer];
	xResourceLib::iterator it = lib.find( index );
	if (it != lib.end())
	{
		hr = reinterpret_cast<IDirect3DVertexBuffer9*>( it->second );
	}
	return hr;
}

IDirect3DVertexShader9* xDirect3DResourceManager::getD3DVSMapping( res_index index )
{
	IDirect3DVertexShader9* hr = NULL;
	xResourceLib& lib = g_resourceManager.m_resLibs[eDRT_VertexShader];
	xResourceLib::iterator it = lib.find( index );
	if (it != lib.end())
	{
		hr = reinterpret_cast<IDirect3DVertexShader9*>( it->second );
	}
	return hr;
}

IDirect3DPixelShader9* xDirect3DResourceManager::getD3DPSMapping( res_index index )
{
	IDirect3DPixelShader9* hr = NULL;
	xResourceLib& lib = g_resourceManager.m_resLibs[eDRT_PixelShader];
	xResourceLib::iterator it = lib.find( index );
	if (it != lib.end())
	{
		hr = reinterpret_cast<IDirect3DPixelShader9*>( it->second );
	}
	return hr;
}


IDirect3DVertexDeclaration9* xDirect3DResourceManager::getD3DVCMapping( res_index index )
{
	IDirect3DVertexDeclaration9* hr = NULL;
	xResourceLib& lib = g_resourceManager.m_resLibs[eDRT_VertexDeclaration];
	xResourceLib::iterator it = lib.find( index );
	if (it != lib.end())
	{
		hr = reinterpret_cast<IDirect3DVertexDeclaration9*>( it->second );
	}
	return hr;
}


xDirect3DVolume9* xDirect3DResourceManager::getXVolumeMapping( res_index index )
{
	xDirect3DVolume9* hr = NULL;
	xResourceLib& lib = g_resourceManager.m_resLibs[eDRT_Volume];
	xResourceLib::iterator it = lib.find( index );
	if (it != lib.end())
	{
		hr = reinterpret_cast<xDirect3DVolume9*>( it->second );
	}
	return hr;
}


xDirect3DTexture9* xDirect3DResourceManager::getXTexMapping( res_index index )
{
	xDirect3DTexture9* hr = NULL;
	xResourceLib& lib = g_resourceManager.m_resReflect[eDRT_Texture2D];
	xResourceLib::iterator it = lib.find( index );
	if (it != lib.end())
	{
		hr = reinterpret_cast<xDirect3DTexture9*>( it->second );
	}
	else
	{
		// 没找到，从cubeMap里面找[2/19/2013 YiKaiming]
		xResourceLib& lib = g_resourceManager.m_resReflect[eDRT_TextureCUBE];
		xResourceLib::iterator it = lib.find( index );
		if (it != lib.end())
		{
			hr = reinterpret_cast<xDirect3DTexture9*>( it->second );
		}
		else
		{
			// 没找到，从volume里面找 [2/20/2013 YiKaiming]
			xResourceLib& lib = g_resourceManager.m_resReflect[eDRT_TextureVolume];
			xResourceLib::iterator it = lib.find( index );
			if (it != lib.end())
			{
				hr = reinterpret_cast<xDirect3DTexture9*>( it->second );
			}
		}
	}
	return hr;
}

xDirect3DVertexBuffer9* xDirect3DResourceManager::getXVBMapping( res_index index )
{
	xDirect3DVertexBuffer9* hr = NULL;
	xResourceLib& lib = g_resourceManager.m_resReflect[eDRT_VertexBuffer];
	xResourceLib::iterator it = lib.find( index );
	if (it != lib.end())
	{
		hr = reinterpret_cast<xDirect3DVertexBuffer9*>( it->second );
	}
	return hr;
}

xDirect3DVertexShader9* xDirect3DResourceManager::getXVSMapping( res_index index )
{
	xDirect3DVertexShader9* hr = NULL;
	xResourceLib& lib = g_resourceManager.m_resReflect[eDRT_VertexShader];
	xResourceLib::iterator it = lib.find( index );
	if (it != lib.end())
	{
		hr = reinterpret_cast<xDirect3DVertexShader9*>( it->second );
	}
	return hr;
}

xDirect3DPixelShader9* xDirect3DResourceManager::getXPSMapping( res_index index )
{
	xDirect3DPixelShader9* hr = NULL;
	xResourceLib& lib = g_resourceManager.m_resReflect[eDRT_PixelShader];
	xResourceLib::iterator it = lib.find( index );
	if (it != lib.end())
	{
		hr = reinterpret_cast<xDirect3DPixelShader9*>( it->second );
	}
	return hr;
}



xDirect3DVertexDeclaration9* xDirect3DResourceManager::getXVCMapping( res_index index )
{
	xDirect3DVertexDeclaration9* hr = NULL;
	xResourceLib& lib = g_resourceManager.m_resReflect[eDRT_VertexDeclaration];
	xResourceLib::iterator it = lib.find( index );
	if (it != lib.end())
	{
		hr = reinterpret_cast<xDirect3DVertexDeclaration9*>( it->second );
	}
	return hr;
}

xDirect3DSurface9* xDirect3DResourceManager::getXSurfaceMapping( res_index index )
{
	xDirect3DSurface9* hr = NULL;
	xResourceLib& lib = g_resourceManager.m_resReflect[eDRT_Surface];
	xResourceLib::iterator it = lib.find( index );
	if (it != lib.end())
	{
		hr = reinterpret_cast<xDirect3DSurface9*>( it->second );
	}
	return hr;
}

IDirect3DSurface9* xDirect3DResourceManager::getD3DSurfaceMapping( res_index index )
{
	IDirect3DSurface9* hr = NULL;
	xResourceLib& lib = g_resourceManager.m_resLibs[eDRT_Surface];
	xResourceLib::iterator it = lib.find( index );
	if (it != lib.end())
	{
		hr = reinterpret_cast<IDirect3DSurface9*>( it->second );
	}
	return hr;
}


xDirect3DVertexBuffer9* xDirect3DResourceManager::getXVBByIndex( uint32 index )
{
	xDirect3DVertexBuffer9* ret = NULL;
	if (index < m_resLibs[eDRT_VertexBuffer].size())
	{
		xResourceLib::iterator it = m_resLibs[eDRT_VertexBuffer].begin();
		for ( uint32 i=0; i < index; ++i)
		{
			it = ++it;
		}
		ret = (xDirect3DVertexBuffer9*)it->first;
	}

	return ret;
}


xDirect3DTexture9* xDirect3DResourceManager::getXTexByIndex( uint32 index )
{
	xDirect3DTexture9* ret = NULL;
	if (index < m_resLibs[eDRT_Texture2D].size())
	{
		xResourceLib::iterator it = m_resLibs[eDRT_Texture2D].begin();
		for ( uint32 i=0; i < index; ++i)
		{
			it = ++it;
		}
		ret = (xDirect3DTexture9*)it->first;
	}

	return ret;
}

xModel* xDirect3DResourceManager::getModelByIndex( uint32 index )
{
	if ( index < m_models.size() && index >= 0)
	{
		return &( m_models[index] );
	}
	else
	{
		return NULL;
	}
}

xModel& xDirect3DResourceManager::addModel( xModel& model )
{
	for ( uint32 i = 0; i < m_models.size(); ++i )
	{
		if ( m_models[i] == model  )
		{
			return m_models[i];
		}
	}

	model.CalcBoundingBox();

	m_models.push_back( model );

	return m_models.back();
}

uint32 xDirect3DResourceManager::getModelCount()
{
	return m_models.size();
}

void xDirect3DResourceManager::removeModelWithVB( xDirect3DVertexBuffer9* vb )
{
	if (m_models.empty())
	{
		return;
	}

	xModelLib::iterator it = m_models.begin();

	for (; it != m_models.end(); ++it)
	{
		if ( it->vb == vb)
		{
			it = m_models.erase(it);
			if (it == m_models.end())
			{
				return;
			}
		}
	}
}

void xDirect3DResourceManager::removeModelWithIB( xDirect3DIndexBuffer9* ib )
{
	if (m_models.empty())
	{
		return;
	}

	xModelLib::iterator it = m_models.begin();

	for (; it != m_models.end(); ++it)
	{
		if ( it->ib == ib)
		{
			it = m_models.erase(it);
			if (it == m_models.end())
			{
				return;
			}
		}
	}
}

uint32 xDirect3DResourceManager::getTexCount()
{
	return m_resLibs[eDRT_Texture2D].size() + m_resLibs[eDRT_TextureCUBE].size();
}

float xDirect3DResourceManager::getTexMemUsage()
{
	return m_texMemUsage;
}

float xDirect3DResourceManager::getTexVMemUsage()
{
	return m_texMemUsageGPU;
}

float xDirect3DResourceManager::getVBMemUsage()
{
	return m_vbMemUsage;
}

float xDirect3DResourceManager::getVBVMemUsage()
{
	return m_vbMemUsageGPU;
}

void xDirect3DResourceManager::cleanAllMapping()
{
	for (uint32 i=0; i < eDRT_Count; ++i)
	{
		g_resourceManager.m_resLibs[i].clear();
		g_resourceManager.m_resReflect[i].clear();
	}
}

void xDirect3DResourceManager::reCalcMemUsage()
{
	m_vbMemUsage = 0;
	m_vbMemUsageGPU = 0;
	for ( uint32 i=0; i < m_resLibs[eDRT_VertexBuffer].size(); ++i)
	{
		xDirect3DVertexBuffer9* tex = getXVBByIndex(i);
		m_vbMemUsage += tex->m_memUsage  / 1024.f / 1024.f;
		m_vbMemUsageGPU += tex->m_memUsageGPU  / 1024.f / 1024.f;
	}
// 	m_vbMemUsage = m_vbMemUsage;
// 	m_vbMemUsageGPU = m_vbMemUsageGPU;

	m_texMemUsage = 0;
	m_texMemUsageGPU = 0;
	for ( uint32 i=0; i < m_resLibs[eDRT_Texture2D].size(); ++i)
	{
		xDirect3DTexture9* tex = getXTexByIndex(i);
		m_texMemUsage += tex->m_memUsage  / 1024.f / 1024.f;
		m_texMemUsageGPU += tex->m_memUsageGPU  / 1024.f / 1024.f;
	}
	//m_texMemUsage = m_texMemUsage / 1024.f / 1024.f;
	//m_texMemUsageGPU = m_texMemUsageGPU / 1024.f / 1024.f;

	m_texAll.clear();
	m_texRenderTarget.clear();
	m_texGeneral.clear();
	for ( uint32 i=0; i < m_resLibs[eDRT_Texture2D].size(); ++i)
	{
		xDirect3DTexture9* tex = getXTexByIndex(i);
		m_texAll.push_back( tex );

		if (tex->m_rt)
		{
			m_texRenderTarget.push_back( tex );
		}
		else
		{
			m_texGeneral.push_back( tex );
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// sort the tex list
	SortTexArray(m_texAll);
	SortTexArray(m_texRenderTarget);
	SortTexArray(m_texGeneral);
}

struct xTextureSorter
{
	xDirect3DTexture9* pTex;

	xTextureSorter( xDirect3DTexture9* tex):pTex(tex) {}

	bool operator < (const xTextureSorter& other)
	{
		if ( pTex->m_memUsageGPU < other.pTex->m_memUsageGPU)
		{
			return false;
		}
		return true;
	}
};
typedef std::list<xTextureSorter> xTextureSortList;

void xDirect3DResourceManager::SortTexArray( xTextureArray &thisList )
{
	xTextureSortList sortList;
	for ( uint32 i=0; i < thisList.size(); ++i )
	{
		sortList.push_back( thisList[i] );
	}

	sortList.sort();

	thisList.clear();

	xTextureSortList::iterator it = sortList.begin();
	for (; it != sortList.end(); ++it)
	{
		thisList.push_back( it->pTex );
	}
}

xDirect3DTexture9* xDirect3DResourceManager::getTexAllByIndex( uint32 index )
{
	if (index < m_texAll.size())
	{
		return m_texAll[index];
	}
	return false;
}

xDirect3DTexture9* xDirect3DResourceManager::getTexRTByIndex( uint32 index )
{
	if (index < m_texRenderTarget.size())
	{
		return m_texRenderTarget[index];
	}
	return false;
}

xDirect3DTexture9* xDirect3DResourceManager::getTexGeneralByIndex( uint32 index )
{
	if (index < m_texGeneral.size())
	{
		return m_texGeneral[index];
	}
	return false;
}




