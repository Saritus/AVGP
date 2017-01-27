
// DirectX_SoundDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "DirectX_Sound.h"
#include "DirectX_SoundDlg.h"
#include "afxdialogex.h"
#include <fstream>

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
	ON_BN_CLICKED(IDC_BUTTON2, &CDirectX_SoundDlg::OnBnClickedButton2)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_C, &CDirectX_SoundDlg::OnBnClickedC)
	ON_BN_CLICKED(IDC_D, &CDirectX_SoundDlg::OnBnClickedD)
	ON_BN_CLICKED(IDC_E, &CDirectX_SoundDlg::OnBnClickedE)
	ON_BN_CLICKED(IDC_F, &CDirectX_SoundDlg::OnBnClickedF)
	ON_BN_CLICKED(IDC_G, &CDirectX_SoundDlg::OnBnClickedG)
	ON_BN_CLICKED(IDC_A, &CDirectX_SoundDlg::OnBnClickedA)
	ON_BN_CLICKED(IDC_H, &CDirectX_SoundDlg::OnBnClickedH)
	ON_BN_CLICKED(IDC_C2, &CDirectX_SoundDlg::OnBnClickedC2)
	ON_BN_CLICKED(IDC_BUTTON5, &CDirectX_SoundDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON4, &CDirectX_SoundDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CDirectX_SoundDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_CHECK1, &CDirectX_SoundDlg::OnBnClickedCheck1)
END_MESSAGE_MAP()


// CDirectX_SoundDlg-Meldungshandler

BOOL CDirectX_SoundDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Symbol für dieses Dialogfeld festlegen.  Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden

	ton[0] = c;
	ton[1] = c * 9 / 8.;
	ton[2] = c * 5 / 4.;
	ton[3] = c * 4 / 3.;
	ton[4] = c * 3 / 2.;
	ton[5] = c * 5 / 3.;
	ton[6] = c * 15 / 8.;
	ton[7] = c * 2;
	ton[8] = 0;

	// creates a DirectSound object
	if (!m_ds.Create(this))
		OnCancel();

	// create a 4 second sound buffer
	if ((lpDSBSecondary = m_ds.CreateSoundBuffer(2, 16, 22050, 4)) == 0)
		OnCancel();

	// create 3 sound buffers
	for (int i = 0; i < 3; i++) {
		if ((lpDSBTri[i] = m_ds.CreateSoundBuffer(2, 16, 22050, 2)) == 0)
			OnCancel();
		m_ds.GenerateSound(lpDSBTri[i], 0, 2, ton[2 * i]);
	}

	// create 9 sound buffers
	for (int i = 0; i < 9; i++) {
		if ((lpDSBPiano[i] = m_ds.CreateSoundBuffer(2, 16, 22050, 1)) == 0)
			OnCancel();
		m_ds.GenerateSound(lpDSBPiano[i], 0, 1, ton[i]);
	}

	// set values for sliders
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER2))->SetRange(-5000, 0);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER2))->SetPos(-5000);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER2))->SetPos(0);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER3))->SetRange(-5000, 5000);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER3))->SetPos(5000);
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
	/* // Frequenzen einzeln in Soundbuffer schreiben
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
	*/

	m_ds.GenerateSound(lpDSBSecondary, 0, 2, 264);

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

	for (int i = 0; i < 3; i++) {
		if (!m_ds.SetPlaybackVolume(lpDSBTri[i], volume))
			OnCancel();
	}

	for (int i = 0; i < 9; i++) {
		if (!m_ds.SetPlaybackVolume(lpDSBPiano[i], volume))
			OnCancel();
	}

	*pResult = 0;
}


void CDirectX_SoundDlg::OnNMCustomdrawSlider3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	int balance = ((CSliderCtrl*)GetDlgItem(IDC_SLIDER3))->GetPos();
	if (!m_ds.SetBalance(lpDSBSecondary, balance))
		OnCancel();

	for (int i = 0; i < 3; i++) {
		if (!m_ds.SetBalance(lpDSBTri[i], balance))
			OnCancel();
	}

	for (int i = 0; i < 9; i++) {
		if (!m_ds.SetBalance(lpDSBPiano[i], balance))
			OnCancel();
	}
	*pResult = 0;
}


void CDirectX_SoundDlg::OnBnClickedButton2()
{
	SetTimer(1, 700, NULL);
	mode = 0; // 0 - Tonleiter, 1 - PCM-Datei

	m_ds.GenerateSound(lpDSBSecondary, 0, 2, 264);
	if (!m_ds.Play(lpDSBSecondary, true))
		OnCancel();
}


void CDirectX_SoundDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1) {
		switch (mode) {
		case 0:
			Tonleiter();
			break;
		case 1:
			PCM();
			m_ds.Play(lpDSBSecondary);
			break;
		default:
			break;
		}
	}
	else if (nIDEvent == 2) {
		CClientDC dc(this);

		const int transformLength = 1024; // ca. 50ms
		float fftVektor[transformLength * 2];

		// TODO: fill fftVektor
		m_ds;

		// Samples in fftVektor normalisieren
		// TODO:

		m_ds.smsFft(fftVektor, transformLength, -1);

		// magnitude-Vektor berechnen
		m_ds.calcMagnitude(fftVektor, transformLength);

		m_ds.DrawFFT(&dc, CRect(10, 70, 310, 120), transformLength);

	}
	CDialog::OnTimer(nIDEvent);
}

void CDirectX_SoundDlg::Tonleiter() {
	static int j = 0, buffnr = 1, playpos;
	if ((playpos = m_ds.GetPlayPosition(lpDSBSecondary)) == -1) {
		KillTimer(1); return;
	}
	if (((playpos > 50) && (buffnr == 0)) || ((playpos < 50) && (buffnr == 1))) {
		if ((++j) == 9) { // major scale finished
			KillTimer(1);
			j = 0;
			if (!m_ds.Stop(lpDSBSecondary))
				return;
			return;
		}

		if (((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck()) {
			// TODO: Use guitar sound for major scale
			m_ds.GenerateSound(lpDSBSecondary, buffnr * 2, 2, ton[j]);
		}
		else {
			m_ds.GenerateSound(lpDSBSecondary, buffnr * 2, 2, ton[j]);
		}

		if (buffnr == 1) buffnr = 0; // change buffer
		else buffnr = 1;
	}
}

void CDirectX_SoundDlg::PCM() {
	static int buffnr = 1, playpos;
	BOOL end;
	if ((playpos = m_ds.GetPlayPosition(lpDSBSecondary)) == -1) {
		KillTimer(1); return;
	}
	if (((playpos > 50) && (buffnr == 0)) || ((playpos < 50) && (buffnr == 1))) {
		m_ds.GenerateSound(lpDSBSecondary, buffnr * 2, 2, 0);
		end = m_ds.LoadPCMSound(lpDSBSecondary, buffnr * 2, 2, fileptr);
		if (!end) { // major scale finished
			KillTimer(1);
			if (!m_ds.Stop(lpDSBSecondary))
				return;
			return;
		}
		if (buffnr == 1) buffnr = 0; // change buffer
		else buffnr = 1;
	}
}

void CDirectX_SoundDlg::OnBnClickedC()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	if (!m_ds.Play(lpDSBPiano[0]))
		OnCancel();
}


void CDirectX_SoundDlg::OnBnClickedD()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	if (!m_ds.Play(lpDSBPiano[1]))
		OnCancel();
}


void CDirectX_SoundDlg::OnBnClickedE()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	if (!m_ds.Play(lpDSBPiano[2]))
		OnCancel();
}


void CDirectX_SoundDlg::OnBnClickedF()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	if (!m_ds.Play(lpDSBPiano[3]))
		OnCancel();
}


void CDirectX_SoundDlg::OnBnClickedG()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	if (!m_ds.Play(lpDSBPiano[4]))
		OnCancel();
}


void CDirectX_SoundDlg::OnBnClickedA()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	if (!m_ds.Play(lpDSBPiano[5]))
		OnCancel();
}


void CDirectX_SoundDlg::OnBnClickedH()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	if (!m_ds.Play(lpDSBPiano[6]))
		OnCancel();
}


void CDirectX_SoundDlg::OnBnClickedC2()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	if (!m_ds.Play(lpDSBPiano[7]))
		OnCancel();
}


void CDirectX_SoundDlg::OnBnClickedButton5()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	m_ds.Stop(lpDSBSecondary);
	m_ds.GenerateSound(lpDSBSecondary, 0, 4, 0);

	for (int i = 0; i < 3; i++) {
		m_ds.Stop(lpDSBTri[i]);
	}

	for (int i = 0; i < 9; i++) {
		m_ds.Stop(lpDSBPiano[i]);
	}
}


void CDirectX_SoundDlg::OnBnClickedButton4()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	FILE *file[3];

	file[0] = fopen("C.raw", "rb");
	file[1] = fopen("E.raw", "rb");
	file[2] = fopen("G.raw", "rb");

	for (int i = 0; i < 3; i++) {
		if (((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck()) {
			m_ds.LoadPCMSound(lpDSBTri[i], 0, 2, file[i]);
		}
		else {
			m_ds.GenerateSound(lpDSBTri[i], 0, 2, ton[2 * i]);
		}
	}

	for (int i = 0; i < 3; i++) {
		if (!m_ds.Play(lpDSBTri[i], true))
			OnCancel();
	}
}


void CDirectX_SoundDlg::OnBnClickedButton3()
{
	fileptr = fopen("Sound_22050_stereo_16Bit.pcm", "rb");  // Open the file in binary mode
	fseek(fileptr, 0, SEEK_END);          // Jump to the end of the file
	filelen = ftell(fileptr);             // Get the current byte offset in the file
	rewind(fileptr);                      // Jump back to the beginning of the file

	SetTimer(1, 200, NULL);
	SetTimer(2, 1000 / 20, NULL); // 1024 Samples
	mode = 1; // 0 - Tonleiter, 1 - PCM-Datei
}


void CDirectX_SoundDlg::OnBnClickedCheck1()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	if (((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck()) {
		FILE *file[9];

		file[0] = fopen("C.raw", "rb");
		file[1] = fopen("D.raw", "rb");
		file[2] = fopen("E.raw", "rb");
		file[3] = fopen("F.raw", "rb");
		file[4] = fopen("G.raw", "rb");
		file[5] = fopen("A.raw", "rb");
		file[6] = fopen("H.raw", "rb");
		file[7] = fopen("C_hoch.raw", "rb");
		file[8] = fopen("G.raw", "rb");

		for (int i = 0; i < 9; i++) {
			m_ds.LoadPCMSound(lpDSBPiano[i], 0, 1, file[i]);
		}
	}
	else {
		for (int i = 0; i < 9; i++) {
			m_ds.GenerateSound(lpDSBPiano[i], 0, 1, ton[i]);
		}
	}
}
