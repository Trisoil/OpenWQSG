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
// page_PTXT_OUT.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WQSG ����(����).h"
#include "page_PTXT.h"


// Cpage_PTXT_OUT �Ի���

IMPLEMENT_DYNAMIC(Cpage_PTXT_OUT, CDialog)
void Cpage_PTXT_OUT::OnOK()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
void Cpage_PTXT_OUT::OnCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
Cpage_PTXT_OUT::Cpage_PTXT_OUT(CWnd* pParent /*=NULL*/)
	: CDialog(Cpage_PTXT_OUT::IDD, pParent)
	, W_pKS(_T(""))
	, W_pJS(_T(""))
	, W_p�ı�����(_T(""))
	, W_pָ����(_T("2"))
	, W_pʵ��ָ�볤��(_T("2"))
	, W_pָ�뱶��(_T("1"))
	, W_pָ���ʽ(0)
	, W_p���ȿ鱶��(_T("1"))
	, W_�ı�����(_T("2"))
{

}

Cpage_PTXT_OUT::~Cpage_PTXT_OUT()
{
}

void Cpage_PTXT_OUT::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, W_pKS);
	DDV_MaxChars(pDX, W_pKS, 8);
	DDX_Text(pDX, IDC_EDIT2, W_pJS);
	DDV_MaxChars(pDX, W_pJS, 8);
	DDX_Text(pDX, IDC_EDIT3, W_p�ı�����);
	DDV_MaxChars(pDX, W_p�ı�����, 8);
	DDX_CBString(pDX, IDC_COMBO1, W_pָ����);
	DDX_CBString(pDX, IDC_COMBO2, W_pʵ��ָ�볤��);
	DDX_CBString(pDX, IDC_COMBO4, W_pָ�뱶��);
	DDX_CBIndex(pDX, IDC_COMBO5, W_pָ���ʽ);
	DDX_CBString(pDX, IDC_COMBO6, W_p���ȿ鱶��);
	DDX_CBString(pDX, IDC_COMBO3, W_�ı�����);
}

BEGIN_MESSAGE_MAP(Cpage_PTXT_OUT, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO5, &Cpage_PTXT_OUT::OnCbnSelchangeCombo5)
	ON_EN_CHANGE(IDC_EDIT1, &Cpage_PTXT_OUT::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &Cpage_PTXT_OUT::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &Cpage_PTXT_OUT::OnEnChangeEdit3)
END_MESSAGE_MAP()

// Cpage_TXT_OUT ��Ϣ�������
void Cpage_PTXT_OUT::OnCbnSelchangeCombo5(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if( 2 == ((CComboBox*)GetDlgItem(IDC_COMBO5))->GetCurSel()){
		GetDlgItem(IDC_COMBO6)->EnableWindow();
		GetDlgItem(IDC_COMBO3)->EnableWindow();
	}
	else{
		GetDlgItem(IDC_COMBO6)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO3)->EnableWindow(FALSE);
	}
}

void Cpage_PTXT_OUT::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	�༭����֤ʮ�������ı�(W_pKS,(CEdit*)GetDlgItem(IDC_EDIT1),(CWnd*)this);
}

void Cpage_PTXT_OUT::OnEnChangeEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	�༭����֤ʮ�������ı�(W_pJS,(CEdit*)GetDlgItem(IDC_EDIT2),(CWnd*)this);
}

void Cpage_PTXT_OUT::OnEnChangeEdit3()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	�༭����֤ʮ�������ı�(W_p�ı�����,(CEdit*)GetDlgItem(IDC_EDIT3),(CWnd*)this);
}



// page_PTXT_IN.cpp : ʵ���ļ�
//


// Cpage_PTXT_IN �Ի���

IMPLEMENT_DYNAMIC(Cpage_PTXT_IN, CDialog)
void Cpage_PTXT_IN::OnOK()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
void Cpage_PTXT_IN::OnCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
Cpage_PTXT_IN::Cpage_PTXT_IN(CWnd* pParent /*=NULL*/)
	: CDialog(Cpage_PTXT_IN::IDD, pParent)
	, m_p�ı������޵�ַ(_T(""))
	, m_p�ı�����ʼ��ַ(_T(""))
{

}

Cpage_PTXT_IN::~Cpage_PTXT_IN()
{
}

void Cpage_PTXT_IN::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_p�ı������޵�ַ);
	DDV_MaxChars(pDX, m_p�ı������޵�ַ, 8);
	DDX_Text(pDX, IDC_EDIT11, m_p�ı�����ʼ��ַ);
	DDV_MaxChars(pDX, m_p�ı�����ʼ��ַ, 8);
}


BEGIN_MESSAGE_MAP(Cpage_PTXT_IN, CDialog)
	ON_EN_CHANGE(IDC_EDIT1, &Cpage_PTXT_IN::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT11, &Cpage_PTXT_IN::OnEnChangeEdit11)
END_MESSAGE_MAP()

// Cpage_PTXT_IN ��Ϣ�������

void Cpage_PTXT_IN::OnEnChangeEdit1(){
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	�༭����֤ʮ�������ı�(m_p�ı������޵�ַ,(CEdit*)GetDlgItem(IDC_EDIT1),(CWnd*)this);
}

void Cpage_PTXT_IN::OnEnChangeEdit11()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	�༭����֤ʮ�������ı�(m_p�ı�����ʼ��ַ,(CEdit*)GetDlgItem(IDC_EDIT11),(CWnd*)this);
}
