
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

BEGIN_MESSAGE_MAP(CDirectX_ShowDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
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

