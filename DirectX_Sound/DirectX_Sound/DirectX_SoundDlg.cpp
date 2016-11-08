
// DirectX_SoundDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "DirectX_Sound.h"
#include "DirectX_SoundDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDirectX_SoundDlg-Dialogfeld



CDirectX_SoundDlg::CDirectX_SoundDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDirectX_SoundDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDirectX_SoundDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDirectX_SoundDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDirectX_SoundDlg::OnBnClickedButton1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, &CDirectX_SoundDlg::OnNMCustomdrawSlider2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER3, &CDirectX_SoundDlg::OnNMCustomdrawSlider3)
END_MESSAGE_MAP()


// CDirectX_SoundDlg-Meldungshandler

BOOL CDirectX_SoundDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Symbol für dieses Dialogfeld festlegen.  Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden

	// creates a DirectSound object
	if (!m_ds.Create(this))
		OnCancel();

	// create a 4 second sound buffer
	if ((lpDSBSecondary = m_ds.CreateSoundBuffer(2, 16, 22050, 4)) == 0)
		OnCancel();

	// set values for sliders
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER2))->SetRange(-5000, 0);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER2))->SetPos(0);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER3))->SetRange(-5000, 5000);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER3))->SetPos(0);

	return TRUE;  // TRUE zurückgeben, wenn der Fokus nicht auf ein Steuerelement gesetzt wird
}

// Wenn Sie dem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie
//  den nachstehenden Code, um das Symbol zu zeichnen.  Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch ausgeführt.

void CDirectX_SoundDlg::OnPaint()
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
HCURSOR CDirectX_SoundDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDirectX_SoundDlg::OnBnClickedButton1()
{
	void *lpvPtr1, *lpvPtr2; DWORD dwBytes1, dwBytes2;
	if (!m_ds.LockBuffer(lpDSBSecondary, 0, 2, // we use the first 2 seconds
		&lpvPtr1, // get pointer 1
		&dwBytes1, // get bytes available there
		&lpvPtr2, // get pointer 2 (the buffer is circular)
		&dwBytes2)) // get bytes available there
		return; // false;
	// write a sinus sound now (88040/63 = 1397 Hz)
	DWORD i; short int *t; // points to 16 Bit
	for (i = 0, t = (short int*)lpvPtr1; i<(dwBytes1 + dwBytes2); i += 4, t += 2) {
		if (i == dwBytes1) t = (short int*)lpvPtr2;
		// 2 channels with 16 Bit each
		*t = *(t + 1) = (short int)(sin(i / 10.0) * 30000);
	}
	if (!m_ds.UnlockBuffer(lpDSBSecondary,
		lpvPtr1, // pointer 1
		dwBytes1, // bytes written there
		lpvPtr2, // pointer 2
		dwBytes2)) // bytes written there
		return; // false;

	if (!m_ds.Play(lpDSBSecondary, true))
		OnCancel();
}


void CDirectX_SoundDlg::OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	int volume = ((CSliderCtrl*)GetDlgItem(IDC_SLIDER2))->GetPos();
	if (!m_ds.SetPlaybackVolume(lpDSBSecondary, volume))
		OnCancel();

	*pResult = 0;
}


void CDirectX_SoundDlg::OnNMCustomdrawSlider3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	int balance = ((CSliderCtrl*)GetDlgItem(IDC_SLIDER3))->GetPos();
	if (!m_ds.SetBalance(lpDSBSecondary, balance))
		OnCancel();
	*pResult = 0;
}
