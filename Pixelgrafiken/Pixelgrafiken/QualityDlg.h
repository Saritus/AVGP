#pragma once


// CQualityDlg-Dialogfeld

class CQualityDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CQualityDlg)

public:
	CQualityDlg(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CQualityDlg();

	// Dialogfelddaten
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
public:
	int quality = 50;
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
};
