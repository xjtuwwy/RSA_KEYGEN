// RSADlg.cpp : implementation file
//

#include "stdafx.h"
#include "RSA.h"
#include "RSADlg.h"
#include "BigInteger.h"
#include "RSAAlgo.h"

#include <stdlib.h>
#include <time.h>



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TIMECONSUME 0



// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CRSADlg dialog




CRSADlg::CRSADlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRSADlg::IDD, pParent)
	, strInputRawMessage(_T(""))
	, m_Pstr(_T(""))
	, m_Qstr(_T(""))
	, m_strC(_T(""))
	, m_strM(_T(""))
	, m_strN(_T(""))
	, m_strE(_T(""))
	, m_strD(_T(""))
	, m_strdP(_T(""))
	, m_strdQ(_T(""))
	, m_strqInv(_T(""))
	, m_DecryptType(0)
	, m_PQGenMethod(1)
	, m_nKeyLength(4)
	, m_eGenType(0)
	, m_nPQLen(512)
	, m_nEncryptKeySel(0)
	, m_nDecryptKeySel(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRSADlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MESSAGE, strInputRawMessage);
	DDX_Text(pDX, IDC_EDIT_PDATA, m_Pstr);
	DDX_Text(pDX, IDC_EDIT_QDATA, m_Qstr);
	DDX_Text(pDX, IDC_EDIT_ENCRYPTEMESSAGE, m_strC);
	DDX_Text(pDX, IDC_EDIT_DECRYPTEMESSAGE, m_strM);
	DDX_Text(pDX, IDC_EDIT_NDATA, m_strN);
	DDX_Text(pDX, IDC_EDIT_EDATA, m_strE);
	DDX_Text(pDX, IDC_EDIT_DDATA, m_strD);
	DDX_Text(pDX, IDC_EDIT_DPDATA, m_strdP);
	DDX_Text(pDX, IDC_EDIT_DQDATA, m_strdQ);
	DDX_Text(pDX, IDC_EDIT_QINVDATA, m_strqInv);
	DDX_Radio(pDX, IDC_RADIO1, m_DecryptType);
	DDX_Radio(pDX, IDC_RADIO3, m_PQGenMethod);
	DDX_Radio(pDX, IDC_RADIO5, m_nKeyLength);
	DDX_Radio(pDX, IDC_RADIO12, m_eGenType);
	DDX_Radio(pDX, IDC_RADIO_PUBLIC_KEY, m_nEncryptKeySel);
	DDX_Radio(pDX, IDC_RADIO_DE_PRIVATE_KEY, m_nDecryptKeySel);
}

BEGIN_MESSAGE_MAP(CRSADlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_RUN, &CRSADlg::OnBnClickedButtonRun)
	ON_BN_CLICKED(IDC_BUTTON_GENPQ, &CRSADlg::OnBnClickedButtonGenpq)
	ON_BN_CLICKED(IDC_BUTTON_GENKEYPAIR, &CRSADlg::OnBnClickedButtonGenkeypair)
	ON_BN_CLICKED(IDC_BUTTON_ENCRYPTMESSAGE, &CRSADlg::OnBnClickedButtonEncryptmessage)
	ON_BN_CLICKED(IDC_BUTTON_DECRYPTECYPHER, &CRSADlg::OnBnClickedButtonDecryptecypher)
	ON_BN_CLICKED(IDC_BUTTON1, &CRSADlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_RADIO3, &CRSADlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CRSADlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO12, &CRSADlg::OnBnClickedRadio12)
	ON_BN_CLICKED(IDC_RADIO13, &CRSADlg::OnBnClickedRadio13)
	ON_BN_CLICKED(IDC_RADIO5, &CRSADlg::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_RADIO6, &CRSADlg::OnBnClickedRadio6)
	ON_BN_CLICKED(IDC_RADIO7, &CRSADlg::OnBnClickedRadio7)
	ON_BN_CLICKED(IDC_RADIO8, &CRSADlg::OnBnClickedRadio8)
	ON_BN_CLICKED(IDC_RADIO9, &CRSADlg::OnBnClickedRadio9)
	ON_BN_CLICKED(IDC_RADIO10, &CRSADlg::OnBnClickedRadio10)
	ON_BN_CLICKED(IDC_RADIO11, &CRSADlg::OnBnClickedRadio11)
	ON_BN_CLICKED(IDC_RADIO_PUBLIC_KEY, &CRSADlg::OnBnClickedRadioPublicKey)
	ON_BN_CLICKED(IDC_RADIO_PRIVATE_KEY, &CRSADlg::OnBnClickedRadioPrivateKey)
	ON_BN_CLICKED(IDC_RADIO_DE_PRIVATE_KEY, &CRSADlg::OnBnClickedRadioDePrivateKey)
	ON_BN_CLICKED(IDC_RADIO_DE_PUBLIC_KEY, &CRSADlg::OnBnClickedRadioDePublicKey)
	ON_BN_CLICKED(IDC_RADIO1, &CRSADlg::OnBnClickedRadio1)
END_MESSAGE_MAP()


// CRSADlg message handlers

BOOL CRSADlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	m_nKeyLength = 4;
	GetDlgItem(IDC_BUTTON_GENPQ)->SetWindowText(_T("Enter big P,Q"));

	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRSADlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRSADlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRSADlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CRSADlg::OnBnClickedButtonRun()
{
	// TODO: 在此添加控件通知处理程序代码


	CBigInteger A,B,C,D,E,F,G,H,I;

	A.m_nSign = 1;
	A.m_nLength = 5;
	A.m_ulvalue[0] = 0xFF;
	A.m_ulvalue[1] = 0xFE;
	A.m_ulvalue[2] = 0xFF;
	A.m_ulvalue[3] = 0;
	A.m_ulvalue[4] = 1;

	C.m_nSign  = 1;
	C.m_nLength = 2;
	C.m_ulvalue[0] = 1;
	C.m_ulvalue[1] = 1;
	D.Mov(A.Div(C));



	// TODO: Add your control notification handler code here
	CString strFilter,fileName,strText;
	strFilter="Txt Files(*.txt)|*.txt||";
	CFileDialog dlg(FALSE, NULL, NULL, OFN_EXPLORER|OFN_HIDEREADONLY|
		OFN_ENABLESIZING|OFN_FILEMUSTEXIST,strFilter);
	if(dlg.DoModal() == IDOK )//显示保存文件对话框
	{
		fileName=dlg.GetPathName();
		CFile savefile(fileName,CFile::modeCreate|CFile::modeWrite);//构造CFile对象
		CString str;
		str = "P: \r\n" + m_Pstr + "\r\n"+ "Q: \r\n" + m_Qstr + "\r\n";
		str +="n: \r\n" + m_strN + "\r\n";
		str +="e: \r\n" + m_strE + "\r\n";
		str +="d: \r\n" + m_strD + "\r\n";
		str +="dP: \r\n" + m_strdP + "\r\n";
		str +="dQ: \r\n" + m_strdQ + "\r\n" ;
		str +="qInv: \r\n" + m_strqInv;
    	savefile.Write(str,str.GetLength());//写文件数据

		savefile.Close();//关闭文件
	}

	/*
	CString Astr = "FFFFFFFF";
	CBigInteger A,B,C,D,E,F,G,H,I;
	BOOL bTrue;
	*/

	/*
	A.m_nSign = 1;
	A.m_nLength = 6;
	A.m_ulvalue[0] = 10007;
	A.m_ulvalue[1] = 10000;
	A.m_ulvalue[2] = 10001;
	A.m_ulvalue[3] = 10002;
	A.m_ulvalue[4] = 10003;
	A.m_ulvalue[5] = 1;
	B.Mov(A.ShiftOneBit());
	B.Mod(A.Div(2));

	B.Mov(A.ShiftRight(66));
	B.Mov(A.ShiftMod(66));

	C.m_nSign  = 1;
	C.m_nLength = 3;
	C.m_ulvalue[0] = 0;
	C.m_ulvalue[1] = 0;
	C.m_ulvalue[2] = 4;
	D.Mov(A.Div(C));
	D.Mov(A.Mod(C));

	CBigInteger ntemp,rtemp;
	ntemp.m_nSign = 1;
	ntemp.m_nLength = 1;
	ntemp.m_ulvalue[0] = 23;
	rtemp= myRSAAlog.GetRvalueforMontgomeryAlgo(ntemp);
	unsigned long index = myRSAAlog.GetRbase2valueforMontgomeryAlgo(ntemp);
	A.m_nSign = 1;
	A.m_nLength = 1;
	A.m_ulvalue[0] = 10007;
    E.Mov(A.Div(rtemp));
	E.Mov(A.Mod(rtemp));
	F.Mov(A.ShiftRight(index));
	F.Mov(A.ShiftMod(index));
	*/

	//A.InPutFromStr(Astr,DEC);
	/*
	A.m_nSign =  0;
	A.m_nLength = 4;
	A.m_ulvalue[0] = 0xFFFFFFFF;
	A.m_ulvalue[1] = 0xFFFFFFFF;
	A.m_ulvalue[2] = 0xFFFFFFFF;
	A.m_ulvalue[3] = 0xFFFFFFFF;

	B.m_nSign =  1;
	B.m_nLength = 5;
	B.m_ulvalue[0] = 0;//0x80000000;
	B.m_ulvalue[1] = 0;//0x80000000;
	B.m_ulvalue[2] = 0;//0x80000000;
	B.m_ulvalue[3] = 0;//0x80000000;
	B.m_ulvalue[4] = 1;//0x80000000;

	F.m_nSign = 1;
	F.m_nLength = 3;
	F.m_ulvalue[0] = 0;
	F.m_ulvalue[1] = 1;
	F.m_ulvalue[2] = 1;

	C.Mov(A.Add(1)); // C = A+1;
	C.Mov(A.Sub(1)); // C = A-1;
	C.Mov(A.Add(B)); // C = A+B;
	C.Mov(A.Sub(B)); // C = A-B;
	D.Mov(A.Mul(B)); // D = AB;
	E.Mov(D.Add(F)); // E = D + F;
	G.Mov(E.Div(B)); // G = E/B,G should be equal to A.
	H.Mov(E.Mod(B)); // H = Mod(E,B),H should be equal to F;
    */

	/*
	A.m_nSign = 1;
	A.m_nLength = 1;
	A.m_ulvalue[0] = 10007;

	B.m_nSign = 1;
	B.m_nLength = 1;
	B.m_ulvalue[0] = 10093;
	
	// 10007*2934 + 10093*(-2909) = gcd(10007,10093) = 1
	E = myRSAAlog.ExeuclideanGCD(A,B,C,D); //A*C + B*D = gcd(A,B) = E;
	*/
	
	/*
	CBigInteger Xtemp;
	Xtemp.m_nSign = 1;
	Xtemp.m_nLength = 1;
	Xtemp.m_ulvalue[0] = 10007;
	BOOL xreturn = myRSAAlog.CheckIsBigPrimewithMillerRabin(Xtemp);
	xreturn = myRSAAlog.CheckIsBigPrimewithMillerRabinWithMontgomery(Xtemp);
	*/

	
	/*
	A.m_nSign =  1;
	A.m_nLength = 2;
	A.m_ulvalue[0] = 0x12345678;//0x72E01AC1;
	A.m_ulvalue[1] = 0xabcdef90;
	A.m_ulvalue[2] = 0x00000000;
	A.m_ulvalue[3] = 0xFFFFFFFF;
	CString Ahexstr;
	A.OutPutToHexStr(Ahexstr);
	CString str;
	str = Ahexstr.Mid(0,8);
	*/
	
	/*
	CBigInteger ntemp,rtemp;
	ntemp.m_nSign = 1;
	ntemp.m_nLength = 1;
	ntemp.m_ulvalue[0] = 13;
	rtemp= myRSAAlog.GetRvalueforMontgomeryAlgo(ntemp);

	unsigned long index = myRSAAlog.GetRbase2valueforMontgomeryAlgo(ntemp);

	CBigInteger rinv,ntempplus;
	CBigInteger ctemp;

	BOOL result;
	C.Mov(1);
	ntemp.m_nSign = 0;
	result=myRSAAlog.LinearEquationExeuclidean(rtemp,ntemp,C,rinv,ntempplus);
	ntemp.m_nSign = 1;

	CBigInteger S,FinalValue;

	A.m_nSign = 1;
	A.m_nLength = 1;
	A.m_ulvalue[0] = 7;
	B.m_nSign = 1;
	B.m_nLength = 1;
	B.m_ulvalue[0] = 10;

	FinalValue = myRSAAlog.ProductModualwithMontgomeryAlgo(A,B,ntemp); // A*B mod ntemp
	FinalValue = myRSAAlog.PowerModualwithMontgomeryAlgo(A,B,ntemp); // A^B mod ntemp

	FinalValue = myRSAAlog.NewPowerModualwithMontgomeryAlgo(A,B,ntemp);
	*/
    


  
	// Suppose P, Q has been determined, Use P, Q to generate key pairs start	
    /*
	CBigInteger P, Q;
	CBigInteger n,e,d;
	CBigInteger P1,Q1,Fn;
	CBigInteger dP,dQ,qInv;
	*/

	/*
	P.Mov(myRSAAlog.GenBigRandomNumber(512));
	Q.Mov(myRSAAlog.GenBigRandomNumber(512));

	bTrue = FALSE;
	while (!bTrue)
	{
		bTrue = myRSAAlog.RoughCheckIsBigPrime(P);

		if (!bTrue)
		{
			P.Mov(P.Add(1));
		}
		else
		{
			bTrue = myRSAAlog.CheckIsBigPrimewithMillerRabin(P);

			if (!bTrue)
			{
				P.Mov(P.Add(1));
			}
		}

	}

	bTrue = FALSE;
	while (!bTrue)
	{
		bTrue = myRSAAlog.RoughCheckIsBigPrime(Q);

		if (!bTrue)
		{
			Q.Mov(Q.Add(1));
		}
		else
		{
			bTrue = myRSAAlog.CheckIsBigPrimewithMillerRabin(Q);

			if (!bTrue)
			{
				Q.Mov(Q.Add(1));
			}
		}
	}

	bTrue = myRSAAlog.CheckIsInterPrime(P,Q);
	*/
	
/*	
	P.m_nSign =  1;
	P.m_nLength = 16;
	P.m_ulvalue[0] = 0x72E01AC1;
	P.m_ulvalue[1] = 0xD57DE0DC;
	P.m_ulvalue[2] = 0xE0C457E0;
	P.m_ulvalue[3] = 0x6DE0B964;
	P.m_ulvalue[4] = 0xFF4DE027;
	P.m_ulvalue[5] = 0xE0451BE0;
	P.m_ulvalue[6] = 0x1FE04726;
	P.m_ulvalue[7] = 0xFE53E0EF;
	P.m_ulvalue[8] = 0xE0D637E0;
	P.m_ulvalue[9] = 0x5EE0BE2F;
	P.m_ulvalue[10] = 0x0127E024;
	P.m_ulvalue[11] = 0xE0AC00E0;
	P.m_ulvalue[12] = 0x19E0CD02;
	P.m_ulvalue[13] = 0x7811E0D1;
	P.m_ulvalue[14] = 0xE0263FE0;
	P.m_ulvalue[15] = 0xE8E0037F;

	Q.m_nSign = 1;
	Q.m_nLength = 16;
	Q.m_ulvalue[0] = 0x3BE05EBF;
	Q.m_ulvalue[1] = 0xB558E066;
	Q.m_ulvalue[2] = 0xE0C171E0;
	Q.m_ulvalue[3] = 0x0EE06276;
	Q.m_ulvalue[4] = 0xCF1AE05F;
	Q.m_ulvalue[5] = 0xE00A1EE0;
	Q.m_ulvalue[6] = 0x74E0224A;
	Q.m_ulvalue[7] = 0xC51AE0C3;
    Q.m_ulvalue[8] = 0xE09E1EE0;
	Q.m_ulvalue[9] = 0x66E0A148;
	Q.m_ulvalue[10] = 0x997DE0BC;
	Q.m_ulvalue[11] = 0xE0EE5AE0;
	Q.m_ulvalue[12] = 0x67E0C87F;
	Q.m_ulvalue[13] = 0xA310E08D;
	Q.m_ulvalue[14] = 0xE0F435E0;
	Q.m_ulvalue[15] = 0xF3E0021C;
*/
	
    /*
	n.Mov(P.Mul(Q));
	P1.Mov(P.Sub(1));
	Q1.Mov(Q.Sub(1));
	Fn.Mov(P1.Mul(Q1));
	*/

	/*
	e.m_nLength = 1;
	e.m_ulvalue[0] = 0x00010001;
	BOOL isInterPrime = FALSE;
	isInterPrime = myRSAAlog.CheckIsInterPrime(Fn,e);
	*/

    /*
	unsigned int i;
	for (i=0x10000;i<0xFFFFFFFF;i++)
	{
		e.Mov(i);
		if (myRSAAlog.CheckIsInterPrime(Fn,e))
		{
			e.Mov(i);
			break;
		}
	}
	
	
	// 1.d must be > 0
	// 2. e*d + Fn*B = gcd(e,Fn) = A;
	// 2.if gcd(e,Fn) = 1, this equation has only one solution
	BOOL res;
	C.Mov(1);
	res = myRSAAlog.LinearEquationExeuclidean(e,Fn,C,d,B);

	// 1.dP must be > 0
	// 2.e*dP + P1*B = gcd(e,P1) = C
	// 3.if gcd(e,P1) != 1, and C | gcd(e,P1) this equation has more than one solution
	// 4.if C !| gcd(e,P1) this equation has no solution
	
	C.Mov(1);
	res = myRSAAlog.LinearEquationExeuclidean(e,P1,C,dP,B);
	if (res == FALSE)
	{
		dP.Mov(d.Mod(P1));
	}

	// 1.dQ must be > 0
	// 2.e*dQ + Q1*B = gcd(e,Q1) = C
	// 3.if gcd(e,Q1) != 1, and C | gcd(e,Q1) this equation has more than one solution
	// 4.if C !| gcd(e,Q1) this equation has no solution
	C.Mov(1);
	res = myRSAAlog.LinearEquationExeuclidean(e,Q1,C,dQ,B);
    if (res == FALSE) 
    {
		dQ.Mov(d.Mod(Q1));
    }
	
	// 1.qInv must be > 0
	// 2. Q*qInv + P*B = gcd(Q,P) = A;
	// 2.if gcd(Q,P) = 1, this equation has only one solution
	//A = myRSAAlog.ExeuclideanGCD(Q,P,qInv,B);
	C.Mov(1);
	res = myRSAAlog.LinearEquationExeuclidean(Q,P,C,qInv,B);

	CBigInteger m,c;
	CBigInteger m1,m2;
	
	m.m_nSign = 1;
	m.m_nLength = 8;
	m.m_ulvalue[0] = 0x12345678;
	m.m_ulvalue[1] = 0x87654321;
	m.m_ulvalue[2] = 0x12345678;
	m.m_ulvalue[3] = 0x87654321;
	m.m_ulvalue[4] = 0x12345678;
	m.m_ulvalue[5] = 0x87654321;
	m.m_ulvalue[6] = 0x12345678;
	m.m_ulvalue[7] = 0x87654321;
	m.m_ulvalue[8] = 0x12345678;
	m.m_ulvalue[9] = 0x87654321;
	m.m_ulvalue[10] = 0x12345678;
	m.m_ulvalue[11] = 0x87654321;
	m.m_ulvalue[12] = 0x12345678;
	m.m_ulvalue[13] = 0x87654321;
	m.m_ulvalue[14] = 0x12345678;
	m.m_ulvalue[15] = 0x87654321;

	c = myRSAAlog.RSAEP(n,e,m);
	m1 = myRSAAlog.RSADPwithType1privateKey(n,d,c);
	m2 = myRSAAlog.RSADPwithType2privateKey(P,Q,dP,dQ,qInv,c);
	*/
}

void CRSADlg::OnBnClickedButtonGenpq()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);

	CBigInteger P, Q;
    BOOL bTrue;

	CString pstr,qstr;

	/*
	P.m_nSign =  1;
	P.m_nLength = 16;
	P.m_ulvalue[0] = 0x72E01AC1;
	P.m_ulvalue[1] = 0xD57DE0DC;
	P.m_ulvalue[2] = 0xE0C457E0;
	P.m_ulvalue[3] = 0x6DE0B964;
	P.m_ulvalue[4] = 0xFF4DE027;
	P.m_ulvalue[5] = 0xE0451BE0;
	P.m_ulvalue[6] = 0x1FE04726;
	P.m_ulvalue[7] = 0xFE53E0EF;
	P.m_ulvalue[8] = 0xE0D637E0;
	P.m_ulvalue[9] = 0x5EE0BE2F;
	P.m_ulvalue[10] = 0x0127E024;
	P.m_ulvalue[11] = 0xE0AC00E0;
	P.m_ulvalue[12] = 0x19E0CD02;
	P.m_ulvalue[13] = 0x7811E0D1;
	P.m_ulvalue[14] = 0xE0263FE0;
	P.m_ulvalue[15] = 0xE8E0037F;


	Q.m_nSign = 1;
	Q.m_nLength = 16;
	Q.m_ulvalue[0] = 0x3BE05EBF;
	Q.m_ulvalue[1] = 0xB558E066;
	Q.m_ulvalue[2] = 0xE0C171E0;
	Q.m_ulvalue[3] = 0x0EE06276;
	Q.m_ulvalue[4] = 0xCF1AE05F;
	Q.m_ulvalue[5] = 0xE00A1EE0;
	Q.m_ulvalue[6] = 0x74E0224A;
	Q.m_ulvalue[7] = 0xC51AE0C3;
	Q.m_ulvalue[8] = 0xE09E1EE0;
	Q.m_ulvalue[9] = 0x66E0A148;
	Q.m_ulvalue[10] = 0x997DE0BC;
	Q.m_ulvalue[11] = 0xE0EE5AE0;
	Q.m_ulvalue[12] = 0x67E0C87F;
	Q.m_ulvalue[13] = 0xA310E08D;
	Q.m_ulvalue[14] = 0xE0F435E0;
	Q.m_ulvalue[15] = 0xF3E0021C;

	BOOL xreturn = myRSAAlog.CheckIsBigPrimewithMillerRabinWithMontgomery(P);
 	xreturn = myRSAAlog.CheckIsBigPrimewithMillerRabinWithMontgomery(Q);

	bTrue = myRSAAlog.CheckIsInterPrime(P,Q);
	*/

	//CBigInteger Ptest,AddP,Qtest,AddQ;

#if TIMECONSUME
	clock_t start,finish;
	double chktimes;
	start = clock();
#endif

	if (m_PQGenMethod == 0) // Tool random gen
	{
		P.Mov(myRSAAlog.GenBigRandomNumber(m_nPQLen));
		Sleep(5000);
		Q.Mov(myRSAAlog.GenBigRandomNumber(m_nPQLen));

		// Check P and Q is even or odd start
		if ((P.m_ulvalue[0] & 0x01)!=0x01)
		{
			P.Mov(P.Add(1)); // Change to odd number
		}

		if ((Q.m_ulvalue[0] & 0x01)!=0x01)
		{
			Q.Mov(Q.Add(1)); // Change to odd number
		}
		// Check P and Q is even or odd end

		// Test start
		/*
		Ptest.Mov(P);
		CString AddPtestStr;
		Ptest.OutPutToHexStr(AddPtestStr);
		AfxMessageBox(AddPtestStr);

		Qtest.Mov(Q);
		CString AddQtestStr;
		Qtest.OutPutToHexStr(AddQtestStr);
		AfxMessageBox(AddQtestStr);
		*/
		// Test end

		bTrue = FALSE;
		while (!bTrue)
		{
			bTrue = myRSAAlog.RoughCheckIsBigPrime(P);

			if (!bTrue)
			{
				P.Mov(P.Add(2));
			}
			else
			{
				bTrue = myRSAAlog.CheckIsBigPrimewithMillerRabinWithMontgomery(P);
				//bTrue = myRSAAlog.CheckIsBigPrimewithMillerRabin(P);

				if (!bTrue)
				{
					P.Mov(P.Add(2));
				}
			}

		}

		// Test start
		/*
		AddP.Mov(P.Sub(Ptest));
		CString AddPStr;
		AddP.OutPutToHexStr(AddPStr);
		AfxMessageBox(AddPStr);
		*/
		// Test end


		bTrue = FALSE;
		while (!bTrue)
		{
			bTrue = myRSAAlog.RoughCheckIsBigPrime(Q);

			if (!bTrue)
			{
				Q.Mov(Q.Add(2));
			}
			else
			{
				bTrue = myRSAAlog.CheckIsBigPrimewithMillerRabinWithMontgomery(Q);
				//bTrue = myRSAAlog.CheckIsBigPrimewithMillerRabin(Q);

				if (!bTrue)
				{
					Q.Mov(Q.Add(2));
				}
			}
		}
	}
	else   // Manual input
	{
		m_Pstr.MakeUpper();
		m_Pstr.Remove(' ');
		m_Pstr.Remove('\n');
		m_Pstr.Remove('\r');

		P.InPutFromHexStr(m_Pstr);

		m_Qstr.MakeUpper();
		m_Qstr.Remove(' ');
		m_Qstr.Remove('\n');
		m_Qstr.Remove('\r');

		Q.InPutFromHexStr(m_Qstr);
	}

	// Test start
	/*
	AddQ.Mov(Q.Sub(Qtest));
	CString AddQStr;
	AddQ.OutPutToHexStr(AddQStr);
	AfxMessageBox(AddQStr);
	*/
	// Test end

	bTrue = myRSAAlog.CheckIsInterPrime(P,Q);

#if TIMECONSUME
	finish = clock();
	chktimes = (double)(finish-start)/CLOCKS_PER_SEC;
	CString timestr;
	timestr.Format("Gen P,Q time %2.3fs",chktimes);
	AfxMessageBox(timestr);
#endif

	if (!bTrue)
	{
		// Generate P and Q fail
		pstr = "Gen P and Q fail, Regen!";
		qstr = "Gen P and Q fail, Regen!";
	}
	else
	{
		myP.Mov(P);
		myQ.Mov(Q);
		P.OutPutToHexStr(pstr);
		Q.OutPutToHexStr(qstr);

		CBigInteger P1,Q1;

		myn.Mov(myP.Mul(myQ));
		P1.Mov(myP.Sub(1));
		Q1.Mov(myQ.Sub(1));
		myFn.Mov(P1.Mul(Q1));
	}
	
	/*
	P.m_nSign =  1;
	P.m_nLength = 16;
	P.m_ulvalue[0] = 0x72E01AC1;
	P.m_ulvalue[1] = 0xD57DE0DC;
	P.m_ulvalue[2] = 0xE0C457E0;
	P.m_ulvalue[3] = 0x6DE0B964;
	P.m_ulvalue[4] = 0xFF4DE027;
	P.m_ulvalue[5] = 0xE0451BE0;
	P.m_ulvalue[6] = 0x1FE04726;
	P.m_ulvalue[7] = 0xFE53E0EF;
	P.m_ulvalue[8] = 0xE0D637E0;
	P.m_ulvalue[9] = 0x5EE0BE2F;
	P.m_ulvalue[10] = 0x0127E024;
	P.m_ulvalue[11] = 0xE0AC00E0;
	P.m_ulvalue[12] = 0x19E0CD02;
	P.m_ulvalue[13] = 0x7811E0D1;
	P.m_ulvalue[14] = 0xE0263FE0;
	P.m_ulvalue[15] = 0xE8E0037F;
	

	Q.m_nSign = 1;
	Q.m_nLength = 16;
	Q.m_ulvalue[0] = 0x3BE05EBF;
	Q.m_ulvalue[1] = 0xB558E066;
	Q.m_ulvalue[2] = 0xE0C171E0;
	Q.m_ulvalue[3] = 0x0EE06276;
	Q.m_ulvalue[4] = 0xCF1AE05F;
	Q.m_ulvalue[5] = 0xE00A1EE0;
	Q.m_ulvalue[6] = 0x74E0224A;
	Q.m_ulvalue[7] = 0xC51AE0C3;
	Q.m_ulvalue[8] = 0xE09E1EE0;
	Q.m_ulvalue[9] = 0x66E0A148;
	Q.m_ulvalue[10] = 0x997DE0BC;
	Q.m_ulvalue[11] = 0xE0EE5AE0;
	Q.m_ulvalue[12] = 0x67E0C87F;
	Q.m_ulvalue[13] = 0xA310E08D;
	Q.m_ulvalue[14] = 0xE0F435E0;
	Q.m_ulvalue[15] = 0xF3E0021C;

	BOOL xreturn = myRSAAlog.CheckIsBigPrimewithMillerRabinWithMontgomery(P);
	xreturn = myRSAAlog.CheckIsBigPrimewithMillerRabinWithMontgomery(Q);
    */
	

	m_Pstr = pstr;
	m_Qstr = qstr;
	m_Pstr = OutputStringFormat(m_Pstr);
	m_Qstr = OutputStringFormat(m_Qstr);

    UpdateData(FALSE);

}

void CRSADlg::OnBnClickedButtonGenkeypair()
{
	// TODO: 在此添加控件通知处理程序代码
	CBigInteger P1,Q1;

	P1.Mov(myP.Sub(1));
	Q1.Mov(myQ.Sub(1));

	/*
	myP.m_nSign =  1;
	myP.m_nLength = 16;
	myP.m_ulvalue[0] = 0x72E01AC1;
	myP.m_ulvalue[1] = 0xD57DE0DC;
	myP.m_ulvalue[2] = 0xE0C457E0;
	myP.m_ulvalue[3] = 0x6DE0B964;

	myP.m_ulvalue[4] = 0xFF4DE027;
	myP.m_ulvalue[5] = 0xE0451BE0;
	myP.m_ulvalue[6] = 0x1FE04726;
	myP.m_ulvalue[7] = 0xFE53E0EF;

	myP.m_ulvalue[8] = 0xE0D637E0;
	myP.m_ulvalue[9] = 0x5EE0BE2F;
	myP.m_ulvalue[10] = 0x0127E024;
	myP.m_ulvalue[11] = 0xE0AC00E0;

	myP.m_ulvalue[12] = 0x19E0CD02;
	myP.m_ulvalue[13] = 0x7811E0D1;
	myP.m_ulvalue[14] = 0xE0263FE0;
	myP.m_ulvalue[15] = 0xE8E0037F;


	myQ.m_nSign = 1;
	myQ.m_nLength = 16;
	myQ.m_ulvalue[0] = 0x3BE05EBF;
	myQ.m_ulvalue[1] = 0xB558E066;
	myQ.m_ulvalue[2] = 0xE0C171E0;
	myQ.m_ulvalue[3] = 0x0EE06276;

	myQ.m_ulvalue[4] = 0xCF1AE05F;
	myQ.m_ulvalue[5] = 0xE00A1EE0;
	myQ.m_ulvalue[6] = 0x74E0224A;
	myQ.m_ulvalue[7] = 0xC51AE0C3;

	myQ.m_ulvalue[8] = 0xE09E1EE0;
	myQ.m_ulvalue[9] = 0x66E0A148;
	myQ.m_ulvalue[10] = 0x997DE0BC;
	myQ.m_ulvalue[11] = 0xE0EE5AE0;

	myQ.m_ulvalue[12] = 0x67E0C87F;
	myQ.m_ulvalue[13] = 0xA310E08D;
	myQ.m_ulvalue[14] = 0xE0F435E0;
	myQ.m_ulvalue[15] = 0xF3E0021C;
    */



	CBigInteger A,B,C;



	/*
	unsigned int i;
	for (i=0x10000;i<0xFFFFFFFF;i++)
	{
		mye.Mov(i);
		if (myRSAAlog.CheckIsInterPrime(Fn,mye))
		{
			mye.Mov(i);
			break;
		}
	}
	*/
	
	// 1.d must be > 0
	// 2. e*d + Fn*B = gcd(e,Fn) = A;
	// 2.if gcd(e,Fn) = 1, this equation has only one solution
	BOOL res;
	C.Mov(1);
	res = myRSAAlog.LinearEquationExeuclidean(mye,myFn,C,myd,B);

	// 1.dP must be > 0
	// 2.e*dP + P1*B = gcd(e,P1) = C
	// 3.if gcd(e,P1) != 1, and C | gcd(e,P1) this equation has more than one solution
	// 4.if C !| gcd(e,P1) this equation has no solution
	C.Mov(1);
	res = myRSAAlog.LinearEquationExeuclidean(mye,P1,C,mydP,B);
	if (res == FALSE)
	{
		mydP.Mov(myd.Mod(P1));
	}

	// 1.dQ must be > 0
	// 2.e*dQ + Q1*B = gcd(e,Q1) = C
	// 3.if gcd(e,Q1) != 1, and C | gcd(e,Q1) this equation has more than one solution
	// 4.if C !| gcd(e,Q1) this equation has no solution
	C.Mov(1);
	res = myRSAAlog.LinearEquationExeuclidean(mye,Q1,C,mydQ,B);
    if (res == FALSE) 
    {
		mydQ.Mov(myd.Mod(Q1));
    }
	
	// 1.qInv must be > 0
	// 2. Q*qInv + P*B = gcd(Q,P) = A;
	// 2.if gcd(Q,P) = 1, this equation has only one solution
	//A = myRSAAlog.ExeuclideanGCD(Q,P,qInv,B);
	C.Mov(1);
	res = myRSAAlog.LinearEquationExeuclidean(myQ,myP,C,myqInv,B);


	CString dstr,estr,nstr,dPstr,dQstr,qInvstr;

	myd.OutPutToHexStr(m_strD);
	mye.OutPutToHexStr(m_strE);
	myn.OutPutToHexStr(m_strN);
	mydP.OutPutToHexStr(m_strdP);
	mydQ.OutPutToHexStr(m_strdQ);
	myqInv.OutPutToHexStr(m_strqInv);

	m_strD = OutputStringFormat(m_strD);
	m_strE = OutputStringFormat(m_strE);
	m_strN = OutputStringFormat(m_strN);
	m_strdP = OutputStringFormat(m_strdP);
	m_strdQ = OutputStringFormat(m_strdQ);
	m_strqInv = OutputStringFormat(m_strqInv);

	UpdateData(FALSE);

}

CString CRSADlg::OutputStringFormat(CString str)
{
	CString returnstr,tempstr;

	int nlength = str.GetLength();
	int cnt = 0;

	returnstr = "";

	for (int i = 0; i < nlength/8;i++)
	{
		tempstr = str.Mid(8*i,8);
		returnstr += tempstr + " ";
		if(i%4 == 3)
		{
			returnstr += "\r\n";
		}
	}

	return returnstr;
}

BOOL CRSADlg::IsValidDigit(CHAR ch)
{
	if ((ch >= 48) && (ch <=57))
	{
		return TRUE;
	}

	if ((ch >= 65) && (ch <=70))
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CRSADlg::IsNumbericDigit(CHAR ch)
{
	if ((ch >= 48) && (ch <=57))
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CRSADlg::IsHexnumberDigit(CHAR ch)
{
	if ((ch >= 65) && (ch <=70))
	{
		return TRUE;
	}

	return FALSE;
}

void CRSADlg::OnBnClickedButtonEncryptmessage()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);

	CBigInteger m,c;

	CString messagestr;
	//CHAR ch;

	messagestr = strInputRawMessage;
	messagestr.MakeUpper();
	messagestr.Remove(' ');
	messagestr.Remove('\n');
	messagestr.Remove('\r');

	m.InPutFromHexStr(messagestr);

#if TIMECONSUME
	clock_t start,finish;
	double chktimes;
	start = clock();
#endif

	if (m_nEncryptKeySel == 0) // Encrypt plaintext with public key
	{
		c = myRSAAlog.NewPowerModualwithMontgomeryAlgo(m,mye,myn);
	}
	else                       // Encrypt plaintext with private key
	{
		c = myRSAAlog.NewPowerModualwithMontgomeryAlgo(m,myd,myn);
	}

	//c = myRSAAlog.RSAEP(myn,mye,m);
	

#if TIMECONSUME
	finish = clock();
	chktimes = (double)(finish-start)/CLOCKS_PER_SEC;
	CString timestr;
	timestr.Format("Encrypt time %2.3fs",chktimes);
	AfxMessageBox(timestr);
#endif

	c.OutPutToHexStr(m_strC);
	m_strC = OutputStringFormat(m_strC);

	AfxMessageBox("Encrypt plaintext to ciphertext OK!");

	UpdateData(FALSE);
}

void CRSADlg::OnBnClickedButtonDecryptecypher()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	CBigInteger m,c;

	CString cstr;
	CString mstr;

	//CHAR ch;

	cstr = m_strC;

	cstr.MakeUpper();
	cstr.Remove(' ');
	cstr.Remove('\n');
	cstr.Remove('\r');

	c.InPutFromHexStr(cstr);

#if TIMECONSUME
	clock_t start,finish;
	double chktimes;
	start = clock();
#endif

	if (m_nDecryptKeySel == 0) // Decrypt cypher text with private key
	{
		if (m_DecryptType == 0)
		{
			//m = myRSAAlog.RSADPwithType1privateKey(myn,myd,c);
			//m = myRSAAlog.PowerModualwithMontgomeryAlgo(c,myd,myn);
			m= myRSAAlog.NewPowerModualwithMontgomeryAlgo(c,myd,myn);
		}
		else
		{
			m = myRSAAlog.RSADPwithType2privateKey(myP,myQ,mydP,mydQ,myqInv,c);
		}
	}
	else                       // Decrypt cypher text with public key
	{
		m= myRSAAlog.NewPowerModualwithMontgomeryAlgo(c,mye,myn);
	}

	

#if TIMECONSUME
	finish = clock();
	chktimes = (double)(finish-start)/CLOCKS_PER_SEC;
	CString timestr;
	timestr.Format("Decrypt time %2.3fs",chktimes);
	AfxMessageBox(timestr);
#endif

	m.OutPutToHexStr(mstr);
	m_strM = OutputStringFormat(mstr);

	AfxMessageBox("Decrypt ciphertext to plaintext OK!");

	UpdateData(FALSE);
}

void CRSADlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	CBigInteger e;
	CBigInteger tempe;
	CBigInteger index;
	CBigInteger Max;
	Max.m_nSign = 1;
	Max.m_nLength = 1;
	Max.Mov(0xFFFFFFFF);

    // William test start
    /*
    CBigInteger A,B,C,D;
	A.m_nSign = 1;
	A.m_nLength = 8;
    A.m_ulvalue[0] = 0x11111111;
    A.m_ulvalue[1] = 0x22222222;
    A.m_ulvalue[2] = 0x33333333;
    A.m_ulvalue[3] = 0x44444444;
    A.m_ulvalue[4] = 0x1;
    A.m_ulvalue[5] = 0x2;
    A.m_ulvalue[6] = 0x3;
    A.m_ulvalue[7] = 0x4;

    B.m_nSign = 1;
	B.m_nLength = 7;
    B.m_ulvalue[0] = 0x143;
    B.m_ulvalue[1] = 0x145;
    B.m_ulvalue[2] = 0x11FFA3;
    B.m_ulvalue[3] = 0x2CD86A;
    B.m_ulvalue[4] = 0x143;
    B.m_ulvalue[5] = 0x145;
    B.m_ulvalue[6] = 0x11FFA3;

    
    //C.Mov(A.Add(1)); // C = A+1;
	//C.Mov(A.Sub(1)); // C = A-1;
	//C.Mov(A.Add(B)); // C = A+B;
	//C.Mov(A.Sub(B)); // C = A-B;
    C.Mov(A.Mul(B)); // D = AB;
    C.Mov(A.Div(B));
	D.Mov(C.Mul(B)); // D = AB;
    C.Mov(C.Add(1));
    D.Mov(C.Mod(B));
	//E.Mov(D.Add(F)); // E = D + F;
	//G.Mov(E.Div(B)); // G = E/B,G should be equal to A.
	//H.Mov(E.Mod(B)); // H = Mod(E,B),H should be equal to F;
    */
    // William test end
	
	if (m_eGenType == 0)  // random gen
	{
		
		tempe = myRSAAlog.GenBigRandomNumber(32);
		
		index.Mov(tempe);
        
		while (index.Cmp(Max) < 0)
		{
			e.Mov(index);
			if (myRSAAlog.CheckIsInterPrime(myFn,e))
			{
				e.Mov(index);
				break;
			}
			
			index.Mov(index.Add(1));
			if (index.Cmp(Max) == 0)
			{
				index.Mov(1);
			}
		}
	}
	else
	{

		m_strE.MakeUpper();
		m_strE.Remove(' ');
		m_strE.Remove('\n');
		m_strE.Remove('\r');

		e.InPutFromHexStr(m_strE);
	}

	if (myRSAAlog.CheckIsInterPrime(myFn,e))
	{
		mye.Mov(e);
		mye.OutPutToHexStr(m_strE);
		m_strE = OutputStringFormat(m_strE);
	}
	else
	{
		mye.Mov(0);
		m_strE = "input e is invalid";
	}

	UpdateData(FALSE);
}

void CRSADlg::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	GetDlgItem(IDC_BUTTON_GENPQ)->SetWindowText(_T("Gen big P,Q"));

	UpdateData(FALSE);
}

void CRSADlg::OnBnClickedRadio4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	GetDlgItem(IDC_BUTTON_GENPQ)->SetWindowText(_T("Enter big P,Q"));

	UpdateData(FALSE);
}

void CRSADlg::OnBnClickedRadio12()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	GetDlgItem(IDC_BUTTON1)->SetWindowText(_T("ReGen e"));

	UpdateData(FALSE);
}

void CRSADlg::OnBnClickedRadio13()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	GetDlgItem(IDC_BUTTON1)->SetWindowText(_T("Enter e"));

	UpdateData(FALSE);
}

void CRSADlg::OnBnClickedRadio5()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_nPQLen = 32;
	UpdateData(FALSE);
}

void CRSADlg::OnBnClickedRadio6()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_nPQLen =64;
	UpdateData(FALSE);
}

void CRSADlg::OnBnClickedRadio7()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_nPQLen = 128;
	UpdateData(FALSE);
}

void CRSADlg::OnBnClickedRadio8()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_nPQLen = 256;
	UpdateData(FALSE);
}

void CRSADlg::OnBnClickedRadio9()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_nPQLen = 512;
	UpdateData(FALSE);
}

void CRSADlg::OnBnClickedRadio10()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_nPQLen = 1024;
	UpdateData(FALSE);
}

void CRSADlg::OnBnClickedRadio11()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_nPQLen = 1536;
	UpdateData(FALSE);
}

void CRSADlg::OnBnClickedRadioPublicKey()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CRSADlg::OnBnClickedRadioPrivateKey()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CRSADlg::OnBnClickedRadioDePrivateKey()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CRSADlg::OnBnClickedRadioDePublicKey()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CRSADlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
}
