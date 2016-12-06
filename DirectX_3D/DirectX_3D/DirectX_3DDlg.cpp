
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
	ON_BN_CLICKED(IDC_BUTTON2, &CDirectX_3DDlg::OnBnClickedButton2)
	ON_WM_CLOSE()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON3, &CDirectX_3DDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CDirectX_3DDlg-Meldungshandler

BOOL CDirectX_3DDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Symbol für dieses Dialogfeld festlegen.  Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden

	// TODO: Hier zusätzliche Initialisierung einfügen

	return TRUE;  // TRUE zurückgeben, wenn der Fokus nicht auf ein Steuerelement gesetzt wird
}

// Wenn Sie dem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie
//  den nachstehenden Code, um das Symbol zu zeichnen.  Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch ausgeführt.

void CDirectX_3DDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext zum Zeichnen

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

// Die System ruft diese Funktion auf, um den Cursor abzufragen, der angezeigt wird, während der Benutzer
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
		AfxMessageBox(L"Direct3D nicht verfügbar"); return;
	}
	//DisableButtons();
	// Set up our view matrix. A view matrix can be defined given an eye point,
	// a point to lookat, and a direction for which way is up. Here, we look at the
	// origin, and define "up" to be in the y-direction.
	D3DXVECTOR3 vEyePt(-2.0f, 1.5f, -4.0f),
		vLookatPt(0.0f, 0.0f, 0.0f),
		vUpVec(0.0f, 1.0f, 0.0f);
	if (!m_d3d.ViewTransform(vEyePt, vLookatPt, vUpVec))  {
		AfxMessageBox(L"ViewPoint konnte nicht initialisiert werden"); return;
	}
	LPD3DXFONT font = m_d3d.CreateD3DFont(12, L"Verdana", 0xffffffff);

	// 3 Beispielobjekte als "Modell"	
	D3DXVECTOR3 vertices[] = {

		// Rechteck 1
		D3DXVECTOR3(1.0f, 1.0f, 0.0f), // 0
		D3DXVECTOR3(1.0f, -1.0f, 0.0f), // 1
		D3DXVECTOR3(-1.0f, -1.0f, 0.0f), // 2
		D3DXVECTOR3(-1.0f, 1.0f, 0.0f), // 3

		// Rechteck 2
		D3DXVECTOR3(1.0f, 0.0f, 1.0f), // 4
		D3DXVECTOR3(1.0f, 0.0f, -1.0f), // 5
		D3DXVECTOR3(-1.0f, 0.0f, -1.0f), // 6
		D3DXVECTOR3(-1.0f, 0.0f, 1.0f), // 7
	};
	DWORD colors[] = { 0xffff0000,      // 0 - rot  
		0xff0000ff,      // 1 - blau 
		0xff00ff00,      // 2 - grün 
		0xffffffff,      // 3 - weiss 
		0xff000000,      // 4 - schwarz
		0xffffff00,      // 5 - gelb    (blau+rot)
		0xff00ff00,      // 6 - magenda (grün+blau)
		0xff00ff00       // 7 - cyan    (grün+rot)
	};
	int modell1[][2] = {                 // Modell 1 (Rechteck mit Farbe) 
		{ 1, 1 }, { 2, 2 }, { 0, 0 },
		{ 3, 3 }, { 0, 0 }, { 2, 2 },     // {vertex_nr, textur_nr}
	};
	o[0].BuildColoredVertexes(m_d3d.m_pd3dDevice, vertices, colors, modell1, 2);
	o[0].Rotate(0.0f, 0.0f, 0.0f);
	//o[0].Move(0.0f, -1.0f, 0.0f);
	o[1].BuildColoredVertexes(m_d3d.m_pd3dDevice, vertices, colors, modell1, 2);
	o[1].Rotate(1.57079632679f, 0.0f, 0.0f);
	//o[1].Move(0.0f, -2.0f, 0.0f);

	for (m_run = true; m_run;) {              // animation loop
		o[0].Rotate(-0.01f, 0.0f, 0.0f);
		o[1].Rotate(-0.01f, 0.0f, 0.0f);
		m_d3d.BeginRender();
		if (!m_d3d.Render(o, 2)) {
			AfxMessageBox(L"Szene konnte nicht gerendert werden"); return;
		}
		CString s;
		s.Format(L"%.2f fps", m_d3d.m_fps);
		m_d3d.TextOut(20, 20, s, font);
		m_d3d.EndRender();

		// process messages if there any
		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	font->Release();
}


void CDirectX_3DDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	MSG msg;

	if (!m_d3d.Create(GetDlgItem(IDC_OUTPUT), 0x00000000)) { // color as ARGB
		AfxMessageBox(L"Direct3D nicht verfügbar"); return;
	}
	//DisableButtons();
	// Set up our view matrix. A view matrix can be defined given an eye point,
	// a point to lookat, and a direction for which way is up. Here, we look at the
	// origin, and define "up" to be in the y-direction.
	D3DXVECTOR3 vEyePt(-2.0f, 1.5f, -4.0f),
		vLookatPt(0.0f, 0.0f, 0.0f),
		vUpVec(0.0f, 1.0f, 0.0f);
	if (!m_d3d.ViewTransform(vEyePt, vLookatPt, vUpVec))  {
		AfxMessageBox(L"ViewPoint konnte nicht initialisiert werden"); return;
	}
	LPD3DXFONT font = m_d3d.CreateD3DFont(12, L"Verdana", 0xffffffff);

	// 3 Beispielobjekte als "Modell"	
	D3DXVECTOR3 vertices[] = {

		// Rechteck 1
		D3DXVECTOR3(1.0f, 1.0f, 0.0f), // 0
		D3DXVECTOR3(1.0f, -1.0f, 0.0f), // 1
		D3DXVECTOR3(-1.0f, -1.0f, 0.0f), // 2
		D3DXVECTOR3(-1.0f, 1.0f, 0.0f), // 3

		// Rechteck 2
		D3DXVECTOR3(1.0f, 0.0f, 1.0f), // 4
		D3DXVECTOR3(1.0f, 0.0f, -1.0f), // 5
		D3DXVECTOR3(-1.0f, 0.0f, -1.0f), // 6
		D3DXVECTOR3(-1.0f, 0.0f, 1.0f), // 7
	};
	D3DXVECTOR2 textures[] = {
		D3DXVECTOR2(1.0f, 0.0f), // 0
		D3DXVECTOR2(1.0f, 1.0f), // 1
		D3DXVECTOR2(0.0f, 1.0f), // 2
		D3DXVECTOR2(0.0f, 0.0f), // 3
	};
	int modell1[][2] = {                 // Modell 1 (Rechteck mit Textur) 
		{ 1, 1 }, { 2, 2 }, { 0, 0 },
		{ 3, 3 }, { 0, 0 }, { 2, 2 },     // {vertex_nr, textur_nr}
	};
	//o[0].BuildColoredVertexes(m_d3d.m_pd3dDevice, vertices, colors, modell1, 1);
	o[0].BuildTexturedVertexes(m_d3d.m_pd3dDevice, vertices, textures, modell1, 2);
	o[0].SetTextureFromFile(L"chesstextur.jpg");
	o[0].ScaleTexture(1 / 3.f, 1 / 2.f);
	o[0].Rotate(0.0f, 0.0f, 0.0f);
	//o[0].Move(0.0f, -1.0f, 0.0f);
	o[1].BuildTexturedVertexes(m_d3d.m_pd3dDevice, vertices, textures, modell1, 2);
	o[1].SetTextureFromFile(L"chesstextur.jpg");
	o[1].ScaleTexture(1 / 3.f, 1 / 2.f);
	o[1].Rotate(1.57079632679f, 0.0f, 0.0f);
	//o[1].Move(0.0f, -2.0f, 0.0f);

	for (m_run = true; m_run;) {              // animation loop
		o[0].Rotate(-0.01f, 0.0f, 0.0f);
		o[1].Rotate(-0.01f, 0.0f, 0.0f);
		m_d3d.BeginRender();
		if (!m_d3d.Render(o, 2)) {
			AfxMessageBox(L"Szene konnte nicht gerendert werden"); return;
		}
		CString s;
		s.Format(L"%.2f fps\nDirect3D-Beispielanwendung", m_d3d.m_fps);
		m_d3d.TextOut(20, 20, s, font);
		m_d3d.EndRender();

		// process messages if there any
		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	font->Release();
}


void CDirectX_3DDlg::OnClose()
{
	m_run = false;
	CDialog::OnClose();
}


void CDirectX_3DDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	float rotaspeed = 0.05f;
	float movespeed = 0.05f;
	if (nFlags & MK_LBUTTON) {
		if (point.x < m_p.x) {
			o[0].Rotate(0.0f, rotaspeed, 0.0f);
			o[1].Rotate(0.0f, rotaspeed, 0.0f);
		}
		if (point.x > m_p.x) {
			o[0].Rotate(0.0f, -rotaspeed, 0.0f);
			o[1].Rotate(0.0f, -rotaspeed, 0.0f);
		}
		if (point.y < m_p.y) {
			o[0].Rotate(rotaspeed, 0.0f, 0.0f);
			o[1].Rotate(rotaspeed, 0.0f, 0.0f);
		}
		if (point.y > m_p.y) {
			o[0].Rotate(-rotaspeed, 0.0f, 0.0f);
			o[1].Rotate(-rotaspeed, 0.0f, 0.0f);
		}
		m_p = point;
	}
	else if (nFlags & MK_RBUTTON) {
		if (point.x < m_p.x) {
			o[0].Move(-movespeed, 0.0f, 0.0f);
			o[1].Move(-movespeed, 0.0f, 0.0f);
		}
		if (point.x > m_p.x) {
			o[0].Move(movespeed, 0.0f, 0.0f);
			o[1].Move(movespeed, 0.0f, 0.0f);
		}
		if (point.y < m_p.y) {
			o[0].Move(0.0, movespeed, 0.0f);
			o[1].Move(0.0, movespeed, 0.0f);
		}
		if (point.y > m_p.y) {
			o[0].Move(0.0, -movespeed, 0.0f);
			o[1].Move(0.0, -movespeed, 0.0f);
		}
		m_p = point;
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


void CDirectX_3DDlg::OnBnClickedButton3()
{
	MSG msg;

	if (!m_d3d.Create(GetDlgItem(IDC_OUTPUT), 0x00000000)) { // color as ARGB
		AfxMessageBox(L"Direct3D nicht verfügbar"); return;
	}
	//DisableButtons();

	// Set up our view matrix. A view matrix can be defined given an eye point,
	// a point to lookat, and a direction for which way is up. Here, we look at the
	// origin, and define "up" to be in the y-direction.
	D3DXVECTOR3 vEyePt(0.0f, 3.0f, -8.0f),
		vLookatPt(0.0f, 0.0f, 0.0f),
		vUpVec(0.0f, 1.0f, 0.0f);
	if (!m_d3d.ViewTransform(vEyePt, vLookatPt, vUpVec))  {
		AfxMessageBox(L"ViewPoint konnte nicht initialisiert werden"); return;
	}
	LPD3DXFONT font = m_d3d.CreateD3DFont(12, L"Verdana", 0xffffffff);

	o[0].BuildFromObtFile(m_d3d.m_pd3dDevice, "m_fish1.obt", 0.0025f);
	o[0].Rotate(-1.55f, 0.0f, 0.0f);
	o[0].Move(1.f, 0.0f, 0.0f);
	o[0].SetMaterial(0.0f, 0.0f, 1.0f);
	o[0].RenderWired(true);

	for (m_run = true; m_run;) {              // animation loop
		//o[0].Rotate(0.0f, 0.01f, 0.0f);
		m_d3d.BeginRender();
		if (!m_d3d.Render(o, 1)) {
			AfxMessageBox(L"Szene konnte nicht gerendert werden"); return;
		}
		CString s;
		s.Format(L"%.2f fps", m_d3d.m_fps);
		m_d3d.TextOut(20, 20, s, font);
		m_d3d.EndRender();

		// process messages if there any
		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	font->Release();
}
