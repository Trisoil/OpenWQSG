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
// PTXT_OutDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WQSG ����(����).h"
#include "PTXT_OutDlg.h"


// CPTXT_OutDlg �Ի���

IMPLEMENT_DYNAMIC(CPTXT_OutDlg, CDialog)

CPTXT_OutDlg::CPTXT_OutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPTXT_OutDlg::IDD, pParent)
	, m_index0(_T(""))
	, m_index1(_T(""))
	, m_baseOffset(_T("0"))
	, m_indexLen(_T("2"))
	, m_ptrLen(_T("2"))
	, m_ptrMul(_T("1"))
	, m_Type(0)
	, m_ROM(_T(""))
	, m_TBL(_T(""))
	, m_TBL2(_T(""))
{

}

CPTXT_OutDlg::~CPTXT_OutDlg()
{
}

void CPTXT_OutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_index0);
	DDV_MaxChars(pDX, m_index0, 8);
	DDX_Text(pDX, IDC_EDIT2, m_index1);
	DDV_MaxChars(pDX, m_index1, 8);
	DDX_Text(pDX, IDC_EDIT3, m_baseOffset);
	DDV_MaxChars(pDX, m_baseOffset, 8);
	DDX_CBString(pDX, IDC_COMBO1, m_indexLen);
	DDX_CBString(pDX, IDC_COMBO2, m_ptrLen);
	DDX_CBString(pDX, IDC_COMBO4, m_ptrMul);
	DDX_CBIndex(pDX, IDC_COMBO5, m_Type);
	DDX_Text(pDX, IDC_EDIT_ROM, m_ROM);
	DDV_MaxChars(pDX, m_ROM, 255);
	DDX_Text(pDX, IDC_EDIT_TBL, m_TBL);
	DDV_MaxChars(pDX, m_TBL, 255);
	DDX_Text(pDX, IDC_EDIT_TBL2, m_TBL2);
	DDV_MaxChars(pDX, m_TBL2, 255);
}


BEGIN_MESSAGE_MAP(CPTXT_OutDlg, CDialog)
	ON_EN_CHANGE(IDC_EDIT1, &CPTXT_OutDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CPTXT_OutDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CPTXT_OutDlg::OnEnChangeEdit3)
	ON_CBN_SELENDOK(IDC_COMBO5, &CPTXT_OutDlg::OnCbnSelendokCombo5)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_ROM, &CPTXT_OutDlg::OnBnClickedButtonRom)
	ON_BN_CLICKED(IDC_BUTTON_TBL, &CPTXT_OutDlg::OnBnClickedButtonTbl)
	ON_BN_CLICKED(IDC_BUTTON_TBL2, &CPTXT_OutDlg::OnBnClickedButtonTbl2)
	ON_BN_CLICKED(IDC_BUTTON1, &CPTXT_OutDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CPTXT_OutDlg ��Ϣ�������

void CPTXT_OutDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	::�༭����֤ʮ�������ı�( m_index0 , (CEdit*)GetDlgItem( IDC_EDIT1 ) , this , TRUE);
}

void CPTXT_OutDlg::OnEnChangeEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	::�༭����֤ʮ�������ı�( m_index1 , (CEdit*)GetDlgItem( IDC_EDIT2 ) , this , TRUE);
}

void CPTXT_OutDlg::OnEnChangeEdit3()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	::�༭����֤ʮ�������ı�( m_baseOffset , (CEdit*)GetDlgItem( IDC_EDIT3 ) , this , TRUE);
}

void CPTXT_OutDlg::OnCbnSelendokCombo5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	GetDlgItem( IDC_EDIT1 )->EnableWindow( TRUE );
	GetDlgItem( IDC_EDIT2 )->EnableWindow( TRUE );
	GetDlgItem( IDC_EDIT3 )->EnableWindow( TRUE );
	GetDlgItem( IDC_COMBO1 )->EnableWindow( TRUE );
	GetDlgItem( IDC_COMBO2 )->EnableWindow( TRUE );
	GetDlgItem( IDC_COMBO4 )->EnableWindow( TRUE );
	GetDlgItem( IDC_COMBO5 )->EnableWindow( TRUE );

	switch( m_Type )
	{
	case 0:
	case 1:
		GetDlgItem( IDC_COMBO3 )->EnableWindow( FALSE );
		GetDlgItem( IDC_COMBO6 )->EnableWindow( FALSE );
		break;
	case 2:
		GetDlgItem( IDC_COMBO3 )->EnableWindow( TRUE );
		GetDlgItem( IDC_COMBO6 )->EnableWindow( TRUE );
		break;
	default:
		break;
	}
}

BOOL CPTXT_OutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	OnCbnSelendokCombo5();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CPTXT_OutDlg::OnCancel(){}
void CPTXT_OutDlg::OnOK(){}
void CPTXT_OutDlg::OnClose()
{
	CDialog::OnClose();
	CDialog::OnCancel();
}

void CPTXT_OutDlg::OnBnClickedButtonRom()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	static CString strPath;

	CWQSGFileDialog dlg( TRUE );
	dlg.m_ofn.lpstrTitle = L"ѡ��һ��ROM...";
	dlg.m_ofn.lpstrInitialDir = strPath;

	if( dlg.DoModal() != IDOK )
		return;

	strPath = dlg.GetFolderPath();

	m_ROM = dlg.GetPathName();
	UpdateData( FALSE );
}

void CPTXT_OutDlg::OnBnClickedButtonTbl()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	static CString strPath;

	CWQSGFileDialog dlg( TRUE );
	dlg.m_ofn.lpstrTitle = L"ѡ��һ�����...";
	dlg.m_ofn.lpstrFilter = L"����ļ�(*.TBL,*.TXT)\0*.TBL;*.TXT\0\0";
	dlg.m_ofn.lpstrInitialDir = strPath;

	if( dlg.DoModal() != IDOK )
		return;

	strPath = dlg.GetFolderPath();

	m_TBL = dlg.GetPathName();
	UpdateData( FALSE );
}

void CPTXT_OutDlg::OnBnClickedButtonTbl2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	static CString strPath;

	CWQSGFileDialog dlg( TRUE );
	dlg.m_ofn.lpstrTitle = L"ѡ��һ���������...";
	dlg.m_ofn.lpstrFilter = L"����ļ�(*.TBL,*.TXT)\0*.TBL;*.TXT\0\0";
	dlg.m_ofn.lpstrInitialDir = strPath;

	if( dlg.DoModal() != IDOK )
		return;

	strPath = dlg.GetFolderPath();

	m_TBL2 = dlg.GetPathName();
	UpdateData( FALSE );
}

void CPTXT_OutDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();

	if( !::WQSG_IsFile( m_ROM.GetString() ) )
	{
		MessageBox( m_ROM + L"\r\n\r\nRom�ļ�������");
		return;
	}

	if( !::WQSG_IsFile( m_TBL.GetString() ) )
	{
		MessageBox( m_TBL + L"\r\n\r\n����ļ�������");
		return;
	}

	if( m_TBL2.GetLength() > 0 )
	{
		if( !::WQSG_IsFile( m_TBL2.GetString() ) )
		{
			MessageBox( m_TBL2 + L"\r\n\r\n��������ļ�������");
			return;
		}
	}
}
