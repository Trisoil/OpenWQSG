/*  OpenWQSG - Ps2MemoryCard
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

// Ps2MemoryCardDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Ps2MemoryCard.h"
#include "Ps2MemoryCardDlg.h"
#include "VPscMc.h"
#include "SelDir.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPs2MemoryCardDlg �Ի���

int CALLBACK ItemSort( LPARAM a , LPARAM b , LPARAM c )
{
	SItemSortData* pData1 = (SItemSortData*)((c&0xF0000000)?a:b);
	SItemSortData* pData2 = (SItemSortData*)((c&0xF0000000)?b:a);

	switch ( c & 0x0FFFFFFF )
	{
	case 1:
		return pData1->m_nSize - pData2->m_nSize;
		break;
	case 2:
		return pData1->m_strFileName.Compare( pData2->m_strFileName );
		break;
	}

	return pData1->m_strTitleName.Compare( pData2->m_strTitleName );
}

CPs2MemoryCardDlg::CPs2MemoryCardDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPs2MemoryCardDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPs2MemoryCardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_cList1);
	DDX_Control(pDX, IDC_LIST2, m_cList2);
}

BEGIN_MESSAGE_MAP(CPs2MemoryCardDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_OPEN_MC1, &CPs2MemoryCardDlg::OnBnClickedButtonOpenMc1)
	ON_BN_CLICKED(IDC_BUTTON_CREATE_MC1, &CPs2MemoryCardDlg::OnBnClickedButtonCreateMc1)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_MC1, &CPs2MemoryCardDlg::OnBnClickedButtonSaveMc1)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_BIN1, &CPs2MemoryCardDlg::OnBnClickedButtonSaveBin1)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT_PSU1, &CPs2MemoryCardDlg::OnBnClickedButtonImportPsu1)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT_PSU1, &CPs2MemoryCardDlg::OnBnClickedButtonExportPsu1)
	ON_BN_CLICKED(IDC_BUTTON_SEL_PSU_DIR, &CPs2MemoryCardDlg::OnBnClickedButtonSelPsuDir)
	ON_BN_CLICKED(IDC_BUTTON_ABOUT, &CPs2MemoryCardDlg::OnBnClickedButtonAbout)
	ON_BN_CLICKED(IDC_BUTTON1, &CPs2MemoryCardDlg::OnBnClickedButton1)

	ON_NOTIFY(HDN_ITEMCLICK, 0, &CPs2MemoryCardDlg::OnHdnItemclickList)
	ON_NOTIFY(LVN_DELETEITEM, IDC_LIST1, &CPs2MemoryCardDlg::OnLvnDeleteitemList)
	ON_NOTIFY(LVN_DELETEITEM, IDC_LIST2, &CPs2MemoryCardDlg::OnLvnDeleteitemList)
END_MESSAGE_MAP()


// CPs2MemoryCardDlg ��Ϣ�������

BOOL CPs2MemoryCardDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	HDITEM hi = {};
	hi.mask = HDI_FORMAT;

	m_cList1.SetExtendedStyle( m_cList1.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );

	m_cList1.InsertColumn( 0 , L"�浵��" , 0 , 450 );
	m_cList1.InsertColumn( 1 , L"size" , 0 , 40 );
	m_cList1.InsertColumn( 2 , L"ԭ��" , 0 , 180 );

	m_cList1.GetHeaderCtrl()->GetItem( 0 , &hi );
	hi.fmt |= HDF_SORTUP;
	m_cList1.GetHeaderCtrl()->SetItem( 0 , &hi );

	m_cList2.SetExtendedStyle( m_cList2.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );

	m_cList2.InsertColumn( 0 , L"�浵��" , 0 , 450 );
	m_cList2.InsertColumn( 1 , L"size" , 0 , 40 );
	m_cList2.InsertColumn( 2 , L"ԭ��" , 0 , 180 );

	m_cList2.GetHeaderCtrl()->GetItem( 0 , &hi );
	hi.fmt |= HDF_SORTUP;
	m_cList2.GetHeaderCtrl()->SetItem( 0 , &hi );

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPs2MemoryCardDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
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
HCURSOR CPs2MemoryCardDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPs2MemoryCardDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialog::OnClose();
}

void CPs2MemoryCardDlg::OnBnClickedButtonOpenMc1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	static CWQSGFileDialog_Open dlg( L"*.ps2;*.bin|*.ps2;*.bin||" );
	if( IDOK != dlg.DoModal() )
		return;

	if( !m_Mc1.LoadMc( dlg.GetPathName() ) )
	{
		SetDlgItemText( IDC_EDIT1 , L"" );
		m_Mc1.FormatMc();
		UpdateMcUI();
		MessageBox( L"���ؼ��俨ʧ��" );
		return;
	}

	SetDlgItemText( IDC_EDIT1 , dlg.GetPathName() );
	UpdateMcUI();
}

void CPs2MemoryCardDlg::OnBnClickedButtonCreateMc1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText( IDC_EDIT1 , L"" );
	if( !m_Mc1.FormatMc() )
	{
		MessageBox( L"��ʱ��֧��" );
	}
	UpdateMcUI();
}

void CPs2MemoryCardDlg::OnBnClickedButtonSaveMc1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if( !m_Mc1.isOpen() )
		return ;

	static CWQSGFileDialog_Save dlg( L"*.ps2|*.ps2||" , L"ps2" );
	if( IDOK != dlg.DoModal() )
		return;

	if( m_Mc1.SaveMc( dlg.GetPathName() ) )
	{
		SetDlgItemText( IDC_EDIT1 , dlg.GetPathName() );
	}
	else
	{
		MessageBox( L"������俨ʧ��" );
	}
}

void CPs2MemoryCardDlg::OnBnClickedButtonImportPsu1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if( !m_Mc1.isOpen() )
		return ;

	static CWQSGFileDialog_OpenS dlg( L"*.psu|*.psu||" );
	if( IDOK != dlg.DoModal() )
		return;

	CString strName;
	POSITION pos = dlg.GetStartPosition();
	while( dlg.GetNextPathName( strName , pos ) )
	{
		m_Mc1.Bak();
		if( !m_Mc1.Import_Psu( strName ) )
		{
			m_Mc1.UnBak();
			UpdateMcUI();
			MessageBox( L"����PSUʧ��" , strName );
			return;
		}
	}
	UpdateMcUI();
	MessageBox( L"����ɹ�" );
}

void CPs2MemoryCardDlg::OnBnClickedButtonExportPsu1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if( !m_Mc1.isOpen() )
		return ;

	POSITION pos = m_cList1.GetFirstSelectedItemPosition();
	const int iIndex = m_cList1.GetNextSelectedItem( pos );
	if( iIndex == -1 )
		return ;

	const CString str = m_cList1.GetItemText( iIndex , 2 );

	CWQSGFileDialog_Save dlg( L"*.psu|*.psu||" , L"psu" , str );
	if( IDOK != dlg.DoModal() )
		return;

	char* pName = WQSG_W_char( str.GetString() , 932 );
	if( m_Mc1.Export_Psu( dlg.GetPathName() , pName ) )
	{
		delete[]pName;
		MessageBox( L"�����ɹ�" );
	}
	else
	{
		delete[]pName;
		MessageBox( L"����PSUʧ��" );
	}
}

void CPs2MemoryCardDlg::UISort( CListCtrl& a_cList )
{
	CHeaderCtrl& cc = *a_cList.GetHeaderCtrl();

	HDITEM hi = {};
	hi.mask = HDI_FORMAT;

	u32 uFlag = 0;
	for( int i = 0 ; i < cc.GetItemCount() ; ++i )
	{
		cc.GetItem( i , &hi );

		if( hi.fmt & (HDF_SORTUP|HDF_SORTDOWN) )
		{
			uFlag = i;
			break;
		}
	}

	if( hi.fmt & HDF_SORTDOWN )
		uFlag |= 0xF0000000;

	a_cList.SortItems( &ItemSort , uFlag );
}

void CPs2MemoryCardDlg::UpdateMcUI()
{
	m_cList1.DeleteAllItems();
	if( !m_Mc1.isOpen() )
		return ;

	std::vector<CVPscMc::SFileInfo> files;
	if( !m_Mc1.GetFiles( files , "" ) )
	{
		MessageBox( L"��ȡ�ļ��б�ʧ��" );
		return;
	}

	m_cList1.SetRedraw( FALSE );
	for( std::vector<CVPscMc::SFileInfo>::iterator it = files.begin() ;
		it != files.end() ; ++it )
	{
		const CVPscMc::SFileInfo& info = *it;

		SItemSortData data;

		CWQSG_memFile mf;
		if( m_Mc1.Vmc_ReadFile( mf , info.szName , "icon.sys" ) )
		{
			mf.Seek( 0xC0 );

			char buf[0x100];
			if( sizeof(buf) != mf.Read( buf , sizeof(buf) ) )
			{
				MessageBox( L"ȡ�浵�ļ���ʧ��" );
				break;
			}

			WCHAR* pTitle = WQSG_char_W( buf , 932 );
			data.m_strTitleName = pTitle;
			delete[]pTitle;
		}
		else
		{
			WCHAR* pX = WQSG_char_W( info.szName , 932 );
			data.m_strTitleName = pX;
			delete[]pX;
		}

		data.m_nSize = info.uSize;

		WCHAR* pX = WQSG_char_W( info.szName , 932 );
		data.m_strFileName = pX;
		delete[]pX;

		UIInsert( m_cList1 , data );
	}
	//--------------------------
	UISort( m_cList1 );
	//--------------------------
	m_cList1.SetRedraw( TRUE );

	u32 count = 0;
	if( m_Mc1.GetFreeClusterCount( count ) )
	{
		CStringW str;
		str.Format( L"���п� = %d , size = %d\r\n" , count , m_Mc1.GetPreClusterSize() * count );
		OutputDebugString( str );
	}
	else
	{
		CStringW str;
		str.Format( L"ȡ���п�ʧ��,���п� = %d , size = %d\r\n" , count , m_Mc1.GetPreClusterSize() * count );
		OutputDebugString( str );
	}
}

void CPs2MemoryCardDlg::UpdateDirUI()
{
	m_cList2.DeleteAllItems();
	CString strDir;
	GetDlgItemText( IDC_EDIT2 , strDir );

	if( strDir.GetLength() == 0 )
		return;

	strDir += L"\\";

	WIN32_FIND_DATAW findData;
	const HANDLE hFind = FindFirstFileW( strDir + L"*.psu" , &findData );
	if( hFind == INVALID_HANDLE_VALUE )
		return;

	m_cList2.SetRedraw( FALSE );
	do
	{
		if( findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
			continue;

		SPsuData files;
		if( !Load_Psu( strDir + findData.cFileName , files ) )
			continue;

		SItemSortData data;

		TPsuFile::iterator it = files.m_files.find( "icon.sys" );
		if( it != files.m_files.end() )
		{
			CWQSG_memFile mf;
			mf.Write( &it->second.at(0) , it->second.size() );

			mf.Seek( 0xC0 );

			char buf[0x100];
			if( sizeof(buf) != mf.Read( buf , sizeof(buf) ) )
			{
				MessageBox( L"ȡ�浵�ļ���ʧ��" );
				break;
			}

			WCHAR* pTitle = WQSG_char_W( buf , 932 );
			data.m_strTitleName = pTitle;
			delete[]pTitle;
		}
		else
		{
			WCHAR* pX = WQSG_char_W( files.m_strName , 932 );
			data.m_strTitleName = pX;
			delete[]pX;
		}

		data.m_nSize = files.m_files.size();

		WCHAR* pX = WQSG_char_W( files.m_strName , 932 );
		data.m_strFileName = pX;
		delete[]pX;

		UIInsert( m_cList2 , data );
	}
	while( FindNextFileW( hFind , &findData ) );
	//--------------------------
	UISort( m_cList2 );
	//--------------------------
	m_cList2.SetRedraw( TRUE );
}

void CPs2MemoryCardDlg::UIInsert( CListCtrl& a_cList , const SItemSortData& a_Data )
{
	const int iIndex = a_cList.InsertItem( a_cList.GetItemCount() , a_Data.m_strTitleName );

	if( iIndex == -1 )
	{
		MessageBox( L"���ʧ��" );
		return;
	}

	SItemSortData* pData = new SItemSortData;
	a_cList.SetItemData( iIndex , (DWORD_PTR)pData );

	*pData = a_Data;

	CString str;
	str.Format( L"%d" , pData->m_nSize );
	a_cList.SetItemText( iIndex , 1 , str );
	a_cList.SetItemText( iIndex , 2 , pData->m_strFileName );
}
// 00833A00 map? 00000000 ,��֮ȫFF
// 0083DF00 MAP  0000A500
void CPs2MemoryCardDlg::OnBnClickedButtonAbout()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strAppName;
	strAppName.LoadString( IDS_APP_NAME );

	CString strAppVer;
	strAppVer.LoadString( IDS_APP_VER );

	CString strAuthor1;
	strAuthor1.LoadString( IDS_APP_AUTHOR );

	CString strAuthor2;
	strAuthor2.LoadString( IDS_APP_AUTHOR2 );

	WQSG_About( m_hIcon , m_hWnd , L"���ڱ����" , strAppName + L"\r\nv" + strAppVer ,
		L"��Ŀsvn : <A HREF=\"http://code.google.com/p/openwqsg\">http://code.google.com/p/openwqsg</A>\r\n"
		L"������svn : <A HREF=\"http://code.google.com/p/wqsglib\">http://code.google.com/p/wqsglib</A>\r\n                 <A HREF=\"http://wqsg.ys168.com\">http://wqsg.ys168.com</A>\r\n" ,
		strAuthor2 + L"(" + strAuthor1 + L")" );
}

bool CPs2MemoryCardDlg::Load_Psu( const CStringW& a_strFile , SPsuData& a_Files )
{
	CWQSG_File fp;
	if( !fp.OpenFile( a_strFile.GetString() , 1 , 3 ) )
		return false;

	SPsu_header psu_head = {};
	if( sizeof(psu_head) != fp.Read( &psu_head , sizeof(psu_head) ) )
		return false;

	if( !(psu_head.attr & DF_DIRECTORY) )
		return false;

	if( !(psu_head.attr & DF_EXISTS) )
		return false;

	{
		static const SPsu_header psu_x = {};

		if( psu_head.unknown_1_u16 != 0 || psu_head.unknown_2_u64 != 0 || psu_head.EMS_used_u64 != 0 )
			return false;

		if( memcmp( psu_head.unknown_3_24_bytes , psu_x.unknown_3_24_bytes , sizeof(psu_x.unknown_3_24_bytes) ) != 0 ||
			memcmp( psu_head.unknown_4_416_bytes , psu_x.unknown_4_416_bytes , sizeof(psu_x.unknown_4_416_bytes) ) != 0)
			return false;
	}


	a_Files.m_strName = (const char*)psu_head.name;
	a_Files.m_files.clear();

	for( u32 i = 0 ; i < psu_head.size ; ++i )
	{
		SPsu_header head1 = {};
		if( sizeof(head1) != fp.Read( &head1 , sizeof(head1) ) )
			return false;

		{
			static const SPsu_header psu_x = {};

			if( head1.unknown_1_u16 != 0 || head1.unknown_2_u64 != 0 || head1.EMS_used_u64 != 0 )
				return false;

			if( memcmp( head1.unknown_3_24_bytes , psu_x.unknown_3_24_bytes , sizeof(psu_x.unknown_3_24_bytes) ) != 0 ||
				memcmp( head1.unknown_4_416_bytes , psu_x.unknown_4_416_bytes , sizeof(psu_x.unknown_4_416_bytes) ) != 0)
				return false;
		}

		if( head1.attr & DF_DIRECTORY )
		{
			if( head1.size == 0 )
				continue;

			return false;
		}

		if( !(head1.attr & DF_EXISTS) )
			return false;

		std::vector<u8>& buff = a_Files.m_files[std::string((const char*)head1.name)];

		if( head1.size )
		{
			buff.resize( head1.size , 0 );

			if( head1.size != fp.Read( &buff[0] , head1.size ) )
				return false;

			const u32 p = head1.size % 0x400;

			if( p )
				fp.Seek( fp.Tell() + (0x400 - p) );

			if( 0 )
			{
				CWQSG_File FP;
				if( FP.OpenFile( L"D:\\WQSG\\ICON.BIN" , 4 , 3 ) )
				{
					FP.Write( &buff[0] , head1.size );
					FP.Close();
				}
			}
		}
	}

	return true;
}

void CPs2MemoryCardDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	static CWQSGFileDialog_Open dlg1( L"*.psu|*.psu||" );
	if( IDOK != dlg1.DoModal() )
		return;

	static CWQSGFileDialog_Open dlg2( L"*.psu|*.psu||" );
	if( IDOK != dlg2.DoModal() )
		return;

	SPsuData psu1;
	SPsuData psu2;

	if( !Load_Psu( dlg1.GetPathName() , psu1 ) )
	{
		MessageBox( L"��ȡʧ��" , dlg1.GetPathName() );
		return;
	}

	if( !Load_Psu( dlg2.GetPathName() , psu2 ) )
	{
		MessageBox( L"��ȡʧ��" , dlg2.GetPathName() );
		return;
	}

	if( psu1.m_strName != psu2.m_strName )
	{
		MessageBox( L"�浵��ͬ" );
		return;
	}

	if( psu1.m_files.size() != psu2.m_files.size() )
	{
		MessageBox( L"�ļ�������" );
		return;
	}

	for( TPsuFile::const_iterator it1 = psu1.m_files.begin() ;
		it1 != psu1.m_files.end() ; ++it1 )
	{
		TPsuFile::const_iterator it2 = psu2.m_files.find(it1->first);
		if( it2 == psu2.m_files.end() )
		{
			MessageBox( L"�ļ�������" );
			return;
		}

		if( it1->second.size() != it2->second.size() )
		{
			CString str;
			str = it1->first.c_str();
			MessageBox( L"���ݳ��Ȳ���" , str );
			return;
		}

		if( memcmp( &(it1->second[0]) , &(it2->second[0]) , it2->second.size() ) )
		{
			CString str;
			str = it1->first.c_str();
			MessageBox( L"���ݲ���" , str );
			return;
		}
	}

	MessageBox( L"���" );
}

void CPs2MemoryCardDlg::OnBnClickedButtonSaveBin1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if( !m_Mc1.isOpen() )
		return ;

	static CWQSGFileDialog_Save dlg( L"*.bin|*.bin||" , L"bin" );
	if( IDOK != dlg.DoModal() )
		return;

	if( m_Mc1.SaveMcNoEcc( dlg.GetPathName() ) )
	{
		SetDlgItemText( IDC_EDIT1 , dlg.GetPathName() );
	}
	else
	{
		MessageBox( L"������俨ʧ��" );
	}
}

void CPs2MemoryCardDlg::OnHdnItemclickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	if( phdr->iButton != 0 )
		return;

	CHeaderCtrl& cc = *(CHeaderCtrl*)CHeaderCtrl::FromHandle( phdr->hdr.hwndFrom );

	HDITEM hi = {};
	hi.mask = HDI_FORMAT;

	cc.GetItem( phdr->iItem , &hi );
	if( hi.fmt & (HDF_SORTUP|HDF_SORTDOWN) )
	{
	}
	else
	{
		for( int i = 0 ; i < cc.GetItemCount() ; ++i )
		{
			cc.GetItem( i , &hi );

			const int oldFmt = hi.fmt & (HDF_SORTUP|HDF_SORTDOWN);
			if( oldFmt )
			{
				hi.fmt &= ~(HDF_SORTUP|HDF_SORTDOWN);
				cc.SetItem( i , &hi );
				break;
			}
		}
		cc.GetItem( phdr->iItem , &hi );
	}

	const int oldFmt = hi.fmt & (HDF_SORTUP|HDF_SORTDOWN);
	hi.fmt &= ~(HDF_SORTUP|HDF_SORTDOWN);
	if( oldFmt & HDF_SORTUP )
		hi.fmt |= HDF_SORTDOWN;
	else
		hi.fmt |= HDF_SORTUP;

	cc.SetItem( phdr->iItem , &hi );

	if( m_cList1.GetHeaderCtrl() == &cc )
		UISort( m_cList1 );
	else if( m_cList2.GetHeaderCtrl() == &cc )
		UISort( m_cList2 );
}

void CPs2MemoryCardDlg::OnLvnDeleteitemList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	CListCtrl* pList = (CListCtrl*)CListCtrl::FromHandle( pNMLV->hdr.hwndFrom );

	delete (SItemSortData*)pList->GetItemData( pNMLV->iItem );
}


void CPs2MemoryCardDlg::OnBnClickedButtonSelPsuDir()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString oldDir;

	GetDlgItemText( IDC_EDIT2 , oldDir );

	CSelDir dlg( oldDir );
	if( dlg.DoModal() != IDOK )
		return;

	SetDlgItemText( IDC_EDIT2 , dlg.GetSel() );

	UpdateDirUI();
}
