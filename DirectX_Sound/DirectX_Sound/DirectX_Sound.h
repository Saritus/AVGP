
// DirectX_Sound.h: Hauptheaderdatei f�r die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error "'stdafx.h' vor dieser Datei f�r PCH einschlie�en"
#endif

#include "resource.h"		// Hauptsymbole


// CDirectX_SoundApp:
// Siehe DirectX_Sound.cpp f�r die Implementierung dieser Klasse
//

class CDirectX_SoundApp : public CWinApp
{
public:
	CDirectX_SoundApp();

// �berschreibungen
public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern CDirectX_SoundApp theApp;