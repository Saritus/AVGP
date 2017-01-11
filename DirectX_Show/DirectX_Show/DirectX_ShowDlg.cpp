
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
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDirectX_ShowDlg-Meldungshandler

BOOL CDirectX_ShowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Symbol für dieses Dialogfeld festlegen.  Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden

	// TODO: Hier zusätzliche Initialisierung einfügen	
	directshow.setWindow((OAHWND)GetSafeHwnd());
	directshow.setNotifyWindow(WM_GRAPHNOTIFY);

	return TRUE;  // TRUE zurückgeben, wenn der Fokus nicht auf ein Steuerelement gesetzt wird
}

// Wenn Sie dem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie
//  den nachstehenden Code, um das Symbol zu zeichnen.  Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch ausgeführt.

void CDirectX_ShowDlg::OnPaint()
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
HCURSOR CDirectX_ShowDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDirectX_ShowDlg::OnBnClickedButton1()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	directshow.setVideoWindow();
	directshow.Run();
	SetTimer(1, 200, NULL);

}

LONG CDirectX_ShowDlg::GetIt(UINT wparam, LONG lparam) {
	return directshow.GetIt(wparam, lparam);
}

void CDirectX_ShowDlg::OnTimer(UINT_PTR nIDEvent)
{
	REFERENCE_TIME rtTotal, rtNow = 0; CString s;
	rtTotal = directshow.getLenght();
	rtNow = directshow.getCurrentPosition();
	s.Format(L"Zeit: %02d:%02d (%d%%)",
		(int)((rtNow / 10000000L) / 60), // min
		(int)((rtNow / 10000000L) % 60), // sek
		(int)((rtNow * 100) / rtTotal)); // Prozent
	GetDlgItem(IDC_STATUS)->SetWindowText(s);


	REFERENCE_TIME d;
	d = directshow.getLenght();
	CSliderCtrl *sl;
	sl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER);
	sl->SetRange(0, (int)(d / 1000000)); sl->SetPos(0);


	((CSliderCtrl*)GetDlgItem(IDC_SLIDER))->SetPos((int)(rtNow / 1000000));
	CDialog::OnTimer(nIDEvent);
}


void CDirectX_ShowDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CSliderCtrl *sl1 = (CSliderCtrl*)GetDlgItem(IDC_SLIDER);
	if ((void*)sl1 == (void*)pScrollBar) {
		REFERENCE_TIME pos = (REFERENCE_TIME)sl1->GetPos() * 1000000;
		directshow.setCurrentPosition(pos);
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
		directshow.setFilename(fileDlg.GetPathName());
		GetDlgItem(IDC_FILENAME)->SetWindowText(directshow.filename);
	}
}


void CDirectX_ShowDlg::OnBnClickedPause()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	directshow.Pause();
}


void CDirectX_ShowDlg::OnBnClickedResume()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	directshow.Resume();
}


void CDirectX_ShowDlg::OnBnClickedStop()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	KillTimer(1);
	directshow.Stop();
}


void CDirectX_ShowDlg::OnBnClickedVollbild()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	directshow.Vollbild(true);
}


void CDirectX_ShowDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	directshow.Vollbild(false);
	CDialog::OnLButtonDown(nFlags, point);
}

void CDirectX_ShowDlg::buttonsEnabled(bool) {

}

void CDirectX_ShowDlg::OnClose()
{
	// TODO: Fügen Sie hier Ihren Meldungsbehandlungscode ein, und/oder benutzen Sie den Standard.
	directshow.CleanUp();
	CDialogEx::OnClose();
}
