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

#include "WQSG_cfg.h"

#if DEF_ON_�ı��滻

#include "afxwin.h"


// C�����ı��滻Dlg �Ի���

class C�����ı��滻Dlg : public CDialog
{
	DECLARE_DYNAMIC(C�����ı��滻Dlg)
	CWQSG_TypeLinkList< CStringW >	m_�滻����[2];
	u32 m_�������;
// ����
public:
	C�����ı��滻Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TXT_R };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CString m_��������;
public:
	CString m_�滻Ϊ;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnClose();
protected:
	virtual void OnCancel();
	virtual void OnOK();
public:
	afx_msg void OnBnClickedCheck1();
private:
	CButton m_C�߼��滻;
	CButton m_C�滻��Ŀ¼;
public:
	afx_msg void OnBnClickedButton2();
private:
	CString m_�滻��;
public:
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
private:
	bool �����滻��(void);
	bool �滻Ŀ¼(CString ·��);
	bool �滻�ı�(CString �ļ�);
};

#endif //DEF_ON_�ı��滻