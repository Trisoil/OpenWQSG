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
// MFCDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "WQSG��ǰ�˶Ի���.h"


class CWQSG��������Dlg : public CDialog
{

// ����
public:
	CWQSG��������Dlg(CWnd* pParent = NULL);	// ��׼���캯��
// �Ի�������
	enum { IDD = IDD_MFC_DIALOG };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	void �ı�ѡ��(void);
	void д����(void);
	void д�б�(CListBox * lb_tmp);
	void ����Ŀ¼(void);
	virtual void OnOK();
	virtual void OnCancel();

	afx_msg void OnBnClickedButtonRom();
	afx_msg void OnBnClickedButtonTbl();
	afx_msg void OnBnClickedButtonTbl2();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnEnUpdateEditName();
	afx_msg void OnLbnSelchangeList2();
	afx_msg void OnBnClickedButtonEdit();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnEnKillfocusEditName();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCheckPtxt();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnEnChangeEditRom();
	afx_msg void OnEnChangeEditTbl();
	afx_msg void OnEnChangeEditTbl2();
	afx_msg void OnBnClickedButtonBat();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnEnKillfocusEditRom();

	CString �����ļ�,
		�����б��ļ�;

	CString m_ROM
		, m_ROM_DIR
		, m_TXT
		, m_TBL
		, m_TBL
		, m_NAME;

	CString W_����Ŀ¼;

protected:
	afx_msg LRESULT ����ǰ������( WPARAM ���� , LPARAM ���� );
	afx_msg LRESULT ȡǰ�˴���( WPARAM ���� , LPARAM ����ָ�� );
	WQSG��ǰ�˶Ի��� m_��ǰ�˶Ի���;
	static DWORD WINAPI ��ͨ����(LPVOID lpParameter);
	static DWORD WINAPI ��ͨ����(LPVOID lpParameter);
	static DWORD WINAPI ��ַ_ָ�뵼��(LPVOID lpParameter);
	static DWORD WINAPI ��ַ_ָ�뵼��(LPVOID lpParameter);
	struct �����ṹ{
		HWND hwnd;
		CString ROM,TBL,TBL2,TXT;
		int ��֤;
	}m_������;

public:
	afx_msg void OnClose();
private:
	CString m_EDIT_TXT;
};
