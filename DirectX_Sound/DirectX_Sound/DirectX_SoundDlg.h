
// DirectX_SoundDlg.h: Headerdatei
//

#pragma once
#include "DirectSound.h"

// CDirectX_SoundDlg-Dialogfeld
class CDirectX_SoundDlg : public CDialogEx
{
// Konstruktion
public:
	CDirectX_SoundDlg(CWnd* pParent = NULL);	// Standardkonstruktor

// Dialogfelddaten
	enum { IDD = IDD_DIRECTX_SOUND_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung


// Implementierung
protected:
	HICON m_hIcon;
	CDirectSound m_ds;
	LPDIRECTSOUNDBUFFER lpDSBSecondary;
	LPDIRECTSOUNDBUFFER lpDSBTri[3];
	LPDIRECTSOUNDBUFFER lpDSBPiano[9];

	double ton[9]; int c = 264; //Hz
	int mode = -1;

	FILE *fileptr;
	long filelen;

	// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	void Tonleiter();
	void PCM();
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSlider3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedC();
	afx_msg void OnBnClickedD();
	afx_msg void OnBnClickedE();
	afx_msg void OnBnClickedF();
	afx_msg void OnBnClickedG();
	afx_msg void OnBnClickedA();
	afx_msg void OnBnClickedH();
	afx_msg void OnBnClickedC2();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
};
