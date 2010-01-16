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

IMPLEMENT_DYNAMIC(CWIPS_O_Dlg, CDialog)
CWIPS_O_Dlg::CWIPS_O_Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWIPS_O_Dlg::IDD, pParent)
	, W_����˵��_OUT(_T(""))
	, W_ԭ�ļ�(_T(""))
	, W_���ļ�(_T(""))
	, W_��ʼ��ַ(_T("0"))
	, W_������ַ(_T("7FFFFFFFFFFFFFFF"))
{
	HRSRC hrexe = ::FindResource(NULL,MAKEINTRESOURCE(IDR_EXE1),_T("EXE"));
//	if(NULL == hrexe)return FALSE;

	DWORD dwSize = ::SizeofResource(NULL, hrexe);
	if(dwSize != 0){
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
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT7, W_����˵��_OUT);
	DDV_MaxChars(pDX, W_����˵��_OUT, 65535);
	DDX_Text(pDX, IDC_EDIT2, W_ԭ�ļ�);
	DDV_MaxChars(pDX, W_ԭ�ļ�, MAX_PATH);
	DDX_Text(pDX, IDC_EDIT3, W_���ļ�);
	DDV_MaxChars(pDX, W_���ļ�, MAX_PATH);
	DDX_Text(pDX, IDC_EDIT4, W_��ʼ��ַ);
	DDV_MaxChars(pDX, W_��ʼ��ַ, 16);
	DDX_Text(pDX, IDC_EDIT5, W_������ַ);
	DDV_MaxChars(pDX, W_������ַ, 16);
}
BEGIN_MESSAGE_MAP(CWIPS_O_Dlg, CDialog)
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

	static CString strPath;

	CWQSGFileDialog fopendlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,_T("ԭ�ļ�(*.*)|*.*||"));
	fopendlg.m_ofn.lpstrTitle = _T("ѡ��һ��ԭ�ļ�...");
	fopendlg.m_ofn.lpstrInitialDir = strPath;

	if(IDOK == fopendlg.DoModal())
	{
		strPath = fopendlg.GetFolderPath();
		W_ԭ�ļ� = fopendlg.GetPathName();
		UpdateData(FALSE);
	}
}

void CWIPS_O_Dlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	static CString strPath;

	CWQSGFileDialog fopendlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,_T("���ļ�(*.*)|*.*||"));
	fopendlg.m_ofn.lpstrTitle = _T("ѡ��һ�����ļ�...");
	fopendlg.m_ofn.lpstrInitialDir = strPath;

	if(IDOK == fopendlg.DoModal())
	{
		strPath = fopendlg.GetFolderPath();
		W_���ļ� = fopendlg.GetPathName();
		UpdateData(FALSE);
	}
}

void CWIPS_O_Dlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if(W_ԭ�ļ�.GetLength() == 0){
		MessageBox(_T("ԭ�ļ�����Ϊ��"));
		return;
	}
	if(W_���ļ�.GetLength() == 0){
		MessageBox(_T("���ļ�����Ϊ��"));
		return;
	}
	s64 ��ʼ��ַ = 0,
		������ַ = 0;

	::swscanf( W_��ʼ��ַ.GetString() ,L"%llx" , &��ʼ��ַ );
	/////////////////////
	::swscanf( W_������ַ.GetString() ,L"%llx" , &������ַ );
	//////////////////////////
	BOOL ����EXE = (((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck() == 1);

	static CString strPath;
	CWQSGFileDialog fopendlg( FALSE );
	fopendlg.m_ofn.lpstrInitialDir = strPath;

	fopendlg.m_ofn.lpstrFilter = (����EXE)?_T("��ִ���ļ�(*.EXE)\0*.EXE\0\0"):_T("WIPS�����ļ�(*.WIPS)\0*.WIPS\0\0");
	fopendlg.m_ofn.lpstrDefExt = (����EXE)?_T("EXE"):_T("WIPS");
	fopendlg.m_ofn.lpstrTitle = _T("�������浽...");

	if(IDOK == fopendlg.DoModal())
	{
		strPath = fopendlg.GetFolderPath();
		CString �ļ� = fopendlg.GetPathName();
		::CWQSG_IPS_OUT WQSG(m_hWnd,_T("WQSG IPS��������"));
		WQSG.��������30( W_ԭ�ļ�.GetString() , W_���ļ�.GetString() , �ļ�.GetString() ,
			��ʼ��ַ , ������ַ , 0 , (((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck() == 1)?1:0 ,
			W_����˵��_OUT.GetString() , ::WQSG_strlen(W_����˵��_OUT.GetString()) , (����EXE)?&m_�Խ�ͷ30:NULL );
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
	�༭����֤ʮ�������ı�(W_��ʼ��ַ,(CEdit*)GetDlgItem(IDC_EDIT4),(CWnd*)this);
	if(W_��ʼ��ַ.GetLength() == 0)
	{
		W_��ʼ��ַ = _T("0");
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
	�༭����֤ʮ�������ı�( W_������ַ , (CEdit*)GetDlgItem(IDC_EDIT5),(CWnd*)this);
	if(W_������ַ.GetLength() == 0)
	{
		W_������ַ = _T("0");
		UpdateData(FALSE);
	}
}

void CWIPS_O_Dlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialog::OnClose();
//	if(IDOK == MessageBox(_T("Ҫ����WIPS��������?"),NULL,MB_OKCANCEL)){
		CDialog::OnCancel();
//	}
}
//------------------------------------------------
IMPLEMENT_DYNAMIC(CWIPS_I_Dlg, CDialog)
CWIPS_I_Dlg::CWIPS_I_Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWIPS_I_Dlg::IDD, pParent)
	, W_�����ļ�(_T(""))
	, W_����˵��_IN(_T(""))
{
}

CWIPS_I_Dlg::~CWIPS_I_Dlg()
{
}
void CWIPS_I_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT6, W_�����ļ�);
	DDV_MaxChars(pDX, W_�����ļ�, MAX_PATH);
	DDX_Text(pDX, IDC_EDIT10, W_����˵��_IN);
}


BEGIN_MESSAGE_MAP(CWIPS_I_Dlg, CDialog)
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
	static CString strPath;

	CWQSGFileDialog fopendlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,_T("WIPS�����ļ�(*.WIPS)|*.WIPS||"));
	fopendlg.m_ofn.lpstrTitle = _T("ѡ��һ��WIPS�����ļ�...");
	fopendlg.m_ofn.lpstrInitialDir = strPath;

	if(IDOK == fopendlg.DoModal())
	{
		strPath = fopendlg.GetFolderPath();
		W_�����ļ� = fopendlg.GetPathName();
		��ʾ������Ϣ(W_�����ļ�);
		UpdateData(FALSE);
	}
}

void CWIPS_I_Dlg::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if(W_�����ļ�.GetLength() == 0)
	{
		MessageBox(_T("�����ļ�����Ϊ��"));
		return;
	}

	static CString strPath;

	CWQSGFileDialog fopendlg(FALSE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,_T("Ŀ���ļ��ļ�(*.*)|*.*||"));
	fopendlg.m_ofn.lpstrTitle = _T("��ѡ����ļ��򲹶�...");
	fopendlg.m_ofn.lpstrInitialDir = strPath;

	if(IDOK == fopendlg.DoModal())
	{
		strPath = fopendlg.GetFolderPath();
		CString �ļ� = fopendlg.GetPathName();
		::CWQSG_IPS_IN WQSG(m_hWnd,_T("WQSG IPS��������"));
		WQSG.�򲹶�(W_�����ļ�.GetString(),�ļ�.GetString());
	}
}
void CWIPS_I_Dlg::��ʾ������Ϣ(CString �ļ�)
{
	::CWQSG_IPS_IN WQSG(m_hWnd,_T("WQSG IPS��������"));
	::CWD_WIPS��Ϣ ������Ϣ;
	W_����˵��_IN = _T("�Ƿ����߲�֧�ֵĲ����ļ�");
	if(WQSG.ȡ�ļ�������Ϣ( �ļ�.GetString(),&������Ϣ) )
	{
		if(::WQSG_strlen(������Ϣ.˵���ı�) == 0)
		{
			::WQSG_strcpy(L"��",������Ϣ.˵���ı�);
		}
		if(������Ϣ.��֤CRC32)
		{
			W_����˵��_IN.Format(L"�����汾: %s\r\nĿ���ļ���CRC32��֤: %X\r\n�򲹶�����ļ���С: %u\r\n\r\n����˵��:\r\n",
				������Ϣ.������ʶ,������Ϣ.��֤CRC32,������Ϣ.Ŀ���С);
		}
		else
		{
			W_����˵��_IN.Format(L"�����汾: %s\r\nĿ���ļ���CRC32��֤: ��\r\n�򲹶�����ļ���С: %u\r\n\r\n����˵��:\r\n"
				,������Ϣ.������ʶ,������Ϣ.Ŀ���С);
		}
		W_����˵��_IN += ������Ϣ.˵���ı�;
	}
}
void CWIPS_I_Dlg::OnBnClickedButton1()
{
	UpdateData();
	��ʾ������Ϣ(W_�����ļ�);
	UpdateData(FALSE);
}
void CWIPS_I_Dlg::OnClose()
{
	CDialog::OnClose();
	CDialog::OnCancel();
}
