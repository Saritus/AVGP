
// WAV-MP3-EncoderDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "WAV-MP3-Encoder.h"
#include "WAV-MP3-EncoderDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWAVMP3EncoderDlg-Dialogfeld



CWAVMP3EncoderDlg::CWAVMP3EncoderDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWAVMP3EncoderDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWAVMP3EncoderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

static UINT NEAR WM_GRAPHNOTIFY = RegisterWindowMessage(L"GRAPHNOTIFY");

BEGIN_MESSAGE_MAP(CWAVMP3EncoderDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CWAVMP3EncoderDlg::OnBnClickedButton1)
	ON_REGISTERED_MESSAGE(WM_GRAPHNOTIFY, NewMessage)
END_MESSAGE_MAP()


// CWAVMP3EncoderDlg-Meldungshandler

BOOL CWAVMP3EncoderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Symbol für dieses Dialogfeld festlegen.  Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden

	// TODO: Hier zusätzliche Initialisierung einfügen

	return TRUE;  // TRUE zurückgeben, wenn der Fokus nicht auf ein Steuerelement gesetzt wird
}

// Wenn Sie dem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie
//  den nachstehenden Code, um das Symbol zu zeichnen.  Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch ausgeführt.

void CWAVMP3EncoderDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext zum Zeichnen

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Symbol in Clientrechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Die System ruft diese Funktion auf, um den Cursor abzufragen, der angezeigt wird, während der Benutzer
//  das minimierte Fenster mit der Maus zieht.
HCURSOR CWAVMP3EncoderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CWAVMP3EncoderDlg::OnBnClickedButton1()
{
	// Schritt 1:
	CoInitialize(NULL);
	CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
		IID_IGraphBuilder, (void **)&m_Graph1);

	// Schritt 2:
	CoCreateInstance(CLSID_AsyncReader, NULL, CLSCTX_INPROC_SERVER,
		IID_IBaseFilter, (void**)&g_pSource);
	const GUID CLSID_WAVEParser = { 0xD51BD5A1, 0x7548, 0x11CF, 0xA5, 0x20, 0x00,
		0x80, 0xC7, 0x7E, 0xF5, 0x8A };
	CoCreateInstance(CLSID_WAVEParser, NULL, CLSCTX_INPROC_SERVER,
		IID_IBaseFilter, (void**)(&g_pWaveParser));
	// const GUID CLSID_LameMP3Encoder = { 0xB8D27088, 0xFF5F, 0x4B7C, 0x98, 0xDC, 0x0E,
	// 0x91, 0xA1, 0x69, 0x62, 0x86 };
	const GUID CLSID_LameMP3Encoder = { 0xB8D27088, 0xDF5F, 0x4B7C, 0x98, 0xDC, 0x0E,
		0x91, 0xA1, 0x69, 0x62, 0x86 };
	CoCreateInstance(CLSID_LameMP3Encoder, NULL, CLSCTX_INPROC_SERVER,
		IID_IBaseFilter, (void**)(&g_pMP3Coder));
	const GUID CLSID_DumpFile = { 0x36A5F770, 0xFE4C, 0x11CE, 0xA8, 0xED, 0x00,
		0xAA, 0x00, 0x2F, 0xEA, 0xB5 };
	CoCreateInstance(CLSID_DumpFile, NULL, CLSCTX_INPROC_SERVER,
		IID_IBaseFilter, (void**)(&g_pDest));

	// Schritt 3:
	// Quellfile setzen
	IFileSourceFilter* FileSource = NULL;
	CString srcname;
	((CEdit*)GetDlgItem(IDC_EDIT1))->GetWindowTextW(srcname);
	g_pSource->QueryInterface(IID_IFileSourceFilter, (void**)&FileSource);
	FileSource->Load(srcname.AllocSysString(), NULL);
	FileSource->Release();
	// Zielfile setzen
	IFileSinkFilter* FileDest = NULL;
	CString destname;
	((CEdit*)GetDlgItem(IDC_OUTPUT))->GetWindowTextW(destname);
	g_pDest->QueryInterface(IID_IFileSinkFilter, (void**)&FileDest);
	FileDest->SetFileName(destname.AllocSysString(), NULL);
	FileDest->Release();

	// Schritt 4:
	if (m_Graph1->AddFilter(g_pSource, NULL) != S_OK) {
		AfxMessageBox(L"Fehler im Filtergraphen");
	}
	if (m_Graph1->AddFilter(g_pWaveParser, NULL) != S_OK) {
		AfxMessageBox(L"Fehler im Filtergraphen");
	}
	if (m_Graph1->AddFilter(g_pMP3Coder, NULL) != S_OK) {
		AfxMessageBox(L"Fehler im Filtergraphen");
	}
	if (m_Graph1->AddFilter(g_pDest, NULL) != S_OK) {
		AfxMessageBox(L"Fehler im Filtergraphen");
	}

	// Schritt 5:
	IPin *pPinIn = NULL, *pPinOut = NULL;
	if (g_pSource->FindPin(L"Output", &pPinOut) != S_OK)
		AfxMessageBox(L"Fehler im Filtergraphen");
	if (g_pWaveParser->FindPin(L"input pin", &pPinIn) != S_OK)
		AfxMessageBox(L"Fehler im Filtergraphen");
	if (m_Graph1->Connect(pPinOut, pPinIn) != S_OK)
		AfxMessageBox(L"Fehler im Filtergraphen");
	pPinIn->Release(); pPinOut->Release();
	if (g_pWaveParser->FindPin(L"output", &pPinOut) != S_OK)
		AfxMessageBox(L"Fehler im Filtergraphen");
	if (g_pMP3Coder->FindPin(L"In", &pPinIn) != S_OK)
		AfxMessageBox(L"Fehler im Filtergraphen");
	if (m_Graph1->Connect(pPinOut, pPinIn) != S_OK)
		AfxMessageBox(L"Fehler im Filtergraphen");
	pPinIn->Release(); pPinOut->Release();
	if (g_pMP3Coder->FindPin(L"Out", &pPinOut) != S_OK)
		AfxMessageBox(L"Fehler im Filtergraphen");
	if (g_pDest->FindPin(L"Input", &pPinIn) != S_OK)
		AfxMessageBox(L"Fehler im Filtergraphen");
	if (m_Graph1->Connect(pPinOut, pPinIn) != S_OK)
		AfxMessageBox(L"Fehler im Filtergraphen");
	pPinIn->Release(); pPinOut->Release();

	// Schritt 6:
	ISpecifyPropertyPages *pSpecify = NULL;
	if (g_pMP3Coder->QueryInterface(IID_ISpecifyPropertyPages,
		(void **)&pSpecify) == S_OK) {
		CAUUID caGUID;
		pSpecify->GetPages(&caGUID); pSpecify->Release();
		OleCreatePropertyFrame(
			this->GetSafeHwnd(), // Parent window
			0, // x (Reserved)
			0, // y (Reserved)
			L"MP3 Einstellungen", // Caption for the dialog box
			1, // Number of filters
			(IUnknown **)&g_pMP3Coder, // Pointer to the filter
			caGUID.cElems, // Number of property pages
			caGUID.pElems, // Pointer to property page CLSIDs
			0, // Locale identifier
			0, // Reserved
			NULL); // Reserved
		CoTaskMemFree(caGUID.pElems);
	}

	// Schritt 7:
	g_pSource->Release();
	g_pWaveParser->Release();
	g_pMP3Coder->Release();
	g_pDest->Release();

	// Schritt 8:
	m_Graph1->QueryInterface(IID_IMediaControl, (void **)&m_Ctrl1);
	m_Graph1->QueryInterface(IID_IMediaEventEx, (void **)&m_Event1);
	//m_Event1->SetNotifyWindow((long)GetSafeHwnd(), WM_GRAPHNOTIFY, NULL);
	m_Ctrl1->Run();
}

LONG CWAVMP3EncoderDlg::NewMessage(UINT wparam, LONG lparam) {
	LONG evCode, evParam1, evParam2;
	if (m_Event1)
		while (SUCCEEDED(m_Event1->GetEvent(&evCode, &evParam1, &evParam2, 0))) {
			m_Event1->FreeEventParams(evCode, evParam1, evParam2);
			switch (evCode) {
			case EC_COMPLETE:
				OnRelease();
				AfxMessageBox(L"Fertig"); return 0;
			case EC_USERABORT:
				OnRelease(); return 0;
			}
		}
	return 0;
}

void CWAVMP3EncoderDlg::OnRelease() {
	if (m_Ctrl1) {
		m_Ctrl1->Stop();
		m_Ctrl1->Release();
		m_Ctrl1 = NULL;
	}
	if (m_Event1) {
		m_Event1->Release();
		m_Event1 = NULL;
	}
	if (m_Graph1) {
		m_Graph1->Release();
		m_Graph1 = NULL;
	}
	CoUninitialize();
}

void CWAVMP3EncoderDlg::OnBnClickedButton2()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
}


void CWAVMP3EncoderDlg::OnBnClickedButton3()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
}
