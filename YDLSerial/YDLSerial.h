
// YDLSerial.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CYDLSerialApp: 
// �йش����ʵ�֣������ YDLSerial.cpp
//

class CYDLSerialApp : public CWinApp
{
public:
	CYDLSerialApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CYDLSerialApp theApp;