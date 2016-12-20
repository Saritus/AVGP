
// DirectX_ShowDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "DirectX_Show.h"
#include "DirectX_ShowDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDirectX_ShowDlg-Dialogfeld



CDirectX_ShowDlg::CDirectX_ShowDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDirectX_ShowDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDirectX_ShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

static UINT NEAR WM_GRAPHNOTIFY = RegisterWindowMessage(L"GRAPHNOTIFY");

BEGIN_MESSAGE_MAP(CDirectX_ShowDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDirectX_ShowDlg::OnBnClickedButton1)
	ON_REGISTERED_MESSAGE(WM_GRAPHNOTIFY, GetIt)
	ON_WM_TIMER()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON2, &CDirectX_ShowDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_PAUSE, &CDirectX_ShowDlg::OnBnClickedPause)
	ON_BN_CLICKED(IDC_RESUME, &CDirectX_ShowDlg::OnBnClickedResume)
	ON_BN_CLICKED(IDC_STOP, &CDirectX_ShowDlg::OnBnClickedStop)
	ON_BN_CLICKED(IDC_VOLLBILD, &CDirectX_ShowDlg::OnBnClickedVollbild)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CDirectX_ShowDlg-Meldungshandler

BOOL CDirectX_ShowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Symbol f�r dieses Dialogfeld festlegen.  Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Gro�es Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden

	// TODO: Hier zus�tzliche Initialisierung einf�gen

	

	return TRUE;  // TRUE zur�ckgeben, wenn der Fokus nicht auf ein Steuerelement gesetzt wird
}

// Wenn Sie dem Dialogfeld eine Schaltfl�che "Minimieren" hinzuf�gen, ben�tigen Sie
//  den nachstehenden Code, um das Symbol zu zeichnen.  F�r MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch ausgef�hrt.

void CDirectX_ShowDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Ger�tekontext zum Zeichnen

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

// Die System ruft diese Funktion auf, um den Cursor abzufragen, der angezeigt wird, w�hrend der Benutzer
//  das minimierte Fenster mit der Maus zieht.
HCURSOR CDirectX_ShowDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDirectX_ShowDlg::OnBnClickedButton1()
{
	// TODO: F�gen Sie hier Ihren Kontrollbehandlungscode f�r die Benachrichtigung ein.
	CoInitialize(NULL); // zur Initialisierung des COM-Interfaces
	CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
		IID_IGraphBuilder, (void **)&pGraph);

	pGraph->QueryInterface(IID_IMediaControl, (void **)&pMediaControl);
	pGraph->QueryInterface(IID_IMediaEventEx, (void **)&pEvent);
	pGraph->QueryInterface(IID_IVideoWindow, (void **)&pVidWin);
	pGraph->QueryInterface(IID_IMediaSeeking, (void**)&pSeek);

	// Nachrichtenbehandlung (Maus, Keyboard)
	pVidWin->put_MessageDrain((OAHWND)GetSafeHwnd());

	pEvent->SetNotifyWindow((OAHWND)GetSafeHwnd(), WM_GRAPHNOTIFY, 0);

	SetTimer(1, 200, NULL);

	pGraph->RenderFile(filename, NULL);

	// set timeformat to 100-nanoseconds units
	if (pSeek->IsFormatSupported(&TIME_FORMAT_MEDIA_TIME) == S_OK)
		pSeek->SetTimeFormat(&TIME_FORMAT_MEDIA_TIME);
	else
		AfxMessageBox(L"Zeitformat wird nicht unterst�tzt");

	if (pSeek) {
		REFERENCE_TIME d;
		pSeek->GetDuration(&d);
		CSliderCtrl *sl;
		sl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER);
		sl->SetRange(0, (int)(d / 1000000)); sl->SetPos(0);
	}

	pVidWin->put_Owner((OAHWND)GetSafeHwnd());
	pVidWin->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS);
	pVidWin->put_Visible(OATRUE);
	pVidWin->SetWindowPosition(10, 70, 300, 200);

	pMediaControl->Run(); long evCode;
	//pEvent->WaitForCompletion(INFINITE, &evCode);

	

}

LONG CDirectX_ShowDlg::GetIt(UINT wparam, LONG lparam) {
	long evCode, param1, param2; HRESULT hr;
	while (SUCCEEDED(pEvent->GetEvent(&evCode, &param1, &param2, 0))) {
		pEvent->FreeEventParams(evCode, param1, param2);
		switch (evCode) {
		case EC_COMPLETE:
		case EC_USERABORT:
			CleanUp(); return 0;
		}
	}
	return 0;
}

void CDirectX_ShowDlg::OnStop() {
	if (pMediaControl != 0) {
		pMediaControl->Stop(); CleanUp();
	}
}

void CDirectX_ShowDlg::OnResume() {
	if (pMediaControl != 0)
		pMediaControl->Run();
}

void CDirectX_ShowDlg::OnPause() {
	if (pMediaControl != 0)
		pMediaControl->Pause();
}

void CDirectX_ShowDlg::CleanUp() {
	KillTimer(1);
	Vollbild(false);
	pVidWin->put_Visible(OAFALSE);
	pVidWin->put_Owner(NULL);
	pSeek->Release();
	pMediaControl->Release();
	pVidWin->Release();
	pEvent->Release();
	pGraph->Release();
	pMediaControl = 0; pVidWin = 0;
	pEvent = 0; pGraph = 0;
	CoUninitialize();
}

void CDirectX_ShowDlg::Vollbild(bool v) {
	if (pGraph) {
		IVideoWindow *pVidWin1 = NULL;
		pGraph->QueryInterface(IID_IVideoWindow, (void **)&pVidWin1);
		pVidWin1->put_FullScreenMode(v ? OATRUE : OAFALSE);
		pVidWin1->Release();
	}
}

void CDirectX_ShowDlg::OnTimer(UINT_PTR nIDEvent)
{
	REFERENCE_TIME rtTotal, rtNow = 0; CString s;
	pSeek->GetDuration(&rtTotal);
	pSeek->GetCurrentPosition(&rtNow);
	s.Format(L"Abspielvorgang: %02d:%02d (%d%%)",
		(int)((rtNow / 10000000L) / 60), // min
		(int)((rtNow / 10000000L) % 60), // sek
		(int)((rtNow * 100) / rtTotal)); // Prozent
	GetDlgItem(IDC_STATUS)->SetWindowText(s);

	((CSliderCtrl*)GetDlgItem(IDC_SLIDER))->SetPos((int)(rtNow / 1000000));
	CDialog::OnTimer(nIDEvent);

	CDialog::OnTimer(nIDEvent);
}


void CDirectX_ShowDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CSliderCtrl *sl1 = (CSliderCtrl*)GetDlgItem(IDC_SLIDER);
	if ((pSeek) && ((void*)sl1 == (void*)pScrollBar)) {
		REFERENCE_TIME pos = (REFERENCE_TIME)sl1->GetPos() * 1000000;
		pSeek->SetPositions(&pos, AM_SEEKING_AbsolutePositioning,
			NULL, AM_SEEKING_NoPositioning);
	}
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CDirectX_ShowDlg::OnBnClickedButton2()
{
	CString szFilters = L"AVI Files (*.avi)|*.avi|All Files (*.*)|*.*||";
	// Create an Open dialog; the default file name extension is ".my".
	CFileDialog fileDlg(TRUE, L"avi", L"*.avi", OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters, this);

	// Display the file dialog. When user clicks OK, fileDlg.DoModal()
	// returns IDOK.
	if (fileDlg.DoModal() == IDOK)
	{
		filename = fileDlg.GetPathName();
		GetDlgItem(IDC_FILENAME)->SetWindowText(filename);
	}
}


void CDirectX_ShowDlg::OnBnClickedPause()
{
	// TODO: F�gen Sie hier Ihren Kontrollbehandlungscode f�r die Benachrichtigung ein.
	OnPause();
}


void CDirectX_ShowDlg::OnBnClickedResume()
{
	// TODO: F�gen Sie hier Ihren Kontrollbehandlungscode f�r die Benachrichtigung ein.
	OnResume();
}


void CDirectX_ShowDlg::OnBnClickedStop()
{
	// TODO: F�gen Sie hier Ihren Kontrollbehandlungscode f�r die Benachrichtigung ein.
	OnStop();
}


void CDirectX_ShowDlg::OnBnClickedVollbild()
{
	// TODO: F�gen Sie hier Ihren Kontrollbehandlungscode f�r die Benachrichtigung ein.
	Vollbild(true);
}


void CDirectX_ShowDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	Vollbild(false);
	CDialog::OnLButtonDown(nFlags, point);
}
