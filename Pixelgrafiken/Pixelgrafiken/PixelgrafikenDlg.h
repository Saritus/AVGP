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
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterst�tzung


														// Implementierung
protected:
	HICON m_hIcon;

	CDIB m_dib;

	// Generierte Funktionen f�r die Meldungstabellen
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void draw_histogramm();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
