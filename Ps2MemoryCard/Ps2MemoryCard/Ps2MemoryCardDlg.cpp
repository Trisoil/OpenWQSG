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

	m_cList.InsertColumn( 0 , L"�浵��" , 0 , 350 );
	m_cList.InsertColumn( 1 , L"size" , 0 , 40 );
	m_cList.InsertColumn( 2 , L"ԭ��" , 0 , 150 );

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
	static CWQSGFileDialog_Open dlg( L"*.ps2|*.ps2||" );
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

	static CWQSGFileDialog_Open dlg( L"*.psu|*.psu||" );
	if( IDOK != dlg.DoModal() )
		return;

	m_Mc.Bak();
	if( m_Mc.Import_Psu( dlg.GetPathName() ) )
	{
		UpdateUI();
		MessageBox( L"����ɹ�" );
	}
	else
	{
		m_Mc.UnBak();
		UpdateUI();
		MessageBox( L"����PSUʧ��" );
	}
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

		CWQSG_memFile mf;
		if( !m_Mc.Vmc_ReadFile( mf , info.szName , "icon.sys" ) )
			continue;

		mf.Seek( 0xC0 );

		char buf[0x100];
		if( sizeof(buf) != mf.Read( buf , sizeof(buf) ) )
		{
			MessageBox( L"ȡ�浵�ļ���ʧ��" );
			break;
		}

		WCHAR* pTitle = WQSG_char_W( buf , 932 );
		const int iIndex = m_cList.InsertItem( m_cList.GetItemCount() , pTitle );
		delete[]pTitle;

		if( iIndex == -1 )
		{
			MessageBox( L"���ʧ��" );
			break;
		}

		CString str;

		str.Format( L"%d" , info.uSize );
		m_cList.SetItemText( iIndex , 1 , str );

		WCHAR* pX = WQSG_char_W( info.szName , 932 );
		m_cList.SetItemText( iIndex , 2 , pX );
		delete[]pX;
	}

	m_cList.SetRedraw( TRUE );
}

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
		L"��Ŀsvn : <A HREF=\"http://code.google.com/p/wqsg-umd\">http://code.google.com/p/OpenWqsg</A>\r\n"
		L"������svn : <A HREF=\"http://code.google.com/p/wqsglib\">http://code.google.com/p/wqsglib</A>\r\n                 <A HREF=\"http://wqsg.ys168.com\">http://wqsg.ys168.com</A>\r\n" ,
		strAuthor2 + L"(" + strAuthor1 + L")" );
}
