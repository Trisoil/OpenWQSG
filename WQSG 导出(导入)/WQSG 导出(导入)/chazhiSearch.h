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


// CchazhiSearch �Ի���
#include "WQSG_cfg.h"
#if DEF_ON_��ֵ����

class CchazhiSearch : public CDialog
{
	DECLARE_DYNAMIC(CchazhiSearch)
	CWQSG_TypeLinkList<s64> m_��ֵ��;
// ����
public:
	CchazhiSearch(CWnd* pParent = NULL);	// ��׼���캯��
// �Ի�������
	enum { IDD = IDD_chazhiSearch };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
protected:
	virtual void OnCancel();
	virtual void OnOK();
private:
	CString m_input;
	CString m_�ֽ�����;
	CString m_��������;
	CString m_log;
	CButton m_C�ߵͽ���;
	CString m_�ļ�·��;
	CListCtrl m_CList;
	void ˢ�²�ֵ( INT  startPos );
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnCbnSelendokCombo1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedCheck1();
};

#endif //DEF_ON_��ֵ����