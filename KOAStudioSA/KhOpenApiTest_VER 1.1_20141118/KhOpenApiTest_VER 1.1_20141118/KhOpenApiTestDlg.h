//******************************************************************/
//******************************************************************/
//! All Rights Reserved. Copyright(c)   2014 (주)한국소리마치        /
//******************************************************************/
//! File Name     : KhOpenApiTestDlg.h
//! Function      : 키움 오픈API 테스트 다이얼로그
//! System Name   : 키움 오픈API 테스트
//! Create        : , 2014/06/02
//! Update        : 
//! Comment       : 
//******************************************************************/
// KhOpenApiTestDlg.h : 헤더 파일
//

#pragma once

// CKhOpenApiTestDlg 대화 상자
class CKhOpenApiTestDlg : public CDialogEx
{
// 생성입니다.
public:
	CKhOpenApiTestDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_KHOPENAPITEST_DLG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

public:
	CMapStringToPtr m_mapScreen;

	int m_nScrN0;
	CMapStringToString m_mapScreenNum;
	BOOL GetNextScreenNum(int nScreenType);

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnScreenClose(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBtnCurrentPrice();
	afx_msg void OnBtnOrder();
	afx_msg void OnBtnKwanSim();
	DECLARE_MESSAGE_MAP()
	void OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg);
	void OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData);
	void OnReceiveMsgKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sMsg);
	void OnReceiveChejanData(LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList);
	void OnEventConnect(LONG nItemCnt);
	DECLARE_EVENTSINK_MAP()
};