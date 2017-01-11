
// DirectX_Sound.h: Hauptheaderdatei für die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error "'stdafx.h' vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"		// Hauptsymbole


// CDirectX_SoundApp:
// Siehe DirectX_Sound.cpp für die Implementierung dieser Klasse
//

class CDirectX_SoundApp : public CWinApp
{
public:
	CDirectX_SoundApp();

// Überschreibungen
public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern CDirectX_SoundApp theApp;