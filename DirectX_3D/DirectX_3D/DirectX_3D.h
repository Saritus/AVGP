
// DirectX_3D.h: Hauptheaderdatei f�r die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error "'stdafx.h' vor dieser Datei f�r PCH einschlie�en"
#endif

#include "resource.h"		// Hauptsymbole


// CDirectX_3DApp:
// Siehe DirectX_3D.cpp f�r die Implementierung dieser Klasse
//

class CDirectX_3DApp : public CWinApp
{
public:
	CDirectX_3DApp();

// �berschreibungen
public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern CDirectX_3DApp theApp;