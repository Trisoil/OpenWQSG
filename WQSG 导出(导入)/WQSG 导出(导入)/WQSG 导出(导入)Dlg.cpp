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
// MFCDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WQSG ����(����).h"
#include "WQSG ����(����)Dlg.h"
#include "page_TXT.h"
#include "page_PTXT.h"
#include "��������������.h"

#include "page_txt.h"
#include "page_ptxt.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CTabCtrl W_TabC;
static Cpage_TXT_OUT	W_page_TXT_OUT;
static Cpage_TXT_IN		W_page_TXT_IN;
static Cpage_PTXT_OUT	W_page_PTXT_OUT;
static Cpage_PTXT_IN	W_page_PTXT_IN;
static CString			W_����;

#define WM_WQSG_����ǰ������	(WM_USER + 1)
#define WM_WQSG_ȡǰ�˴���		(WM_WQSG_����ǰ������ + 1)

LRESULT CWQSG��������Dlg::����ǰ������( WPARAM ���� , LPARAM ���� )
{
	BOOL �Ƿ���� = ( ���� != 0 );
	if( �Ƿ���� )
	{
		if( m_��ǰ�˶Ի���.m_hWnd == NULL )
		{
			m_��ǰ�˶Ի���.Create(IDD_AB);
			m_��ǰ�˶Ի���.ShowWindow(TRUE);
			m_��ǰ�˶Ի���.SetWindowText( W_���� );
			m_��ǰ�˶Ի���.��������( (WCHAR*)���� );
		}
		else
		{
			m_��ǰ�˶Ի���.��������( (WCHAR*)���� );
		}
	}
	else
	{
		m_��ǰ�˶Ի���.DestroyWindow();
	}
	ShowWindow( !�Ƿ���� );
	return 0;
}

LRESULT CWQSG��������Dlg::ȡǰ�˴���( WPARAM ���� , LPARAM ����ָ�� )
{
	*(HWND*)����ָ�� = m_��ǰ�˶Ի���.m_hWnd;
	return 0;
}
//////////////////////////
DWORD WINAPI CWQSG��������Dlg::��ͨ����(LPVOID lpParameter)
{
	�����ṹ*������ = (�����ṹ*)lpParameter;
	U64 ��ʼ��ַ = 0,������ַ = 0;
	UINT xyz;
	_stscanf_s(W_page_TXT_OUT.W_KS2.GetBuffer(),_T("%x"),&xyz);
	��ʼ��ַ |= xyz;
	������ַ |= xyz;
	��ʼ��ַ <<= 32;
	������ַ <<= 32;
	////////////////////////////////////////
	_stscanf_s(W_page_TXT_OUT.W_KS.GetBuffer(),_T("%x"),&xyz);
	��ʼ��ַ |= xyz;
	_stscanf_s(W_page_TXT_OUT.W_JS.GetBuffer(),_T("%x"),&xyz);
	������ַ |= xyz;

	HWND ǰ�˴��� = NULL;
	::SendMessage( ������->hwnd , WM_WQSG_ȡǰ�˴��� , 0 , (LPARAM)&ǰ�˴��� );

	::WQSG_TXT_OUT WQSG( ǰ�˴��� , L"WQSG ��������" );

	if(WQSG.OUT_TXT(������->ROM.GetBuffer(),������->TBL.GetBuffer(),������->TBL2.GetBuffer(),������->TXT.GetBuffer(),
		��ʼ��ַ,������ַ,������->��֤,
		_tstoi(W_page_TXT_OUT.W_MIN),_tstoi(W_page_TXT_OUT.W_MAX)))
	{
		::MessageBox( ǰ�˴���,_T("��ϲ,�����ɹ�"),_T("WQSG ��������"),MB_OK);
	}

	::SendMessage( ������->hwnd , WM_WQSG_����ǰ������ , 0 , (LPARAM)0 );
	return 0;
}

DWORD WINAPI CWQSG��������Dlg::��ͨ����(LPVOID lpParameter){
	//W_page_TXT_IN.UpdateData();
	�����ṹ*������ = (�����ṹ*)lpParameter;

	HWND ǰ�˴��� = NULL;
	::SendMessage( ������->hwnd , WM_WQSG_ȡǰ�˴��� , 0 , (LPARAM)&ǰ�˴��� );

	U8 ��=0,˫_1=0,˫_2=0;
	int kk;
	CString tmp;
	tmp = W_page_TXT_IN.���ֽ����;
	if(W_page_TXT_IN.������� & 1){
		if(0 == (tmp.GetLength())){
			if(IDNO == ::MessageBox( ǰ�˴��� , _T("���ֽ���� Ϊ��,�����Զ��� 00 ���\nҪ������?"),_T("WQSG �������"),MB_OK)){
				::SendMessage( ������->hwnd , WM_WQSG_����ǰ������ , 0 , (LPARAM)0 );
				return 0;
			}
		}
		while(2 != (tmp.GetLength())){
			tmp.Insert(0,_T('0'));
		}
		::_stscanf_s(tmp.GetBuffer(),_T("%2x"),&kk);
		�� = kk;
	}
	tmp = W_page_TXT_IN.˫�ֽ����;
	if(W_page_TXT_IN.������� & 2){
		if(0 == (tmp.GetLength())){
			if(IDNO == ::MessageBox( ǰ�˴��� , _T("˫�ֽ���� Ϊ��,�����Զ��� 0000 ���\nҪ������?"),_T("WQSG �������"),MB_OK)){
				::SendMessage( ������->hwnd , WM_WQSG_����ǰ������ , 0 , (LPARAM)0 );
				return 0;
			}
		}
		while( 4 != (tmp.GetLength())){
			tmp.Insert(0,_T('0'));
		}
		::_stscanf_s(tmp.GetBuffer(),_T("%2x"),&kk);
		˫_1 = kk;
		::_stscanf_s(tmp.GetBuffer() + 2,_T("%2x"),&kk);
		˫_2 = kk;
	}
	INT ���Ȳ�����ʾ = (W_page_TXT_IN.W_���Ȳ�����ʾ)?1:0;

	::WQSG_TXT_IN WQSG( ǰ�˴��� ,_T("WQSG �������"));
	if(WQSG.IN_TXT(������->ROM.GetBuffer(),������->TBL.GetBuffer(),������->TBL2.GetBuffer(),������->TXT.GetBuffer(),
		W_page_TXT_IN.�������,��,˫_1,˫_2,
		������->��֤,
		���Ȳ�����ʾ
		))
	{
		::MessageBox( ǰ�˴��� , _T("��ϲ,����ɹ�"),_T("WQSG �������"),MB_OK);
	}

	::SendMessage( ������->hwnd , WM_WQSG_����ǰ������ , 0 , (LPARAM)0 );
	return 0;
}
DWORD WINAPI CWQSG��������Dlg::��ַ_ָ�뵼��(LPVOID lpParameter)
{
	�����ṹ*������ = (�����ṹ*)lpParameter;
	U64 ��ָ���ַ = 0,���ָ���ַ = 0;
	U32 �ı�������ַ = 0;
	U8 ָ����,ָ��ʵ��,ָ�뱶��;

	UINT xyz = 0;	
	_stscanf_s(W_page_PTXT_OUT.W_pKS.GetBuffer(),_T("%x"),&xyz);
	��ָ���ַ = (U64)xyz;

	xyz = 0;
	_stscanf_s(W_page_PTXT_OUT.W_pJS.GetBuffer(),_T("%x"),&xyz);
	���ָ���ַ = (U64)xyz;

	xyz = 0;
	_stscanf_s(W_page_PTXT_OUT.W_p�ı�����.GetBuffer(),_T("%x"),&xyz);
	�ı�������ַ = (U32)xyz;

	ָ���� = (U8)::_ttoi(W_page_PTXT_OUT.W_pָ����);
	ָ��ʵ�� = (U8)::_ttoi(W_page_PTXT_OUT.W_pʵ��ָ�볤��);
	ָ�뱶�� = (U8)::_ttoi(W_page_PTXT_OUT.W_pָ�뱶��);

	HWND ǰ�˴��� = NULL;
	::SendMessage( ������->hwnd , WM_WQSG_ȡǰ�˴��� , 0 , (LPARAM)&ǰ�˴��� );

	::WQSG_pTXT_OUT WQSG( ǰ�˴��� , L"WQSG ��������");
	WQSG.��ַ_ָ��OUT(������->ROM.GetBuffer(),������->TBL.GetBuffer(),������->TBL2.GetBuffer(),������->TXT.GetBuffer(),
		������->��֤,��ָ���ַ,���ָ���ַ,ָ����,
		ָ��ʵ��,�ı�������ַ,ָ�뱶��);

	::SendMessage( ������->hwnd , WM_WQSG_����ǰ������ , 0 , (LPARAM)0 );
	return 0;
}
DWORD WINAPI CWQSG��������Dlg::��ַ_ָ�뵼��(LPVOID lpParameter){
	�����ṹ*������ = (�����ṹ*)lpParameter;
	U64 �ı�����ʼ��ַ,�ı������޵�ַ;

	
	UINT X = 0;
	::swscanf_s(W_page_PTXT_IN.m_p�ı�����ʼ��ַ.GetBuffer(),L"%x",&X);
	�ı�����ʼ��ַ = X;

	X = 0;
	::swscanf_s(W_page_PTXT_IN.m_p�ı������޵�ַ.GetBuffer(),L"%x",&X);
	�ı������޵�ַ = X;

	HWND ǰ�˴��� = NULL;
	::SendMessage( ������->hwnd , WM_WQSG_ȡǰ�˴��� , 0 , (LPARAM)&ǰ�˴��� );

	::WQSG_pTXT_I WQSG(ǰ�˴���,L"WQSG ָ�뵼�����");
	if(WQSG.�������(������->TBL.GetBuffer(),������->TBL2.GetBuffer(),������->��֤)){
		if(WQSG.�����ı�(������->ROM.GetBuffer(),������->TXT.GetBuffer(),�ı�����ʼ��ַ,�ı������޵�ַ)){
			::MessageBox(ǰ�˴���,_T("��ϲ,����ɹ�"),_T("WQSG �������"),MB_OK);
		}
	}
//	::MessageBox(������->hwnd,_T("��ʱ��֧��"),_T("WQSG ָ�뵼�����"),MB_OK);
	::SendMessage( ������ ->hwnd , WM_WQSG_����ǰ������ , 0 , (LPARAM)0 );
	return 0;
}
// CMFCDlg �Ի���
void CWQSG��������Dlg::д����(void)
{
	W_page_TXT_OUT .UpdateData();
	
	WritePrivateProfileString(m_NAME,_T("��ַ��"),W_page_TXT_OUT.W_KS2,�����ļ�);
	WritePrivateProfileString(m_NAME,_T("��ʼ��ַ"),W_page_TXT_OUT.W_KS,�����ļ�);
	WritePrivateProfileString(m_NAME,_T("������ַ"),W_page_TXT_OUT.W_JS,�����ļ�);
	WritePrivateProfileString(m_NAME,_T("����С"),W_page_TXT_OUT.W_MIN,�����ļ�);
	WritePrivateProfileString(m_NAME,_T("���˴�"),W_page_TXT_OUT.W_MAX,�����ļ�);


	W_page_TXT_IN.UpdateData();
	
	CString tmp;
	tmp.Format(_T("%d"),W_page_TXT_IN.�������);
	WritePrivateProfileString(m_NAME,_T("�������"),tmp,�����ļ�);
	WritePrivateProfileString(m_NAME,_T("���ֽ����"),W_page_TXT_IN.���ֽ����,�����ļ�);
	WritePrivateProfileString(m_NAME,_T("˫�ֽ����"),W_page_TXT_IN.˫�ֽ����,�����ļ�);

	W_page_PTXT_OUT.UpdateData();
	
	WritePrivateProfileString(m_NAME,_T("p��ʼ��ַ"),W_page_PTXT_OUT.W_pKS,�����ļ�);
	WritePrivateProfileString(m_NAME,_T("p������ַ"),W_page_PTXT_OUT.W_pJS,�����ļ�);
	WritePrivateProfileString(m_NAME,_T("p�ı�������ַ"),W_page_PTXT_OUT.W_p�ı�����,�����ļ�);
	WritePrivateProfileString(m_NAME,_T("pָ����"),W_page_PTXT_OUT.W_pָ����,�����ļ�);
	WritePrivateProfileString(m_NAME,_T("pʵ��ָ�볤��"),W_page_PTXT_OUT.W_pʵ��ָ�볤��,�����ļ�);
	WritePrivateProfileString(m_NAME,_T("pָ�뱶��"),W_page_PTXT_OUT.W_pָ�뱶��,�����ļ�);
	WritePrivateProfileString(m_NAME,_T("p�ı�����"),W_page_PTXT_OUT.W_�ı�����,�����ļ�);

	tmp.Format(_T("%d"),W_page_PTXT_OUT.W_pָ���ʽ);
	WritePrivateProfileString(m_NAME,_T("pָ���ʽ"),tmp,�����ļ�);
	WritePrivateProfileString(m_NAME,_T("p���ȿ鱶��"),W_page_PTXT_OUT.W_p���ȿ鱶��,�����ļ�);

	W_page_PTXT_IN.UpdateData();

	WritePrivateProfileString(m_NAME,_T("p�ı������޵�ַ"),W_page_PTXT_IN.m_p�ı������޵�ַ,�����ļ�);
	WritePrivateProfileString(m_NAME,_T("p�ı�����ʼ��ַ"),W_page_PTXT_IN.m_p�ı�����ʼ��ַ,�����ļ�);
}
void CWQSG��������Dlg::д�б�(CListBox * lb_tmp){
	::CWQSG_File wfile;
	if(wfile.OpenFile(�����б��ļ�,4,3)){

		wfile.Write("\377\376",2);

		for( int k = lb_tmp->GetCount(),i = 0;i < k;i++){
			CString tmp;
			lb_tmp->GetText(i,tmp);
			tmp += _T("\r\n");
			wfile.Write(tmp.GetBuffer(),(::WQSG_strlen(tmp.GetBuffer())<<1));
		}
	}
}
void CWQSG��������Dlg::�ı�ѡ��(void){
	CButton*tmp = (CButton*)GetDlgItem(IDC_CHECK_PTXT);
	switch(W_TabC.GetCurSel()){
		case 0:
			W_page_TXT_IN.ShowWindow(FALSE);
			W_page_PTXT_IN.ShowWindow(FALSE);
			if(tmp->GetCheck()){
				W_page_TXT_OUT.ShowWindow(FALSE);
				W_page_PTXT_OUT.ShowWindow(TRUE);
			}
			else{
				W_page_TXT_OUT.ShowWindow(TRUE);
				W_page_PTXT_OUT.ShowWindow(FALSE);
			}			
			break;
		case 1:
			W_page_TXT_OUT.ShowWindow(FALSE);
			W_page_PTXT_OUT.ShowWindow(FALSE);
			if(tmp->GetCheck()){
				W_page_TXT_IN.ShowWindow(FALSE);
				W_page_PTXT_IN.ShowWindow(TRUE);
			}
			else{
				W_page_TXT_IN.ShowWindow(TRUE);
				W_page_PTXT_IN.ShowWindow(FALSE);
			}
			break;
		default:
			;
	}
}

void CWQSG��������Dlg::����Ŀ¼(void)
{
	CString tmp = W_����Ŀ¼;
	tmp += _T("\\DATA");
	CreateDirectory(tmp,NULL);
	tmp += _T("\\WQSG ����(����)");
	CreateDirectory(tmp,NULL);
}
CWQSG��������Dlg::CWQSG��������Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWQSG��������Dlg::IDD, pParent)
	, W_NAME(_T(""))
	, W_ROM(_T(""))
	, W_TBL(_T(""))
	, W_TBL2(_T(""))
	, m_EDIT_ROM(_T(""))
{
	W_����.LoadStringW(IDS_TXTIO);
	m_hIcon = AfxGetApp()->LoadIcon(IDR_WQSG);

}


void CWQSG��������Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_NAME, W_NAME);
	DDV_MaxChars(pDX, W_NAME, 32);
	DDX_Control(pDX, IDC_TAB1, W_TabC);
	//	DDX_Control(pDX, IDC_LIST2, W_LIST);
	DDX_Text(pDX, IDC_EDIT_TXT_DIR, m_EDIT_ROM);
	DDV_MaxChars(pDX, m_EDIT_TXT, 260);
}

BEGIN_MESSAGE_MAP(CWQSG��������Dlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_Add, &CWQSG��������Dlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_Edit, &CWQSG��������Dlg::OnBnClickedButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON_Del, &CWQSG��������Dlg::OnBnClickedButtonDel)
	__i__
	ON_BN_CLICKED(IDC_BUTTON_ROM, &CWQSG��������Dlg::OnBnClickedButtonRom)
	ON_BN_CLICKED(IDC_BUTTON_TBL, &CWQSG��������Dlg::OnBnClickedButtonTbl)
	ON_BN_CLICKED(IDC_BUTTON_TBL2, &CWQSG��������Dlg::OnBnClickedButtonTbl2)
	__i__
	ON_EN_CHANGE(IDC_EDIT_ROM, &CWQSG��������Dlg::OnEnChangeEditRom)
	ON_EN_CHANGE(IDC_EDIT_TBL, &CWQSG��������Dlg::OnEnChangeEditTbl)
	ON_EN_CHANGE(IDC_EDIT_TBL2, &CWQSG��������Dlg::OnEnChangeEditTbl2)
	__i__
	ON_EN_KILLFOCUS(IDC_EDIT_ROM, &CWQSG��������Dlg::OnEnKillfocusEditRom)
	__i__
	ON_BN_CLICKED(IDC_BUTTON_START, &CWQSG��������Dlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_BAT, &CWQSG��������Dlg::OnBnClickedButtonBat)
	__i__
	ON_EN_UPDATE(IDC_EDIT_NAME, &CWQSG��������Dlg::OnEnUpdateEditName)
	ON_LBN_SELCHANGE(IDC_LIST2, &CWQSG��������Dlg::OnLbnSelchangeList2)
	__i__
	ON_EN_KILLFOCUS(IDC_EDIT_NAME, &CWQSG��������Dlg::OnEnKillfocusEditName)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CWQSG��������Dlg::OnTcnSelchangeTab1)
	ON_BN_CLICKED(IDC_CHECK_PTXT, &CWQSG��������Dlg::OnBnClickedCheckPtxt)
	__i__
	ON_WM_CLOSE()
	__i__
	ON_MESSAGE( WM_WQSG_����ǰ������ , &CWQSG��������Dlg::����ǰ������ )
	ON_MESSAGE( WM_WQSG_ȡǰ�˴��� , &CWQSG��������Dlg::ȡǰ�˴��� )
END_MESSAGE_MAP()
BOOL CWQSG��������Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	SetWindowTextW(W_����);


	((CButton*)GetDlgItem(IDC_CHECK_YZ))->SetCheck(TRUE);

	W_TabC.InsertItem(0,_T("����"));
	W_TabC.InsertItem(1,_T("����"));

	W_page_TXT_OUT.Create(IDD_TXT_OUT,&W_TabC);
	W_page_TXT_IN.Create(IDD_TXT_IN,&W_TabC);
	W_page_PTXT_OUT.Create(IDD_PTXT_OUT,&W_TabC);
	W_page_PTXT_IN.Create(IDD_PTXT_IN,&W_TabC);

	CRect rs,rs2;
	W_TabC.GetClientRect(&rs);
	W_TabC.GetItemRect(0,&rs2);
	rs.top += rs2.bottom + 4;
	rs.bottom -= 8;
	rs.left += 4;
	rs.right -= 8;
	W_page_TXT_OUT.MoveWindow(rs);
	W_page_TXT_IN.MoveWindow(rs);
	W_page_PTXT_OUT.MoveWindow(rs);
	W_page_PTXT_IN.MoveWindow(rs);
	W_page_TXT_OUT.ShowWindow(TRUE);
	
	W_TabC.SetCurSel(0);

	::CWQSG_File wfile;
	if(wfile.OpenFile(�����б��ļ�,1,3)){
		CListBox
			*lb_tmp = ((CListBox*)GetDlgItem(IDC_LIST2));

		WCHAR * ȫ�� = NULL;
		U64 SIZE;
		wfile.GetFileSize(&SIZE);
		if(SIZE <= 1048576){

			switch(::WQSG_A_U_X(wfile.GetFileHANDLE())){
				case 1:
					wfile.Seek(0);
					{
						U8 * tmpU = new U8[(UINT)SIZE+1];
						tmpU[(UINT)SIZE] = '\0';

						wfile.Read(tmpU,(UINT)SIZE);

						ȫ�� = ::WQSG_char_W( (char*)tmpU);
						delete[]tmpU;
					}
					break;
				case 2:
					wfile.Seek(2);
					ȫ�� = new WCHAR[((UINT)SIZE)>>1];
					SIZE -= 2;
					ȫ��[((UINT)SIZE)>>1] = L'\0';
					wfile.Read(ȫ��,(UINT)SIZE);
					break;
				default:
					break;
			}
			if(ȫ�� != NULL){
				WCHAR * const ȫ��_del = ȫ��;
				while(WCHAR * const һ�� = ::WQSG_GetTXT_Line(&ȫ��)){
					lb_tmp->AddString(һ��);
					delete[]һ��;
				}
				delete[]ȫ��_del;
			}
		}
	}


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CWQSG��������Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CWQSG��������Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CWQSG��������Dlg::OnOK(){}
void CWQSG��������Dlg::OnCancel(){}
int CWQSG��������Dlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO:  �ڴ������ר�õĴ�������
	TCHAR exeFullPath[MAX_PATH]; 
    GetModuleFileName(NULL,exeFullPath,MAX_PATH);
	W_����Ŀ¼ = exeFullPath;
	W_����Ŀ¼ = W_����Ŀ¼.Left(W_����Ŀ¼.ReverseFind(_T('\\')));
	�����б��ļ� = �����ļ� = W_����Ŀ¼;
	����Ŀ¼();
	�����ļ� += _T("\\DATA\\WQSG ����(����)\\����.CFG");
	�����б��ļ� += _T("\\DATA\\WQSG ����(����)\\�����б�.CFG");
	
	return 0;
}
void CWQSG��������Dlg::OnBnClickedButtonRom()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	static CWQSGFileDialog_Open fopendlg(_T("ROM�ļ�(*.*)|*.*||"));

	fopendlg.SetWindowTitle( _T("ѡ��һ��ROM...") );

	if(IDOK == fopendlg.DoModal())
	{
		W_page_TXT_OUT.W_ROM��ַ = W_ROM = fopendlg.GetPathName();
	}
	UpdateData(FALSE);
}
void CWQSG��������Dlg::OnBnClickedButtonTbl()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	static CWQSGFileDialog_Open fopendlg(_T("����ļ�(*.TBL,*.TXT)|*.TBL;*.TXT||"));
	fopendlg.SetWindowTitle( _T("ѡ��һ������ļ�...") );

	if(IDOK == fopendlg.DoModal())
	{
		W_TBL = fopendlg.GetPathName();
	}
	UpdateData(FALSE);
}

void CWQSG��������Dlg::OnBnClickedButtonTbl2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	static CWQSGFileDialog_Open fopendlg(_T("����ļ�(*.TBL,*.TXT)|*.TBL;*.TXT||"));
	fopendlg.SetWindowTitle( _T("ѡ��һ���������...") );

	if(IDOK == fopendlg.DoModal())
	{
		W_TBL2 = fopendlg.GetPathName();
	}
	UpdateData(FALSE);
}

void CWQSG��������Dlg::OnBnClickedButtonAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if( _T("") == W_NAME )
	{
		MessageBox(_T("�ļ�������Ϊ��"));
		return;
	}
		
	CListBox
		* lb_tmp = ((CListBox*)GetDlgItem(IDC_LIST2));
	if(LB_ERR != lb_tmp->FindString(0,W_NAME))
	{
		MessageBox(_T("�ļ����ظ�"));
		((CEdit*)GetDlgItem(IDC_EDIT_NAME))->SetSel(0,-1);
		((CEdit*)GetDlgItem(IDC_EDIT_NAME))->SetFocus();
		return ;
	}
	lb_tmp->SetCurSel(lb_tmp->AddString(W_NAME));
	lb_tmp->SetFocus();
	UpdateData(FALSE);
	д����();

	д�б�(lb_tmp);
}
void CWQSG��������Dlg::OnEnUpdateEditName()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// �������� EM_SETEVENTMASK ��Ϣ���͵��ؼ���
	// ͬʱ�� ENM_UPDATE ��־�������㵽 lParam �����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	while(
		(_T(' ') == W_NAME.Left(1))
		|| (_T('��') == W_NAME.Left(1))
		)
	{
	W_NAME.TrimLeft(_T(' '));
	W_NAME.TrimLeft(_T('��'));
	}
	UpdateData(FALSE);
}
void CWQSG��������Dlg::OnLbnSelchangeList2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CListBox
		*lb_tmp = ((CListBox*)GetDlgItem(IDC_LIST2));
	INT
		j = lb_tmp->GetCurSel();
	if(-1 != j){
		lb_tmp->GetText(j,W_NAME);
		UpdateData(FALSE);

		TCHAR tmp [1024];
		GetPrivateProfileString(W_NAME,_T("��ַ��"),NULL,tmp,1024,�����ļ�);
		if(0 == *tmp){
			W_page_TXT_OUT.W_KS2 = _T("0");
		}
		else{
			W_page_TXT_OUT.W_KS2 = tmp;
		}
		GetPrivateProfileString(W_NAME,_T("��ʼ��ַ"),NULL,tmp,1024,�����ļ�);
		W_page_TXT_OUT.W_KS = tmp;
		GetPrivateProfileString(W_NAME,_T("������ַ"),NULL,tmp,1024,�����ļ�);
		W_page_TXT_OUT.W_JS = tmp;
		GetPrivateProfileString(W_NAME,_T("����С"),_T("0"),tmp,1024,�����ļ�);
		W_page_TXT_OUT.W_MIN = tmp;
		GetPrivateProfileString(W_NAME,_T("���˴�"),_T("99999"),tmp,1024,�����ļ�);
		W_page_TXT_OUT.W_MAX = tmp;
		W_page_TXT_OUT .UpdateData(FALSE);


		GetPrivateProfileString(W_NAME,_T("�������"),_T("0"),tmp,1024,�����ļ�);
		W_page_TXT_IN.������� = _tstoi(tmp);
		GetPrivateProfileString(W_NAME,_T("���ֽ����"),NULL,tmp,1024,�����ļ�);
		W_page_TXT_IN.���ֽ���� = tmp;
		GetPrivateProfileString(W_NAME,_T("˫�ֽ����"),NULL,tmp,1024,�����ļ�);
		W_page_TXT_IN.˫�ֽ���� = tmp;	
		W_page_TXT_IN.UpdateData(FALSE);
		W_page_TXT_IN.OnCbnSelchangeCombo1();

		GetPrivateProfileString(W_NAME,_T("p��ʼ��ַ"),NULL,tmp,1024,�����ļ�);
		W_page_PTXT_OUT.W_pKS = tmp;
		GetPrivateProfileString(W_NAME,_T("p������ַ"),NULL,tmp,1024,�����ļ�);
		W_page_PTXT_OUT.W_pJS = tmp;
		GetPrivateProfileString(W_NAME,_T("p�ı�������ַ"),NULL,tmp,1024,�����ļ�);
		W_page_PTXT_OUT.W_p�ı����� = tmp;
		GetPrivateProfileString(W_NAME,_T("pָ����"),_T("2"),tmp,1024,�����ļ�);
		W_page_PTXT_OUT.W_pָ���� = tmp;
		GetPrivateProfileString(W_NAME,_T("pʵ��ָ�볤��"),_T("2"),tmp,1024,�����ļ�);
		W_page_PTXT_OUT.W_pʵ��ָ�볤�� = tmp;
		GetPrivateProfileString(W_NAME,_T("pָ�뱶��"),_T("1"),tmp,1024,�����ļ�);
		W_page_PTXT_OUT.W_pָ�뱶�� = tmp;
		GetPrivateProfileString(W_NAME,_T("p�ı�����"),_T("1"),tmp,1024,�����ļ�);
		W_page_PTXT_OUT.W_�ı����� = tmp;


		GetPrivateProfileString(W_NAME,_T("pָ���ʽ"),_T("0"),tmp,1024,�����ļ�);
		W_page_PTXT_OUT.W_pָ���ʽ = _wtoi(tmp);
		GetPrivateProfileString(W_NAME,_T("p���ȿ鱶��"),NULL,tmp,1024,�����ļ�);
		W_page_PTXT_OUT.W_p���ȿ鱶�� = tmp;

		W_page_PTXT_OUT.UpdateData(FALSE);
		W_page_PTXT_OUT.OnCbnSelchangeCombo5();


		GetPrivateProfileString(W_NAME,_T("p�ı������޵�ַ"),NULL,tmp,1024,�����ļ�);
		W_page_PTXT_IN.m_p�ı������޵�ַ = tmp;
		GetPrivateProfileString(W_NAME,_T("p�ı�����ʼ��ַ"),NULL,tmp,1024,�����ļ�);
		W_page_PTXT_IN.m_p�ı�����ʼ��ַ = tmp;

		W_page_PTXT_IN.UpdateData(FALSE);
	}
}
void CWQSG��������Dlg::OnBnClickedButtonEdit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CListBox
		*lb_tmp = ((CListBox*)GetDlgItem(IDC_LIST2));
	INT
		j = lb_tmp->GetCurSel();
	if(-1 == j)
	{
		MessageBox(_T("����ѡ��һ����Ŀ"));
		return;
	}
	if(
		(LB_ERR != lb_tmp->FindString(0,W_NAME))
		&& (j != lb_tmp->FindString(0,W_NAME))
		)
	{ 
		MessageBox(_T("�ļ����ظ�"));
		((CEdit*)GetDlgItem(IDC_EDIT_NAME))->SetSel(0,-1);
		((CEdit*)GetDlgItem(IDC_EDIT_NAME))->SetFocus();
		return ;
	}
	CString tmp;
	lb_tmp->GetText(j,tmp);
	WritePrivateProfileString(tmp,NULL,NULL,�����ļ�);
	lb_tmp->DeleteString(j);
	lb_tmp->SetCurSel(lb_tmp->InsertString(j,W_NAME));
	д����();
	lb_tmp->SetFocus();	

	д�б�(lb_tmp);
}
void CWQSG��������Dlg::OnBnClickedButtonDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CListBox
		*lb_tmp = ((CListBox*)GetDlgItem(IDC_LIST2));
	INT
		j = lb_tmp->GetCurSel();
	if(-1 == j)
	{
		MessageBox(_T("��ѡ��һ����Ŀ"));
		return;
	}
	lb_tmp->GetText(j,W_NAME);
	WritePrivateProfileString(W_NAME,NULL,NULL,�����ļ�);
	W_NAME.Empty();
	lb_tmp->DeleteString(j);
	if(lb_tmp->GetCount() > j)
	{
		lb_tmp->SetCurSel(j);
	}
	else
	{
		lb_tmp->SetCurSel(--j);
	}
	OnLbnSelchangeList2();
	lb_tmp->SetFocus();
	UpdateData(FALSE);

	д�б�(lb_tmp);
}
void CWQSG��������Dlg::OnEnKillfocusEditName()
	{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		////�����Ƿ��з�
	if(
		(-1 != W_NAME.Find(_T('\\')))
		|| (-1 != W_NAME.Find(_T('/')))
		|| (-1 != W_NAME.Find(_T(':')))
		|| (-1 != W_NAME.Find(_T('*')))
		|| (-1 != W_NAME.Find(_T('?')))
		|| (-1 != W_NAME.Find(_T('\"')))
		|| (-1 != W_NAME.Find(_T('<')))
		|| (-1 != W_NAME.Find(_T('>')))
		|| (-1 != W_NAME.Find(_T('|')))
		|| (-1 != W_NAME.Find(_T('[')))
		|| (-1 != W_NAME.Find(_T(']')))
		)
		{
		MessageBox(_T("�ļ������������·���\n \\ / : * ? \" < > | [ ]"));
		((CEdit*)GetDlgItem(IDC_EDIT_NAME))->SetSel(0,-1);
		((CEdit*)GetDlgItem(IDC_EDIT_NAME))->SetFocus();
		return ;
		}
	}

void CWQSG��������Dlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	�ı�ѡ��();
	*pResult = 0;
}
void CWQSG��������Dlg::OnBnClickedCheckPtxt(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	�ı�ѡ��();
}

void CWQSG��������Dlg::OnEnChangeEditRom()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	while(
		(_T(' ') == W_ROM.Left(1))
		|| (_T('��') == W_ROM.Left(1))
		)
		{
			W_ROM.TrimLeft(_T(" "));
			W_ROM.TrimLeft(_T("��"));
		}
	UpdateData(FALSE);
}

void CWQSG��������Dlg::OnEnChangeEditTbl()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	while(
		(_T(' ') == W_TBL.Left(1))
		|| (_T('��') == W_TBL.Left(1))
		)
		{
			W_TBL.TrimLeft(_T(" "));
			W_TBL.TrimLeft(_T("��"));
		}
	UpdateData(FALSE);
}

void CWQSG��������Dlg::OnEnChangeEditTbl2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	while(
		(_T(' ') == W_TBL2.Left(1))
		|| (_T('��') == W_TBL2.Left(1))
		)
		{
			W_TBL2.TrimLeft(_T(" "));
			W_TBL2.TrimLeft(_T("��"));
		}
	UpdateData(FALSE);
}

void CWQSG��������Dlg::OnBnClickedButtonBat()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CButton*tmp = (CButton*)GetDlgItem(IDC_CHECK_PTXT);
	switch(W_TabC.GetCurSel()){
		case 0:
			if(tmp->GetCheck()){
			}
			else{
				ShowWindow(FALSE);
				���������� BAT;
				BAT.DoModal();
				ShowWindow(TRUE);
			}			
			break;
		case 1:
			if(tmp->GetCheck()){
			}
			else{
			}
			break;
		default:
			;
	}
}
void CWQSG��������Dlg::OnBnClickedButtonStart(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString err;

	CButton* tmp = (CButton*)GetDlgItem(IDC_CHECK_PTXT);

	UpdateData();
	m_������.hwnd = m_hWnd;
	m_������.ROM = W_ROM;
	m_������.TBL = W_TBL;
	m_������.TBL2 = W_TBL2;
	m_������.��֤ = ((CButton*)GetDlgItem(IDC_CHECK_YZ))->GetCheck()?1:0;

	if(0 == m_������.ROM.GetLength()){
		err = L"ROM ��ַ����Ϊ��";
		goto __gt�����˳�;
	}
	if(0 == m_������.TBL.GetLength()){
		err = L"��� ��ַ����Ϊ��";
		goto __gt�����˳�;
	}
/*
	if(0 == m_������.TBL2.GetLength()){
		if(IDNO == MessageBox(_T("������� ��ַΪ��,Ҫ������?"),NULL,MB_YESNO)){
			err = L"";
			goto __gt�����˳�;
		}
	}
*/
//	SendMessage( WM_WQSG_����ǰ������ , 0 , (LPARAM)L"Start" );
	switch(W_TabC.GetCurSel())
	{
		case 0://����
			{
				static CWQSGFileDialog_Save fopendlg( _T("�ı��ļ�(*.TXT)|*.TXT||") , _T("TXT") , W_NAME );
				fopendlg.SetWindowTitle( _T("�ı����浽...") );

				HANDLE handle;
				if( IDOK == fopendlg.DoModal() )
				{
					m_������.TXT = fopendlg.GetPathName();

					if(tmp->GetCheck() != 0)//ָ��
					{
						W_page_PTXT_OUT.UpdateData();

						if(0 == W_page_PTXT_OUT.W_pKS.GetLength())
						{
							err = L"��ָ���ַ ����Ϊ��";
							goto __gt�����˳�;
						}
						if(0 == W_page_PTXT_OUT.W_pJS.GetLength())
						{
							err = L"���ָ���ַ ����Ϊ��";
							goto __gt�����˳�;
						}
						if(0 == W_page_PTXT_OUT.W_p�ı�����.GetLength())
						{
							err = L"�ı�������ַ ����Ϊ��";
							goto __gt�����˳�;
						}

						switch( W_page_PTXT_OUT.W_pָ���ʽ )
						{
						case 0:
							SendMessage( WM_WQSG_����ǰ������ , 0 , (LPARAM)L"���ڵ���..." );
							handle = ::CreateThread(NULL,NULL,��ַ_ָ�뵼��,&m_������,NULL,NULL);
							::CloseHandle(handle);
							return;
						case 1:
						case 2:
							err = L"��ʱ��֧�ִ�ģʽ";
							goto __gt�����˳�;
							break;
						default:
							err = L"δ֪��ʽ";
							goto __gt�����˳�;
						}
					}
					else//��ָ��
					{
						W_page_TXT_OUT.UpdateData();

						if(0 == W_page_TXT_OUT.W_KS.GetLength())
						{
							err = L"��ʼ��ַ ����Ϊ��";
							goto __gt�����˳�;
						}
						if(0 == W_page_TXT_OUT.W_JS.GetLength())
						{
							err = L"������ַ ����Ϊ��";
							goto __gt�����˳�;
						}

						SendMessage( WM_WQSG_����ǰ������ , 0 , (LPARAM)L"���ڵ���..." );
						handle = ::CreateThread(NULL,NULL,��ͨ����,&m_������,NULL,NULL);
						::CloseHandle(handle);
						return;
					}
				}
			}
			break;
		case 1://����
			{
				static CWQSGFileDialog_Open fopendlg(_T("�ı��ļ�(*.TXT)|*.TXT||"),W_NAME);
				fopendlg.SetWindowTitle( _T("��ѡ��Ҫ������ı�...") );

				if(IDOK == fopendlg.DoModal())
				{
					m_������.TXT = fopendlg.GetPathName();

					HANDLE handle;
					if(tmp->GetCheck()!=0)
					{
						W_page_PTXT_IN.UpdateData();

						if(W_page_PTXT_IN.m_p�ı�����ʼ��ַ.GetLength() == 0){
							err = L"�ı�����ʼ��ַ����Ϊ��";
							goto __gt�����˳�;
						}
						if(W_page_PTXT_IN.m_p�ı������޵�ַ.GetLength() == 0){
							err = L"�ı������޵�ַ����Ϊ��";
							goto __gt�����˳�;
						}
						SendMessage( WM_WQSG_����ǰ������ , 0 , (LPARAM)L"���ڵ���..." );
						handle = ::CreateThread(NULL,NULL,��ַ_ָ�뵼��,&m_������,NULL,NULL);
						::CloseHandle(handle);
						return;
					}
					else
					{
						W_page_TXT_IN.UpdateData();

						SendMessage( WM_WQSG_����ǰ������ , 0 , (LPARAM)L"���ڵ���..." );
						handle = ::CreateThread(NULL,NULL,��ͨ����,&m_������,NULL,NULL);
						::CloseHandle(handle);
						return;
					}
				}
			}
			break;
		default:
			break;
	}
__gt�����˳�:
	if(err.GetLength() > 0)
		MessageBox( err );
//	SendMessage( WM_WQSG_����ǰ������ , 0 , (LPARAM)0 );
}

void CWQSG��������Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
	CDialog::OnLButtonDown(nFlags, point);
}

void CWQSG��������Dlg::OnEnKillfocusEditRom()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	W_page_TXT_OUT.W_ROM��ַ = W_ROM;
}

void CWQSG��������Dlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDialog::OnClose();
	if(IDOK == MessageBox(_T("�Ƿ�Ҫ�˳�?"),NULL,MB_OKCANCEL) )
	{
		CDialog::OnCancel();
	}
}

