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
// chazhiSearch.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WQSG ����(����).h"
#include "chazhiSearch.h"


template <typename TYPE_1>
class C�������
{
	HWND m_hWnd;
	CString m_����;
	INT MessageBox( CString str , UINT ��ť = MB_OK )
	{
		return ::MessageBox( m_hWnd , str , m_���� , ��ť );
	}
public:
	C�������( HWND hwnd , CString ���� );
	void ��ʼ����0( CString& log , CString �ļ��� , CWQSG_TypeLinkList<s64>& ��ֵ�� )
	{
		CWQSG_File fp;
		if( !fp.OpenFile( �ļ���.GetString() , 1 , 3 ) )
		{
			MessageBox( L"���ļ�ʧ��" );
			return;
		}
		u64 fileSize;
		fp.GetFileSize( &fileSize );

		CWD_BIN bin;
		{
			u32 ���� = (u32)( fileSize % sizeof(TYPE_1) );
			fileSize -= ����;
			bin.LEN = ( fileSize > (1024*1024*32) )?(1024*1024*32):(u32)fileSize;
		}
		if( NULL == bin.SetBufSize( bin.LEN ) )
		{
			MessageBox( L"�����ڴ�ʧ��" );
			return;
		}
		//-----------------------------------------------------------
		const int itemCount = ��ֵ��.GetCount();
		u64 filePos = 0;
		u32 ������ = 0;
		while( u64 size = (fileSize - filePos) )
		{
			fp.Seek( filePos );

			if( size > bin.LEN )
			{
				if( bin.LEN != fp.Read( bin.BIN , bin.LEN ) )
				{
					MessageBox( L"��ȡ�ļ�ʧ��" );
					return;
				}
				size = bin.LEN;
			}
			else
			{
				if( (u32)size != fp.Read( bin.BIN , (u32)size ) )
				{
					MessageBox( L"��ȡ�ļ�ʧ��" );
					return;
				}
			}
			size -= ( size%sizeof(TYPE_1) );

			TYPE_1* sp1 = (TYPE_1*)bin.BIN;
			TYPE_1* ����A = sp1 + ( (u32)size / sizeof(TYPE_1) );

			if( ����A <= (sp1 + itemCount) )
			{
				break;
			}
			TYPE_1* ����B = ����A - itemCount;
			while( sp1 < ����B )
			{
				TYPE_1 ��һ�� = *(sp1++);
				TYPE_1* sp0 = sp1;

				u32 ƫ�Ƽ��� = 1;
				int i_count;
				for( i_count = 0 ; (i_count < itemCount) && ( sp1 <= ����A );
					++i_count , ++ƫ�Ƽ��� , ++sp1 )
				{
#ifdef DEBUG
					s64 fffffff = ��һ��;
#endif
					s64 f1 = *sp1 - ��һ��;
					��һ�� = *sp1;
					s64 f2;
					if( (!��ֵ��.GetItem( i_count , f2 )) || ( f1 != f2 ) )
					{
						sp1 = sp0;
						ƫ�Ƽ��� = 1;
						break;
					}
					INT X = 0;
				}

				if( itemCount == i_count )
				{
					CString str;
					str.Format( L"%08X:%08X\r\n" , (INT)(filePos>>32) , (INT)(filePos&0xFFFFFFFF) );
					log += str;
					if( ++������ > 10000 )
					{
						filePos = fileSize;
						MessageBox( L"Ϊ�˰�ȫ���,ֻ��ʾǰ10000��" );
						break;
					}
				}
				filePos += ( ƫ�Ƽ��� * sizeof(TYPE_1) );
			}
		}
		MessageBox( L"���ҽ���" );
	}
	void ��ʼ����1( CString& log , CString �ļ��� , CWQSG_TypeLinkList<s64>& ��ֵ�� )
	{
		WQSG_File_mem mapfp;
		if( !mapfp.OpenFile( �ļ���.GetString() , 3 ) )
		{
			MessageBox( L"���ļ�ʧ��" );
			return;
		}
		const s64 fileSize = mapfp.GetFileSize( );
		//-----------------------------------------------------------
		const int itemCount = ��ֵ��.GetCount();
		s64 filePos = 0;
		u32 ������ = 0;
		const u32 len8 = 1024*1024*128;
		while( filePos < fileSize )
		{
			u64 size = (fileSize - filePos);
			const u8* bin8;
			if( size > len8 )
			{
				bin8 = mapfp.GetPtr( filePos , len8 );
				size = len8;
			}
			else
			{
				bin8 = mapfp.GetPtr( filePos , (u32)size );
			}

			if( NULL == bin8 )
			{
				MessageBox( L"��ȡ�ļ�ʧ��" );
				return;
			}

			size -= ( size%sizeof(TYPE_1) );

			const TYPE_1* sp1 = (TYPE_1*)bin8;
			const TYPE_1* ����A = sp1 + ( (u32)size / sizeof(TYPE_1) );

			if( ����A <= (sp1 + itemCount) )
			{
				mapfp.Free();
				break;
			}
			const TYPE_1* ����B = ����A - itemCount;
			while( sp1 < ����B )
			{
				TYPE_1 ��һ�� = *(sp1++);
				const TYPE_1* sp0 = sp1;

				u32 ƫ�Ƽ��� = 1;
				int i_count;
				for( i_count = 0 ; (i_count < itemCount) && ( sp1 <= ����A );
					++i_count , ++ƫ�Ƽ��� , ++sp1 )
				{
#ifdef DEBUG
					s64 fffffff = ��һ��;
#endif
					s64 f1 = *sp1 - ��һ��;
					��һ�� = *sp1;
					s64 f2;
					if( (!��ֵ��.GetItem( i_count , f2 )) || ( f1 != f2 ) )
					{
						sp1 = sp0;
						ƫ�Ƽ��� = 1;
						break;
					}
					INT X = 0;
				}

				if( itemCount == i_count )
				{
					CString str;
					str.Format( L"%08X:%08X\r\n" , (INT)(filePos>>32) , (INT)(filePos&0xFFFFFFFF) );
					log += str;
					if( ++������ > 10000 )
					{
						filePos = fileSize;
						MessageBox( L"Ϊ�˰�ȫ���,ֻ��ʾǰ10000��" );
						break;
					}
				}
				filePos += ( ƫ�Ƽ��� * sizeof(TYPE_1) );
			}
			mapfp.Free();
		}
		MessageBox( L"���ҽ���" );
	}
};
#define DEF_XXX( DEF_X ) C�������<DEF_X>::C�������( HWND hwnd , CString ���� ): m_hWnd( hwnd ), m_����(����){}
DEF_XXX(u8)
DEF_XXX(u16)
DEF_XXX(u32)
#undef DEF_XXX
// C�������Dlg �Ի���
IMPLEMENT_DYNAMIC(CchazhiSearch, CDialog)
CchazhiSearch::CchazhiSearch(CWnd* pParent /*=NULL*/)
	: CDialog(CchazhiSearch::IDD, pParent)
	, m_input(_T(""))
	, m_�ֽ�����(_T("���ֽ�"))
	, m_��������(_T("ʮ������"))
	, m_log(_T(""))
	, m_�ļ�·��(_T(""))
{
}

void CchazhiSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_input);
	DDV_MaxChars(pDX, m_input, 10);
	DDX_CBString(pDX, IDC_COMBO2, m_�ֽ�����);
	DDX_CBString(pDX, IDC_COMBO1, m_��������);
	DDX_Text(pDX, IDC_EDIT1, m_log);
	DDX_Control(pDX, IDC_CHECK1, m_C�ߵͽ���);
	DDX_Text(pDX, IDC_EDIT3, m_�ļ�·��);
	DDV_MaxChars(pDX, m_�ļ�·��, 255);
	DDX_Control(pDX, IDC_LIST99, m_CList);
}

BEGIN_MESSAGE_MAP(CchazhiSearch, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON1, &CchazhiSearch::OnBnClickedButton1)
	ON_CBN_SELENDOK(IDC_COMBO1, &CchazhiSearch::OnCbnSelendokCombo1)
	ON_EN_CHANGE(IDC_EDIT2, &CchazhiSearch::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON4, &CchazhiSearch::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CchazhiSearch::OnBnClickedButton3)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CchazhiSearch::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_BUTTON5, &CchazhiSearch::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_CHECK1, &CchazhiSearch::OnBnClickedCheck1)
END_MESSAGE_MAP()
BOOL CchazhiSearch::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_CList.InsertColumn( 0 , L"����ֵ" , 0 , 60 );
	m_CList.InsertColumn( 1 , L"��ֵ" , 0 , 60 );

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}
// �����Ի��������С����ť������Ҫ����Ĵ���
void CchazhiSearch::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialog::OnClose();
	CDialog::OnCancel();
}
void CchazhiSearch::OnCancel(){}
void CchazhiSearch::OnOK(){}
void CchazhiSearch::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if( m_input.GetLength() <= 0 )
	{
		MessageBox( L"������ӿհ׵�ֵ" );
		return;
	}
	UINT val = 0;

	if( m_�������� == L"ʮ������" )
	{
		swscanf( m_input.GetString() , L"%x" , &val );
	}
	else
	{
		val = _wtoi( m_input.GetString() );
	}
	WCHAR* ��ʽ = L"??";
	if( m_�ֽ����� == L"���ֽ�" )
	{
		if( val > 0xFF )
		{
			MessageBox( L"�������ֹ���" );
			return;
		}
		��ʽ = L"%02X";
	}
	else if( m_�ֽ����� == L"˫�ֽ�" )
	{
		if( val > 0xFFFF )
		{
			MessageBox( L"�������ֹ���" );
			return;
		}
		��ʽ = L"%04X";
		if( m_C�ߵͽ���.GetCheck() != 0 )
		{
			u8* ptr = (u8*)&val;
			u8 tmp = ptr[0];
			ptr[0] = ptr[1];
			ptr[1] = tmp;
		}
	}
	else if( m_�ֽ����� == L"���ֽ�" )
	{
		if( val > 0xFFFFFFFF )
		{
			MessageBox( L"�������ֹ���" );
			return;
		}
		��ʽ = L"%08X";
		if( m_C�ߵͽ���.GetCheck() != 0 )
		{
			u8* ptr = (u8*)&val;
			u8 tmp = ptr[0];
			ptr[0] = ptr[1];
			ptr[1] = tmp;

			tmp = ptr[2];
			ptr[2] = ptr[3];
			ptr[3] = tmp;
		}
	}
	else
	{
		MessageBox( L"δ֪����,�������ֹ���" );
		return;
	}
	//------------------------------------
	CString str;
	str.Format( ��ʽ , val );
	int pos = m_CList.InsertItem( m_CList.GetItemCount() , str );
	if( pos >= 0 )
		ˢ�²�ֵ( pos );
}

void CchazhiSearch::OnCbnSelendokCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	UpdateData();
//	m_input = L"";
//	UpdateData( FALSE );
}
#include<2/wqsg_afx.h>
void CchazhiSearch::OnEnChangeEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if( m_�������� == L"ʮ������" )
		�༭����֤ʮ�������ı�( m_input , (CEdit*)GetDlgItem( IDC_EDIT2 ) , this , FALSE );
	else
		�༭����֤ʮ�����ı�( m_input , (CEdit*)GetDlgItem( IDC_EDIT2 ) , this );
}

void CchazhiSearch::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if( m_�ļ�·��.GetLength() <= 0 )
	{
		MessageBox( L"��ѡ��һ���ļ�" );
		return;
	}
	m_��ֵ��.DelAll();
	const int count = m_CList.GetItemCount();
	if( count <= 1 )
	{
		MessageBox( L"��������" );
		return;
	}
	CString str;
	for( int i = 1 ; i < m_CList.GetItemCount() ; ++i )
	{
		str = m_CList.GetItemText( i , 1 );
		LONGLONG val1;
		if( 1 != swscanf( str.GetString() , L"%lld" , &val1 ) )
		{
			MessageBox( L"δ֪����1" );
			return;
		}
		//----------------------------------
		if( m_��ֵ��.AddItem( val1 ) < 0 )
		{
			MessageBox( L"δ֪����2" );
			return;
		}
	}
	CString ����;
	GetWindowTextW( ���� );
	m_log = L"";
	if( m_�ֽ����� == L"���ֽ�"	)
	{
		C�������<u8> xxx( m_hWnd , ���� );
		xxx.��ʼ����1(m_log , m_�ļ�·�� , m_��ֵ�� );
	}
	else if( m_�ֽ����� == L"˫�ֽ�" )
	{
		C�������<u16> xxx( m_hWnd , ���� );
		xxx.��ʼ����1(m_log , m_�ļ�·�� , m_��ֵ�� );
	}
	else if( m_�ֽ����� == L"���ֽ�" )
	{
		C�������<u32> xxx( m_hWnd , ���� );
		xxx.��ʼ����1(m_log , m_�ļ�·�� , m_��ֵ�� );
	}
	else
	{
		MessageBox( L"δ֪����ģʽ?" );
	}
	UpdateData( FALSE );
	m_��ֵ��.DelAll();
}
void CchazhiSearch::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	m_CList.DeleteAllItems();

	m_log = L"";
	UpdateData( FALSE );
}

void CchazhiSearch::OnCbnSelchangeCombo2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnBnClickedButton3();
}

void CchazhiSearch::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	static CWQSGFileDialog_Open dlg;

	if( dlg.DoModal() != IDOK )
		return;

	m_�ļ�·�� = dlg.GetPathName();
	UpdateData( FALSE );
}

void CchazhiSearch::ˢ�²�ֵ( INT  startPos )
{
	m_CList.SetRedraw( FALSE );
	m_CList.SetItemText( 0 , 1 , L"0" );

	if( startPos < 1 )
		startPos = 1;

	for( int i = startPos , count = m_CList.GetItemCount();
		i < count ; ++i )
	{
		CString str1( m_CList.GetItemText( i -1 , 0 ) );
		CString str2( m_CList.GetItemText( i , 0 ) );
		LONGLONG val1 , val2 ;
		swscanf( str1.GetString() , L"%X" , &val1 );
		swscanf( str2.GetString() , L"%X" , &val2 );

		val2 -= val1;

		str1.Format( L"%lld" , val2 );

		m_CList.SetItemText( i , 1 , str1 );
	}

	m_CList.SetRedraw( TRUE );
}

void CchazhiSearch::OnBnClickedCheck1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_CList.SetRedraw( FALSE );

	for( int i = 0 , count = m_CList.GetItemCount();
		i < count ; ++i )
	{
		CString str1( m_CList.GetItemText( i , 0 ) );
		UINT val1 ;
		swscanf( str1.GetString() , L"%X" , &val1 );

		if( m_�ֽ����� == L"���ֽ�" )
		{
			m_CList.SetRedraw( TRUE );
			return;
		}
		else if( m_�ֽ����� == L"˫�ֽ�" )
		{
			u8* ptr = (u8*)&val1;
			u8 tmp = ptr[0];
			ptr[0] = ptr[1];
			ptr[1] = tmp;
			str1.Format( L"%04X" , val1 );
		}
		else if( m_�ֽ����� == L"���ֽ�" )
		{
			u8* ptr = (u8*)&val1;
			u8 tmp = ptr[0];
			ptr[0] = ptr[3];
			ptr[3] = tmp;
			tmp = ptr[1];
			ptr[1] = ptr[2];
			ptr[2] = tmp;
			str1.Format( L"%08X" , val1 );
		}
		else
		{
			m_CList.SetRedraw( TRUE );
			return;
		}
		m_CList.SetItemText( i , 0 , str1 );
	}

	ˢ�²�ֵ( 1 );

	m_CList.SetRedraw( TRUE );
}
