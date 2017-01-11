
// DirectX_3D.h: Hauptheaderdatei für die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error "'stdafx.h' vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"		// Hauptsymbole


// CDirectX_3DApp:
// Siehe DirectX_3D.cpp für die Implementierung dieser Klasse
//

class CDirectX_3DApp : public CWinApp
{
public:
	CDirectX_3DApp();

// Überschreibungen
public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern CDirectX_3DApp theApp;