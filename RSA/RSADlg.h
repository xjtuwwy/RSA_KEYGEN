// RSADlg.h : header file
//

#include "RSAAlgo.h"
#include "BigInteger.h"

#pragma once


// CRSADlg dialog
class CRSADlg : public CDialog
{
// Construction
public:
	CRSADlg(CWnd* pParent = NULL);	// standard constructor

	CBigInteger myP, myQ;
	CBigInteger myn, mye, myd;
	CBigInteger myFn;
	CBigInteger mydP, mydQ, myqInv;

	int m_nPQLen;

	CString OutputStringFormat(CString str);
	BOOL IsValidDigit(CHAR ch);
	BOOL IsNumbericDigit(CHAR ch);
	BOOL IsHexnumberDigit(CHAR ch);

// Dialog Data
	enum { IDD = IDD_RSA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	CRSAAlgo myRSAAlog;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonRun();
	afx_msg void OnBnClickedButtonGenpq();
	afx_msg void OnBnClickedButtonGenkeypair();
	CString strInputRawMessage;
	afx_msg void OnBnClickedButtonEncryptmessage();

	afx_msg void OnBnClickedButtonDecryptecypher();

	CString m_Pstr;
	CString m_Qstr;
	CString m_strC;
	CString m_strM;
	CString m_strN;
	CString m_strE;
	CString m_strD;
	CString m_strdP;
	CString m_strdQ;
	CString m_strqInv;
	int m_DecryptType;
	int m_PQGenMethod;
	int m_nKeyLength;
	int m_eGenType;
	int m_nEncryptKeySel;
	int m_nDecryptKeySel;


	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio12();
	afx_msg void OnBnClickedRadio13();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedRadio6();
	afx_msg void OnBnClickedRadio7();
	afx_msg void OnBnClickedRadio8();
	afx_msg void OnBnClickedRadio9();
	afx_msg void OnBnClickedRadio10();
	afx_msg void OnBnClickedRadio11();
	afx_msg void OnBnClickedRadioPublicKey();
	afx_msg void OnBnClickedRadioPrivateKey();
	afx_msg void OnBnClickedRadioDePrivateKey();
	afx_msg void OnBnClickedRadioDePublicKey();

	afx_msg void OnBnClickedRadio1();
};
