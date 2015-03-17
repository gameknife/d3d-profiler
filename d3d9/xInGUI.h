/**
  @file gkInGUI.h
  
  @author Kaiming

  更改日志 history
  ver:1.0
   
 */

#ifndef _gkInGUI_H_
#define _gkInGUI_H_


#include "InputManager.h"

struct IgkFont;

struct gkPopupMsgStruct
{
	std::string m_msg;
	float m_time;
	float m_totalTime;

	gkPopupMsgStruct(const std::string& msg, float time):m_msg(msg), m_time(time), m_totalTime(time)
	{

	}
};

class gkInGUI : public IInputEventListener
{
	enum EMouseState
	{
		Pressing,
		Hold,
		Releasing,
		Released,
	};

public:
	gkInGUI(void);
	~gkInGUI(void);

	void Init();
	void Shutdown();
	void Update(float fElapsedTime);

	bool gkGUIButton(const TCHAR* title, const float2& pos, int width, int height, const float4& textColor, const float4& bgColor, IgkFont* font = NULL);
	void gkPopupMsg(const TCHAR* title);

	virtual bool OnInputEvent( const SInputEvent &event );

	EMouseState m_LMBState;
	float2 m_lastPoint;
	IgkFont* m_defaultFont;

	std::vector<gkPopupMsgStruct> m_popupMsgs;
};

#endif




