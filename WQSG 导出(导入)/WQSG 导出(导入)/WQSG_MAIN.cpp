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
#include "stdafx.h"
#include "WQSG ����(����).h"
#include "WQSG_MAIN.h"
// CWQSG_MAIN �Ի���
CWnd*				WQSG_MAIN_CWND = NULL;
CWQSG_INI_XML		WQSG_ini;
CString				WQSG_iniSavePathName;
IMPLEMENT_DYNAMIC(CWQSG_MAIN, CDialog)
CWQSG_MAIN::CWQSG_MAIN(CWnd* pParent /*=NULL*/)
	: CDialog(CWQSG_MAIN::IDD, pParent)
#if DEF_ON_TXTIO
	, m_TXTIO( L"�����ı�" , L"�����ı�")
#endif
#if DEF_ON_PTXTIO
	, m_PTXTIO( L"�����ı�" , L"�����ı�" )
#endif
#if	DEF_ON_WIPS
	, m_WIPS( L"��������" , L"ʹ�ò���")
#endif
	, m_CurToolID( WT_ID_MAX )
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_WQSG);
	WQSG_MAIN_CWND = this;

	for( int i = 0; i < WT_ID_MAX ; ++i )
		m_Tool_CWND[i] = NULL;
}

CWQSG_MAIN::~CWQSG_MAIN()
{
}

void CWQSG_MAIN::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_TAB);
	DDX_Control(pDX, IDC_EDIT_LOG, m_CEDIT_LOG);
}


BEGIN_MESSAGE_MAP(CWQSG_MAIN, CDialog)
	ON_WM_CLOSE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CWQSG_MAIN::OnTcnSelchangeTab1)
	ON_MESSAGE( WM_WQSG_�����ı� , &CWQSG_MAIN::�����ı� )
	ON_MESSAGE( WM_WQSG_����LOG�ı� , &CWQSG_MAIN::����LOG�ı� )
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
END_MESSAGE_MAP()
void CWQSG_MAIN::OnOK(){}
void CWQSG_MAIN::OnCancel(){}//	
BOOL CWQSG_MAIN::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	{
		CString strName;strName.LoadString( IDS_APP_NAME );
		CString strVer;strVer.LoadString( IDS_APP_VER );
		CString strWQSG;strWQSG.LoadString( IDS_APP_WQSG );
		SetWindowTextW( strName + L" " + strVer + L"    " + strWQSG );
	}
	//--------------------------------------
	WCHAR exePathName[ MAX_PATH * 2 ];
	if( 0 == GetModuleFileNameW( NULL , exePathName , MAX_PATH * 2 ) )
		goto __gt�����˳�;

	WQSG_iniSavePathName = exePathName;
	WQSG_iniSavePathName = WQSG_iniSavePathName.Left( WQSG_iniSavePathName.ReverseFind( L'\\' ) + 1 ) + L"WQSG��������.XML";
	if( !WQSG_ini.Load( WQSG_iniSavePathName , L"WQSG��������" , FALSE ) )
		goto __gt�����˳�;

	{
		CRect rect , rectTAB;
		m_TAB.GetClientRect( rect );

		m_TAB.GetItemRect( 0 , rectTAB );
		rectTAB.top = rectTAB.bottom + 4;
		rectTAB.left = 2;
		rectTAB.right = rect.Width() - 4;
		rectTAB.bottom = rect.Height() - 5;// - rectTAB.top;

		int __nID = 0;
#define DEF_ADD( __DEF_X , __DEF_Y , __DEF_TYPE ) \
		if( !__DEF_X.Create( (UINT)__DEF_X.IDD , &m_TAB ) )\
		goto __gt�����˳�;\
		m_TAB.InsertItem( __nID , __DEF_Y );\
		m_Tool_CWND[ __nID++ ] = &__DEF_X;\
		__DEF_X.MoveWindow( rectTAB );

#if DEF_ON_TXTIO
		DEF_ADD( m_TXTIO , L"���ı�(��ͨ)" , WT_ID_TXTIO )
#endif
#if DEF_ON_PTXTIO
			DEF_ADD( m_PTXTIO , L"���ı�(ָ��)" , WT_ID_PTXTIO )
#endif
#if DEF_ON_WIPS
			DEF_ADD( m_WIPS , L"WIPS����" , WT_ID_WIPS )
#endif
#if DEF_ON_TBL
			DEF_ADD( m_TBLtool , L"�����" , WT_ID_TBL )	
#endif
#if DEF_ON_�ı��滻
		DEF_ADD( m_�����ı��滻 , L"�ı��滻" , WT_ID_�ı��滻 )
#endif
#if DEF_ON_��ֵ����
		DEF_ADD( m_chazhiSearch , L"��ֵ����" , WT_ID_��ֵ���� )
#endif

		DEF_ADD( m_dlgAbout , L"���ڱ����" , WT_ID_ABOUT )

#undef DEF_ADD
	}
	ѡ�񹤾�();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
__gt�����˳�:
	CDialog::OnCancel();
	return FALSE;
}
void CWQSG_MAIN::OnClose()
{
	
	if( m_������Ϣ.GetLength() > 0 )
	{
		if( IDYES != MessageBox( L"����û����,ȷ��Ҫ�ر�ô?" , NULL , MB_YESNO ) )
		{
			return;
		}
	}
	CDialog::OnClose();
	CDialog::OnCancel();
}

void CWQSG_MAIN::ѡ�񹤾�(void)
{
	int nID = m_TAB.GetCurSel();
	if( m_CurToolID != nID )
	{
		if( (m_CurToolID >= 0) && (m_CurToolID < WT_ID_MAX) )
		{
			if( m_Tool_CWND[ m_CurToolID ] )
			{
				m_Tool_CWND[ m_CurToolID ]->ShowWindow( FALSE );
			}
		}
		m_CurToolID = WT_ID_MAX;
		if( (nID >= 0) && (nID < WT_ID_MAX) )
		{
			m_CurToolID = nID;
			if( m_Tool_CWND[ m_CurToolID ] )
			{
				m_Tool_CWND[ m_CurToolID ]->ShowWindow( TRUE );
			}
		}
	}
}

void CWQSG_MAIN::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ѡ�񹤾�();
	*pResult = 0;
}

LRESULT CWQSG_MAIN::�����ı�( WPARAM ���� , LPARAM �ı� )
{
	if( �ı� )
	{
		m_������Ϣ = (WCHAR*)�ı� ;
		m_TAB.EnableWindow( FALSE );
		m_TAB.ShowWindow( SW_HIDE );
		m_CEDIT_LOG.ShowWindow( SW_NORMAL );
		Invalidate();
	}
	else
	{
		m_������Ϣ = L"";
		m_TAB.EnableWindow( TRUE );
		m_TAB.ShowWindow( SW_NORMAL );
		m_CEDIT_LOG.ShowWindow( SW_HIDE );
		m_CEDIT_LOG.SetWindowTextW( L"" );
		Invalidate();
	}
	return 0;
}
LRESULT CWQSG_MAIN::����LOG�ı�( WPARAM ���� , LPARAM �ı� )
{
	m_CEDIT_LOG.SetWindowTextW( (WCHAR*)�ı� );
	return 0;
}
BOOL CWQSG_MAIN::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	::CBrush hbr( RGB(255,255,255) );
	CRect rect;
	GetClientRect( rect );
	pDC->FillRect( rect , &hbr );

	return TRUE;

	//return CDialog::OnEraseBkgnd(pDC);
}

void CWQSG_MAIN::OnPaint()
{
	CPaintDC dc(this); // ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()

	if( m_������Ϣ.GetLength() )
	{
		CRect rect;
		GetClientRect( rect );
		rect.top = rect.bottom ;//>> 2;
//		rect.bottom = rect.top;
		COLORREF old = dc.SetTextColor( RGB(255,0,0) );
		dc.DrawTextW( m_������Ϣ , rect , DT_CENTER );
		dc.SetTextColor( old );
	}
}
