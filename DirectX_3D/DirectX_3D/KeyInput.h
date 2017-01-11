#pragma once
#include <dinput.h> 


class CKeyInput{

public:
	CKeyInput();
	bool Create(CWnd* wnd);
	CString GetDInputDevices(); 
	bool KeyPressed(int key);
	bool KeyPressedOnce(int key); 
	BYTE*KeyPressedAll(); 
	virtual ~CKeyInput();

private:

	LPDIRECTINPUT8       lpDI;    // DirectInput-Interface 
	LPDIRECTINPUTDEVICE8 lpDIKey; // Tastatur-Interface

};

