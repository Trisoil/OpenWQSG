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
#include "afxwin.h"
#include <vector>
// CTXT_OutBox �Ի���

class CTXT_OutBox : public CDialog
{
	DECLARE_DYNAMIC(CTXT_OutBox)
	struct tg����
	{
		HWND		m_hWnd;
		CString		m_TBL;
		CString		m_TBL2;
		CString		m_TXT_DIR;
		CString		m_ROM_DIR;
		BOOL		m_��֤;
		u64			m_KS;
		u64			m_JS;
		UINT		m_min;
		UINT		m_max;
		CString		m_Ext;
		BOOL		m_SubDir;

		std::vector<CStringW> m_Files;
		CStringW m_LastDir;
		tg����()
		{
		}
	};
	tg���� m_����;

	CString m_�ļ��б���;
public:
	CTXT_OutBox(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTXT_OutBox();

// �Ի�������
	enum { IDD = IDD_TXT_O };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnClose();
private:
	CButton m_C��Ŀ¼����;
	CString m_EDIT_Rom;
	CString m_EDIT_TXT_DIR;
	CString m_EDIT_TBL;
	CString m_EDIT_TBL2;
	static DWORD WINAPI ��ͨ����_�ļ�(LPVOID lpParameter);
	static DWORD WINAPI ��ͨ����_�ļ���(LPVOID lpParameter);
	static BOOL WINAPI zzz_��ͨ����_�ļ���( CStringW ·�� , tg����& ���� , CWQSG_TXT_O& WQSG , INT& countAll , std::vector<CStringW>& szExt );
	static BOOL zzz��ͨ����( CString& �ļ��� , CWQSG_TXT_O& WQSG , tg����& ���� );
	CButton m_C��֤TBL;
	CString m_EDIT_min;
	CString m_EDIT_max;
	CString m_EDIT_�κ�;
	CString m_EDIT_��ʼƫ��;
	CString m_EDIT_����ƫ��;
	CString m_EDIT_EXT;
	CString m_LOG;
	CEdit m_CEDIT_LOG;
	CButton m_Cʹ�ÿ������;
	void ��������(void);
	CListBox m_CList;
	CString m_NodeName;
	BOOL д����( );
public:
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonTxtDir();
	afx_msg void OnBnClickedButtonTbl();
	afx_msg void OnBnClickedButtonTbl2();
	afx_msg void OnBnClickedCheck1();
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEditAddrH();
	afx_msg void OnEnChangeEditAddrKsL();
	afx_msg void OnEnChangeEditAddrJsL();
	afx_msg void OnEnKillfocusEditAddrH();
	afx_msg void OnEnKillfocusEditMin();
	afx_msg void OnEnKillfocusEditMax();
	afx_msg LRESULT �߳���Ϣ( WPARAM ���� , LPARAM �ı� );
	afx_msg LRESULT �߳�LOG( WPARAM ���� , LPARAM �ı� );
	afx_msg void OnBnClickedButtonRom();
	afx_msg void OnEnChangeEditExt();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCheck4();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnLbnSelchangeList2();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnBnClickedButtonEdit();
	afx_msg void OnEnKillfocusEditName();
	afx_msg void OnEnChangeEditName();
private:
	void AppLog(CString str);
	CButton m_C�ı���ͬĿ¼;
public:
	afx_msg void OnBnClickedCheck3();
private:
	CButton m_c������Ŀ¼;
};
