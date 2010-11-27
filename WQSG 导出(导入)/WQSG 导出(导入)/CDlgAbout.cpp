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
// CDlgAbout.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WQSG ����(����).h"
#include "CDlgAbout.h"


// CCDlgAbout �Ի���

IMPLEMENT_DYNAMIC(CCDlgAbout, CBaseDialog)

CCDlgAbout::CCDlgAbout(CWnd* pParent /*=NULL*/)
	: CBaseDialog(CCDlgAbout::IDD, pParent)
	, m_bInUrl(FALSE)
{

}

CCDlgAbout::~CCDlgAbout()
{
}

void CCDlgAbout::DoDataExchange(CDataExchange* pDX)
{
	CBaseDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCDlgAbout, CBaseDialog)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CCDlgAbout ��Ϣ�������

void CCDlgAbout::OnCancel(){}
void CCDlgAbout::OnOK(){}

void CCDlgAbout::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CBaseDialog::OnClose();
	EndDialog(IDCANCEL);
}

HBRUSH CCDlgAbout::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CBaseDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	switch(pWnd->GetDlgCtrlID())
	{
	case IDC_URL:
		pDC->SetTextColor( m_bInUrl?RGB(255,0,0):RGB(0,0,255) );
		pDC->SetBkMode( TRANSPARENT );
		break;
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

void CCDlgAbout::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CRect rectUrl;
	CWnd* pWnd = GetDlgItem( IDC_URL );
	pWnd->GetWindowRect( &rectUrl );

	ScreenToClient( &rectUrl );

	const BOOL bIn = rectUrl.PtInRect( point );

	if( m_bInUrl != bIn )
	{
		pWnd->Invalidate(FALSE);
		m_bInUrl = bIn;
	}

	CBaseDialog::OnMouseMove(nFlags, point);
}

BOOL CCDlgAbout::OnInitDialog()
{
	CBaseDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString strName;strName.LoadString( IDS_APP_NAME );
	CString strVer;strVer.LoadString( IDS_APP_VER );
	CString strWQSG;strWQSG.LoadString( IDS_APP_WQSG );
	SetDlgItemText( IDC_APP_NAME , strName );
	SetDlgItemText( IDC_APP_VER , strVer );
	SetDlgItemText( IDC_STATIC_WQSG , strWQSG );

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CCDlgAbout::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if( m_bInUrl )
		ShellExecute( NULL , L"open" , L"http://wqsg.ys168.com" , NULL , NULL , SW_NORMAL );

	CBaseDialog::OnLButtonDown(nFlags, point);
}

