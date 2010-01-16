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
#include "afxwin.h"
#if DEF_ON_TBL
// Cͳ����Ƶ �Ի���

class Cͳ����Ƶ : public CDialog
{
	DECLARE_DYNAMIC(Cͳ����Ƶ)
	WCHAR W_KZF_L;
	WCHAR W_KZF_R;
public:
	Cͳ����Ƶ(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Cͳ����Ƶ();

// �Ի�������
	enum { IDD = IDD_DIALOG_TongJiZiPin };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	struct SCharTblInfo 
	{
		u32 m_uCount;
		BOOL m_bUnTbl;

		void Clean()
		{
			m_uCount = 0;
			m_bUnTbl = TRUE;
		}
	};
public:
	virtual INT_PTR DoModal();
	virtual BOOL Create(UINT nIDTemplate, CWnd* pParentWnd = NULL);
	virtual void OnOK();
	virtual void OnCancel();
	CString W_����ַ;
	afx_msg void OnBnClickedButtonTbl();
	void ����();
	BOOL �������();
	afx_msg void OnBnClickedButton2();

	SCharTblInfo m_Info[0x10000];

	void ͳ��һ����Ƶ_���˿��Ʒ�(WCHAR* TXT);
	void ͳ��һ����Ƶ_���ı�(WCHAR* TXT);
	CString W_��ʾ��;
	int W_���Ʒ�����;
	BOOL W_�������;
	afx_msg void OnBnClickedCheckTbl();
	BOOL W_ͳ��ģʽ;
	CString W_�ȴ��������;
	CString W_��һ������;
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnKillfocusEdit3();
	BOOL W_�ߵͽ���;
	int W_��������;
	afx_msg void OnBnClickedCheck1();
	CString W_�����;
	afx_msg void OnBnClickedButtonTbl3();
	afx_msg void OnBnClickedButton3();
	BOOL ��������(::CWQSG_File * TXT_File);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
public:
	afx_msg void OnEnKillfocusEditTbl3();
	afx_msg void OnClose();
private:
	CComboBox m_OutType;
};

#endif //DEF_ON_TBL