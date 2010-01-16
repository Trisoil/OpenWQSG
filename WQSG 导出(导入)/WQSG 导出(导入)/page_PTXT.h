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


// Cpage_PTXT_OUT �Ի���

class Cpage_PTXT_OUT : public CDialog
{
	DECLARE_DYNAMIC(Cpage_PTXT_OUT)

public:
	Cpage_PTXT_OUT(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Cpage_PTXT_OUT();

// �Ի�������
	enum { IDD = IDD_PTXT_OUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnOK();
	virtual void OnCancel();
	CString W_pKS;
	CString W_pJS;
	CString W_p�ı�����;
	CString W_pָ����;
	CString W_pʵ��ָ�볤��;
	CString W_pָ�뱶��;
public:
	int W_pָ���ʽ;
public:
	CString W_p���ȿ鱶��;
	afx_msg void OnCbnSelchangeCombo5();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnEnKillfocusEdit4();
	CString W_�ı�����;
};

// Cpage_PTXT_IN �Ի���

class Cpage_PTXT_IN : public CDialog
{
	DECLARE_DYNAMIC(Cpage_PTXT_IN)

public:
	Cpage_PTXT_IN(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Cpage_PTXT_IN();

// �Ի�������
	enum { IDD = IDD_PTXT_IN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnOK();
	virtual void OnCancel();

	DECLARE_MESSAGE_MAP()
	
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit11();
public:
	CString m_p�ı������޵�ַ;
	CString m_p�ı�����ʼ��ַ;
};
