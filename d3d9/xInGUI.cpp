#include "xInGUI.h"
#include "xAuxRenderer.h"


gkInGUI::gkInGUI(void)
{
	m_defaultFont = NULL;
}


gkInGUI::~gkInGUI(void)
{
}

bool gkInGUI::gkGUIButton( const TCHAR* title, const float2& pos, int width, int height, const float4& textColor, const float4& bgColor, IgkFont* font )
{
	bool ret = false;
	bool inside = ( m_lastPoint.x < pos.x || m_lastPoint.x > pos.x + width || m_lastPoint.y < pos.y || m_lastPoint.y > pos.y + height );
	inside = !inside;

	float4 realBgColor = bgColor;

	if (m_LMBState == Pressing)
	{
		if ( inside )
		{
			ret = true;
		}
	}

	if ( inside )
	{
		realBgColor.w = 1.0;
	}

	// Draw
	if (!font)
	{
		font = m_defaultFont;
	}

	gEnv->aux->RenderScreenBox2D(pos, float2(width,height), realBgColor);
	gEnv->aux->RenderText(title, float2( pos.x + width / 2, pos.y +  height /2), DT_NOCLIP | DT_VCENTER | DT_CENTER, textColor );

	return ret;
}

bool gkInGUI::OnInputEvent( const SInputEvent &event )
{
	//if ( event.deviceId == eDI_Mouse)
	{
		switch( event.keyId )
		{
		case eKI_Mouse1:
			{
				if (event.state == eIS_Pressed)
				{
					m_LMBState = Pressing;
					m_lastPoint.x = event.value;
					m_lastPoint.y = event.value2;
				}
				else if (event.state == eIS_Down)
				{
					m_LMBState = Hold;
					m_lastPoint.x = event.value;
					m_lastPoint.y = event.value2;
				}
				else if (event.state == eIS_Released)
				{
					m_LMBState = Released;
					m_lastPoint.x = event.value;
					m_lastPoint.y = event.value2;
				}
			}
			break;
		case eKI_MouseX:
			{
				if (event.state == eIS_Changed)
				{
					m_lastPoint.x = event.value2;
				}
			}
			break;
		case eKI_MouseY:
			{
				if (event.state == eIS_Changed)
				{
					m_lastPoint.y = event.value2;
				}
			}
			break;
		}

	}
	return false;
}

void gkInGUI::Init()
{
	m_LMBState = Released;
	m_lastPoint.zero();
	g_inputManager.AddListener(this);
	m_defaultFont = NULL;
}

void gkInGUI::Shutdown()
{
	g_inputManager.RemoveListener(this);
}

void gkInGUI::gkPopupMsg( const TCHAR* title )
{
	m_popupMsgs.push_back( gkPopupMsgStruct(title, 2.0f) );
}

void gkInGUI::Update( float fElapsedTime )
{

}
