#pragma once


// CExampleDlg-Dialogfeld

class CExampleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CExampleDlg)

public:
	CExampleDlg(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CExampleDlg();

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
};
