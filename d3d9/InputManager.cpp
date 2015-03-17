#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include "InputManager.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "SwMouse.h"




#ifdef _M_X64
#pragma comment(lib, "../dxsdk/lib/x64/dxguid.lib")
#pragma comment(lib, "dinput8.lib") 
#else
#pragma comment(lib, "../dxsdk/lib/x86/dxguid.lib")
#pragma comment(lib, "dinput8.lib") 
#endif

xInputManager::xInputManager(void)
{
}


xInputManager::~xInputManager(void)
{
}

//-----------------------------------------------------------------------------
// Name: InitDirectInput()
// Desc: Initialize the DirectInput variables.
//-----------------------------------------------------------------------------
HRESULT xInputManager::Init( HWND hDlg )
{
	HRESULT hr;

	m_hWnd = hDlg;

// 	if( FAILED( hr = DirectInput8Create( GetModuleHandle( NULL ), DIRECTINPUT_VERSION,
// 		IID_IDirectInput8, ( VOID** )&m_pDI, NULL ) ) )
// 		return hr;

	//if (!AddInputDevice(new Keyboard(this))) return false;
	if (!AddInputDevice(new SwMouse(this))) return false;

	//ClearKeyState();

	return S_OK;
}
InputDeviceBase::InputDeviceBase( xInputManager* creator, const char* deviceName, const GUID& guid ):m_creator(creator)
{

}
//-----------------------------------------------------------------------------
// Name: FreeDirectInput()
// Desc: Initialize the DirectInput variables.
//-----------------------------------------------------------------------------
// void xInputManager::FreeDirectInput()
// {
// 	// Release any DirectInput objects.
// 	//SAFE_RELEASE( m_pMouse );
// 	//m_pDI->Release();
// }


#if 0
bool InputDeviceBase::CreateDirectInputDevice(const DIDATAFORMAT* dataFormat, DWORD coopLevel, DWORD bufSize)
{
	HRESULT hr = m_creator->getDI()->CreateDevice(m_guid, &m_pDevice, 0);

	if (FAILED(hr))
	{
		return false;
	}

	// get capabilities
	DIDEVCAPS caps;
	caps.dwSize = sizeof(DIDEVCAPS);
	m_pDevice->GetCapabilities(&caps);

	if (caps.dwFlags & DIDC_POLLEDDEVICE)
	{
		m_bNeedsPoll = true;
	}

	if (!dataFormat)
	{
		// build a custom one, here
	}

	hr = m_pDevice->SetDataFormat(dataFormat);
	if (FAILED(hr)) 
	{
		return false;
	}				

	m_pDataFormat	= dataFormat;
	m_dwCoopLevel	= coopLevel;

	hr = m_pDevice->SetCooperativeLevel( NULL, m_dwCoopLevel);
	if (FAILED(hr)) 
	{
		return false;
	}						

	DIPROPDWORD dipdw = {{sizeof(DIPROPDWORD), sizeof(DIPROPHEADER), 0, DIPH_DEVICE}, bufSize};
	hr = m_pDevice->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);	
	if (FAILED(hr)) 
	{
		return false;
	}

	return true;
}

bool InputDeviceBase::Acquire()
{
	if (!m_pDevice) return false;

	HRESULT hr = m_pDevice->Acquire();

	unsigned char maxAcquire = 10;

	while (hr == DIERR_INPUTLOST && maxAcquire > 0)
	{
		hr = m_pDevice->Acquire();
		--maxAcquire;
	}

	if (FAILED(hr) || maxAcquire == 0) return false;

	return true;
}

///////////////////////////////////////////
bool InputDeviceBase::Unacquire()
{
	return (m_pDevice && SUCCEEDED(m_pDevice->Unacquire()));
}
#endif
InputDeviceBase::~InputDeviceBase()
{
	//Unacquire();
	//m_pDevice->Release();
}

bool xInputManager::PostInputEvent( SInputEvent& event )
{
	// post process event
	if ( event.keyId >= eKI_Mouse1 && event.keyId <= eKI_Mouse8 )
	{
		POINT point;
		GetCursorPos( &point );
		ScreenToClient( m_hWnd, &point );

		event.value = point.x;
		event.value2 = point.y;
	}
	else if ( event.keyId == eKI_MouseX)
	{

		POINT point;
		GetCursorPos( &point );
		ScreenToClient( m_hWnd, &point );

		event.value2 = point.x;
	}
	else if ( event.keyId == eKI_MouseY)
	{

		POINT point;
		GetCursorPos( &point );
		ScreenToClient( m_hWnd, &point );

		event.value2 = point.y;
	}

	InputEventListeners::iterator it = m_listeners.begin();

	for (; it != m_listeners.end(); ++it)
	{
		if (*it)
		{
			(*it)->OnInputEvent( event );
		}
	}

	return true;

	// 处理按住的情况
	if (event.state == eIS_Pressed)
	{
		event.keyStatePtr->state = eIS_Down;
		m_holdKeys.push_back(event.keyStatePtr);
	}
	else if (event.keyStatePtr && event.keyStatePtr->state == eIS_Released && !m_holdKeys.empty())
	{
		// remove hold key
		int slot = -1;
		int last = m_holdKeys.size()-1;

		for (int i=last; i>=0; --i)
		{
			if (m_holdKeys[i] == event.keyStatePtr)
			{
				slot = i;
				break;
			}
		}
		if (slot != -1)
		{
			m_holdKeys[slot] = m_holdKeys[last];
			m_holdKeys.pop_back();
		}
	}

	return true;
}

void xInputManager::AddListener( IInputEventListener* listener )
{
	InputEventListeners::iterator it = m_listeners.begin();

	for (; it != m_listeners.end(); ++it)
	{
		if (*it == listener)
		{
			return;
		}
	}

	m_listeners.push_back(listener);
}

void xInputManager::RemoveListener( IInputEventListener* listener )
{
	InputEventListeners::iterator it = m_listeners.begin();

	for (; it != m_listeners.end(); ++it)
	{
		if (*it == listener)
		{
			m_listeners.erase(it);
		}
	}
}

bool xInputManager::AddInputDevice(InputDeviceBase* pDevice)
{
	if (pDevice)
	{
		if (pDevice->Init())
		{
			m_inputDevices.push_back(pDevice);
			return true;
		}
		delete pDevice;
	}
	return false;
}

void xInputManager::Destroy()
{
	InputDevices::iterator it = m_inputDevices.begin();
	for (; it != m_inputDevices.end(); ++it)
	{
		if ( *it )
		{
			delete (*it);
		}
	}

	//FreeDirectInput();
}

void xInputManager::Update()
{
	for (uint32 i=0; i < m_holdKeys.size(); ++i)
	{
		SInputEvent event;
		m_holdKeys[i]->MakeEvent(event);
		PostInputEvent( event );
	}

	InputDevices::iterator it = m_inputDevices.begin();
	for (; it != m_inputDevices.end(); ++it)
	{
		if ( *it )
		{
			(*it)->Update(true);
		}
	}
}
