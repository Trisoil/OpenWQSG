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
// �����ı��滻Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WQSG ����(����).h"
#include "�����ı��滻Dlg.h"


// C�����ı��滻Dlg �Ի���

IMPLEMENT_DYNAMIC(C�����ı��滻Dlg, CBaseDialog)


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// C�����ı��滻Dlg �Ի���


C�����ı��滻Dlg::C�����ı��滻Dlg(CWnd* pParent /*=NULL*/)
	: CBaseDialog(C�����ı��滻Dlg::IDD, pParent)
	, m_��������(_T(""))
	, m_�滻Ϊ(_T(""))
	, m_�滻��(_T(""))
{
}

void C�����ı��滻Dlg::DoDataExchange(CDataExchange* pDX)
{
	CBaseDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_��������);
	DDV_MaxChars(pDX, m_��������, 255);
	DDX_Text(pDX, IDC_EDIT2, m_�滻Ϊ);
	DDV_MaxChars(pDX, m_�滻Ϊ, 255);
	DDX_Control(pDX, IDC_CHECK1, m_C�߼��滻);
	DDX_Control(pDX, IDC_CHECK3, m_C�滻��Ŀ¼);
	DDX_Text(pDX, IDC_EDIT3, m_�滻��);
	DDV_MaxChars(pDX, m_�滻��, 260);
}

BEGIN_MESSAGE_MAP(C�����ı��滻Dlg, CBaseDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &C�����ı��滻Dlg::OnBnClickedButton1)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CHECK1, &C�����ı��滻Dlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON2, &C�����ı��滻Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &C�����ı��滻Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &C�����ı��滻Dlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// C�����ı��滻Dlg ��Ϣ�������

BOOL C�����ı��滻Dlg::OnInitDialog()
{
	CBaseDialog::OnInitDialog();

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	OnBnClickedCheck1();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void C�����ı��滻Dlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();

	m_������� = 0;
	m_�滻����[0].DelAll();
	m_�滻����[1].DelAll();
	if( m_��������.GetLength() <= 0 )
	{
		MessageBox( L"�������ݲ���Ϊ��" );
		return;
	}
	if( m_�滻Ϊ.GetLength() <= 0 )
	{
		MessageBox( L"�滻Ϊ����Ϊ��" );
		return;
	}
	m_�滻����[0].AddItem( m_�������� );
	m_�滻����[1].AddItem( m_�滻Ϊ );

	static CWQSGFileDialog_OpenS fopendlg( _T("�ı��ļ�(*.TXT)|*.TXT||") );
	fopendlg.SetWindowTitle( _T("ѡ��Ҫ�滻���ı�...") );

	if( IDOK != fopendlg.DoModal() )
		return;

	POSITION pos = fopendlg.GetStartPosition();
	UINT ���� = 0;
	CString str;
	while( fopendlg.GetNextPathName( str , pos) )
	{
		if( !�滻�ı�( str ) )
			break;
	}
	str.Format( L"�ɹ��滻 %d ��" , m_������� );
	MessageBox( str );
}



void C�����ı��滻Dlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CBaseDialog::OnClose();
	CBaseDialog::OnCancel();
}
void C�����ı��滻Dlg::OnCancel(){}
void C�����ı��滻Dlg::OnOK(){}
void C�����ı��滻Dlg::OnBnClickedCheck1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if( m_C�߼��滻.GetCheck() != 0 )
	{
		GetDlgItem( IDC_EDIT1 )->EnableWindow( FALSE );
		GetDlgItem( IDC_EDIT2 )->EnableWindow( FALSE );
		GetDlgItem( IDC_BUTTON1 )->EnableWindow( FALSE );

		GetDlgItem( IDC_EDIT3 )->EnableWindow( TRUE );
		GetDlgItem( IDC_BUTTON2 )->EnableWindow( TRUE );
		GetDlgItem( IDC_BUTTON3 )->EnableWindow( TRUE );
		GetDlgItem( IDC_BUTTON4 )->EnableWindow( TRUE );
		GetDlgItem( IDC_CHECK3 )->EnableWindow( TRUE );

		
	}
	else
	{
		GetDlgItem( IDC_EDIT1 )->EnableWindow( TRUE );
		GetDlgItem( IDC_EDIT2 )->EnableWindow( TRUE );
		GetDlgItem( IDC_BUTTON1 )->EnableWindow( TRUE );

		GetDlgItem( IDC_EDIT3 )->EnableWindow( FALSE );
		GetDlgItem( IDC_BUTTON2 )->EnableWindow( FALSE );
		GetDlgItem( IDC_BUTTON3 )->EnableWindow( FALSE );
		GetDlgItem( IDC_BUTTON4 )->EnableWindow( FALSE );
		GetDlgItem( IDC_CHECK3 )->EnableWindow( FALSE );
	}
}

void C�����ı��滻Dlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	static CWQSGFileDialog_Open dlg( L"*.TXT,*.TBL|*.TXT;*.TBL||" );
	dlg.SetWindowTitle( L"ѡ��һ��\"�滻��\"" );

	if( dlg.DoModal() != IDOK )
		return;

	m_�滻�� = dlg.GetPathName();
	UpdateData( FALSE );
}

void C�����ı��滻Dlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if( !�����滻��() )
		return;

	static CWQSGFileDialog_OpenS WQSG( _T("*.�ı�|*.TXT|") );
	WQSG.SetWindowTitle( _T("��ѡ��Ҫ�μ��滻���ı�...") );

	if(WQSG.DoModal() != IDOK)
	{
		return;
	}

	POSITION pos = WQSG.GetStartPosition();

	CString str;

	while(WQSG.GetNextPathName(str,pos))
	{
		if( !�滻�ı�( str ) )
			break;
	}

	if( m_������� > 0 )
	{
		str.Format( L"�Ѿ��滻 %u ���ļ�" , m_������� );
		MessageBox( str );
	}
}

void C�����ı��滻Dlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if( !�����滻��() )return;

	CWQSG_DirDlg dlg( m_hWnd );
	WCHAR path[ MAX_PATH * 2 ];
	if( !dlg.GetPath( path ) ) return;

	CString dirPath( path );

	�滻Ŀ¼( path );
	if( m_������� > 0 )
	{
		CString str;
		str.Format( L"�Ѿ��滻 %u ���ļ�" , m_������� );
		MessageBox( str );
	}
	
}

bool C�����ı��滻Dlg::�����滻��(void)
{
	m_������� = 0;
	m_�滻����[0].DelAll();
	m_�滻����[1].DelAll();

	if( m_C�߼��滻.GetCheck() != 0 )
	{
		::CMemTextW tfp;
		if( !tfp.Load( m_�滻��.GetString() , 1024*1024*16 ) )
		{
			MessageBox( L"�滻��\r\n" + m_�滻�� + L"\r\n" + tfp.GetErrTXT() );
			return false;
		}
		const WCHAR* pStr;
		while( pStr = tfp.GetLine() )
		{
			CString str( pStr );
			delete[]pStr;
			if( str.GetLength() <= 0 )
				continue;

			int pos;
			if( ( pos = str.Find( L'=') ) < 0 )
			{
				MessageBox( str + L"\r\n�Ҳ��� \'=\' " );
				return false;;
			}
			CString strL( str.Left( pos ) );
			CString strR( str.Mid( pos + 1 ) );
			if( strR.GetLength() <= 0 )
				continue;

			if( ( pos = m_�滻����[0].AddItem( strL ) ) < 0 )
			{
				MessageBox( str + L"\r\n�ڴ治��??" );
				return false;
			}
			if( m_�滻����[1].AddItem( strR ) < 0 )
			{
				m_�滻����[0].DelItem( pos );
				MessageBox( str + L"\r\n�ڴ治��??" );
				return false;
			}
		}
	}
	else
	{
		if( m_��������.GetLength() == 0 )
		{
			MessageBox(_T("�������ݲ���Ϊ��"));
			return false;
		}
		int pos ;
		if( ( pos = m_�滻����[0].AddItem( m_�������� ) ) < 0 )
		{
			MessageBox( L"\r\n�ڴ治��??" );
			return false;
		}
		if( m_�滻����[1].AddItem( m_�滻Ϊ ) < 0 )
		{
			m_�滻����[0].DelItem( pos );
			MessageBox( L"\r\n�ڴ治��??" );
			return false;
		}
	}
	return true;
}

bool C�����ı��滻Dlg::�滻Ŀ¼(CString ·��)
{
	if( ·��.Right(1) != L'\\' )
		·�� += L'\\';

	WIN32_FIND_DATA FindFileData;

	bool rev = false;
	HANDLE hFind = FindFirstFile( ·�� + L"*.*" , &FindFileData );
	if( hFind != INVALID_HANDLE_VALUE )
	{
		rev = true;
		do
		{
			CString �ļ�( FindFileData.cFileName );

			if( FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
			{
				if( ( m_C�滻��Ŀ¼.GetCheck() != 0 ) && ( �ļ� != "." ) && ( �ļ� != ".." ) )
				{
					if( !�滻Ŀ¼( ·�� + FindFileData.cFileName ) )
					{
						rev = false;
						break;
					}
				}
			}
			else
			{
				CString ��չ��( �ļ�.Right(4) );
				��չ�� = ��չ��.MakeUpper();
				if( ��չ�� == L".TXT" )
				{
					if( !�滻�ı�( ·�� + FindFileData.cFileName ) )
					{
						rev = false;
						break;
					}
				}
			}
		}
		while( FindNextFileW( hFind , &FindFileData ) );
		FindClose( hFind );
	}
	else
	{
		return false;
	}
	return rev;
}

bool C�����ı��滻Dlg::�滻�ı�(CString �ļ�)
{
	::CMemTextW tfp;
	CWQSG_File WFile;

	if( !tfp.Load( �ļ�.GetString() , 1024*1024*16 ) )
	{
		MessageBox( L"�ļ���ʧ��" , �ļ� );
		return false;
	}

	CString �ַ���( tfp.GetText() );
	tfp.Clear();

	CString ��������,�滻Ϊ;
	for( int i = 0; m_�滻����[0].GetItem( i , �������� ) && m_�滻����[1].GetItem( i , �滻Ϊ );++i )
	{
		�ַ���.Replace( �������� , �滻Ϊ );
	}

	if( !WFile.OpenFile( �ļ�.GetString() , 4 , 3 ) )
	{
		MessageBox( L"��ʧ��" , �ļ� );
		return false;
	}
	if( ( 2 != WFile.Write("\xFF\xFE",2) ) ||
		( (�ַ���.GetLength()<<1) != WFile.Write( �ַ���.GetString() , �ַ���.GetLength()<<1 ) ) )
	{
		MessageBox( L"�ļ�ʧ��" , �ļ� );
		return false;
	}
	WFile.Close();

	++m_�������;
	return true;
}
