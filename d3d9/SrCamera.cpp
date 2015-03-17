#include "xd3d9.h"

#include "SrCamera.h"

SrCamera::SrCamera( const float3& p, const Quat& r, float fov, float zN, float zF ) :m_pos(p)
	,m_rot(r)
	,m_fov(fov)
	,m_zNear(zN)
	,m_zFar(zF)
	,dirt(false)
	,m_aspect(1.33f)
{
	Update();
}

SrCamera::~SrCamera(void)
{
}

void SrCamera::Update()
{
	m_rot.Normalize();

	cachedView.LookatLH( m_pos, m_pos + m_rot.GetRow2(), float3(0,0,1) );
	cachedProj.PerspectiveFovLH( m_fov / 180.f * SR_PI, m_aspect, m_zNear, m_zFar );
	cachedViewProj = cachedView * cachedProj;
}

void SrCamera::Move( const float3& localTranslate )
{
	
	m_pos += (localTranslate * m_rot);

	dirt = true;
}

void SrCamera::Rotate( float yaw, float roll )
{
	Quat rollQ = Quat::CreateRotationZ( roll );
	Quat yawQ = Quat::CreateRotationX( yaw );

	m_rot = m_rot * rollQ;
	m_rot = yawQ * m_rot;

	dirt = true;
}

float44 SrCamera::getViewProjMatrix()
{
	if (dirt)
	{
		dirt = false;
		Update();
	}
	return cachedViewProj;
}

float44 SrCamera::getViewMatrix()
{
	if (dirt)
	{
		dirt = false;
		Update();
	}
	return cachedView;
}

void SrCamera::setPos( const float3& pos )
{
	m_pos = pos;

	dirt = true;
}

void SrCamera::setRot( const Quat& rot )
{
	m_rot = rot;

	dirt = true;
}

void SrCamera::setFov( float fov )
{
	m_fov = fov;

	dirt = true;
}

void SrCamera::MarkDirty()
{
	dirt = true;
}
