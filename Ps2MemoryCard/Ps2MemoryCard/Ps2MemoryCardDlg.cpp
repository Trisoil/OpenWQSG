
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
	ON_BN_CLICKED(IDC_BUTTON_OPEN_MC, &CPs2MemoryCardDlg::OnBnClickedButtonOpenMc)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_MC, &CPs2MemoryCardDlg::OnBnClickedButtonSaveMc)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT_PSU, &CPs2MemoryCardDlg::OnBnClickedButtonImportPsu)
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

void CPs2MemoryCardDlg::OnBnClickedButtonOpenMc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	static CWQSGFileDialog_Open dlg( L"*.ps2|*.ps2||" );
	if( IDOK != dlg.DoModal() )
		return;

	if( !m_Mc.LoadMc( dlg.GetPathName() ) )
	{
		MessageBox( L"���ؼ��俨ʧ��" );
		EndDialog( IDCANCEL );
	}
}

void CPs2MemoryCardDlg::OnBnClickedButtonSaveMc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	static CWQSGFileDialog_Open dlg( L"*.psu|*.psu||" );
	if( IDOK != dlg.DoModal() )
		return;

	m_Mc.Bak();
	if( m_Mc.Import_Psu( dlg.GetPathName() ) )
	{
		MessageBox( L"����ɹ�" );
	}
	else
	{
		m_Mc.UnBak();
		MessageBox( L"����PSUʧ��" );
	}
}
