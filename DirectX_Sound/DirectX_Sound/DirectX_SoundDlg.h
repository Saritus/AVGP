
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

	// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSlider3(NMHDR *pNMHDR, LRESULT *pResult);
};
