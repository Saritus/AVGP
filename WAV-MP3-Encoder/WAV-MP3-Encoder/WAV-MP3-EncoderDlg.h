
// WAV-MP3-EncoderDlg.h: Headerdatei
//

#pragma once


// CWAVMP3EncoderDlg-Dialogfeld
class CWAVMP3EncoderDlg : public CDialogEx
{
// Konstruktion
public:
	CWAVMP3EncoderDlg(CWnd* pParent = NULL);	// Standardkonstruktor

// Dialogfelddaten
	enum { IDD = IDD_WAVMP3ENCODER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung


// Implementierung
protected:
	HICON m_hIcon;

	// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
