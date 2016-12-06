
// DirectX_3DDlg.h: Headerdatei
//

#pragma once


// CDirectX_3DDlg-Dialogfeld
class CDirectX_3DDlg : public CDialogEx
{
// Konstruktion
public:
	CDirectX_3DDlg(CWnd* pParent = NULL);	// Standardkonstruktor

// Dialogfelddaten
	enum { IDD = IDD_DIRECTX_3D_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung


// Implementierung
protected:
	HICON m_hIcon;

	CDirect3D m_d3d;
	CDirect3DObject o[5];
	bool m_run;
	CPoint m_p;

	LPDIRECT3D9 m_pD3D; // Used to create the D3DDevice
	LPDIRECT3DDEVICE9 m_pd3dDevice; // Our rendering device
	IDirect3DVertexBuffer9* m_pVB; // vertex buffer

	// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnClose();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
