
// DirectX_ShowDlg.h: Headerdatei
//

#pragma once

#include "DirectShow.h"


// CDirectX_ShowDlg-Dialogfeld
class CDirectX_ShowDlg : public CDialogEx
{
// Konstruktion
public:
	CDirectX_ShowDlg(CWnd* pParent = NULL);	// Standardkonstruktor

// Dialogfelddaten
	enum { IDD = IDD_DIRECTX_SHOW_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung


// Implementierung
protected:
	HICON m_hIcon;

	CDirectShow directshow;

	// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg LONG GetIt(UINT wparam, LONG lparam);


	
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedPause();
	afx_msg void OnBnClickedResume();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedVollbild();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void buttonsEnabled(bool);
	afx_msg void OnClose();
};
