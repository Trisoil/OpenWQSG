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
#pragma once


// WQSG��ǰ�˶Ի��� �Ի���

class WQSG��ǰ�˶Ի��� : public CDialog
{
	DECLARE_DYNAMIC(WQSG��ǰ�˶Ի���)

public:
	WQSG��ǰ�˶Ի���(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~WQSG��ǰ�˶Ի���();

// �Ի�������
	enum { IDD = IDD_AB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_����;
public:
	void SetWindowText(LPCTSTR lpszString){
		CDialog::SetWindowText(lpszString);
	}
	void ��������(CString ����);
};
