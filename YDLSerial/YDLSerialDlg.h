
// YDLSerialDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "mscomm1.h"


// CYDLSerialDlg �Ի���
class CYDLSerialDlg : public CDialogEx
{
// ����
public:
	CYDLSerialDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_YDLSERIAL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
