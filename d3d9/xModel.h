#include "xDirect3DVertexBuffer9.h"
#ifndef xModel_h__
#define xModel_h__

enum EModelType
{
	eMT_TriList = 0,
	eMT_TriSptrip,

	eMT_Count,
};

struct xModel
{
	xDirect3DVertexBuffer9* vb;
	xDirect3DIndexBuffer9* ib;
	xDirect3DVertexDeclaration9* decl;
	EModelType type;
	uint32 stride;

	uint32 numVerts;
	uint32 primCount;

	xDirect3DTexture9* texUnit[8];

	bbox m_box;
	float radius;

	xModel()
	{
		vb = NULL;
		ib = NULL;
		decl = NULL;
		type = eMT_Count;
	}

	bool operator == (const xModel& lhs)
	{
		if ( vb == lhs.vb && ib == lhs.ib && type == lhs.type)
		{
			return true;
		}
		return false;
	}

	void CalcBoundingBox()
	{
		// consume the first 3 float as position
		char* data;
		vb->Lock( 0, stride, (void**)&data, D3DLOCK_READONLY);

		bbox boundingbox;

		for (int i =0; i < numVerts; ++i)
		{
			float3 pos = *(float3*)(data + i * stride);

			boundingbox.add_to_box(pos);
		}

		vb->Unlock();

		m_box = boundingbox;
	}

	void SetTexUnit(int index, xDirect3DTexture9* tex)
	{
		if (index >= 0 && index <= 7)
		{
			texUnit[index] = tex;
		}	
	}
};

#endif // xModel_h__