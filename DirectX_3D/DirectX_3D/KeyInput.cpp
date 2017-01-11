#include "stdafx.h"
#include "KeyInput.h"


CKeyInput::CKeyInput()
{
	lpDIKey = 0; lpDI = 0;
}

bool CKeyInput::Create(CWnd *wnd){
	if (FAILED(DirectInput8Create(GetModuleHandle(NULL),	  // Instanz 
		0x0800, IID_IDirectInput8,							// Version 
		(void**)(&lpDI),									// Doppelzeiger auf Objekt 
		NULL))) 
	{														// Nicht wichtig 
		AfxMessageBox(L"IDirectInput8-Interface nicht erstellt!"); 
		return false; 
	}													 
	
	// IDirectInputDevice8-Schnittstelle für die Tastatur erstellen 
	if(FAILED(lpDI->CreateDevice(GUID_SysKeyboard, &lpDIKey, NULL))){ 
		AfxMessageBox(L"KeyboardObject konnte nicht angelegt werden!"); 
		return false; 
	}															// Als nächstes wird das Datenformat gesetzt. 
	
	if(FAILED(lpDIKey->SetDataFormat(&c_dfDIKeyboard))){ 
		AfxMessageBox(L"Datenformat konnte nicht gesetzt werden!"); 
		return false; 
	}															// Ebene der Kooperation festlegen. 
	if(FAILED(lpDIKey->SetCooperativeLevel(wnd->GetSafeHwnd(), DISCL_NONEXCLUSIVE | DISCL_FOREGROUND))){ 
		AfxMessageBox(L"Kooperation konnte nicht gesetzt werden!"); 
		return false; 
	}
	return true; 
}

bool CKeyInput::KeyPressed(int key){


	if (!lpDIKey || (key<0) || (key>255)) 
		return false; static 
	
	BYTE aKey[256];  // Array von Tastenwerten
	// Vor der Abfrage muss der Zugriff gestartet werden! 
	if(FAILED(lpDIKey->Acquire())) 
		return false; 
	if(FAILED(lpDIKey->GetDeviceState(256,aKey))) 
		return false; 
	return (aKey[key] & 0x80) ? true : false;
}

BYTE* CKeyInput::KeyPressedAll(){
	
	if (!lpDIKey) 
		return 0; 
	static BYTE aKey[256];  // Array von Tastenwerten
	// Vor der Abfrage muss der Zugriff gestartet werden! 
	if(FAILED(lpDIKey->Acquire())) 
		return 0; 
	
	if(FAILED(lpDIKey->GetDeviceState(256,aKey))) 
		return 0; 
	
	return aKey;
}

bool CKeyInput::KeyPressedOnce(int key){

	if (!lpDIKey) return false; static BYTE aKey[256];  // Array von Tastenwerten 
	static BYTE aKeyO[256];								 // Array von bereits abgefragten Tastenwerten
	
	// Vor der Abfrage muss der Zugriff gestartet werden! 
	if (FAILED(lpDIKey->Acquire())) 
		return false; 
	
	if (FAILED(lpDIKey->GetDeviceState(256,aKey))) 
		return false; 
	
	if (aKey[key] & aKeyO[key] & 0x80) 
		return false;										 // abgefragt zum wiederholten Mal 
	
	if (aKey[key] & 0x80) {  
		aKeyO[key] = 0x80;								// Tastendruck merken    
		return true;									// abgefragt zum ersten Mal 
	}
	
	aKeyO[key] = 0x00;									 // abgefragt aber nicht (mehr) gedrückt 
	
	return false;
}

CString CKeyInput::GetDInputDevices(){
	return NULL;
}

CKeyInput::~CKeyInput()
{
	if (lpDIKey) lpDIKey->Release(); 
	if (lpDI) lpDI->Release();
}
