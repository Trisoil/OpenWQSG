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


// �������������� �Ի���

class ���������� : public CDialog
{
	DECLARE_DYNAMIC(����������)

public:
	����������(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~����������();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual BOOL OnInitDialog();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
public:
	virtual void OnOK();
public:
	virtual void OnCancel();
public:
	CListCtrl* W_�б�;
public:
	INT W_�б���һ��λ��;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonTbl();
public:
	afx_msg void OnBnClickedButtonTbl2();
public:
	afx_msg void OnEnChangeEditKs();
public:
	afx_msg void OnEnChangeEditJs();
public:
	afx_msg void OnEnChangeEditMin();
public:
	afx_msg void OnEnChangeEditMax();
public:
	afx_msg void OnBnClickedButtonAdd();
public:
	afx_msg void OnBnClickedButtonDel();
public:
	afx_msg void OnLvnItemActivateListW(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnBnClickedButtonEdit();
public:
	afx_msg void OnEnChangeEditTbl();
public:
	afx_msg void OnEnChangeEditTbl2();
public:
	afx_msg void OnBnClickedButtonStart();
public:
	CString W_��ʼ��ַ;
public:
	CString W_������ַ;
public:
	BOOL W_��֤;
public:
	CString W_MIN;
public:
	CString W_MAX;
public:
	CString W_Ĭ�����;
public:
	CString W_Ĭ�Ͽ������;
public:
	CString W_ROM;
public:
	void ������Ŀ��(CString �ļ���ַ);
public:
	void ������Ŀ��(CString �ļ���ַ);
public:
	CString W_�����ļ���ַ;
public:
	CString W_��ǰĿ¼;
};