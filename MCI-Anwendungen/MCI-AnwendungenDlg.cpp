
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
	ON_BN_CLICKED(IDC_BUTTON6, &CMCIAnwendungenDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CMCIAnwendungenDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CMCIAnwendungenDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CMCIAnwendungenDlg::OnBnClickedButton9)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMCIAnwendungenDlg-Meldungshandler

BOOL CMCIAnwendungenDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Symbol für dieses Dialogfeld festlegen.  Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden

	SetTimer(1, 200, NULL);

	return TRUE;  // TRUE zurückgeben, wenn der Fokus nicht auf ein Steuerelement gesetzt wird
}

// Wenn Sie dem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie
//  den nachstehenden Code, um das Symbol zu zeichnen.  Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch ausgeführt.

void CMCIAnwendungenDlg::OnPaint()
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
	/*
	mci.OpenFile(L"Bombe.avi");
	mci.SetAviPosition(GetSafeHwnd(), CRect(30, 60, 210, 140));
	*/

	CRect r;
	GetDlgItem(IDC_DESTIN)->GetWindowRect(r);
	ScreenToClient(r);
	mci.OpenFile(L"Bombe.avi");
	mci.SetAviPosition(GetSafeHwnd(), CRect(r.left, r.top, r.Width(), r.Height()));
	GetDlgItem(IDC_Name)->SetWindowText(L"Bombe.avi");
}


void CMCIAnwendungenDlg::OnBnClickedButton3()
{
	// TODO: Open WAV
	LPCWSTR filename = L"XYLOPHON.wav";
	mci.OpenFile(filename);
	SetDlgItemText(IDC_Name, filename);
}

void CMCIAnwendungenDlg::OnBnClickedButton4()
{
	mci.OpenAudioCD(0, t);
	mci.TMSFSeek(1, 0, 0, 0); // erster Titel auf der Audio-CD

	BYTE min, sek, frame;
	CString text;
	for (int i = 1; i <= t; i++) {
		mci.GetTrackLength(i, min, sek, frame);
		text.Format(L"Track %02d [%02d:%02d]", i, min, sek);
		((CListBox*)GetDlgItem(IDC_LIST1))->AddString(text);
		// z.B. Eintrag in eine ListBox :-)
	}
}


void CMCIAnwendungenDlg::OnBnClickedButton5()
{
	//mci.Play();
}


void CMCIAnwendungenDlg::OnLbnSelchangeList1()
{
	mci.TMSFSeek(((CListBox*)GetDlgItem(IDC_LIST1))->GetCurSel() + 1, 0, 0, 0);
	mci.Play();
}


void CMCIAnwendungenDlg::OnBnClickedButton6()
{
	if (mci.getPlayed())
		mci.Pause();
	else
		mci.Play();
}


void CMCIAnwendungenDlg::OnBnClickedButton7()
{
	mci.Stop();
	mci.TMSFSeek(0, 0, 0, 0);
}


void CMCIAnwendungenDlg::OnBnClickedButton8()
{
	mci.Close();
	// TODO: Alles reseten
}


void CMCIAnwendungenDlg::OnBnClickedButton9()
{
	// TODO: Eject
}


void CMCIAnwendungenDlg::OnTimer(UINT_PTR nIDEvent)
{
	// Abfrage des Abspielstandes
	CString str;
	unsigned char t, m, s, f;
	mci.GetTMSFPosition(t, m, s, f);
	int akt = m * 60 + s;

	// Abfrage der Trackinformationen
	BYTE min, sek, frame;
	mci.GetTrackLength(t, min, sek, frame);
	int ges = min * 60 + sek;

	// Berechnen des Fortschritts
	int progress;
	if (ges > 0) {
		progress = 100 * akt / ges;
	}
	else {
		progress = 0;
	}


	// Ausgabe der Abspielzeit
	str.Format(L"%02d:%02d/%02d:%02d - %d%%", m, s, min, sek, progress);
	SetDlgItemText(IDC_AKTUELL, str);

	// TODO: Scrollbar fixen
	((CScrollBar*)GetDlgItem(IDC_SCROLLBAR))->SetScrollRange(0, ges);
	((CScrollBar*)GetDlgItem(IDC_SCROLLBAR))->SetScrollPos(0, akt);

	// Weitergabe des Events
	CDialog::OnTimer(nIDEvent);
}
