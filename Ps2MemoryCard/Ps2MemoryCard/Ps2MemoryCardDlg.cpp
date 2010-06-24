
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
}

BEGIN_MESSAGE_MAP(CPs2MemoryCardDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_CLOSE()
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

	//CVPscMc gg;
	//gg.LoadMc( L"D:\\WQSG\\Documents\\pcsx2\\memcards\\Mcd002.ps2" );

	CWQSG_File fp;
	ASSERT( fp.OpenFile( L"c:\\BISCAJ-20028ToD2sv01.psu" , 1 , 3 ) );

	SPsu_header head = {};
	ASSERT( sizeof(head) == fp.Read( &head , sizeof(head) ) );
	ASSERT( head.attr & DF_DIRECTORY );

	for( u32 i = 0 ; i < head.size ; ++i )
	{
		SPsu_header head1 = {};
		ASSERT( sizeof(head1) == fp.Read( &head1 , sizeof(head1) ) );
		if( head1.attr & DF_DIRECTORY )
		{
			if( head1.size == 0 )
				continue;

			ASSERT( head1.size == 0 );
			return FALSE;
		}

		const u32 p = head1.size % 0x400;

		if( p )
			fp.Seek( fp.Tell() + head1.size + (0x400 - p) );
		else
			fp.Seek( fp.Tell() + head1.size );
	}

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

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPs2MemoryCardDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPs2MemoryCardDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialog::OnClose();
}
