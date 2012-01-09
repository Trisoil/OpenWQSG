// SelDir.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Ps2MemoryCard.h"
#include "SelDir.h"


// CSelDir �Ի���

IMPLEMENT_DYNAMIC(CSelDir, CDialog)

CSelDir::CSelDir(const CString& a_strDefSel , CWnd* pParent /*=NULL*/)
	: CDialog(CSelDir::IDD, pParent)
	, m_strDefSel(a_strDefSel)
{
	WCHAR exePath[ MAX_PATH ];
	if( WQSG_GetExePath( exePath , MAX_PATH ) )
	{
		m_strExeDir = exePath;
		m_strExeDir += L"\\";
	}
}

CSelDir::~CSelDir()
{
}

void CSelDir::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_cDir);
}


BEGIN_MESSAGE_MAP(CSelDir, CDialog)
END_MESSAGE_MAP()


// CSelDir ��Ϣ�������

void CSelDir::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	const int iSel = m_cDir.GetCurSel();
	if( iSel == LB_ERR )
		return;

	m_cDir.GetText( iSel , m_strDefSel );
	m_strDefSel.Insert( 0 , m_strExeDir );

	CDialog::OnOK();
}

BOOL CSelDir::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	if( m_strExeDir.GetLength() == 0 )
	{
		EndDialog( IDCANCEL );
		return FALSE;
	}

	SetDlgItemText( IDC_STATIC1 ,
		L"Ŀ¼��������Ϊ:\"MC_XYY\"\r\n"
		L"����X��ѡ��ĸΪA��B\r\n"
		L"����YY��ѡ����Ϊ00��99" );

	CString strDefSel;
	for ( int n = 1 ; n < 100 ; n++ )
	{
		CString str;
		str.Format( L"MC_A%02d" , n );

		const CString strFull = m_strExeDir + str;

		if( WQSG_IsDir( strFull ) )
		{
			m_cDir.AddString( str );
			if( strFull == m_strDefSel )
				strDefSel = str;
		}
	}

	for ( int n = 1 ; n < 100 ; n++ )
	{
		CString str;
		str.Format( L"MC_B%02d" , n );

		const CString strFull = m_strExeDir + str;

		if( WQSG_IsDir( strFull ) )
		{
			m_cDir.AddString( str );
			if( strFull == m_strDefSel )
				strDefSel = str;
		}
	}

	m_cDir.SelectString( 0 , strDefSel );

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
