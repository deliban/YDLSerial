
// YDLSerialDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "YDLSerial.h"
#include "YDLSerialDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CYDLSerialDlg 对话框



CYDLSerialDlg::CYDLSerialDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CYDLSerialDlg::IDD, pParent)
    , m_EditReceive(_T(""))
    , m_EditSend(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CYDLSerialDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT1_REV, m_EditReceive);
    DDX_Text(pDX, IDC_EDIT2_SEND, m_EditSend);
    DDX_Control(pDX, IDC_MSCOMM1, m_Mscom);
    DDX_Control(pDX, IDC_COMBO1_SERIAL, m_CombSerialPort);
    DDX_Control(pDX, IDC_COMBO2_BAUD, m_CombBaudRate);
    DDX_Control(pDX, IDC_COMBO3_CHECK, m_CombCheckDigit);
    DDX_Control(pDX, IDC_COMBO4_DATA, m_CombDataBits);
    DDX_Control(pDX, IDC_COMBO5_STOP, m_CombStopBits);
}

BEGIN_MESSAGE_MAP(CYDLSerialDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON1_OPEN, &CYDLSerialDlg::OnBnClickedButton1Open)
    ON_BN_CLICKED(IDC_BUTTON2_SEND, &CYDLSerialDlg::OnBnClickedButton2Send)
    ON_BN_CLICKED(IDC_BUTTON3_CLEAN, &CYDLSerialDlg::OnBnClickedButton3Clean)
    ON_BN_CLICKED(IDC_BUTTON4_CLOSE, &CYDLSerialDlg::OnBnClickedButton4Close)
END_MESSAGE_MAP()


// CYDLSerialDlg 消息处理程序

BOOL CYDLSerialDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码


    //m_CombSerialPort.SetCurSel(0);//选择并显示
    GetComNum();

    m_CombBaudRate.AddString(L"2400");
    m_CombBaudRate.AddString(L"4800");
    m_CombBaudRate.AddString(L"9600");
    m_CombBaudRate.AddString(L"115200");
    m_CombBaudRate.SetCurSel(3);//选择并显示

    m_CombCheckDigit.AddString(L"e");
    m_CombCheckDigit.AddString(L"m");
    m_CombCheckDigit.AddString(L"n");
    m_CombCheckDigit.AddString(L"s");
    m_CombCheckDigit.SetCurSel(2);//选择并显示

    m_CombDataBits.AddString(L"6");
    m_CombDataBits.AddString(L"7");
    m_CombDataBits.AddString(L"8");
    m_CombDataBits.AddString(L"9");
    m_CombDataBits.SetCurSel(2);//选择并显示

    m_CombStopBits.AddString(L"1");
    m_CombStopBits.AddString(L"1.5");
    m_CombStopBits.AddString(L"2");
    m_CombStopBits.SetCurSel(0);//选择并显示


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CYDLSerialDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CYDLSerialDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CYDLSerialDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);// C++的 static_cast<> 隐式转换  reinterpret_cast<>强制转换
}


/*********************************************
Function:
Desc:
Input:	nullptr
* @param a -
* @param b -
Output:	nullptr
Return:	nullptr
Others:	nullptr
*******************************************************/
void CYDLSerialDlg::OnBnClickedButton1Open()
{
    // TODO:  在此添加控件通知处理程序代码
    CString str, str1, n;					//定义字符串
    GetDlgItemText(IDC_BUTTON1_OPEN, str);
    CWnd *h1;
    h1 = GetDlgItem(IDC_BUTTON1_OPEN);		//指向控件的caption

    if (!m_Mscom.get_PortOpen())
    {
        m_CombBaudRate.GetLBText(m_CombBaudRate.GetCurSel(), str1);//取得所选的字符串，并存放在str1里面
       

        CString m_Combo_CheckDigit, m_Combo_DataBits, m_Combo_StopBits;
        GetDlgItemText(IDC_COMBO3_CHECK, m_Combo_CheckDigit);
        GetDlgItemText(IDC_COMBO4_DATA, m_Combo_DataBits);
        GetDlgItemText(IDC_COMBO5_STOP, m_Combo_StopBits);

        str1 = str1 + ',' + m_Combo_CheckDigit + ',' + m_Combo_DataBits + ',' + m_Combo_StopBits;			//这句话很关键
      /*  GetDlgItemText(IDC_COMBO_SHUJUWEI, m_Combo_SHUJUWEI);
        GetDlgItemText(IDC_COMBO_TINGZHIWEI, m_Combo_TINGZHIWEI);
        GetDlgItemText(IDC_BUTTON1_OPEN,  m_EditSend);*/

        m_Mscom.put_CommPort((m_CombSerialPort.GetCurSel() + 1));	//选择串口
        m_Mscom.put_InputMode(1);			//设置输入方式为二进制方式
        m_Mscom.put_Settings(str1);		//波特率为（波特率组Á合框）无校验，8数据位，1个停止位
        m_Mscom.put_InputLen(1024);		//设置当前接收区数据长度为1024
        m_Mscom.put_RThreshold(1);			//缓冲区一个字符引发事件
        m_Mscom.put_RTSEnable(1);			//设置RT允许

        m_Mscom.put_PortOpen(true);		//打开串口
        if (m_Mscom.get_PortOpen())
        {
            str = _T("关闭串口");
            UpdateData(true);
            h1->SetWindowText(str);			//改变按钮名称为‘’关闭串口”
            //::SetTextColor(GetDlgItem(IDC_BUTTON1_OPEN)->GetDC(), RGB(255, 255, 255));//
        }
    }

    else
    {
        m_Mscom.put_PortOpen(false);
        if (str != _T("打开串口"))
        {
            str = _T("打开串口");
            UpdateData(true);
            h1->SetWindowText(str);			//改变按钮名称为打开串口
        }
    }

}
/*********************************************
Function:
Desc:
Input:	nullptr
* @param a -
* @param b -
Output:	nullptr
Return:	nullptr
Others:	nullptr
*******************************************************/
void CYDLSerialDlg::OnBnClickedButton2Send()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(true);//更新控件数据
    //try 
    //{
    //    m_Mscom.put_Output(COleVariant(m_EditSend));//把发送编辑框的数据发送出去
    //}
    //catch (int e)
    //{

    //}
    //catch (...)
    //{

    //}
    if (m_Mscom.get_PortOpen())
    {
        m_Mscom.put_Output(COleVariant(m_EditSend));
    }
    else
    {
        MessageBox(L"请先打开串口", MB_OK);
    }
    //m_EditSend.Empty(); //发送后清空输入框
    //UpdateData(false); //更新编辑框内容

}

/**************************************************
Function:OnBnClickedButton3Clean()
Desc:
Input:	nullptr
* @param a -
* @param b -
Output:	nullptr
Return:	nullptr
Others:	nullptr
*******************************************************/    
void CYDLSerialDlg::OnBnClickedButton3Clean()
{
    // TODO:  在此添加控件通知处理程序代码
    m_EditReceive = _T("");	//给接收编辑框发送空格符
    UpdateData(false);		//更新数据

}


void CYDLSerialDlg::OnBnClickedButton4Close()
{
    // TODO:  在此添加控件通知处理程序代码
    if (m_Mscom.get_PortOpen())
        m_Mscom.put_PortOpen(false);
    CDialogEx::OnCancel();

}
BEGIN_EVENTSINK_MAP(CYDLSerialDlg, CDialogEx)
    ON_EVENT(CYDLSerialDlg, IDC_MSCOMM1, 1, CYDLSerialDlg::OnCommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()


void CYDLSerialDlg::OnCommMscomm1()
{
    // TODO:  在此处添加消息处理程序代码
    if (m_Mscom.get_CommEvent() == 2)
    {
        char str[1024] = { 0 };
        long k;
        VARIANT InputData = m_Mscom.get_Input();	//读缓冲区
        COleSafeArray fs;
        fs = static_cast<COleSafeArray>(InputData);	//VARIANT型变À量转换为COleSafeArray型变量
        for (k = 0; k<static_cast<long>(fs.GetOneDimSize()); k++)
            fs.GetElement(&k, str + k);	//转换为BYTE型数组

        m_EditReceive += str;      //	接收到编辑框里面
        //SetTimer(1,10,NULL);		//延时10ms
        UpdateData(false);
    }

}

/*****************************************************
Function:GetComNum(void)
Desc:寻找当前计算机可用的COM
Input:	nullptr
* @param a -
* @param b -
Output:	nullptr
Return:	nullptr
Others:	nullptr
*******************************************************/
bool CYDLSerialDlg::GetComNum(void)
{
    long lReg;
    HKEY hKey;
    DWORD MaxValueLength;
    DWORD dwValueNumber;
    int comNum = 0;
    lReg = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("HARDWARE\\DEVICEMAP\\SERIALCOMM"),
        0, KEY_QUERY_VALUE, &hKey);

    if (lReg != ERROR_SUCCESS) //成功时返回ERROR_SUCCESS，
    {
        //MessageBox(TEXT("未自动找到串口!\nOpen Registry Error!\n"));
        return FALSE;
    }

    lReg = RegQueryInfoKey(hKey, NULL, NULL, NULL, NULL, NULL, NULL,
        &dwValueNumber, &MaxValueLength, NULL, NULL, NULL);

    if (lReg != ERROR_SUCCESS) //没有成功
    {
        //MessageBox(TEXT("未自动找到串口!\nGetting Info Error!\n"));
        return FALSE;
    }

    TCHAR *pValueName, *pCOMNumber;
    DWORD cchValueName, dwValueSize = 10;

    for (int i = 0; i <static_cast<int> (dwValueNumber); i++)//类型隐式转换 减少警告
    {
        cchValueName = MaxValueLength + 1;
        dwValueSize = 10;
        pValueName = (TCHAR*)VirtualAlloc(NULL, cchValueName, MEM_COMMIT, PAGE_READWRITE);
        lReg = RegEnumValue(hKey, i, pValueName,
            &cchValueName, NULL, NULL, NULL, NULL);

        if ((lReg != ERROR_SUCCESS) && (lReg != ERROR_NO_MORE_ITEMS))
        {
            //MessageBox(TEXT("未自动找到串口!\nEnum Registry Error or No More Items!\n"));
            return FALSE;
        }

        pCOMNumber = (TCHAR*)VirtualAlloc(NULL, 6, MEM_COMMIT, PAGE_READWRITE);
        lReg = RegQueryValueEx(hKey, pValueName, NULL,
            NULL, (LPBYTE)pCOMNumber, &dwValueSize);

        if (lReg != ERROR_SUCCESS)
        {
            //MessageBox(TEXT("未自动找到串口!\nCan not get the name of the port"));
            return FALSE;
        }

        CString str(pCOMNumber);
        m_CombSerialPort.AddString(str);        
        //int len = str.GetLength();
        //str = str.Right(len - 3);
        //((CComboBox*)GetDlgItem(IDC_COMBO1_SERIAL))->SetCurSel(_ttoi(str) - 1);//把获取的值加入到ComBox控件中
        //                                                                       //char *  -->int 用atoi; CString -->int用_ttoi      
        ((CComboBox*)GetDlgItem(IDC_COMBO1_SERIAL))->SetCurSel(comNum++);        //CurSel从零开始

        VirtualFree(pValueName, 0, MEM_RELEASE);
        VirtualFree(pCOMNumber, 0, MEM_RELEASE);
    }
    return TRUE;
}
