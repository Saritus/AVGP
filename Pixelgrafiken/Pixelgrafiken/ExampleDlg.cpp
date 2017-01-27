// ExampleDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Pixelgrafiken.h"
#include "ExampleDlg.h"
#include "afxdialogex.h"


// CExampleDlg-Dialogfeld

IMPLEMENT_DYNAMIC(CExampleDlg, CDialogEx)

CExampleDlg::CExampleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CExampleDlg::~CExampleDlg()
{
}

void CExampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CExampleDlg, CDialogEx)
END_MESSAGE_MAP()


// CExampleDlg-Meldungshandler
