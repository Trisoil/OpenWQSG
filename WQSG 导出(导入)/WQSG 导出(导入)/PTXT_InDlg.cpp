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
// PTXT_InDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WQSG ����(����).h"
#include "PTXT_InDlg.h"


// CPTXT_InDlg �Ի���

IMPLEMENT_DYNAMIC(CPTXT_InDlg, CBaseDialog)

CPTXT_InDlg::CPTXT_InDlg(CWnd* pParent /*=NULL*/)
	: CBaseDialog(CPTXT_InDlg::IDD, pParent)
{

}

CPTXT_InDlg::~CPTXT_InDlg()
{
}

void CPTXT_InDlg::DoDataExchange(CDataExchange* pDX)
{
	CBaseDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPTXT_InDlg, CBaseDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CPTXT_InDlg::OnBnClickedButton1)
	ON_WM_CLOSE()
END_MESSAGE_MAP()
// CPTXT_InDlg ��Ϣ�������

void CPTXT_InDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CPTXT_InDlg::OnCancel(){}
void CPTXT_InDlg::OnOK(){}
BOOL CPTXT_InDlg::OnInitDialog()
{
	CBaseDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CPTXT_InDlg::OnClose()
{
	CBaseDialog::OnClose();
	CBaseDialog::OnCancel();
}
