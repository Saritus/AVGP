
// MCI-AnwendungenDlg.h: Headerdatei
//

#pragma once
#include "MCIObject.h"

// CMCIAnwendungenDlg-Dialogfeld
class CMCIAnwendungenDlg : public CDialogEx
{
// Konstruktion
public:
	CMCIAnwendungenDlg(CWnd* pParent = NULL);	// Standardkonstruktor

// Dialogfelddaten
	enum { IDD = IDD_MCIANWENDUNGEN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterst�tzung


// Implementierung
protected:
	HICON m_hIcon;
	CMCIObject mci;
	BYTE t;
	BYTE trackcount;

	// Generierte Funktionen f�r die Meldungstabellen
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnLbnSelchangeList1();
};
