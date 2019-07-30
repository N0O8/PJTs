//******************************************************************/
//******************************************************************/
//! All Rights Reserved. Copyright(c)   2014 (주)한국소리마치        /
//******************************************************************/
//! File Name     : OrderDlg.cpp
//! Function      : 주문 다이얼로그
//! System Name   : 키움 오픈API 테스트
//! Create        : , 2014/06/02
//! Update        : 
//! Comment       : 
//******************************************************************/
// OrderDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "KhOpenApiTest.h"
#include "OrderDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// COrderDlg 대화 상자
//*******************************************************************/
//! Function Name : COrderDlg::COrderDlg(CWnd* pParent /*=NULL*/) : CDialogEx(COrderDlg::IDD, pParent)
//! Function      : 생성 초기 처리
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
// Function      : DDX/DDV에 관련 된 함수 호출
// Param         : CDataExchange*	pDX
// Return        : void
// Create        : , 2014/06/02
// Comment       : DDX - 컨트롤과 멤버변수사이에 정보를 교환하는 역할
//				 : DDV - 멤버변수에 저장 될 값의 유효성 체크
//				 : UapdateData()함수로 간접 호출 할 수 있음
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
//! Function      : 생성 초기 처리
//! Param         : void
//! Return        : BOOL
//! Create        : , 2014/06/02
//! Comment       : COrderDlg 메시지 처리기
//******************************************************************/
BOOL COrderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	((CEdit*)GetDlgItem(IDC_EDT_ACCNO))->SetLimitText(10);		// 계좌번호 최대길이 설정
	((CEdit*)GetDlgItem(IDC_EDT_JONGCODE))->SetLimitText(6);	// 종목코드 최대길이 설정

	// 주문입력 콤보 인덱스 초기화
	((CComboBox*)GetDlgItem(IDC_COM_TRTP))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COM_SBTP))->SetCurSel(0);

	// 거래구분 데이터 세팅
	// 0:지정가, 3:시장가, 5:조건부지정가, 6:최유리지정가, 7:최우선지정가, 
	// 10:지정가IOC, 13:시장가IOC, 16:최유리IOC, 20:지정가FOK, 23:시장가FOK, 
	// 26:최유리FOK, 61:장개시전시간외, 62:시간외단일가매매, 81:시간외종가
	int nTrTpCode[] = {0, 3, 5, 6, 7, 10, 13, 16, 20, 23, 26, 61, 62, 81};
	int i, nCnt = sizeof(nTrTpCode) / sizeof(*nTrTpCode);		// 전체크기 / 원소크기 = 원소개수
	for (i = 0; i < nCnt; i++)
	{
		((CComboBox*)GetDlgItem(IDC_COM_TRTP))->SetItemData(i, nTrTpCode[i]);
	}

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

//*******************************************************************/
//! Function Name : OnPaint
//! Function      : 그리기 처리
//! Param         : void
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//!               : 아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//!               : 프레임워크에서 이 작업을 자동으로 수행합니다.
//******************************************************************/
void COrderDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//*******************************************************************/
//! Function Name : OnClose
//! Function      : 파괴자
//! Param         : void
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void COrderDlg::OnClose()
{
	// 화면 닫을 때 부모윈도우에게 통보(화면 관리 위해)
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
//! Function      : 드래그 아이콘 처리
//! Param         : void
//! Return        : HCURSOR
//! Create        : , 2014/06/02
//! Comment       : 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서 
//!               : 이 함수를 호출합니다.
//******************************************************************/
HCURSOR COrderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//*******************************************************************/
//! Function Name : OnBtnOrder
//! Function      : 주문 버튼
//! Param         : void
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void COrderDlg::OnBtnOrder()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 계좌번호 입력 여부
	CString strAccNo;
	((CEdit*)GetDlgItem(IDC_EDT_ACCNO))->GetWindowText(strAccNo);
	if (strAccNo.GetLength() != 10)
	{
		AfxMessageBox("계좌번호 11자를 입력 해 주세요~!");
		((CEdit*)GetDlgItem(IDC_EDT_ACCNO))->SetFocus();
		return;
	}

	// 종목코드 입력 여부
	((CEdit*)GetDlgItem(IDC_EDT_JONGCODE))->GetWindowText(m_strJongCode);
	if (m_strJongCode.GetLength() != 6)
	{
		AfxMessageBox("종목코드 6자를 입력 해 주세요~!");
		((CEdit*)GetDlgItem(IDC_EDT_JONGCODE))->SetFocus();
		return;
	}

	// 주문수량 입력 여부
	CString strQty;
	((CEdit*)GetDlgItem(IDC_EDT_QUANTITY))->GetWindowText(strQty);
	int lQty = atol(strQty);
	if (lQty < 1)
	{
		AfxMessageBox("주문수량을 0보다 큰 수로 입력 해 주세요~!");
		((CEdit*)GetDlgItem(IDC_EDT_QUANTITY))->SetFocus();
		return;
	}

	// 거래구분 취득
	// 0:지정가, 3:시장가, 5:조건부지정가, 6:최유리지정가, 7:최우선지정가, 
	// 10:지정가IOC, 13:시장가IOC, 16:최유리IOC, 20:지정가FOK, 23:시장가FOK, 
	// 26:최유리FOK, 61:장개시전시간외, 62:시간외단일가매매, 81:시간외종가
	CString strHogaGb;
	int nIndex = ((CComboBox*)GetDlgItem(IDC_COM_TRTP))->GetCurSel();
	DWORD dwData = ((CComboBox*)GetDlgItem(IDC_COM_TRTP))->GetItemData(nIndex);
	strHogaGb.Format(_T("%02d"), dwData);

	// 주문가격 입력 여부
	CString strPrice;
	((CEdit*)GetDlgItem(IDC_EDT_PRICE))->GetWindowText(strPrice);
	long lPrice = atoi(strPrice);
	if (dwData != 3 && dwData != 13 && dwData != 23 && lPrice < 1)
	{
		AfxMessageBox("주문가격을 0보다 큰 수로 입력 해 주세요~!");
		((CEdit*)GetDlgItem(IDC_EDT_PRICE))->SetFocus();
		return;
	}

	// 매매구분 취득(1:신규매수, 2:신규매도 3:매수취소, 4:매도취소, 5:매수정정, 6:매도정정)
	long lOrderType = ((CComboBox*)GetDlgItem(IDC_COM_SBTP))->GetCurSel() + 1;

	// 원주문번호 입력 여부
	CString strOrgNo;
	((CEdit*)GetDlgItem(IDC_EDT_ORGNO))->GetWindowText(strOrgNo);
	if (lOrderType > 2 && strOrgNo.GetLength() < 1)
	{
		AfxMessageBox("원주문번호를 입력 해 주세요~!");
		((CEdit*)GetDlgItem(IDC_EDT_ORGNO))->SetFocus();
		return;
	}

	CString strRQName = _T("주식주문");
	int i;
	long lRet;
//	for (i = 0; i < 10; i++)
	{
		// 주문전송 과부하 시 주문전송 가능 할 때까지 계속 내도록 처리.
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
//! Function      : 조회 응답 처리
//! Param         : LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void COrderDlg::OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg)
{
	CString strRQName = sRQName;
	if (strRQName == _T("주식주문"))		// 주식기본정보 설정
	{
		// 주문 번호
		CString strData = theApp.m_khOpenApi.GetCommData(sTrcode, sRQName, 0, _T(""));	strData.Trim();

		CString str111 = theApp.m_khOpenApi.GetCommData(sTrcode, sRQName, 0, _T("원주문번호"));
		CString str222 = theApp.m_khOpenApi.GetCommData(sTrcode, sRQName, 0, _T("종목코드"));
		CString str333 = theApp.m_khOpenApi.GetCommData(sTrcode, sRQName, 0, _T("주문가격"));
		CString str444 = theApp.m_khOpenApi.GetCommData(sTrcode, sRQName, 0, _T("주문수량"));
//		CString strData = theApp.m_khOpenApi.CommGetData(sTrcode, _T(""), _T(""), 0, _T(""));	strData.Trim();
		((CEdit*)GetDlgItem(IDC_EDT_ORGNO))->SetWindowText(strData);
	}
}

//*******************************************************************/
//! Function Name : OnReceiveMsgKhopenapictrl
//! Function      : 조회 에러 처리
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
//! Function      : 실시간 처리
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
//! Function      : 체결잔고 실시간 처리
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

	m_listCtl.AddString("체결정보");
	strText.Format(_T("계좌번호[%s], 주문번호[%s], 주문가격[%s], 주문수량[%s]"), strAccNo, strOrdNo, strOrdPrice, strOrdCnt);
	m_listCtl.AddString(strText);
}