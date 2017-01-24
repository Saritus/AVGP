#include "DIB.h"

// PixelgrafikenDlg.h: Headerdatei
//

#pragma once


// CPixelgrafikenDlg-Dialogfeld
class CPixelgrafikenDlg : public CDialogEx
{
	// Konstruktion
public:
	CPixelgrafikenDlg(CWnd* pParent = NULL);	// Standardkonstruktor

												// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PIXELGRAFIKEN_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung


														// Implementierung
protected:
	HICON m_hIcon;

	CDIB m_dib;
	CMenu menu;

	// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void draw_histogramm();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	BOOL OnCommand(WPARAM wParam, LPARAM lParam);
};
