
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
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterst�tzung


// Implementierung
protected:
	HICON m_hIcon;

	IGraphBuilder *pGraph; // ein Zeiger auf das COM-Interface
	IMediaControl *pMediaControl;
	IMediaEventEx *pEvent;
	IVideoWindow *pVidWin = NULL;
	IMediaSeeking *pSeek = NULL;

	// Generierte Funktionen f�r die Meldungstabellen
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg LONG GetIt(UINT wparam, LONG lparam);	void OnStop();	void OnResume();	void OnPause();	void CleanUp();
	
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
