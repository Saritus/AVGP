// QualityDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Pixelgrafiken.h"
#include "QualityDlg.h"
#include "afxdialogex.h"


// CQualityDlg-Dialogfeld

IMPLEMENT_DYNAMIC(CQualityDlg, CDialogEx)

CQualityDlg::CQualityDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CQualityDlg::IDD, pParent)
{

}

CQualityDlg::~CQualityDlg()
{
}

void CQualityDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CQualityDlg, CDialogEx)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CQualityDlg::OnNMCustomdrawSlider1)
END_MESSAGE_MAP()


// CQualityDlg-Meldungshandler


void CQualityDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: F�gen Sie hier Ihren Kontrollbehandlungscode f�r die Benachrichtigung ein.
	quality = ((CSliderCtrl*)GetDlgItem(IDC_SLIDER1))->GetPos();
	*pResult = 0;
}


BOOL CQualityDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  hier zus�tzliche Initialisierung hinzuf�gen.
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER1))->SetRange(0, 100, true);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER1))->SetPos(50);
	return TRUE;  // return TRUE unless you set the focus to a control
	// AUSNAHME: OCX-Eigenschaftenseite muss FALSE zur�ckgeben.
}
