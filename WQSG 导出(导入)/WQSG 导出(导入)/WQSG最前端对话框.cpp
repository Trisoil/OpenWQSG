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
// WQSG��ǰ�˶Ի���.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WQSG ����(����).h"
#include "WQSG��ǰ�˶Ի���.h"


// WQSG��ǰ�˶Ի��� �Ի���

IMPLEMENT_DYNAMIC(WQSG��ǰ�˶Ի���, CDialog)

WQSG��ǰ�˶Ի���::WQSG��ǰ�˶Ի���(CWnd* pParent /*=NULL*/)
	: CDialog(WQSG��ǰ�˶Ի���::IDD, pParent)
	, m_����(_T(""))
{
}

WQSG��ǰ�˶Ի���::~WQSG��ǰ�˶Ի���()
{
}

void WQSG��ǰ�˶Ի���::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_����);
}


BEGIN_MESSAGE_MAP(WQSG��ǰ�˶Ի���, CDialog)
END_MESSAGE_MAP()


// WQSG��ǰ�˶Ի��� ��Ϣ�������

void WQSG��ǰ�˶Ի���::��������(CString ����)
{
	m_���� = ����;
	UpdateData(FALSE);
}
