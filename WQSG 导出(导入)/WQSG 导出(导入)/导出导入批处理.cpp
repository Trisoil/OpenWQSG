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
// ��������������.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WQSG ����(����).h"
#include "��������������.h"

CString �ϸ����һ���ı�(HANDLE F_ID){
	DWORD III;
	CString tmp;
	WCHAR wtmp;
	while(::ReadFile(F_ID,&wtmp,2,&III,NULL),2 == III){
		if(0x0D == wtmp){
			if(::ReadFile(F_ID,&wtmp,2,&III,NULL),2 == III){
				if(0x0A != wtmp){
					//��дλ�� -2
					::SetFilePointer(F_ID,-2L,NULL,FILE_CURRENT);
				}
			}
			break;
		}
		else if(0x00 == wtmp){
			break;
		}
		tmp += wtmp;
	}
	return tmp;
}
void ����������::������Ŀ��(CString �ļ���ַ){
	CString tmp = W_��ǰĿ¼;
	tmp += _T("\\DATA");
	CreateDirectory(tmp,NULL);
	tmp += _T("\\WQSG ����(����)");
	CreateDirectory(tmp,NULL);
	::CWQSG_File File;
	if( !File.OpenFile( �ļ���ַ,4,3)){
		MessageBox(_T("������Ŀ��ʧ��"));
		return;
	}
	U32 II = W_�б���һ��λ�� - 1;
	File.Write("WIO0",4);
	File.Write(&II,4);
	for(INT ���� = 0;���� < (INT)II;����++){
		tmp = W_�б�->GetItemText(����,1);
		tmp += L"\15\12";
		tmp += W_�б�->GetItemText(����,2);
		tmp += L"\15\12";
		tmp += W_�б�->GetItemText(����,3);
		tmp += L"\15\12";
		tmp += W_�б�->GetItemText(����,4);
		tmp += L"\15\12";
		tmp += W_�б�->GetItemText(����,5);
		tmp += L"\15\12";
		tmp += W_�б�->GetItemText(����,6);
		tmp += L"\15\12";
		tmp += W_�б�->GetItemText(����,7);
		tmp += L"\15\12";
		tmp += W_�б�->GetItemText(����,8);
		tmp += L"\15\12";
		File.Write(tmp.GetBuffer(),(tmp.GetLength()<< 1));
	}
}
void ����������::������Ŀ��(CString �ļ���ַ){
	CString tmp = W_��ǰĿ¼;
	tmp += _T("\\DATA");
	CreateDirectory(tmp,NULL);
	tmp += _T("\\WQSG ����(����)");
	CreateDirectory(tmp,NULL);

	::CWQSG_File File;
	if(! File.OpenFile(�ļ���ַ,1,3)){
		return;
	}

	U32 II;
	File.Read(&II,4);
	if( *((U32*)"WIO0") != II){
		W_�б�->DeleteAllItems();
		W_�б���һ��λ�� = 1;
		MessageBox(_T("���ݿ��Ѿ���"));
		return;
	}
	File.Read(&II,4);

	WCHAR ���[6];
	for(INT ���� = 0;���� < (INT)II;����++){
		::swprintf_s(���,6,L"%05d",W_�б���һ��λ��++);
		W_�б�->InsertItem(����,���);

		tmp = �ϸ����һ���ı�(File.GetFileHANDLE());
		if(tmp.GetLength() == 0){
			W_�б�->DeleteAllItems();
			W_�б���һ��λ�� = 1;
			MessageBox(_T("���ݿ��Ѿ���"));
			return;
		}
		W_�б�->SetItemText(����,1,tmp);
		tmp = �ϸ����һ���ı�(File.GetFileHANDLE());
		if(tmp.GetLength() == 0){
			W_�б�->DeleteAllItems();
			W_�б���һ��λ�� = 1;
			MessageBox(_T("���ݿ��Ѿ���"));
			return;
		}
		W_�б�->SetItemText(����,2,tmp);
		tmp = �ϸ����һ���ı�(File.GetFileHANDLE());
		if(tmp.GetLength() == 0){
			W_�б�->DeleteAllItems();
			W_�б���һ��λ�� = 1;
			MessageBox(_T("���ݿ��Ѿ���"));
			return;
		}
		W_�б�->SetItemText(����,3,tmp);
		tmp = �ϸ����һ���ı�(File.GetFileHANDLE());
		if(tmp.GetLength() == 0){
			W_�б�->DeleteAllItems();
			W_�б���һ��λ�� = 1;
			MessageBox(_T("���ݿ��Ѿ���"));
			return;
		}
		W_�б�->SetItemText(����,4,tmp);
		tmp = �ϸ����һ���ı�(File.GetFileHANDLE());
		if(tmp.GetLength() == 0){
			W_�б�->DeleteAllItems();
			W_�б���һ��λ�� = 1;
			MessageBox(_T("���ݿ��Ѿ���"));
			return;
		}
		W_�б�->SetItemText(����,5,tmp);
		tmp = �ϸ����һ���ı�(File.GetFileHANDLE());
		if(tmp.GetLength() == 0){
			W_�б�->DeleteAllItems();
			W_�б���һ��λ�� = 1;
			MessageBox(_T("���ݿ��Ѿ���"));
			return;
		}
		W_�б�->SetItemText(����,6,tmp);
		tmp = �ϸ����һ���ı�(File.GetFileHANDLE());
		if(tmp.GetLength() == 0){
			W_�б�->DeleteAllItems();
			W_�б���һ��λ�� = 1;
			MessageBox(_T("���ݿ��Ѿ���"));
			return;
		}
		W_�б�->SetItemText(����,7,tmp);
		tmp = �ϸ����һ���ı�(File.GetFileHANDLE());
		if(tmp.GetLength() == 0){
			W_�б�->DeleteAllItems();
			W_�б���һ��λ�� = 1;
			MessageBox(_T("���ݿ��Ѿ���"));
			return;
		}
		W_�б�->SetItemText(����,8,tmp);
	};
}
void ����������::OnOK()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
void ����������::OnCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if( IDOK == MessageBox(_T("�Ƿ�Ҫ�ر�?"),NULL,MB_OKCANCEL) )
	{
		//ReleaseMutex(WQSG_Mutex);
		CDialog::OnCancel();
	}
}
// �������������� �Ի���

IMPLEMENT_DYNAMIC(����������, CDialog)

����������::����������(CWnd* pParent /*=NULL*/)
	: CDialog(����������::IDD, pParent)
//	, W_��ʼ��ַ(_T(""))
//	, W_������ַ(_T(""))
	, W_��֤(TRUE)
	, W_MIN(_T("0"))
	, W_MAX(_T("99999"))
//	, W_Ĭ�����(_T(""))
//	, W_Ĭ�Ͽ������(_T(""))
//	, W_ROM(_T(""))
{
	W_�б���һ��λ�� = 1;
	
	TCHAR exeFullPath[MAX_PATH]; 
    GetModuleFileName(NULL,exeFullPath,MAX_PATH);
	W_��ǰĿ¼ = exeFullPath;
	W_��ǰĿ¼ = W_��ǰĿ¼.Left(W_��ǰĿ¼.ReverseFind(_T('\\')));
	W_�����ļ���ַ = W_��ǰĿ¼;

	W_�����ļ���ַ += _T("\\DATA\\WQSG ����(����)\\����0.CFG");
}

����������::~����������()
{
}
BOOL ����������::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	//SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	//SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	W_�б� = (CListCtrl*)GetDlgItem(IDC_LIST_W);
	W_�б�->InsertColumn(0,_T("��Ŀ���"),LVCFMT_CENTER,65);
	W_�б�->InsertColumn(1,_T("ROM��ַ"),LVCFMT_CENTER,335);
	W_�б�->InsertColumn(2,_T("����ַ"),LVCFMT_CENTER,200);
	W_�б�->InsertColumn(3,_T("��������ַ"),LVCFMT_CENTER,200);
	W_�б�->InsertColumn(4,_T("��ʼ��ַ(HEX)"),LVCFMT_CENTER,100);
	W_�б�->InsertColumn(5,_T("������ַ(HEX)"),LVCFMT_CENTER,100);
	W_�б�->InsertColumn(6,_T("��֤����ظ�"),LVCFMT_CENTER,90);
	W_�б�->InsertColumn(7,_T("����<="),LVCFMT_CENTER,70);
	W_�б�->InsertColumn(8,_T("����>="),LVCFMT_CENTER,70);


	W_�б�->SetExtendedStyle(W_�б�->GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);

	������Ŀ��(W_�����ļ���ַ);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void ����������::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_KS, W_��ʼ��ַ);
	DDV_MaxChars(pDX, W_��ʼ��ַ, 8);
	DDX_Text(pDX, IDC_EDIT_JS, W_������ַ);
	DDV_MaxChars(pDX, W_������ַ, 8);
	DDX_Check(pDX, IDC_CHECK1, W_��֤);
	DDX_Text(pDX, IDC_EDIT_MIN, W_MIN);
	DDV_MaxChars(pDX, W_MIN, 5);
	DDX_Text(pDX, IDC_EDIT_MAX, W_MAX);
	DDV_MaxChars(pDX, W_MAX, 5);
	DDX_Text(pDX, IDC_EDIT_TBL, W_Ĭ�����);
	DDV_MaxChars(pDX, W_Ĭ�����, MAX_PATH - 1);
	DDX_Text(pDX, IDC_EDIT_TBL2, W_Ĭ�Ͽ������);
	DDV_MaxChars(pDX, W_Ĭ�Ͽ������, MAX_PATH - 1);
}


BEGIN_MESSAGE_MAP(����������, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_TBL, &����������::OnBnClickedButtonTbl)
	ON_BN_CLICKED(IDC_BUTTON_TBL2, &����������::OnBnClickedButtonTbl2)
	ON_EN_CHANGE(IDC_EDIT_KS, &����������::OnEnChangeEditKs)
	ON_EN_CHANGE(IDC_EDIT_JS, &����������::OnEnChangeEditJs)
	ON_EN_CHANGE(IDC_EDIT_MIN, &����������::OnEnChangeEditMin)
	ON_EN_CHANGE(IDC_EDIT_MAX, &����������::OnEnChangeEditMax)
	ON_BN_CLICKED(IDC_BUTTON_Add, &����������::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_Del, &����������::OnBnClickedButtonDel)
	ON_NOTIFY(LVN_ITEMACTIVATE, IDC_LIST_W, &����������::OnLvnItemActivateListW)
	ON_BN_CLICKED(IDC_BUTTON_Edit, &����������::OnBnClickedButtonEdit)
	ON_EN_CHANGE(IDC_EDIT_TBL, &����������::OnEnChangeEditTbl)
	ON_EN_CHANGE(IDC_EDIT_TBL2, &����������::OnEnChangeEditTbl2)
	ON_BN_CLICKED(IDC_BUTTON_START, &����������::OnBnClickedButtonStart)
END_MESSAGE_MAP()


// �������������� ��Ϣ�������

void ����������::OnBnClickedButtonTbl()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	static CWQSGFileDialog_Open fopendlg(_T("����ļ�(*.TBL,*.TXT)|*.TBL;*.TXT||"));
	fopendlg.m_ofn.lpstrTitle = _T("ѡ��һ�����...");
	if(IDOK == fopendlg.DoModal())
	{
		W_Ĭ����� = fopendlg.GetPathName();
	}
	UpdateData(FALSE);
}

void ����������::OnBnClickedButtonTbl2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	static CWQSGFileDialog_Open fopendlg(_T("����ļ�(*.TBL,*.TXT)|*.TBL;*.TXT||"));
	fopendlg.m_ofn.lpstrTitle = _T("ѡ��һ���������...");
	if(IDOK == fopendlg.DoModal())
	{
		W_Ĭ�Ͽ������ = fopendlg.GetPathName();
	}
	UpdateData(FALSE);
}

void ����������::OnEnChangeEditKs()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	�༭����֤ʮ�������ı�(W_��ʼ��ַ,(CEdit*)GetDlgItem(IDC_EDIT_KS),(CWnd*)this);
}

void ����������::OnEnChangeEditJs()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	�༭����֤ʮ�������ı�(W_������ַ,(CEdit*)GetDlgItem(IDC_EDIT_JS),(CWnd*)this);
}

void ����������::OnEnChangeEditMin()
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

void ����������::OnEnChangeEditMax()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	�༭����֤ʮ�����ı�(W_MAX,(CEdit*)GetDlgItem(IDC_EDIT_MAX),(CWnd*)this);
	if(0 == W_MIN.GetLength())
	{
		W_MIN = _T("99999");
		UpdateData(FALSE);
		((CEdit*)GetDlgItem(IDC_EDIT_MAX))->SetSel(5,5,FALSE);
	}
}
void ����������::OnBnClickedButtonAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if(0 == W_Ĭ�����.GetLength())
	{
		MessageBox(_T("����ַ����Ϊ��"));
		return;
	}
	if(0 == W_Ĭ�Ͽ������.GetLength())
	{
		MessageBox(_T("��������ַ����Ϊ��"));
		return;
	}
	if(0 == W_��ʼ��ַ.GetLength()){
		MessageBox(_T("��ʼ��ַ����Ϊ��"));
		return;
	}
	if(0 == W_������ַ.GetLength()){
		MessageBox(_T("������ַ����Ϊ��"));
		return;
	}

	static CWQSGFileDialog_Open fopendlg(_T("ROM�ļ�(*.*)|*.*||"));
	fopendlg.m_ofn.lpstrTitle = _T("ѡ��һ��ROM...");
	if(IDOK == fopendlg.DoModal())
	{
		W_ROM = fopendlg.GetPathName();
		INT λ�� = W_�б���һ��λ��;
		if(W_�б���һ��λ��)
		{
			λ��--;
		}
		TCHAR ���[6];
		::_stprintf_s(���,6,_T("%05d"),W_�б���һ��λ��);
		W_�б�->InsertItem(λ��,���);
		W_�б�->SetItemText(λ��,1,W_ROM);
		W_�б�->SetItemText(λ��,2,W_Ĭ�����);
		W_�б�->SetItemText(λ��,3,W_Ĭ�Ͽ������);
		W_�б�->SetItemText(λ��,4,W_��ʼ��ַ);
		W_�б�->SetItemText(λ��,5,W_������ַ);
		if(W_��֤)
		{
			W_�б�->SetItemText(λ��,6,_T("��"));
		}
		else
		{
			W_�б�->SetItemText(λ��,6,_T("��"));
		}
		W_�б�->SetItemText(λ��,7,W_MIN);
		W_�б�->SetItemText(λ��,8,W_MAX);
		
		W_�б���һ��λ��++;
		UpdateData(FALSE);
		������Ŀ��(W_�����ļ���ַ);
	}
}
void ����������::OnBnClickedButtonDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	POSITION P = W_�б�->GetFirstSelectedItemPosition();
	if(NULL != P)
	{
		INT ���� = (INT)P - 1;
		W_�б�->DeleteItem(����);
		W_�б���һ��λ��--;
		WCHAR ����[6];
		INT tmp;
		for(;���� < (W_�б���һ��λ�� - 1);����++)
		{
			tmp = ::_ttoi(W_�б�->GetItemText(����,0)) - 1;
			::swprintf_s(����,6,L"%05d",tmp);
			W_�б�->SetItemText(����,0,����);
		}
	}
	������Ŀ��(W_�����ļ���ַ);
}

void ����������::OnLvnItemActivateListW(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	POSITION P = W_�б�->GetFirstSelectedItemPosition();
	if(	NULL != P )
	{
		UpdateData();
		INT λ�� = (INT)P - 1;
		W_Ĭ����� = W_�б�->GetItemText(λ��,2);
		W_Ĭ�Ͽ������ = W_�б�->GetItemText(λ��,3);
		W_��ʼ��ַ = W_�б�->GetItemText(λ��,4);
		W_������ַ = W_�б�->GetItemText(λ��,5);
		W_MIN = W_�б�->GetItemText(λ��,6);
		if(W_MIN == _T("��"))
		{
			W_��֤ = TRUE;
		}
		else
		{
			W_��֤ = FALSE;
		}
		W_MIN = W_�б�->GetItemText(λ��,7);
		W_MAX = W_�б�->GetItemText(λ��,8);
		UpdateData(FALSE);
	}
	*pResult = 0;
}
void ����������::OnBnClickedButtonEdit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if(0 == W_Ĭ�����.GetLength())
	{
		MessageBox(_T("����ַ����Ϊ��"));
		return;
	}
	if(0 == W_Ĭ�Ͽ������.GetLength())
	{
		MessageBox(_T("��������ַ����Ϊ��"));
		return;
	}
	if(0 == W_��ʼ��ַ.GetLength())
	{
		MessageBox(_T("��ʼ��ַ����Ϊ��"));
		return;
	}
	if(0 == W_������ַ.GetLength())
	{
		MessageBox(_T("������ַ����Ϊ��"));
		return;
	}

	POSITION P = W_�б�->GetFirstSelectedItemPosition();
	if(	NULL != P )
	{
		UpdateData();
		INT λ�� = (INT)P - 1;

		W_�б�->SetItemText(λ��,2,W_Ĭ�����);
		W_�б�->SetItemText(λ��,3,W_Ĭ�Ͽ������);
		W_�б�->SetItemText(λ��,4,W_��ʼ��ַ);
		W_�б�->SetItemText(λ��,5,W_������ַ);
		if(W_��֤)
		{
			W_�б�->SetItemText(λ��,6,_T("��"));
		}
		else
		{
			W_�б�->SetItemText(λ��,6,_T("��"));
		}
		W_�б�->SetItemText(λ��,7,W_MIN);
		W_�б�->SetItemText(λ��,8,W_MAX);

		UpdateData(FALSE);
		������Ŀ��(W_�����ļ���ַ);
	}
}
void ����������::OnEnChangeEditTbl()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	while(
		(_T(' ') == W_Ĭ�����.Left(1))
		|| (_T('��') == W_Ĭ�����.Left(1))
		)
	{
		W_Ĭ�����.TrimLeft(_T(' '));
		W_Ĭ�����.TrimLeft(_T('��'));
	}
	UpdateData(FALSE);
}

void ����������::OnEnChangeEditTbl2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	while(
		(_T(' ') == W_Ĭ�Ͽ������.Left(1))
		|| (_T('��') == W_Ĭ�Ͽ������.Left(1))
		)
	{
		W_Ĭ�Ͽ������.TrimLeft(_T(' '));
		W_Ĭ�Ͽ������.TrimLeft(_T('��'));
	}
	UpdateData(FALSE);
}

void ����������::OnBnClickedButtonStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString ��Ŀ���,ROM,TBL,TBL2,TXT;
	u64 KS,JS;
	INT ��֤;
	UINT MIN,MAX;

	::WQSG_��ͨ�������� WQSG(m_hWnd,L"WQSG ��������");
	INT ���� = W_�б�->GetItemCount();

	for(INT I = 0;I < ����;I++)
	{
		if(W_�б�->GetCheck(I))
		{
			��Ŀ��� = W_�б�->GetItemText(I,0);
			ROM = W_�б�->GetItemText(I,1);
			TBL = W_�б�->GetItemText(I,2);
			TBL2 = W_�б�->GetItemText(I,3);

			KS = JS = 0;
			TXT = W_�б�->GetItemText(I,4);
			_stscanf_s(TXT,_T("%x"),&KS);

			TXT = W_�б�->GetItemText(I,5);
			_stscanf_s(TXT,_T("%x"),&JS);

			TXT = W_�б�->GetItemText(I,6);
			if(_T("��") == TXT)
			{
				��֤ = 1;
			}
			else
			{
				��֤ = 0;
			}
			TXT = W_�б�->GetItemText(I,7);
			MIN = ::_ttoi(TXT);

			TXT = W_�б�->GetItemText(I,8);
			MAX = ::_ttoi(TXT);

			TXT = ROM;
			TXT += _T(".TXT");

			WQSG.���(��Ŀ���.GetBuffer(),ROM.GetBuffer(),TBL.GetBuffer(),TBL2.GetBuffer(),TXT.GetBuffer(),KS,JS,��֤,MIN,MAX);
		}
	}
	WQSG.����();
}
