/*  OpenWQSG - WQSG ����(����)
*  Copyright (C) WQSG <wqsg@qq.com>
*
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
*/
// WIPS.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WQSG ����(����).h"
#include "WIPS.h"
#include"WQSG_IPS.h"


// WIPS �Ի���

IMPLEMENT_DYNAMIC(CWIPS_O_Dlg, CBaseDialog)
CWIPS_O_Dlg::CWIPS_O_Dlg(CWnd* pParent /*=NULL*/)
	: CBaseDialog(CWIPS_O_Dlg::IDD, pParent)
	, m_strWipsDesc(_T(""))
	, m_strOldFile(_T(""))
	, m_strNewFle(_T(""))
	, m_strBeginOffset(_T("0"))
	, m_strEndOffset(_T("7FFFFFFFFFFFFFFF"))
{
	HRSRC hrexe = ::FindResource(NULL,MAKEINTRESOURCE(IDR_EXE1),_T("EXE"));
//	if(NULL == hrexe)return FALSE;

	DWORD dwSize = ::SizeofResource(NULL, hrexe);
	if(dwSize != 0)
	{
	}
	HGLOBAL hgdexe = ::LoadResource(NULL,hrexe);
//	if(NULL == hgdexe)return FALSE;

	u8 * lp_BIN = (u8*)::LockResource(hgdexe);
///////////////////////////////////
	m_�Խ�ͷ30.BIN = new u8[dwSize];
	m_�Խ�ͷ30.LEN = dwSize;
	::memcpy_s(m_�Խ�ͷ30.BIN,dwSize,lp_BIN,dwSize);
///////////////////////////////////
	::FreeResource(hgdexe);
}

CWIPS_O_Dlg::~CWIPS_O_Dlg()
{
}
void CWIPS_O_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CBaseDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT7, m_strWipsDesc);
	DDV_MaxChars(pDX, m_strWipsDesc, 65535);
	DDX_Text(pDX, IDC_EDIT2, m_strOldFile);
	DDV_MaxChars(pDX, m_strOldFile, MAX_PATH);
	DDX_Text(pDX, IDC_EDIT3, m_strNewFle);
	DDV_MaxChars(pDX, m_strNewFle, MAX_PATH);
	DDX_Text(pDX, IDC_EDIT4, m_strBeginOffset);
	DDV_MaxChars(pDX, m_strBeginOffset, 16);
	DDX_Text(pDX, IDC_EDIT5, m_strEndOffset);
	DDV_MaxChars(pDX, m_strEndOffset, 16);
}
BEGIN_MESSAGE_MAP(CWIPS_O_Dlg, CBaseDialog)
	ON_BN_CLICKED(IDC_BUTTON2, &CWIPS_O_Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CWIPS_O_Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CWIPS_O_Dlg::OnBnClickedButton4)
	ON_EN_CHANGE(IDC_EDIT4, &CWIPS_O_Dlg::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, &CWIPS_O_Dlg::OnEnChangeEdit5)
	ON_WM_CLOSE()
END_MESSAGE_MAP()
void CWIPS_O_Dlg::OnOK(){}
void CWIPS_O_Dlg::OnCancel(){}
void CWIPS_O_Dlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();

	static CWQSGFileDialog_Open fopendlg(_T("ԭ�ļ�(*.*)|*.*||"));
	fopendlg.SetWindowTitle( _T("ѡ��һ��ԭ�ļ�...") );

	if(IDOK == fopendlg.DoModal())
	{
		m_strOldFile = fopendlg.GetPathName();
		UpdateData(FALSE);
	}
}

void CWIPS_O_Dlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	static CWQSGFileDialog_Open fopendlg(_T("���ļ�(*.*)|*.*||"));
	fopendlg.SetWindowTitle( _T("ѡ��һ�����ļ�...") );

	if(IDOK == fopendlg.DoModal())
	{
		m_strNewFle = fopendlg.GetPathName();
		UpdateData(FALSE);
	}
}

void CWIPS_O_Dlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if(m_strOldFile.GetLength() == 0)
	{
		MessageBox(_T("ԭ�ļ�����Ϊ��"));
		return;
	}
	if(m_strNewFle.GetLength() == 0)
	{
		MessageBox(_T("���ļ�����Ϊ��"));
		return;
	}
	s64 nBeginOffset = 0,
		nEndOffset = 0;

	::swscanf( m_strBeginOffset.GetString() ,L"%llx" , &nBeginOffset );
	/////////////////////
	::swscanf( m_strEndOffset.GetString() ,L"%llx" , &nEndOffset );
	//////////////////////////
	BOOL bMakeExe = (((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck() == 1);

	CWQSGFileDialog_Save fopendlg( ((bMakeExe)?_T("��ִ���ļ�(*.EXE)|*.EXE||"):_T("WIPS�����ļ�(*.WIPS)|*.WIPS||")) , (bMakeExe)?_T("EXE"):_T("WIPS") );
	fopendlg.SetWindowTitle( _T("�������浽...") );

	if(IDOK == fopendlg.DoModal())
	{
		CString strFile = fopendlg.GetPathName();
		::CWQSG_IPS_OUT WQSG(m_hWnd,_T("WQSG IPS��������"));

		WQSG.MakeWips30( m_strOldFile.GetString() , m_strNewFle.GetString() , strFile.GetString() ,
			nBeginOffset , nEndOffset , 0 , (((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck() == 1)?1:0 ,
			m_strWipsDesc.GetString() , ::WQSG_strlen(m_strWipsDesc.GetString()) , (bMakeExe)?&m_�Խ�ͷ30:NULL );
	}
}
void CWIPS_O_Dlg::OnEnChangeEdit4()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	EditCheckHaxStr(m_strBeginOffset,(CEdit*)GetDlgItem(IDC_EDIT4),(CWnd*)this);
	if(m_strBeginOffset.GetLength() == 0)
	{
		m_strBeginOffset = _T("0");
		UpdateData(FALSE);
	}
}

void CWIPS_O_Dlg::OnEnChangeEdit5()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	EditCheckHaxStr( m_strEndOffset , (CEdit*)GetDlgItem(IDC_EDIT5),(CWnd*)this);
	if(m_strEndOffset.GetLength() == 0)
	{
		m_strEndOffset = _T("0");
		UpdateData(FALSE);
	}
}

void CWIPS_O_Dlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CBaseDialog::OnClose();
//	if(IDOK == MessageBox(_T("Ҫ����WIPS��������?"),NULL,MB_OKCANCEL))
//	{
		CBaseDialog::OnCancel();
//	}
}
//------------------------------------------------
IMPLEMENT_DYNAMIC(CWIPS_I_Dlg, CBaseDialog)
CWIPS_I_Dlg::CWIPS_I_Dlg(CWnd* pParent /*=NULL*/)
	: CBaseDialog(CWIPS_I_Dlg::IDD, pParent)
	, m_strWipsFile(_T(""))
	, m_strWipsDesc_In(_T(""))
{
}

CWIPS_I_Dlg::~CWIPS_I_Dlg()
{
}
void CWIPS_I_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CBaseDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT6, m_strWipsFile);
	DDV_MaxChars(pDX, m_strWipsFile, MAX_PATH);
	DDX_Text(pDX, IDC_EDIT10, m_strWipsDesc_In);
}


BEGIN_MESSAGE_MAP(CWIPS_I_Dlg, CBaseDialog)
	ON_BN_CLICKED(IDC_BUTTON5, &CWIPS_I_Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CWIPS_I_Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON1, &CWIPS_I_Dlg::OnBnClickedButton1)
	ON_WM_CLOSE()
END_MESSAGE_MAP()
void CWIPS_I_Dlg::OnOK(){}
void CWIPS_I_Dlg::OnCancel(){}
void CWIPS_I_Dlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	static CWQSGFileDialog_Open fopendlg( _T("WIPS�����ļ�(*.WIPS)|*.WIPS||") );
	fopendlg.SetWindowTitle( _T("ѡ��һ��WIPS�����ļ�...") );

	if(IDOK == fopendlg.DoModal())
	{
		m_strWipsFile = fopendlg.GetPathName();
		ShowWipsInfo(m_strWipsFile);
		UpdateData(FALSE);
	}
}

void CWIPS_I_Dlg::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if(m_strWipsFile.GetLength() == 0)
	{
		MessageBox(_T("�����ļ�����Ϊ��"));
		return;
	}


	static CWQSGFileDialog_Save fopendlg( _T("Ŀ���ļ��ļ�(*.*)|*.*||") );
	fopendlg.SetWindowTitle( _T("��ѡ����ļ��򲹶�...") );

	if(IDOK == fopendlg.DoModal())
	{
		CString strFile = fopendlg.GetPathName();
		::CWQSG_IPS_IN WQSG(m_hWnd,_T("WQSG IPS��������"));
		WQSG.�򲹶�(m_strWipsFile.GetString(),strFile.GetString());
	}
}
void CWIPS_I_Dlg::ShowWipsInfo(const CString& a_strFile)
{
	::CWD_WipsInfo info;
	m_strWipsDesc_In = _T("�Ƿ����߲�֧�ֵĲ����ļ�");

	if(info.LoadWipsDesc( a_strFile.GetString() ) )
	{
		if(::WQSG_strlen(info.m_szDesc) == 0)
		{
			::WQSG_strcpy(L"��",info.m_szDesc);
		}

		if(info.m_uCrc32)
		{
			m_strWipsDesc_In.Format( L"�����汾: %s\r\nĿ���ļ���CRC32��֤: %X\r\n�򲹶�����ļ���С: %u\r\n\r\n����˵��:\r\n",
				info.������ʶ , info.m_uCrc32 , info.Ŀ���С );
		}
		else
		{
			m_strWipsDesc_In.Format( L"�����汾: %s\r\nĿ���ļ���CRC32��֤: ��\r\n�򲹶�����ļ���С: %u\r\n\r\n����˵��:\r\n"
				, info.������ʶ , info.Ŀ���С );
		}
		m_strWipsDesc_In += info.m_szDesc;
	}
}
void CWIPS_I_Dlg::OnBnClickedButton1()
{
	UpdateData();
	ShowWipsInfo(m_strWipsFile);
	UpdateData(FALSE);
}
void CWIPS_I_Dlg::OnClose()
{
	CBaseDialog::OnClose();
	CBaseDialog::OnCancel();
}
