
// DirectX_ShowDlg.h: Headerdatei
//

#pragma once


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

	// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
