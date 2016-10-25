
// MCI-AnwendungenDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "MCI-Anwendungen.h"
#include "MCI-AnwendungenDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMCIAnwendungenDlg-Dialogfeld



CMCIAnwendungenDlg::CMCIAnwendungenDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMCIAnwendungenDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMCIAnwendungenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMCIAnwendungenDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMCIAnwendungenDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMCIAnwendungenDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMCIAnwendungenDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMCIAnwendungenDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMCIAnwendungenDlg::OnBnClickedButton5)
	ON_LBN_SELCHANGE(IDC_LIST1, &CMCIAnwendungenDlg::OnLbnSelchangeList1)
END_MESSAGE_MAP()


// CMCIAnwendungenDlg-Meldungshandler

BOOL CMCIAnwendungenDlg::OnInitDialog()
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

void CMCIAnwendungenDlg::OnPaint()
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
HCURSOR CMCIAnwendungenDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMCIAnwendungenDlg::OnBnClickedButton1()
{
	//CButton* btn = (CButton*) GetDlgItem(IDC_BUTTON2);
	//btn->SetWindowText(_T("Lahore"));
	exit(0);
}


void CMCIAnwendungenDlg::OnBnClickedButton2()
{
	mci.OpenFile(L"Bombe.avi");
	mci.SetAviPosition(GetSafeHwnd(), CRect(30, 60, 210, 140));
	mci.Play();
}


void CMCIAnwendungenDlg::OnBnClickedButton3()
{
	// TODO: Open WAV	mci.OpenFile(L"XYLOPHON.wav");
	mci.Play();
}

void CMCIAnwendungenDlg::OnBnClickedButton4()
{
	mci.OpenAudioCD(L"e:", t);
	mci.TMSFSeek(2, 0, 0, 0); // zweiter Titel auf der Audio-CD
	mci.Play();

	BYTE min, sek, frame;
	CString text;
	for (int i = 1; i <= t; i++) {
		mci.GetTrackLength(i, min, sek, frame);
		text.Format(L"Track %d [%d:%d]", i, min, sek);
		((CListBox*)GetDlgItem(IDC_LIST1))->AddString(text);
		// z.B. Eintrag in eine ListBox :-)
	}
}


void CMCIAnwendungenDlg::OnBnClickedButton5()
{
	// TODO: Open MIDI
}


void CMCIAnwendungenDlg::OnLbnSelchangeList1()
{
	mci.TMSFSeek(((CListBox*)GetDlgItem(IDC_LIST1))->GetCurSel() + 1, 0, 0, 0);
	mci.Play();
}
