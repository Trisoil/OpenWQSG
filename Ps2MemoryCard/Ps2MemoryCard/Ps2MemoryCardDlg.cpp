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


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPs2MemoryCardDlg �Ի���

struct SItemSortData
{
	CStringW m_strTitleName;
	n32 m_nSize;
	CStringW m_strFileName;
};

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
	DDX_Control(pDX, IDC_LIST1, m_cList);
}

BEGIN_MESSAGE_MAP(CPs2MemoryCardDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_OPEN_MC, &CPs2MemoryCardDlg::OnBnClickedButtonOpenMc)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_MC, &CPs2MemoryCardDlg::OnBnClickedButtonSaveMc)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT_PSU, &CPs2MemoryCardDlg::OnBnClickedButtonImportPsu)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT_PSU, &CPs2MemoryCardDlg::OnBnClickedButtonExportPsu)
	ON_BN_CLICKED(IDC_BUTTON_ABOUT, &CPs2MemoryCardDlg::OnBnClickedButtonAbout)
	ON_BN_CLICKED(IDC_BUTTON1, &CPs2MemoryCardDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_BIN, &CPs2MemoryCardDlg::OnBnClickedButtonSaveBin)
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CPs2MemoryCardDlg::OnHdnItemclickList1)
	ON_NOTIFY(LVN_DELETEITEM, IDC_LIST1, &CPs2MemoryCardDlg::OnLvnDeleteitemList1)
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
	m_cList.SetExtendedStyle( m_cList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );

	m_cList.InsertColumn( 0 , L"�浵��" , 0 , 450 );
	m_cList.InsertColumn( 1 , L"size" , 0 , 40 );
	m_cList.InsertColumn( 2 , L"ԭ��" , 0 , 150 );

	HDITEM hi = {};
	hi.mask = HDI_FORMAT;
	m_cList.GetHeaderCtrl()->GetItem( 0 , &hi );
	hi.fmt |= HDF_SORTUP;
	m_cList.GetHeaderCtrl()->SetItem( 0 , &hi );

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

void CPs2MemoryCardDlg::OnBnClickedButtonOpenMc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	static CWQSGFileDialog_Open dlg( L"*.ps2;*.bin|*.ps2;*.bin||" );
	if( IDOK != dlg.DoModal() )
		return;

	if( !m_Mc.LoadMc( dlg.GetPathName() ) )
	{
		UpdateUI();
		MessageBox( L"���ؼ��俨ʧ��" );
		EndDialog( IDCANCEL );
	}

	UpdateUI();
}

void CPs2MemoryCardDlg::OnBnClickedButtonSaveMc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if( !m_Mc.isOpen() )
		return ;

	static CWQSGFileDialog_Save dlg( L"*.ps2|*.ps2||" , L"ps2" );
	if( IDOK != dlg.DoModal() )
		return;

	if( !m_Mc.SaveMc( dlg.GetPathName() ) )
	{
		MessageBox( L"������俨ʧ��" );
	}
}

void CPs2MemoryCardDlg::OnBnClickedButtonImportPsu()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if( !m_Mc.isOpen() )
		return ;

	static CWQSGFileDialog_OpenS dlg( L"*.psu|*.psu||" );
	if( IDOK != dlg.DoModal() )
		return;

	CString strName;
	POSITION pos = dlg.GetStartPosition();
	while( dlg.GetNextPathName( strName , pos ) )
	{
		m_Mc.Bak();
		if( !m_Mc.Import_Psu( strName ) )
		{
			m_Mc.UnBak();
			UpdateUI();
			MessageBox( L"����PSUʧ��" , strName );
			return;
		}
	}
	UpdateUI();
	MessageBox( L"����ɹ�" );
}

void CPs2MemoryCardDlg::OnBnClickedButtonExportPsu()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if( !m_Mc.isOpen() )
		return ;

	POSITION pos = m_cList.GetFirstSelectedItemPosition();
	const int iIndex = m_cList.GetNextSelectedItem( pos );
	if( iIndex == -1 )
		return ;

	const CString str = m_cList.GetItemText( iIndex , 2 );

	CWQSGFileDialog_Save dlg( L"*.psu|*.psu||" , L"psu" , str );
	if( IDOK != dlg.DoModal() )
		return;

	char* pName = WQSG_W_char( str.GetString() , 932 );
	if( m_Mc.Export_Psu( dlg.GetPathName() , pName ) )
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

void CPs2MemoryCardDlg::UISort()
{
	CHeaderCtrl& cc = *m_cList.GetHeaderCtrl();

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

	m_cList.SortItems( &ItemSort , uFlag );
}

void CPs2MemoryCardDlg::UpdateUI()
{
	m_cList.DeleteAllItems();
	if( !m_Mc.isOpen() )
		return ;

	std::vector<CVPscMc::SFileInfo> files;
	if( !m_Mc.GetFiles( files , "" ) )
	{
		MessageBox( L"��ȡ�ļ��б�ʧ��" );
		return;
	}

	m_cList.SetRedraw( FALSE );
	for( std::vector<CVPscMc::SFileInfo>::iterator it = files.begin() ;
		it != files.end() ; ++it )
	{
		const CVPscMc::SFileInfo& info = *it;

		CStringW str;

		CWQSG_memFile mf;
		if( m_Mc.Vmc_ReadFile( mf , info.szName , "icon.sys" ) )
		{
			mf.Seek( 0xC0 );

			char buf[0x100];
			if( sizeof(buf) != mf.Read( buf , sizeof(buf) ) )
			{
				MessageBox( L"ȡ�浵�ļ���ʧ��" );
				break;
			}

			WCHAR* pTitle = WQSG_char_W( buf , 932 );
			str = pTitle;
			delete[]pTitle;
		}
		else
		{
			WCHAR* pX = WQSG_char_W( info.szName , 932 );
			str = pX;
			delete[]pX;
		}

		const int iIndex = m_cList.InsertItem( m_cList.GetItemCount() , str );

		if( iIndex == -1 )
		{
			MessageBox( L"���ʧ��" );
			break;
		}

		SItemSortData* pData = new SItemSortData;
		m_cList.SetItemData( iIndex , (DWORD_PTR)pData );

		pData->m_strTitleName = str;
		pData->m_nSize = info.uSize;
		

		str.Format( L"%d" , info.uSize );
		m_cList.SetItemText( iIndex , 1 , str );

		WCHAR* pX = WQSG_char_W( info.szName , 932 );
		pData->m_strFileName = pX;
		delete[]pX;

		m_cList.SetItemText( iIndex , 2 , pData->m_strFileName );
	}
	//--------------------------
	UISort();
	//--------------------------
	m_cList.SetRedraw( TRUE );

	u32 count = 0;
	if( m_Mc.GetFreeClusterCount( count ) )
	{
		CStringW str;
		str.Format( L"���п� = %d , size = %d\r\n" , count , m_Mc.GetPreClusterSize() * count );
		OutputDebugString( str );
	}
	else
	{
		CStringW str;
		str.Format( L"ȡ���п�ʧ��,���п� = %d , size = %d\r\n" , count , m_Mc.GetPreClusterSize() * count );
		OutputDebugString( str );
	}
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

void CPs2MemoryCardDlg::OnBnClickedButtonSaveBin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if( !m_Mc.isOpen() )
		return ;

	static CWQSGFileDialog_Save dlg( L"*.bin|*.bin||" , L"bin" );
	if( IDOK != dlg.DoModal() )
		return;

	if( !m_Mc.SaveMcNoEcc( dlg.GetPathName() ) )
	{
		MessageBox( L"������俨ʧ��" );
	}
}

void CPs2MemoryCardDlg::OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	if( phdr->iButton != 0 )
		return;

	HDITEM hi = {};
	hi.mask = HDI_FORMAT;

	CHeaderCtrl& cc = *m_cList.GetHeaderCtrl();
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

	UISort();
}

void CPs2MemoryCardDlg::OnLvnDeleteitemList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	delete (SItemSortData*)m_cList.GetItemData( pNMLV->iItem );
}
