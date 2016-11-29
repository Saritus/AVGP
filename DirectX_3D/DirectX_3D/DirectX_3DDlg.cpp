
// DirectX_3DDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "DirectX_3D.h"
#include "DirectX_3DDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDirectX_3DDlg-Dialogfeld



CDirectX_3DDlg::CDirectX_3DDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDirectX_3DDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDirectX_3DDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDirectX_3DDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDirectX_3DDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDirectX_3DDlg-Meldungshandler

BOOL CDirectX_3DDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Symbol f�r dieses Dialogfeld festlegen.  Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Gro�es Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden

	// TODO: Hier zus�tzliche Initialisierung einf�gen

	return TRUE;  // TRUE zur�ckgeben, wenn der Fokus nicht auf ein Steuerelement gesetzt wird
}

// Wenn Sie dem Dialogfeld eine Schaltfl�che "Minimieren" hinzuf�gen, ben�tigen Sie
//  den nachstehenden Code, um das Symbol zu zeichnen.  F�r MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch ausgef�hrt.

void CDirectX_3DDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Ger�tekontext zum Zeichnen

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Symbol in Clientrechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Die System ruft diese Funktion auf, um den Cursor abzufragen, der angezeigt wird, w�hrend der Benutzer
//  das minimierte Fenster mit der Maus zieht.
HCURSOR CDirectX_3DDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDirectX_3DDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	MSG msg;

	if (!m_d3d.Create(GetDlgItem(IDC_OUTPUT), 0x00000000)) { // color as ARGB
		AfxMessageBox(L"Direct3D nicht verf�gbar"); return;
	}
	//DisableButtons();
	// Set up our view matrix. A view matrix can be defined given an eye point,
    // a point to lookat, and a direction for which way is up. Here, we look at the
    // origin, and define "up" to be in the y-direction.
    D3DXVECTOR3 vEyePt( 0.0f, 3.0f, -8.0f ),
				vLookatPt( 0.0f, 0.0f, 0.0f ),
				vUpVec( 0.0f, 1.0f, 0.0f );
	if (!m_d3d.ViewTransform(vEyePt, vLookatPt, vUpVec))  {
		AfxMessageBox(L"ViewPoint konnte nicht initialisiert werden"); return;
	}	
	LPD3DXFONT font = m_d3d.CreateD3DFont(12, L"Verdana", 0xffffffff);

	// 3 Beispielobjekte als "Modell"	
	D3DXVECTOR3 vertices[] = {
		D3DXVECTOR3(-1.0f,-1.0f, 0.0f), // 0
        D3DXVECTOR3( 1.0f,-1.0f, 0.0f), // 1
        D3DXVECTOR3( 0.0f, 1.0f, 0.0f), // 2
        D3DXVECTOR3(-1.0f, 1.0f, 0.0f), // 3
        D3DXVECTOR3( 1.0f, 1.0f, 0.0f), // 4
        D3DXVECTOR3(-1.0f,-1.0f, 2.0f), // 5
        D3DXVECTOR3( 1.0f,-1.0f, 2.0f), // 6
        D3DXVECTOR3(-1.0f, 1.0f, 2.0f), // 7
        D3DXVECTOR3( 1.0f, 1.0f, 2.0f)  // 8
	};
	D3DXVECTOR2 textures[] = {
		D3DXVECTOR2( 0.0f, 0.0f), // 0
		D3DXVECTOR2( 1.0f, 0.0f), // 1
		D3DXVECTOR2( 0.0f, 1.0f), // 2
		D3DXVECTOR2( 1.0f, 1.0f), // 3
	};
	DWORD colors[] = { 0xffff0000,      // 0 - rot  
		               0xff0000ff,      // 1 - blau 
				   	   0xff00ff00,      // 2 - gr�n 
				   	   0xffffffff,      // 3 - weiss 
				   	   0xff000000,      // 4 - schwarz
				   	   0xffffff00,      // 5 - gelb    (blau+rot)
				   	   0xff00ff00,      // 6 - magenda (gr�n+blau)
				   	   0xff00ff00       // 7 - cyan    (gr�n+rot)
    }; 
	int modell1[][2] = {                // Modell 1 (Dreieck) 
		{ 0, 0} , { 1, 1} , { 2, 2} };  // {vertex_nr, color_nr}
	int modell2[][2] = {                // Modell 2 (W�rfel) 
		{ 0, 4} , { 1, 0} , { 3, 1},
		{ 1, 0} , { 3, 1} , { 4, 5},
		{ 1, 0} , { 4, 5} , { 6, 7},
		{ 6, 7} , { 4, 5} , { 8, 3},
		{ 5, 2} , { 7, 6} , { 6, 7},
		{ 6, 7} , { 7, 6} , { 8, 3},
		{ 0, 4} , { 3, 1} , { 5, 2},
		{ 3, 1} , { 5, 2} , { 7, 6},
		{ 0, 4} , { 1, 0} , { 5, 2},
		{ 1, 0} , { 5, 2} , { 6, 7},
		{ 3, 1} , { 4, 5} , { 7, 6},
		{ 4, 5} , { 7, 6} , { 8, 3}	     // {vertex_nr, color_nr}
	}; 
	int modell3[][2] = {                 // Modell 3 (Rechteck mit Textur) 
		{ 0, 2} , { 1, 3} , { 3, 0},
		{ 1, 3} , { 3, 0} , { 4, 1},     // {vertex_nr, textur_nr}
	}; 
	o[0].BuildColoredVertexes(m_d3d.m_pd3dDevice, vertices, colors, modell1, 1);
	o[0].Move(-1.5f, 1.0f, 1.0f);
	o[1].BuildColoredVertexes(m_d3d.m_pd3dDevice, vertices, colors, modell2, 12);
    o[1].Move( 1.5f, 1.0f, 1.0f);
	if (((CButton*)GetDlgItem(IDC_CHECK))->GetCheck()) {
		o[2].BuildTexturedVertexes(m_d3d.m_pd3dDevice, vertices, textures, modell3, 2);
		o[2].SetTextureFromFile(L"textur.jpg");
		o[2].ScaleTexture(1 / 3.f, 1 / 2.f);
		o[2].Move(0.0f, -1.0f, 0.0f);
	}
	else {
		o[0].BuildColoredVertexes(m_d3d.m_pd3dDevice, vertices, colors, modell3, 2);
		o[2].Move(0.0f, -1.0f, 0.0f);
	}
 
	for(m_run=true;m_run;) {              // animation loop
		o[0].Rotate(0.0f, 0.01f, 0.0f);
		o[1].Rotate(-0.01f, -0.01f, 0.0f);
		o[1].Scale(0.999f, 0.999f, 0.999f);
		o[2].Rotate(-0.01f, 0.0f, 0.0f);
		m_d3d.BeginRender();		
			if (!m_d3d.Render(o,3)) {
				AfxMessageBox(L"Szene konnte nicht gerendert werden"); return;
			}
			CString s;
			s.Format(L"%.2f fps\nDirect3D-Beispielanwendung", m_d3d.m_fps);
			m_d3d.TextOut(20,20,s,font);	
		m_d3d.EndRender();

		// process messages if there any
		while (PeekMessage(&msg,0,0,0,PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	font->Release();
}