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
// page_TXT_OUT.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WQSG ����(����).h"
#include "page_TXT.h"


// Cpage_TXT_OUT �Ի���

IMPLEMENT_DYNAMIC(Cpage_TXT_OUT, CDialog)
void Cpage_TXT_OUT::OnOK()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
void Cpage_TXT_OUT::OnCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
Cpage_TXT_OUT::Cpage_TXT_OUT(CWnd* pParent /*=NULL*/)
	: CDialog(Cpage_TXT_OUT::IDD, pParent)
	, W_KS(_T(""))
	, W_JS(_T(""))
	, W_MIN(_T("0"))
	, W_MAX(_T("99999"))
	, W_KS2(_T("0"))
	, W_ROM��ַ(_T(""))
{
}

Cpage_TXT_OUT::~Cpage_TXT_OUT()
{
}

void Cpage_TXT_OUT::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_KS, W_KS);
	DDV_MaxChars(pDX, W_KS, 8);
	DDX_Text(pDX, IDC_EDIT_JS, W_JS);
	DDV_MaxChars(pDX, W_JS, 8);
	DDX_Text(pDX, IDC_EDIT_MIN, W_MIN);
	DDV_MaxChars(pDX, W_MIN, 5);
	DDX_Text(pDX, IDC_EDIT_MAX, W_MAX);
	DDV_MaxChars(pDX, W_MAX, 5);
	DDX_Text(pDX, IDC_EDIT_KS2, W_KS2);
	DDV_MaxChars(pDX, W_KS2, 8);
}


BEGIN_MESSAGE_MAP(Cpage_TXT_OUT, CDialog)
	ON_EN_CHANGE(IDC_EDIT_KS, &Cpage_TXT_OUT::OnEnChangeEditKs)
	ON_EN_CHANGE(IDC_EDIT_JS, &Cpage_TXT_OUT::OnEnChangeEditJs)
	ON_EN_CHANGE(IDC_EDIT_MIN, &Cpage_TXT_OUT::OnEnChangeEditMin)
	ON_EN_CHANGE(IDC_EDIT_MAX, &Cpage_TXT_OUT::OnEnChangeEditMax)
	ON_EN_CHANGE(IDC_EDIT_KS2, &Cpage_TXT_OUT::OnEnChangeEditKs2)
	ON_BN_CLICKED(IDC_BUTTON1, &Cpage_TXT_OUT::OnBnClickedButton1)
END_MESSAGE_MAP()

// Cpage_TXT_OUT ��Ϣ�������
void Cpage_TXT_OUT::OnEnChangeEditKs()
	{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	�༭����֤ʮ�������ı�(W_KS,(CEdit*)GetDlgItem(IDC_EDIT_KS),(CWnd*)this);
	}

void Cpage_TXT_OUT::OnEnChangeEditJs()
	{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	�༭����֤ʮ�������ı�(W_JS,(CEdit*)GetDlgItem(IDC_EDIT_JS),(CWnd*)this);
	}

void Cpage_TXT_OUT::OnEnChangeEditMin()
	{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	�༭����֤ʮ�����ı�(W_MIN,(CEdit*)GetDlgItem(IDC_EDIT_MIN),(CWnd*)this);
	if(0 == W_MIN.GetLength())
		{
		W_MIN = _T("0");
		UpdateData(FALSE);
		((CEdit*)GetDlgItem(IDC_EDIT_MIN))->SetSel(1,1,FALSE);
		}
	}

void Cpage_TXT_OUT::OnEnChangeEditMax()
	{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	�༭����֤ʮ�����ı�(W_MAX,(CEdit*)GetDlgItem(IDC_EDIT_MAX),(CWnd*)this);
	if(0 == W_MAX.GetLength())
		{
		W_MAX = _T("99999");
		UpdateData(FALSE);
		((CEdit*)GetDlgItem(IDC_EDIT_MAX))->SetSel(5,5,FALSE);
		}
	}

void Cpage_TXT_OUT::OnEnChangeEditKs2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	�༭����֤ʮ�������ı�(W_KS2,(CEdit*)GetDlgItem(IDC_EDIT_KS2),(CWnd*)this);
	if(0 == W_KS2.GetLength())
	{
		W_KS2 = _T("0");
		UpdateData(FALSE);
		((CEdit*)GetDlgItem(IDC_EDIT_KS2))->SetSel(1,1,FALSE);
	}
}
void Cpage_TXT_OUT::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	U64 �κ� = 0;
	::swscanf_s(W_KS2.GetBuffer(),_T("%x"),&�κ�);
	�κ� <<= 32;
	if(W_ROM��ַ.GetLength() == 0){
		W_JS = _T("");
		UpdateData(FALSE);
		return;
	}
	::CWQSG_File ROM_File;
	if(! ROM_File.OpenFile(W_ROM��ַ.GetBuffer(),1,3)){
		MessageBox(_T("��ȡROM����ʧ��"));
		return;
	}
	U64 ����;
	ROM_File.GetFileSize(&����);
	if(���� < �κ�){
		W_JS = _T("");
	}
	else{
		if(���� >= (�κ� + 0x100000000)){
			���� = 0xFFFFFFFF;
		}
		else{
			���� -= �κ�;
		}
		W_JS.Format(_T("%X"),(���� - 1));
	}
	UpdateData(FALSE);
}

// page_TXT_IN.cpp : ʵ���ļ�
//


// Cpage_TXT_IN �Ի���

IMPLEMENT_DYNAMIC(Cpage_TXT_IN, CDialog)
void Cpage_TXT_IN::OnOK()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
void Cpage_TXT_IN::OnCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
Cpage_TXT_IN::Cpage_TXT_IN(CWnd* pParent /*=NULL*/)
	: CDialog(Cpage_TXT_IN::IDD, pParent)
	, �������(0)
	, ���ֽ����(_T(""))
	, ˫�ֽ����(_T(""))
	, W_���Ȳ�����ʾ(FALSE)
{

}

Cpage_TXT_IN::~Cpage_TXT_IN()
{
}

void Cpage_TXT_IN::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBO1, �������);
	DDX_Text(pDX, IDC_EDIT1, ���ֽ����);
	DDV_MaxChars(pDX, ���ֽ����, 2);
	DDX_Text(pDX, IDC_EDIT2, ˫�ֽ����);
	DDV_MaxChars(pDX, ˫�ֽ����, 4);
	DDX_Check(pDX, IDC_CHECK1, W_���Ȳ�����ʾ);
}


BEGIN_MESSAGE_MAP(Cpage_TXT_IN, CDialog)
//	ON_BN_CLICKED(IDC_BUTTON_ST, &Cpage_TXT_IN::OnBnClickedButtonSt)
	ON_CBN_SELCHANGE(IDC_COMBO1, &Cpage_TXT_IN::OnCbnSelchangeCombo1)
	ON_EN_CHANGE(IDC_EDIT1, &Cpage_TXT_IN::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &Cpage_TXT_IN::OnEnChangeEdit2)
	ON_EN_KILLFOCUS(IDC_EDIT1, &Cpage_TXT_IN::OnEnKillfocusEdit1)
	ON_EN_KILLFOCUS(IDC_EDIT2, &Cpage_TXT_IN::OnEnKillfocusEdit2)
END_MESSAGE_MAP()


// Cpage_TXT_IN ��Ϣ�������
void Cpage_TXT_IN::OnCbnSelchangeCombo1()
	{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	switch(�������)
		{
		case 1:
			GetDlgItem(IDC_EDIT1)->EnableWindow();
			GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
			break;
		case 2:
			GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT2)->EnableWindow();
			break;
		case 3:
			GetDlgItem(IDC_EDIT1)->EnableWindow();
			GetDlgItem(IDC_EDIT2)->EnableWindow();
			break;
		default:
			GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
		}
	}
void Cpage_TXT_IN::OnEnChangeEdit1(){
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	�༭����֤ʮ�������ı�(���ֽ����,(CEdit*)GetDlgItem(IDC_EDIT1),(CWnd*)this,0);
}

void Cpage_TXT_IN::OnEnChangeEdit2(){
		// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
		// ���͸�֪ͨ��������д CDialog::OnInitDialog()
		// ���������� CRichEditCtrl().SetEventMask()��
		// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

		// TODO:  �ڴ���ӿؼ�֪ͨ����������
		UpdateData();
		�༭����֤ʮ�������ı�(˫�ֽ����,(CEdit*)GetDlgItem(IDC_EDIT2),(CWnd*)this,0);
}
void Cpage_TXT_IN::OnEnKillfocusEdit1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(���ֽ����.GetLength()&1){
		���ֽ����.Insert(0,_T('0'));
		UpdateData();
	}
}

void Cpage_TXT_IN::OnEnKillfocusEdit2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(˫�ֽ����.GetLength()&1){
		˫�ֽ����.Insert(0,_T('0'));
		UpdateData();
	}
}
