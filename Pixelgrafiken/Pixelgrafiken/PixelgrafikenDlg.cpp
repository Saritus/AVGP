
// PixelgrafikenDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Pixelgrafiken.h"
#include "PixelgrafikenDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPixelgrafikenDlg-Dialogfeld



CPixelgrafikenDlg::CPixelgrafikenDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PIXELGRAFIKEN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPixelgrafikenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPixelgrafikenDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CPixelgrafikenDlg::OnBnClickedButton1)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CPixelgrafikenDlg-Meldungshandler

BOOL CPixelgrafikenDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Symbol für dieses Dialogfeld festlegen.  Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden

									// TODO: Hier zusätzliche Initialisierung einfügen
	if (!m_dib.Load("bild.bmp")) {
		AfxMessageBox(L"Keine bmp-Datei");
		OnCancel(); return FALSE;
	}

	return TRUE;  // TRUE zurückgeben, wenn der Fokus nicht auf ein Steuerelement gesetzt wird
}

// Wenn Sie dem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie
//  den nachstehenden Code, um das Symbol zu zeichnen.  Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch ausgeführt.

void CPixelgrafikenDlg::OnPaint()
{
	CPaintDC dc(this); // Gerätekontext zum Zeichnen

	CRect rect;
	GetClientRect(&rect);
	m_dib.Draw(&dc, 0, 0, rect.Width(), rect.Height());

	if (IsIconic())
	{
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
HCURSOR CPixelgrafikenDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPixelgrafikenDlg::draw_histogramm() {
	float h[256] = { 0.f }; int x = 10, y = 105;
	CClientDC dc(this);
	m_dib.histogramm(h, 20.f);
	dc.MoveTo(x, y); dc.LineTo(x + 255 + 2, y); // Rahmen zeichnen
	dc.LineTo(x + 255 + 2, y - 101); dc.LineTo(x, y - 101); dc.LineTo(x, y);
	CPen p(PS_SOLID, 1, RGB(255, 255, 0)); dc.SelectObject(&p);
	for (int i = 0; i < 255; i++) { // Histogramm zeichnen
		dc.MoveTo(x + i + 1, y - 1);
		dc.LineTo(x + i + 1, y - 1 - (100 * h[i]));
	}
}

void CPixelgrafikenDlg::OnBnClickedButton1()
{
	CPaintDC dc(this); // Gerätekontext zum Zeichnen
	m_dib.Draw(&dc, 0, 0);

	OnPaint();

	//CRect rect;
	//GetClientRect(&rect);
	//m_dib.Draw(&dc, 0, 0, rect.Width(), rect.Height());

	//draw_histogramm();
}


void CPixelgrafikenDlg::OnSize(UINT nType, int cx, int cy)
{
	RedrawWindow();
	CDialogEx::OnSize(nType, cx, cy);
}
