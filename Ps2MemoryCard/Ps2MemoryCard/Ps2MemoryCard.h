
// Ps2MemoryCard.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPs2MemoryCardApp:
// �йش����ʵ�֣������ Ps2MemoryCard.cpp
//

class CPs2MemoryCardApp : public CWinApp
{
public:
	CPs2MemoryCardApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPs2MemoryCardApp theApp;