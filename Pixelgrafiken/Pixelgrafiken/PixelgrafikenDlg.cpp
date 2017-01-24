
// PixelgrafikenDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Pixelgrafiken.h"
#include "PixelgrafikenDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPixelgrafikenDlg-Dialogfeld



CPixelgrafikenDlg::CPixelgrafikenDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PIXELGRAFIKEN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPixelgrafikenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPixelgrafikenDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_WM_MENUSELECT()
END_MESSAGE_MAP()


// CPixelgrafikenDlg-Meldungshandler

BOOL CPixelgrafikenDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	histogram = false;

	create_popup_menu();

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

void CPixelgrafikenDlg::OnPaint()
{
	CPaintDC dc(this); // Gerätekontext zum Zeichnen

	CRect rect;
	GetClientRect(&rect);
	m_dib.Draw(&dc, 0, 0, rect.Width(), rect.Height());
	if (histogram) {
		draw_histogram();
	}

	if (IsIconic())
	{
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
HCURSOR CPixelgrafikenDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPixelgrafikenDlg::OnSize(UINT nType, int cx, int cy)
{
	RedrawWindow();
	CDialogEx::OnSize(nType, cx, cy);
}


void CPixelgrafikenDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, point.x, point.y, this);
}


void CPixelgrafikenDlg::OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu)
{
	CDialogEx::OnMenuSelect(nItemID, nFlags, hSysMenu);
}


BOOL CPixelgrafikenDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	int sharpen_matrix[9] = { -1,-1,-1,-1,9,-1,-1,-1,-1 }; // 12
	int soften_matrix[9] = { 6,12,6,12,25,12,6,12,6 }; // 13
	int emboss_matrix[9] = { -1,0,0,0,0,0,0,0,1 }; // 14
	int edge_matrix[9] = { -1,-1,-1,-1,8,-1,-1,-1,-1 }; // 15

	char strFilter[] = { "Windows Bitmap (*.bmp)|*.bmp|JPEG File (*.jpg)|*.jpg|" };
	CFileDialog SaveFileDlg(FALSE, CString(".bmp"), NULL, 0, CString(strFilter));
	CFileDialog OpenFileDlg(TRUE, CString(".bmp"), NULL, 0, CString(strFilter));

	switch (wParam)
	{
	case 1001: // Laden
		if (OpenFileDlg.DoModal() == IDOK)
		{
			if (OpenFileDlg.GetFileExt() == L"bmp") {
				CString agendaName = OpenFileDlg.GetFileName(); //filename
				CString agendaPath = OpenFileDlg.GetFolderPath(); //filepath (folders)
				m_dib.Load(agendaPath + "\\" + agendaName);
			}
			else if (OpenFileDlg.GetFileExt() == L"jpg") {
				// TODO: load jpg
			}
			else {
				AfxMessageBox(L"File extension is not supported");
			}
		}
		break;
	case 1002: // Speichern
		if (SaveFileDlg.DoModal() == IDOK)
		{
			if (SaveFileDlg.GetFileExt() == L"bmp") {
				CString agendaName = SaveFileDlg.GetFileName(); //filename
				CString agendaPath = SaveFileDlg.GetFolderPath(); //filepath (folders)
				m_dib.Save(agendaPath + "\\" + agendaName);
			}
			else if (SaveFileDlg.GetFileExt() == L"jpg") {
				// TODO: save as jpg
			}
			else {
				AfxMessageBox(L"File extension is not supported");
			}
		}
		break;
	case 1003: // Aufhellen
		m_dib.brighten(10);
		break;
	case 1004: // Abdunkeln
		m_dib.brighten(-10);
		break;
	case 1005: // Graustufen
		m_dib.grey();
		break;
	case 1006: // Negativ
		m_dib.negative();
		break;
	case 1007: // mehr Kontrast
		m_dib.contrast(1.1f);
		break;
	case 1008: // Rotebene
		m_dib.rgb('r');
		break;
	case 1009: // Grünebene
		m_dib.rgb('g');
		break;
	case 1010: // Blauebene
		m_dib.rgb('b');
		break;
	case 1011: // Histogramm
		histogram = !histogram;
		break;
	case 1012: // Schärfen
		m_dib.matrix(sharpen_matrix, 1, 1);
		break;
	case 1013: // Unschärfe
		m_dib.matrix(soften_matrix, 1, 97);
		break;
	case 1014: // Emboss
		m_dib.matrix(emboss_matrix, 1, 1, 127);
		break;
	case 1015: // Kantenerkennung
		m_dib.matrix(edge_matrix, 1, 1);
		break;
	case 1016: // Flip horizontal
		m_dib.flip('h');
		break;
	case 1017: // Flip vertikal
		m_dib.flip('v');
		break;
	case 1018: // Schmelzen
		m_dib.slur(10);
		break;
	case 1019: // Ölgemälde
		break;
	case 1020: // Mosaik
		break;
	case 1021: // inverse FFT
		break;
	default: // Do nothing
		break;
	}
	RedrawWindow();
	return CDialog::OnCommand(wParam, lParam);
}

void CPixelgrafikenDlg::create_popup_menu() {
	VERIFY(menu.CreatePopupMenu());
	menu.AppendMenu(MF_STRING, 1001, L"Laden ...");
	menu.AppendMenu(MF_STRING, 1002, L"Speichern ...");

	// Seperatorline
	menu.AppendMenu(MF_SEPARATOR, 0, L"");

	menu.AppendMenu(MF_STRING, 1003, L"Aufhellen");
	menu.AppendMenu(MF_STRING, 1004, L"Abdunkeln");
	menu.AppendMenu(MF_STRING, 1005, L"Graustufen");
	menu.AppendMenu(MF_STRING, 1006, L"Negativ");
	menu.AppendMenu(MF_STRING, 1007, L"mehr Kontrast");

	// Seperatorline
	menu.AppendMenu(MF_SEPARATOR, 0, L"");

	menu.AppendMenu(MF_STRING, 1008, L"Rotebene");
	menu.AppendMenu(MF_STRING, 1009, L"Grünebene");
	menu.AppendMenu(MF_STRING, 1010, L"Blauebene");

	// Seperatorline
	menu.AppendMenu(MF_SEPARATOR, 0, L"");

	menu.AppendMenu(MF_STRING, 10011, L"Histogramm");

	// Seperatorline
	menu.AppendMenu(MF_SEPARATOR, 0, L"");

	menu.AppendMenu(MF_STRING, 1012, L"Schärfen");
	menu.AppendMenu(MF_STRING, 1013, L"Unschärfe");
	menu.AppendMenu(MF_STRING, 1014, L"Emboss");
	menu.AppendMenu(MF_STRING, 1015, L"Kantenerkennung");

	// Seperatorline
	menu.AppendMenu(MF_SEPARATOR, 0, L"");

	menu.AppendMenu(MF_STRING, 1016, L"Flip horizontal");
	menu.AppendMenu(MF_STRING, 1017, L"Flip vertikal");
	menu.AppendMenu(MF_STRING, 1018, L"Schmelzen");
	menu.AppendMenu(MF_STRING, 1019, L"Ölgemälde");
	menu.AppendMenu(MF_STRING, 1020, L"Mosaik");

	// Seperatorline
	menu.AppendMenu(MF_SEPARATOR, 0, L"");

	menu.AppendMenu(MF_STRING, 1021, L"(inverse) FFT");
}

void CPixelgrafikenDlg::draw_histogram()
{
	float h[256] = { 0.f }; int x = 10, y = 105;
	CClientDC dc(this);
	m_dib.histogramm(h, 20.f);
	dc.MoveTo(x, y); dc.LineTo(x + 255 + 2, y); // Rahmen zeichnen
	dc.LineTo(x + 255 + 2, y - 101); dc.LineTo(x, y - 101); dc.LineTo(x, y);
	CPen p(PS_SOLID, 1, RGB(255, 255, 0)); dc.SelectObject(&p);
	for (int i = 0; i < 255; i++) { // Histogramm zeichnen
		dc.MoveTo(x + i + 1, y - 1);
		dc.LineTo(x + i + 1, y - 1 - (100 * h[i]));
	}
}
