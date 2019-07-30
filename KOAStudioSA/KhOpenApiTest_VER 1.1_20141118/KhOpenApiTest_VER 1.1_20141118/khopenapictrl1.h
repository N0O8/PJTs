// CKhopenapictrl1.h  : Microsoft Visual C++로 만든 ActiveX 컨트롤 래퍼 클래스의 선언입니다.

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CKhopenapictrl1

class CKhopenapictrl1 : public CWnd
{
protected:
	DECLARE_DYNCREATE(CKhopenapictrl1)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xA1574A0D, 0x6BFA, 0x4BD7, { 0x90, 0x20, 0xDE, 0xD8, 0x87, 0x11, 0x81, 0x8D } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// 특성입니다.
public:

// 작업입니다.
public:

	long CommConnect()
	{
		long result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void CommTerminate()
	{
		InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long CommRqData(LPCTSTR sRQName, LPCTSTR sTrCode, long nPrevNext, LPCTSTR sScreenNo)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR ;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, parms, sRQName, sTrCode, nPrevNext, sScreenNo);
		return result;
	}
	CString GetLoginInfo(LPCTSTR sTag)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, sTag);
		return result;
	}
	long SendOrder(LPCTSTR sRQName, LPCTSTR sScreenNo, LPCTSTR sAccNo, long nOrderType, LPCTSTR sCode, long nQty, long nPrice, LPCTSTR sHogaGb, LPCTSTR sOrgOrderNo)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, parms, sRQName, sScreenNo, sAccNo, nOrderType, sCode, nQty, nPrice, sHogaGb, sOrgOrderNo);
		return result;
	}
	long SendOrderFO(LPCTSTR sScreenNo, LPCTSTR sAccNo, LPCTSTR sPw, LPCTSTR sCode, long nOrderType, long nOrderCount, long nOrderPrice, LPCTSTR sOrderDTCD, long nCndtDTCD, LPCTSTR sOrgOrderNo)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR ;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_I4, (void*)&result, parms, sScreenNo, sAccNo, sPw, sCode, nOrderType, nOrderCount, nOrderPrice, sOrderDTCD, nCndtDTCD, sOrgOrderNo);
		return result;
	}
	void SetInputValue(LPCTSTR sID, LPCTSTR sValue)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms, sID, sValue);
	}
	long SetOutputFID(LPCTSTR sID)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_I4, (void*)&result, parms, sID);
		return result;
	}
	CString CommGetData(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sFieldName, long nIndex, LPCTSTR sInnerFieldName)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR ;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, sJongmokCode, sRealType, sFieldName, nIndex, sInnerFieldName);
		return result;
	}
	void DisconnectRealData(LPCTSTR sScnNo)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms, sScnNo);
	}
	long GetRepeatCnt(LPCTSTR sTrCode, LPCTSTR sRecordName)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_I4, (void*)&result, parms, sTrCode, sRecordName);
		return result;
	}
	long CommKwRqData(LPCTSTR sArrCode, long bNext, long nCodeCount, long nTypeFlag, LPCTSTR sRQName, LPCTSTR sScreenNo)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR ;
		InvokeHelper(0xc, DISPATCH_METHOD, VT_I4, (void*)&result, parms, sArrCode, bNext, nCodeCount, nTypeFlag, sRQName, sScreenNo);
		return result;
	}
	CString GetAPIModulePath()
	{
		CString result;
		InvokeHelper(0xd, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString GetCodeListByMarket(LPCTSTR sMarket)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xe, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, sMarket);
		return result;
	}
	long GetConnectState()
	{
		long result;
		InvokeHelper(0xf, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString GetMasterCodeName(LPCTSTR sTrCode)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x10, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, sTrCode);
		return result;
	}
	long GetMasterListedStockCnt(LPCTSTR sTrCode)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x11, DISPATCH_METHOD, VT_I4, (void*)&result, parms, sTrCode);
		return result;
	}
	CString GetMasterConstruction(LPCTSTR sTrCode)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x12, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, sTrCode);
		return result;
	}
	CString GetMasterListedStockDate(LPCTSTR sTrCode)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x13, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, sTrCode);
		return result;
	}
	CString GetMasterLastPrice(LPCTSTR sTrCode)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x14, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, sTrCode);
		return result;
	}
	CString GetMasterStockState(LPCTSTR sTrCode)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x15, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, sTrCode);
		return result;
	}
	long GetDataCount(LPCTSTR strRecordName)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x16, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strRecordName);
		return result;
	}
	CString GetOutputValue(LPCTSTR strRecordName, long nRepeatIdx, long nItemIdx)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 ;
		InvokeHelper(0x17, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, strRecordName, nRepeatIdx, nItemIdx);
		return result;
	}
	CString GetCommData(LPCTSTR strTrCode, LPCTSTR strRecordName, long nIndex, LPCTSTR strItemName)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR ;
		InvokeHelper(0x18, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, strTrCode, strRecordName, nIndex, strItemName);
		return result;
	}
	CString GetCommRealData(LPCTSTR strCode, long nIndex)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x19, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, strCode, nIndex);
		return result;
	}
	CString GetChejanData(long nIndex)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1a, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, nIndex);
		return result;
	}


};
