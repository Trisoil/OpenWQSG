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
// WQSG_IPS_IO.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WQSG ����(����).h"
#include "WQSG_WIPS_IO.h"


// CWQSG_IPS_IO �Ի���

IMPLEMENT_DYNAMIC(CWQSG_WIPS_IO, CDialog)

CWQSG_WIPS_IO::CWQSG_WIPS_IO(CWnd* pParent /*=NULL*/)
	: CDialog(CWQSG_WIPS_IO::IDD, pParent)
{

}

CWQSG_WIPS_IO::~CWQSG_WIPS_IO()
{
}

void CWQSG_WIPS_IO::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWQSG_WIPS_IO, CDialog)
END_MESSAGE_MAP()


// CWQSG_IPS_IO ��Ϣ�������
