
// YDLSerialDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "mscomm1.h"


// CYDLSerialDlg 对话框
class CYDLSerialDlg : public CDialogEx
{
// 构造
public:
	CYDLSerialDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_YDLSERIAL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
    CString m_EditReceive;
    CString m_EditSend;

public:    
    CMscomm1 m_Mscom;
    afx_msg void OnBnClickedButton1Open();
private:
    CComboBox m_CombSerialPort;
public:
    CComboBox m_CombBaudRate;
    CComboBox m_CombCheckDigit;
    CComboBox m_CombDataBits;
    CComboBox m_CombStopBits;
    afx_msg void OnBnClickedButton2Send();
    afx_msg void OnBnClickedButton3Clean();
    afx_msg void OnBnClickedButton4Close();
    DECLARE_EVENTSINK_MAP()
    void OnCommMscomm1();
    bool GetComNum(void);
};
