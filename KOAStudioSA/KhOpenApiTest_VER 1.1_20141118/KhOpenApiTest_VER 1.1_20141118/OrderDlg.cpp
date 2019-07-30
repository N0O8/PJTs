//******************************************************************/
//******************************************************************/
//! All Rights Reserved. Copyright(c)   2014 (��)�ѱ��Ҹ���ġ        /
//******************************************************************/
//! File Name     : OrderDlg.cpp
//! Function      : �ֹ� ���̾�α�
//! System Name   : Ű�� ����API �׽�Ʈ
//! Create        : , 2014/06/02
//! Update        : 
//! Comment       : 
//******************************************************************/
// OrderDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "KhOpenApiTest.h"
#include "OrderDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// COrderDlg ��ȭ ����
//*******************************************************************/
//! Function Name : COrderDlg::COrderDlg(CWnd* pParent /*=NULL*/) : CDialogEx(COrderDlg::IDD, pParent)
//! Function      : ���� �ʱ� ó��
//! Param         : HANDLE hBitmap, int bits
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
COrderDlg::COrderDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COrderDlg::IDD, pParent)
{
	m_pParent = pParent;
	m_strScrNo = "8888";
	m_strJongCode = "";
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

//*******************************************************************/
// Function Name : DoDataExchange
// Function      : DDX/DDV�� ���� �� �Լ� ȣ��
// Param         : CDataExchange*	pDX
// Return        : void
// Create        : , 2014/06/02
// Comment       : DDX - ��Ʈ�Ѱ� ����������̿� ������ ��ȯ�ϴ� ����
//				 : DDV - ��������� ���� �� ���� ��ȿ�� üũ
//				 : UapdateData()�Լ��� ���� ȣ�� �� �� ����
//*******************************************************************/
void COrderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COrderDlg)
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_LIST1, m_listCtl);
}

//*******************************************************************/
// BEGIN_MESSAGE_MAP
//*******************************************************************/
BEGIN_MESSAGE_MAP(COrderDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_ORDER,	OnBtnOrder)
END_MESSAGE_MAP()

//*******************************************************************/
//! Function Name : OnInitDialog
//! Function      : ���� �ʱ� ó��
//! Param         : void
//! Return        : BOOL
//! Create        : , 2014/06/02
//! Comment       : COrderDlg �޽��� ó����
//******************************************************************/
BOOL COrderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	((CEdit*)GetDlgItem(IDC_EDT_ACCNO))->SetLimitText(10);		// ���¹�ȣ �ִ���� ����
	((CEdit*)GetDlgItem(IDC_EDT_JONGCODE))->SetLimitText(6);	// �����ڵ� �ִ���� ����

	// �ֹ��Է� �޺� �ε��� �ʱ�ȭ
	((CComboBox*)GetDlgItem(IDC_COM_TRTP))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COM_SBTP))->SetCurSel(0);

	// �ŷ����� ������ ����
	// 0:������, 3:���尡, 5:���Ǻ�������, 6:������������, 7:�ֿ켱������, 
	// 10:������IOC, 13:���尡IOC, 16:������IOC, 20:������FOK, 23:���尡FOK, 
	// 26:������FOK, 61:�尳�����ð���, 62:�ð��ܴ��ϰ��Ÿ�, 81:�ð�������
	int nTrTpCode[] = {0, 3, 5, 6, 7, 10, 13, 16, 20, 23, 26, 61, 62, 81};
	int i, nCnt = sizeof(nTrTpCode) / sizeof(*nTrTpCode);		// ��üũ�� / ����ũ�� = ���Ұ���
	for (i = 0; i < nCnt; i++)
	{
		((CComboBox*)GetDlgItem(IDC_COM_TRTP))->SetItemData(i, nTrTpCode[i]);
	}

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

//*******************************************************************/
//! Function Name : OnPaint
//! Function      : �׸��� ó��
//! Param         : void
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//!               : �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//!               : �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.
//******************************************************************/
void COrderDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//*******************************************************************/
//! Function Name : OnClose
//! Function      : �ı���
//! Param         : void
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void COrderDlg::OnClose()
{
	// ȭ�� ���� �� �θ������쿡�� �뺸(ȭ�� ���� ����)
	if (m_pParent)
	{
		int nLen = m_strScrNo.GetLength();
		char *cScrNo = new char[nLen + 1];
		memset(cScrNo, 0x00, nLen + 1);
		memcpy(cScrNo, m_strScrNo, nLen);
		m_pParent->PostMessage(UM_SCRENN_CLOSE, 0U, (LPARAM)cScrNo);
	}

	CDialogEx::OnClose();
}

//*******************************************************************/
//! Function Name : OnQueryDragIcon
//! Function      : �巡�� ������ ó��
//! Param         : void
//! Return        : HCURSOR
//! Create        : , 2014/06/02
//! Comment       : ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ��� 
//!               : �� �Լ��� ȣ���մϴ�.
//******************************************************************/
HCURSOR COrderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//*******************************************************************/
//! Function Name : OnBtnOrder
//! Function      : �ֹ� ��ư
//! Param         : void
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void COrderDlg::OnBtnOrder()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// ���¹�ȣ �Է� ����
	CString strAccNo;
	((CEdit*)GetDlgItem(IDC_EDT_ACCNO))->GetWindowText(strAccNo);
	if (strAccNo.GetLength() != 10)
	{
		AfxMessageBox("���¹�ȣ 11�ڸ� �Է� �� �ּ���~!");
		((CEdit*)GetDlgItem(IDC_EDT_ACCNO))->SetFocus();
		return;
	}

	// �����ڵ� �Է� ����
	((CEdit*)GetDlgItem(IDC_EDT_JONGCODE))->GetWindowText(m_strJongCode);
	if (m_strJongCode.GetLength() != 6)
	{
		AfxMessageBox("�����ڵ� 6�ڸ� �Է� �� �ּ���~!");
		((CEdit*)GetDlgItem(IDC_EDT_JONGCODE))->SetFocus();
		return;
	}

	// �ֹ����� �Է� ����
	CString strQty;
	((CEdit*)GetDlgItem(IDC_EDT_QUANTITY))->GetWindowText(strQty);
	int lQty = atol(strQty);
	if (lQty < 1)
	{
		AfxMessageBox("�ֹ������� 0���� ū ���� �Է� �� �ּ���~!");
		((CEdit*)GetDlgItem(IDC_EDT_QUANTITY))->SetFocus();
		return;
	}

	// �ŷ����� ���
	// 0:������, 3:���尡, 5:���Ǻ�������, 6:������������, 7:�ֿ켱������, 
	// 10:������IOC, 13:���尡IOC, 16:������IOC, 20:������FOK, 23:���尡FOK, 
	// 26:������FOK, 61:�尳�����ð���, 62:�ð��ܴ��ϰ��Ÿ�, 81:�ð�������
	CString strHogaGb;
	int nIndex = ((CComboBox*)GetDlgItem(IDC_COM_TRTP))->GetCurSel();
	DWORD dwData = ((CComboBox*)GetDlgItem(IDC_COM_TRTP))->GetItemData(nIndex);
	strHogaGb.Format(_T("%02d"), dwData);

	// �ֹ����� �Է� ����
	CString strPrice;
	((CEdit*)GetDlgItem(IDC_EDT_PRICE))->GetWindowText(strPrice);
	long lPrice = atoi(strPrice);
	if (dwData != 3 && dwData != 13 && dwData != 23 && lPrice < 1)
	{
		AfxMessageBox("�ֹ������� 0���� ū ���� �Է� �� �ּ���~!");
		((CEdit*)GetDlgItem(IDC_EDT_PRICE))->SetFocus();
		return;
	}

	// �Ÿű��� ���(1:�űԸż�, 2:�űԸŵ� 3:�ż����, 4:�ŵ����, 5:�ż�����, 6:�ŵ�����)
	long lOrderType = ((CComboBox*)GetDlgItem(IDC_COM_SBTP))->GetCurSel() + 1;

	// ���ֹ���ȣ �Է� ����
	CString strOrgNo;
	((CEdit*)GetDlgItem(IDC_EDT_ORGNO))->GetWindowText(strOrgNo);
	if (lOrderType > 2 && strOrgNo.GetLength() < 1)
	{
		AfxMessageBox("���ֹ���ȣ�� �Է� �� �ּ���~!");
		((CEdit*)GetDlgItem(IDC_EDT_ORGNO))->SetFocus();
		return;
	}

	CString strRQName = _T("�ֽ��ֹ�");
	int i;
	long lRet;
//	for (i = 0; i < 10; i++)
	{
		// �ֹ����� ������ �� �ֹ����� ���� �� ������ ��� ������ ó��.
		lRet = OP_ERR_ORD_OVERFLOW;
		while (lRet == OP_ERR_ORD_OVERFLOW)
		{
			lRet = theApp.m_khOpenApi.SendOrder(strRQName, m_strScrNo, strAccNo, lOrderType, 
												m_strJongCode, lQty, lPrice, strHogaGb, strOrgNo);
			if (lRet == OP_ERR_ORD_OVERFLOW)
			{
				Sleep(300);
			}
		}
	}
	if (!theApp.IsError(lRet))
	{
		return;
	}
}

//*******************************************************************/
//! Function Name : OnReceiveTrDataKhopenapictrl
//! Function      : ��ȸ ���� ó��
//! Param         : LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void COrderDlg::OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg)
{
	CString strRQName = sRQName;
	if (strRQName == _T("�ֽ��ֹ�"))		// �ֽı⺻���� ����
	{
		// �ֹ� ��ȣ
		CString strData = theApp.m_khOpenApi.GetCommData(sTrcode, sRQName, 0, _T(""));	strData.Trim();

		CString str111 = theApp.m_khOpenApi.GetCommData(sTrcode, sRQName, 0, _T("���ֹ���ȣ"));
		CString str222 = theApp.m_khOpenApi.GetCommData(sTrcode, sRQName, 0, _T("�����ڵ�"));
		CString str333 = theApp.m_khOpenApi.GetCommData(sTrcode, sRQName, 0, _T("�ֹ�����"));
		CString str444 = theApp.m_khOpenApi.GetCommData(sTrcode, sRQName, 0, _T("�ֹ�����"));
//		CString strData = theApp.m_khOpenApi.CommGetData(sTrcode, _T(""), _T(""), 0, _T(""));	strData.Trim();
		((CEdit*)GetDlgItem(IDC_EDT_ORGNO))->SetWindowText(strData);
	}
}

//*******************************************************************/
//! Function Name : OnReceiveMsgKhopenapictrl
//! Function      : ��ȸ ���� ó��
//! Param         : LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sMsg
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void COrderDlg::OnReceiveMsgKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sMsg)
{
	((CStatic*)GetDlgItem(IDC_STC_MSGBAR))->SetWindowText(sMsg);
}

//*******************************************************************/
//! Function Name : OnReceiveRealDataKhopenapictrl
//! Function      : �ǽð� ó��
//! Param         : LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void COrderDlg::OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData)
{
}

//*******************************************************************/
//! Function Name : OnReceiveChejanData
//! Function      : ü���ܰ� �ǽð� ó��
//! Param         : LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void COrderDlg::OnReceiveChejanData(LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList)
{
	CString strGubun, strFidList, strText;
	CString	strAccNo, strOrdNo, strOrdPrice, strOrdCnt;

	int nIndex(0);
	LONG lFid;
	strGubun	= sGubun;
	strFidList	= sFidList;
	
	strAccNo	= theApp.m_khOpenApi.GetChejanData(9201);
	strOrdNo	= theApp.m_khOpenApi.GetChejanData(9203);
	strOrdPrice	= theApp.m_khOpenApi.GetChejanData(901);
	strOrdCnt	= theApp.m_khOpenApi.GetChejanData(900);

	m_listCtl.AddString("ü������");
	strText.Format(_T("���¹�ȣ[%s], �ֹ���ȣ[%s], �ֹ�����[%s], �ֹ�����[%s]"), strAccNo, strOrdNo, strOrdPrice, strOrdCnt);
	m_listCtl.AddString(strText);
}