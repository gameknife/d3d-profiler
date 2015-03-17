#ifndef SwMouse_h__
#define SwMouse_h__

#include "InputManager.h"

class SwMouse : public InputDeviceBase
{
public:
	SwMouse(xInputManager* creator);
	~SwMouse(void);

	virtual const char* GetDeviceName() const {return "sw_mouse";}

	virtual EDeviceId GetDeviceId() const {return eDI_Mouse;}

	virtual bool Init();

	virtual void Update( bool bFocus );

private:
	uint32 keyState[255];
	POINT m_last_pt;

};
#endif // SwMouse_h__