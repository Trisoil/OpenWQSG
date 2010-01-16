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
// TXT_OutBox.cpp : ʵ���ļ�
#include "stdafx.h"
#include "WQSG ����(����).h"
#include "TXT_OutBox.h"
#include "WQSG_MAIN.h"

#include "WQSG_DirDlg.h"
#define WM_WQSG_�߳���Ϣ	( WM_USER + 1 )
#define WM_WQSG_�߳�LOG		( WM_WQSG_�߳���Ϣ + 1 )

#define	DEF_V_export L"export"
BOOL CTXT_OutBox::zzz��ͨ����( CString& �ļ��� , CWQSG_TXT_O& WQSG , tg����& ���� )
{
	CString �ı�pathName;
	if( ����.m_TXT_DIR.GetLength() <= 0 )
	{
		�ı�pathName = �ļ���.Left( �ļ���.ReverseFind(L'\\') + 1 ) + �ļ���.Mid( �ļ���.ReverseFind(L'\\') + 1 ) + L".TXT";
	}
	else
	{
		WQSG_CreateDir( ����.m_TXT_DIR.GetString() );
		�ı�pathName = ����.m_TXT_DIR + �ļ���.Mid( �ļ���.ReverseFind(L'\\') + 1 ) + L".TXT";
	}
	return WQSG.�����ı�( �ļ���.GetString() , �ı�pathName.GetString() , ����.m_KS , ����.m_JS , ����.m_min , ����.m_max );
}
// CTXT_OutBox �Ի���
DWORD WINAPI CTXT_OutBox::��ͨ����_�ļ�(LPVOID lpParameter)
{
	tg����& ���� = *(tg����*)lpParameter;

	::SendMessage( ����.m_hWnd , WM_WQSG_�߳�LOG , 0 , (LPARAM)L"�����ļ�ģʽ" );
///--------------------------
	CWQSG_TXT_O WQSG;
	CString �ļ�;
///-------------------------
	HiResTimer RunTime;
	if( !WQSG.LoadTbl( ����.m_TBL.GetString() , (����.m_TBL2.GetLength() < 4)?NULL:����.m_TBL2.GetString() , ����.m_��֤ ) )
		goto __gt�˳�;

	RunTime.Start();
	for( std::vector<CStringW>::iterator it = ����.m_Files.begin() ; it != ����.m_Files.end() ; ++it )
	{
		�ļ� = *it;
		zzz��ͨ����( �ļ� , WQSG , ���� );
		/*
		if( !zzz��ͨ����( �ļ� , WQSG , ���� ) )
			goto __gt�˳�;
			*/
	}
	RunTime.Stop();
	{
		WQSG_tgElapsedTime _tg;
		WQSG_Milliseconds2struct( RunTime.getElapsedMilliseconds() , _tg );
		CString str;
		str.Format( L"����ʱ:%d �� %d ʱ %d �� %d �� %d ����" , _tg.wDay ,_tg.wHour ,_tg.wMinute ,_tg.wSecond , _tg.wMilliseconds );
		::SendMessage( ����.m_hWnd , WM_WQSG_�߳�LOG , 0 , (LPARAM)str.GetString() );
	}
__gt�˳�:
	::SendMessage( ����.m_hWnd , WM_WQSG_�߳�LOG , 0 , (LPARAM)L"�ر��ļ�ģʽ" );
	::SendMessage( ����.m_hWnd , WM_WQSG_�߳���Ϣ , 0 , 0 );
	return 0;
}
BOOL CTXT_OutBox::zzz_��ͨ����_�ļ���( CStringW ·�� , tg����& ���� , CWQSG_TXT_O& WQSG , INT& countAll , std::vector<CStringW>& szExt )
{
	if( ·��.Right(1) != L'\\')
		·�� += L'\\';

	::SendMessage( ����.m_hWnd , WM_WQSG_�߳�LOG , 0 , (LPARAM)( L"���� " + ·�� ).GetString() );

	WIN32_FIND_DATAW FindFileData;
	const HANDLE hFind = ::FindFirstFileW( ·�� + L"*", &FindFileData );
	if ( hFind != INVALID_HANDLE_VALUE )
	{
		INT count = 0;
		do
		{
			CStringW fileName( FindFileData.cFileName );
			if( FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
			{
				if( ( fileName != L"." ) && ( fileName != L".." ) && ����.m_SubDir )
				{
					zzz_��ͨ����_�ļ���( ·�� + FindFileData.cFileName , ���� , WQSG , count , szExt );
				/*	if( !zzz_��ͨ����_�ļ���( ·�� + FindFileData.cFileName , ���� , WQSG , count , szExt ) )
						return FALSE;*/

					::SendMessage( ����.m_hWnd , WM_WQSG_�߳�LOG , 0 , (LPARAM)( L"���� " + ·�� ).GetString() );
				}
			}
			else
			{
				for( int i = 0 ; (i >= 0) && ( (size_t)i < szExt.size() ) ; ++i )
				{
					if( fileName.Right( szExt[i].GetLength() ).MakeUpper() == szExt[i] )
					{
						if( zzz��ͨ����( ·�� + FindFileData.cFileName , WQSG , ���� ) )
						{
							++count;
							++countAll;
						}
						/*if( !zzz��ͨ����( ·�� + FindFileData.cFileName , WQSG , ���� ) )
							return FALSE;
						++count;
						++countAll;*/
						break;
					}
				}
			}
		}
		while( ::FindNextFile( hFind , &FindFileData ) );

		::FindClose( hFind );
		·��.Format( L"���� %u ���ļ�" , count );
		::SendMessage( ����.m_hWnd , WM_WQSG_�߳�LOG , 0 , (LPARAM)·��.GetString() );
	}
	else 
	{
		GetLastError();
	}
	return TRUE;
}
DWORD WINAPI CTXT_OutBox::��ͨ����_�ļ���(LPVOID lpParameter)
{
	tg����& ���� = *(tg����*)lpParameter;
///-------------------------------------------------
	::SendMessage( ����.m_hWnd , WM_WQSG_�߳�LOG , 0 , (LPARAM)L"�����ļ���ģʽ" );

	if( ����.m_TXT_DIR.GetLength() > 0 )
	{
		if( ����.m_TXT_DIR.Right(1) != L'\\')
			����.m_TXT_DIR += L'\\';
	}

	CWQSG_TXT_O WQSG;
///-------------------------------------------------
	HiResTimer RunTime;
	std::vector<CStringW> szExt;
	INT count = 0;

	if( !WQSG.LoadTbl( ����.m_TBL.GetString() , (����.m_TBL2.GetLength() < 4)?NULL:����.m_TBL2.GetString() , ����.m_��֤ ) )
		goto __gt�˳�;
	//
	�ֽ�Ext( ����.m_Ext , szExt );
	if( szExt.size() == 0 )
		szExt.push_back( CStringW(L"") );
	//
	RunTime.Start();
	zzz_��ͨ����_�ļ���( ����.m_ROM_DIR , ���� , WQSG , count , szExt );
	RunTime.Stop();
	//
	{
		WQSG_tgElapsedTime _tg;
		WQSG_Milliseconds2struct( RunTime.getElapsedMilliseconds() , _tg );
		CString str;
		str.Format( L"����ʱ:%d �� %d ʱ %d �� %d �� %d ����" , _tg.wDay ,_tg.wHour ,_tg.wMinute ,_tg.wSecond , _tg.wMilliseconds );
		::SendMessage( ����.m_hWnd , WM_WQSG_�߳�LOG , 0 , (LPARAM)str.GetString() );

		str.Format( L"һ���ɹ����� %u ���ļ�" , count );
		::SendMessage( ����.m_hWnd , WM_WQSG_�߳�LOG , 0 , (LPARAM)str.GetString() );
	}
__gt�˳�:
	::SendMessage( ����.m_hWnd , WM_WQSG_�߳�LOG , 0 , (LPARAM)L"�ر��ļ���ģʽ" );
	::SendMessage( ����.m_hWnd , WM_WQSG_�߳���Ϣ , 0 , 0 );
	return 0;
}
IMPLEMENT_DYNAMIC(CTXT_OutBox, CDialog)
CTXT_OutBox::CTXT_OutBox(CWnd* pParent /*=NULL*/)
	: CDialog(CTXT_OutBox::IDD, pParent)
	, m_EDIT_Rom(_T(""))
	, m_EDIT_TXT_DIR(_T(""))
	, m_EDIT_TBL(_T(""))
	, m_EDIT_TBL2(_T(""))
	, m_EDIT_min(_T("2"))
	, m_EDIT_max(_T("99999"))
	, m_EDIT_�κ�(_T("0"))
	, m_EDIT_��ʼƫ��(_T("0"))
	, m_EDIT_����ƫ��(_T("FFFFFFFF"))
	, m_EDIT_EXT(_T(""))
	, m_LOG(_T(""))
	, m_NodeName(_T(""))
{
}

CTXT_OutBox::~CTXT_OutBox()
{
}

void CTXT_OutBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_C��Ŀ¼����);
	DDX_Text(pDX, IDC_EDIT_ROM, m_EDIT_Rom);
	DDV_MaxChars(pDX, m_EDIT_Rom, MAX_PATH);
	DDX_Text(pDX, IDC_EDIT_TXT_DIR, m_EDIT_TXT_DIR);
	DDV_MaxChars(pDX, m_EDIT_TXT_DIR, MAX_PATH);
	DDX_Text(pDX, IDC_EDIT_TBL, m_EDIT_TBL);
	DDV_MaxChars(pDX, m_EDIT_TBL, MAX_PATH);
	DDX_Text(pDX, IDC_EDIT_TBL2, m_EDIT_TBL2);
	DDV_MaxChars(pDX, m_EDIT_TBL2, MAX_PATH);
	DDX_Control(pDX, IDC_CHKTBL, m_C��֤TBL);
	DDX_Text(pDX, IDC_EDIT_MIN, m_EDIT_min);
	DDV_MaxChars(pDX, m_EDIT_min, 5);
	DDX_Text(pDX, IDC_EDIT_MAX, m_EDIT_max);
	DDV_MaxChars(pDX, m_EDIT_max, 5);
	DDX_Text(pDX, IDC_EDIT_ADDR_H, m_EDIT_�κ�);
	DDV_MaxChars(pDX, m_EDIT_�κ�, 8);
	DDX_Text(pDX, IDC_EDIT_ADDR_KS_L, m_EDIT_��ʼƫ��);
	DDV_MaxChars(pDX, m_EDIT_��ʼƫ��, 8);
	DDX_Text(pDX, IDC_EDIT_ADDR_JS_L, m_EDIT_����ƫ��);
	DDV_MaxChars(pDX, m_EDIT_����ƫ��, 8);
	DDX_Text(pDX, IDC_EDIT_EXT, m_EDIT_EXT);
	DDV_MaxChars(pDX, m_EDIT_EXT, 100);
	DDX_Control(pDX, IDC_EDIT_LOG, m_CEDIT_LOG);
	DDX_Control(pDX, IDC_CHECK4, m_Cʹ�ÿ������);
	DDX_Control(pDX, IDC_LIST2, m_CList);
	DDX_Text(pDX, IDC_EDIT_NAME, m_NodeName);
	DDV_MaxChars(pDX, m_NodeName, 20);
	DDX_Control(pDX, IDC_CHECK3, m_C�ı���ͬĿ¼);
	DDX_Control(pDX, IDC_CHECK5, m_c������Ŀ¼);
}


BEGIN_MESSAGE_MAP(CTXT_OutBox, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_START, &CTXT_OutBox::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_TXT_DIR, &CTXT_OutBox::OnBnClickedButtonTxtDir)
	ON_BN_CLICKED(IDC_BUTTON_TBL, &CTXT_OutBox::OnBnClickedButtonTbl)
	ON_BN_CLICKED(IDC_BUTTON_TBL2, &CTXT_OutBox::OnBnClickedButtonTbl2)
	ON_BN_CLICKED(IDC_CHECK1, &CTXT_OutBox::OnBnClickedCheck1)
	ON_EN_CHANGE(IDC_EDIT_ADDR_H, &CTXT_OutBox::OnEnChangeEditAddrH)
	ON_EN_CHANGE(IDC_EDIT_ADDR_KS_L, &CTXT_OutBox::OnEnChangeEditAddrKsL)
	ON_EN_CHANGE(IDC_EDIT_ADDR_JS_L, &CTXT_OutBox::OnEnChangeEditAddrJsL)
	ON_EN_KILLFOCUS(IDC_EDIT_ADDR_H, &CTXT_OutBox::OnEnKillfocusEditAddrH)
	ON_EN_KILLFOCUS(IDC_EDIT_MIN, &CTXT_OutBox::OnEnKillfocusEditMin)
	ON_EN_KILLFOCUS(IDC_EDIT_MAX, &CTXT_OutBox::OnEnKillfocusEditMax)
	ON_MESSAGE( WM_WQSG_�߳���Ϣ , &CTXT_OutBox::�߳���Ϣ )
	ON_MESSAGE( WM_WQSG_�߳�LOG , &CTXT_OutBox::�߳�LOG )
	ON_BN_CLICKED(IDC_BUTTON_ROM, &CTXT_OutBox::OnBnClickedButtonRom)
	ON_EN_CHANGE(IDC_EDIT_EXT, &CTXT_OutBox::OnEnChangeEditExt)
	ON_BN_CLICKED(IDC_BUTTON1, &CTXT_OutBox::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHECK4, &CTXT_OutBox::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_BUTTON_Add, &CTXT_OutBox::OnBnClickedButtonAdd)
	ON_LBN_SELCHANGE(IDC_LIST2, &CTXT_OutBox::OnLbnSelchangeList2)
	ON_BN_CLICKED(IDC_BUTTON_Del, &CTXT_OutBox::OnBnClickedButtonDel)
	ON_BN_CLICKED(IDC_BUTTON_Edit, &CTXT_OutBox::OnBnClickedButtonEdit)
	ON_EN_KILLFOCUS(IDC_EDIT_NAME, &CTXT_OutBox::OnEnKillfocusEditName)
	ON_EN_CHANGE(IDC_EDIT_NAME, &CTXT_OutBox::OnEnChangeEditName)
	ON_BN_CLICKED(IDC_CHECK3, &CTXT_OutBox::OnBnClickedCheck3)
END_MESSAGE_MAP()
void CTXT_OutBox::OnOK(){}
void CTXT_OutBox::OnCancel(){}
void CTXT_OutBox::OnClose()
{
	CDialog::OnClose();
	CDialog::OnCancel();
}

//--------------------------------------------------------
void CTXT_OutBox::OnBnClickedButtonStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();

	if( m_C�ı���ͬĿ¼.GetCheck() != 0 )
	{
		m_����.m_TXT_DIR = L"";
	}
	else
	{
		if( !::WQSG_IsDir( m_EDIT_TXT_DIR.GetString() ) )
		{
			MessageBoxW( L"�ı�Ŀ¼����" );
			return;
		}
		m_����.m_TXT_DIR = m_EDIT_TXT_DIR;
		if( m_����.m_TXT_DIR.Right(1) != L'\\')
			m_����.m_TXT_DIR += L'\\';
	}
	if( !::WQSG_IsFile( m_EDIT_TBL.GetString() ) )
	{
		MessageBoxW( L"�������·��" );
		return;
	}
	if( (m_Cʹ�ÿ������.GetCheck() != 0 ) && !::WQSG_IsFile( m_EDIT_TBL2.GetString() ) )
	{
		MessageBoxW( L"����������·��" );
		return;
	}
	m_����.m_��֤ = m_C��֤TBL.GetCheck() != 0;
	m_����.m_SubDir = m_c������Ŀ¼.GetCheck() != 0;
	m_����.m_TBL = m_EDIT_TBL;
	m_����.m_TBL2 = (m_Cʹ�ÿ������.GetCheck() != 0)?m_EDIT_TBL2:L"";

	m_����.m_Files.clear();

	u32 val;
	if ( 1 != swscanf( m_EDIT_�κ� , L"%X" , &val ) )
	{
		MessageBoxW( L"����\"�κ�\"!!" );
		GetDlgItem( IDC_EDIT_ADDR_KS_L )->SetFocus();
		return;
	}
	m_����.m_KS = val;
	m_����.m_KS <<= 32;
	m_����.m_JS = m_����.m_KS;

	if ( 1 != swscanf( m_EDIT_��ʼƫ�� , L"%X" , &val ) )
	{
		MessageBoxW( L"����\"��ʼƫ��\"!!" );
		GetDlgItem( IDC_EDIT_ADDR_KS_L )->SetFocus();
		return;
	}
	m_����.m_KS |= val;

	if ( 1 != swscanf( m_EDIT_����ƫ�� , L"%X" , &val ) )
	{
		MessageBoxW( L"����\"����ƫ��\"!!" );
		GetDlgItem( IDC_EDIT_ADDR_JS_L )->SetFocus();
		return;
	}
	m_����.m_JS |= val;

	m_����.m_min = _wtoi( m_EDIT_min.GetString() );
	m_����.m_max = _wtoi( m_EDIT_max.GetString() );

	HANDLE handle;
	if( m_C��Ŀ¼����.GetCheck() != 0 )
	{
		if( !��֤Ext( m_EDIT_EXT ) )
		{
			MessageBox( L"��չ������");
			return;
		}
		m_����.m_Ext = ( m_EDIT_EXT.GetLength() > 0 )?m_EDIT_EXT:L"*";

		m_����.m_ROM_DIR = m_EDIT_Rom;
		if( m_����.m_ROM_DIR.Right(1) != L'\\')
			m_����.m_ROM_DIR += L'\\';

		SendMessage( WM_WQSG_�߳���Ϣ , 0 , (LPARAM)L"���ڵ���..." );
		handle = CreateThread( NULL , NULL
		, ��ͨ����_�ļ���
		, &m_���� , NULL , NULL );
	}
	else
	{
		

		CWQSGFileDialog fileDlg ( TRUE , NULL , NULL , OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT , L"ROM�ļ�(*.*)|*.*|" );
		fileDlg.m_ofn.lpstrTitle = L"ѡ��Ҫ�����ı����ļ�(��ѡ)...";
		fileDlg.m_ofn.lpstrFile = m_�ļ��б���.GetBuffer();
		fileDlg.m_ofn.nMaxFile = 65535;
		fileDlg.m_ofn.lpstrInitialDir = m_����.m_LastDir;

		if( fileDlg.DoModal() != IDOK )
			return;

		m_����.m_LastDir = fileDlg.GetFolderPath();

		POSITION pos = fileDlg.GetStartPosition();
		while( pos )
		{
			m_����.m_Files.push_back( fileDlg.GetNextPathName( pos ) );
		}

		SendMessage( WM_WQSG_�߳���Ϣ , 0 , (LPARAM)L"���ڵ���..." );

		handle = CreateThread( NULL , NULL
			, ��ͨ����_�ļ�
			, &m_���� , NULL , NULL );
	}
	if( handle != NULL )
	{
		CloseHandle( handle );
	}
	else
		SendMessage( WM_WQSG_�߳���Ϣ , 0 , 0 );
}
//--------------------------------------------------------
void CTXT_OutBox::OnBnClickedButtonTxtDir()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	CWQSG_DirDlg DirDlg( m_hWnd );
	WCHAR path[ MAX_PATH ];
	if( !DirDlg.GetPath( path ) )return;
	m_EDIT_TXT_DIR = path;

	UpdateData( FALSE );
}

void CTXT_OutBox::OnBnClickedButtonTbl()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	static CString strPath;

	CWQSGFileDialog dlg( TRUE );
	dlg.m_ofn.lpstrFilter = L"����ļ�(*.TBL,*.TXT)\0*.TBL;*.TXT\0\0";
	dlg.m_ofn.lpstrInitialDir = strPath;

	if( IDOK != dlg.DoModal() )
		return;

	strPath = dlg.GetFolderPath();

	m_EDIT_TBL = dlg.GetPathName();
	UpdateData( FALSE );
}

void CTXT_OutBox::OnBnClickedButtonTbl2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	static CString strPath;

	CWQSGFileDialog dlg( TRUE );
	dlg.m_ofn.lpstrFilter = L"��������ļ�(*.TBL,*.TXT)\0*.TBL;*.TXT\0\0";
	dlg.m_ofn.lpstrInitialDir = strPath;

	if( IDOK != dlg.DoModal() )
		return;

	strPath = dlg.GetFolderPath();

	m_EDIT_TBL2 = dlg.GetPathName();
	UpdateData( FALSE );
}

void CTXT_OutBox::OnBnClickedCheck1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();

	const BOOL ѡ�� = m_C��Ŀ¼����.GetCheck() != 0;
	GetDlgItem( IDC_EDIT_ROM )->EnableWindow( ѡ�� );
	GetDlgItem( IDC_EDIT_EXT )->EnableWindow( ѡ�� );
	GetDlgItem( IDC_CHECK5 )->EnableWindow( ѡ�� );
}

BOOL CTXT_OutBox::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_����.m_hWnd = m_hWnd;
	if( NULL == m_�ļ��б���.GetBuffer(65536) )
	{
		CDialog::OnCancel();
		return FALSE;
	}

	m_C��֤TBL.SetCheck(TRUE);

	m_C�ı���ͬĿ¼.SetCheck( TRUE );
	OnBnClickedCheck3();

	��������();

	return TRUE;
}

void CTXT_OutBox::OnEnChangeEditAddrH()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	�༭����֤ʮ�������ı�( m_EDIT_�κ� , (CEdit*)GetDlgItem( IDC_EDIT_ADDR_H ) , this , TRUE );
}

void CTXT_OutBox::OnEnChangeEditAddrKsL()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	�༭����֤ʮ�������ı�( m_EDIT_��ʼƫ�� , (CEdit*)GetDlgItem( IDC_EDIT_ADDR_KS_L ) , this , TRUE );
}

void CTXT_OutBox::OnEnChangeEditAddrJsL()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	�༭����֤ʮ�������ı�( m_EDIT_����ƫ�� , (CEdit*)GetDlgItem( IDC_EDIT_ADDR_JS_L ) , this , TRUE );
}

void CTXT_OutBox::OnEnKillfocusEditAddrH()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if( m_EDIT_�κ�.GetLength() == 0)
	{
		m_EDIT_�κ� = L"0";
		UpdateData( FALSE );
	}
}

void CTXT_OutBox::OnEnKillfocusEditMin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if( m_EDIT_min.GetLength() == 0)
	{
		m_EDIT_min = L"0";
		UpdateData( FALSE );
	}
}

void CTXT_OutBox::OnEnKillfocusEditMax()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if( m_EDIT_max.GetLength() == 0)
	{
		m_EDIT_max = L"9999";
		UpdateData( FALSE );
	}
}
LRESULT CTXT_OutBox::�߳���Ϣ( WPARAM ���� , LPARAM �ı� )
{
	if( 0 == �ı� )
	{
		AppLog( (WCHAR*)�ı� );
//		MessageBox(L"�������!!");
	}

	WQSG_MAIN_CWND->SendMessage( WM_WQSG_�����ı� , 0 , �ı� );
	return 0;
}

LRESULT CTXT_OutBox::�߳�LOG( WPARAM ���� , LPARAM �ı� )
{
	AppLog( (WCHAR*)�ı� );
	WQSG_MAIN_CWND->SendMessage( WM_WQSG_����LOG�ı� , 0 , (LPARAM)m_LOG.GetString() );
	return 0;
}
void CTXT_OutBox::OnBnClickedButtonRom()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	CWQSG_DirDlg DirDlg( m_hWnd );
	WCHAR path[ MAX_PATH ];
	if( !DirDlg.GetPath( path ) )return;
	m_EDIT_Rom = path;

	UpdateData( FALSE );
}

void CTXT_OutBox::OnEnChangeEditExt()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	ɾ���׿�( m_EDIT_EXT );
	UpdateData( FALSE );
}

void CTXT_OutBox::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_LOG = L"";
	m_CEDIT_LOG.SetWindowTextW( m_LOG );
}

void CTXT_OutBox::OnBnClickedCheck4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if( m_Cʹ�ÿ������.GetCheck() != 0 )
		GetDlgItem( IDC_EDIT_TBL2 )->EnableWindow( TRUE );
	else
		GetDlgItem( IDC_EDIT_TBL2 )->EnableWindow( FALSE );
}


void CTXT_OutBox::��������(void)
{
	while( m_CList.GetCount() )
	{
		m_CList.DeleteString( 0 );
	}

	if( !WQSG_ini.SelConfigName( DEF_V_export ) )
		return ;

	CString str;
	for( long count = WQSG_ini.GetItemCount() , i = 0;
		i < count ; ++i )
	{
		if( WQSG_ini.GetAppName( i , str ) )
			m_CList.AddString( str );
	}
}

void CTXT_OutBox::OnBnClickedButtonAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if( m_NodeName.GetLength() <= 0 )
	{
		return;
	}
	int count = m_CList.GetCount();
	CString str;
	for( int i = 0 ; i < count; ++i )
	{
		m_CList.GetText( i , str );
		if( str == m_NodeName )
		{
			MessageBox( L"�Ѿ�������ͬ������");
			return;
		}
	}
	if( д����() )
	{
		m_CList.SetCurSel( m_CList.AddString( m_NodeName ) );
	}
}

BOOL CTXT_OutBox::д����( )
{
	UpdateData();
	if( !WQSG_ini.SelConfigName( DEF_V_export ) )
	{
		MessageBox( L"ѡ��ڵ�ʧ��" );
		return FALSE;
	}
#define DEF_FN_XYZ( __DEF_x , __DEF_y ) \
	if( !WQSG_ini.SetApp( m_NodeName , __DEF_x , __DEF_y )	){	MessageBox( L"���ʧ��" );	return FALSE;	}

	DEF_FN_XYZ( L"ROMPath" , m_EDIT_Rom )
	DEF_FN_XYZ( L"TXTPath" , m_EDIT_TXT_DIR )
	DEF_FN_XYZ( L"TBLPathName" , m_EDIT_TBL )
	DEF_FN_XYZ( L"TBL2PathName" , m_EDIT_TBL2 )
	DEF_FN_XYZ( L"ExtName" , m_EDIT_EXT )
	DEF_FN_XYZ( L"SegmentAddr" , m_EDIT_�κ� )
	DEF_FN_XYZ( L"BeginOffset" , m_EDIT_��ʼƫ�� )
	DEF_FN_XYZ( L"EndOffset" , m_EDIT_����ƫ�� )
	DEF_FN_XYZ( L"MinLen" , m_EDIT_min )
	DEF_FN_XYZ( L"MaxLen" , m_EDIT_max )
	DEF_FN_XYZ( L"UseDirectory" , (m_C��Ŀ¼����.GetCheck()!=0)?L"1":L"0" )
	DEF_FN_XYZ( L"CheckTblOverlap" , (m_C��֤TBL.GetCheck()!=0)?L"1":L"0" )
	DEF_FN_XYZ( L"UseTBL2" , (m_Cʹ�ÿ������.GetCheck()!=0)?L"1":L"0" )
	DEF_FN_XYZ( L"TxtDirDefault" , (m_C�ı���ͬĿ¼.GetCheck()!=0)?L"1":L"0" )
	DEF_FN_XYZ( L"SubDir" , (m_c������Ŀ¼.GetCheck()!=0)?L"1":L"0" )
#undef DEF_FN_XYZ

	if( !WQSG_ini.Save( WQSG_iniSavePathName ) )
	{
		MessageBox( L"�����ļ�ʧ��" );
		return FALSE;
	}

	return TRUE;
}

void CTXT_OutBox::OnLbnSelchangeList2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	int sel = m_CList.GetCurSel();
	if( sel < 0 )return;

	if( !WQSG_ini.SelConfigName( DEF_V_export ) )
	{
		MessageBox( L"ѡ��ڵ�ʧ��" );
		return ;
	}
	CString NodeName;
	m_CList.GetText( sel , NodeName );

#define DEF_FN_XYZ( __DEF_x , __DEF_y , __DEF_z ) WQSG_ini.GetApp( NodeName , __DEF_x , __DEF_y , __DEF_z )

	DEF_FN_XYZ( L"ROMPath" , m_EDIT_Rom , L"" );
	DEF_FN_XYZ( L"TXTPath" , m_EDIT_TXT_DIR , L"" );
	DEF_FN_XYZ( L"TBLPathName" , m_EDIT_TBL , L"" );
	DEF_FN_XYZ( L"TBL2PathName" , m_EDIT_TBL2 , L"" );
	DEF_FN_XYZ( L"ExtName" , m_EDIT_EXT , L"" );
	DEF_FN_XYZ( L"SegmentAddr" , m_EDIT_�κ� , L"0" );
	DEF_FN_XYZ( L"BeginOffset" , m_EDIT_��ʼƫ�� , L"" );
	DEF_FN_XYZ( L"EndOffset" , m_EDIT_����ƫ�� , L"" );
	DEF_FN_XYZ( L"MinLen" , m_EDIT_min , L"2" );
	DEF_FN_XYZ( L"MaxLen" , m_EDIT_max , L"9999" );
	CString str;

	DEF_FN_XYZ( L"UseDirectory" , str , L"0" );
	m_C��Ŀ¼����.SetCheck( 0 != ::_wtoi( str.GetString() ) );
	UpdateData( FALSE );
	OnBnClickedCheck1();

	DEF_FN_XYZ( L"CheckTblOverlap" , str , L"1" );
	m_C��֤TBL.SetCheck( 0 != ::_wtoi( str.GetString() ) );

	DEF_FN_XYZ( L"UseTBL2" , str , L"0" );
	m_Cʹ�ÿ������.SetCheck( 0 != ::_wtoi( str.GetString() ) );
	UpdateData( FALSE );
	OnBnClickedCheck4();

	DEF_FN_XYZ( L"TxtDirDefault" , str , L"0" );
	m_C�ı���ͬĿ¼.SetCheck( 0 != ::_wtoi( str.GetString() ) );
	UpdateData( FALSE );
	OnBnClickedCheck3();

	DEF_FN_XYZ( L"SubDir" , str , L"0" );
	m_c������Ŀ¼.SetCheck( 0 != ::_wtoi( str.GetString() ) );
#undef DEF_FN_XYZ
	m_NodeName = NodeName;

	UpdateData( FALSE );
}

void CTXT_OutBox::OnBnClickedButtonDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	int sel = m_CList.GetCurSel();
	if( sel < 0 )
	{
		MessageBox( L"��~~~~��ûѡ����ôɾ" );
		return;
	}

	if( !WQSG_ini.SelConfigName( DEF_V_export ) )
	{
		MessageBox( L"ѡ��ڵ�ʧ��" );
		return ;
	}

	CString NodeName;
	m_CList.GetText( sel , NodeName );

	m_CList.DeleteString( sel );
	m_CList.SetCurSel( -1 );

	WQSG_ini.DelApp( NodeName );

	if( !WQSG_ini.Save( WQSG_iniSavePathName ) )
	{
		MessageBox( L"�����ļ�ʧ��" );
	}
}

void CTXT_OutBox::OnBnClickedButtonEdit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	int sel = m_CList.GetCurSel();
	if( sel < 0 )
	{
		MessageBox( L"�ҳ�~~~~��ûѡ����ô��" );
		return;
	}

	if( !WQSG_ini.SelConfigName( DEF_V_export ) )
	{
		MessageBox( L"ѡ��ڵ�ʧ��" );
		return ;
	}

	CString NodeName;
	m_CList.GetText( sel , NodeName );
	if( NodeName != m_NodeName )
	{
		int count = m_CList.GetCount();
		CString str;
		for( int i = 0 ; i < count; ++i )
		{
			m_CList.GetText( i , str );
			if( str == m_NodeName )
			{
				MessageBox( L"�Ѿ�������ͬ������");
				return;
			}
		}
		if( !WQSG_ini.�޸�AppName( NodeName , m_NodeName ) )
		{
			MessageBox( L"�޸�ʧ��" );
			return ;
		}
		m_CList.DeleteString( sel );
		m_CList.InsertString( sel , m_NodeName );
		if( !WQSG_ini.Save( WQSG_iniSavePathName ) )
		{
			MessageBox( L"�����ļ�ʧ��" );
		}
	}
	else if( !д����() )
	{
	}
}

void CTXT_OutBox::OnEnKillfocusEditName()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData( FALSE );
}

void CTXT_OutBox::OnEnChangeEditName()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();

	m_NodeName.Trim( L' ' );
	m_NodeName.Trim( L'��' );

	WCHAR wCh;
	BOOL ��ʾ = FALSE;
	for(int i = 0 ; wCh = m_NodeName.GetAt( i ) ; )
	{
		if(
			( wCh >= L'0' && wCh <= L'9' ) ||
			( wCh >= L'a' && wCh <= L'z' ) ||
			( wCh >= L'A' && wCh <= L'Z' ) ||
			( wCh == L'_' )
			)
		{
			++i;
		}
		else
		{
			��ʾ = TRUE;
			m_NodeName.Delete( i );
		}
	}
	if( ��ʾ )
		AppLog( L"����ֻ��ʹ�� ��ĸ ����  �»��� �Լ� ȫ���ַ�" );


	if( ( ( wCh = m_NodeName.GetAt( 0 ) ) >= L'0' ) && ( wCh <= L'9' ) )
	{
		while( ( ( wCh = m_NodeName.GetAt( 0 ) ) >= L'0' ) && ( wCh <= L'9' ) )
		{
			m_NodeName.Delete( 0 );
		}
		AppLog( L"���Ʋ��������ֿ�ͷ" );
	}

	UpdateData( FALSE );
	((CEdit*)GetDlgItem( IDC_EDIT_NAME ))->SetSel( m_NodeName.GetLength() , m_NodeName.GetLength() ,TRUE );
}

void CTXT_OutBox::AppLog(CString str)
{
	m_LOG += (str + L"\r\n");
	m_CEDIT_LOG.SetWindowTextW( m_LOG );
}

void CTXT_OutBox::OnBnClickedCheck3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem( IDC_EDIT_TXT_DIR )->EnableWindow( m_C�ı���ͬĿ¼.GetCheck() == 0 );
}
