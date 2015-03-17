#include "SwMouse.h"
#include "Logger.h"

bool SwMouse::Init()
{
	for (uint32 i=0; i < 255; ++i)
	{
		keyState[i] = false;
	}
	return true;
}

void SwMouse::Update( bool bFocus )
{
	SInputEvent event;


	if( ((GetKeyState( VK_LBUTTON ) & 0x80) == 0x80) && (keyState[VK_LBUTTON] == false) )
	{
		keyState[VK_LBUTTON] = true;
		event.state = eIS_Pressed;
		event.keyId = eKI_Mouse1;
		GetInputManager()->PostInputEvent(event);
	}
	else if ( ((GetKeyState( VK_LBUTTON ) & 0x80) == 0x80) && (keyState[VK_LBUTTON] != false) )
	{
		event.state = eIS_Down;
		event.keyId = eKI_Mouse1;
		GetInputManager()->PostInputEvent(event);
	}

	if ( ((GetKeyState( VK_LBUTTON ) & 0x80)) != 0x80 && (keyState[VK_LBUTTON] == true) )
	{
		keyState[VK_LBUTTON] = false;
		event.state = eIS_Released;
		event.keyId = eKI_Mouse1;
		GetInputManager()->PostInputEvent(event);
	}

	POINT pt;
	::GetCursorPos(&pt);

	int changex = pt.x - m_last_pt.x;
	int changey = pt.y - m_last_pt.y;

	event.state = eIS_Changed;
	event.keyId = eKI_MouseX;
	event.value = changex;
	GetInputManager()->PostInputEvent(event);
	event.state = eIS_Changed;
	event.keyId = eKI_MouseY;
	event.value = changey;
	GetInputManager()->PostInputEvent(event);

	m_last_pt = pt;
}

SwMouse::SwMouse( xInputManager* creator ):InputDeviceBase(creator, "sw_mouse", GUID_SysMouse)
{
	m_deviceId = eDI_Mouse;
}

SwMouse::~SwMouse( void )
{

}

