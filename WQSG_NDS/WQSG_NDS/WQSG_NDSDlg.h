/*  OpenWQSG - WQSG_NDS
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

// WQSG_NDSDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"

#define OVERLAY_FMT		_T("/FSI.CT/overlay%d_%04d.bin")
#define GetNDSSize(header) ( 1 << (17 + header.devicecap) )
#define HEADERCOUNT 8
#define GETFILEID(Param) (LOWORD(Param))
#define GETITEMID(Param) (HIWORD(Param))
#define MAKEPARAM(nFileID, iItem) (MAKELONG(nFileID, iItem))


// CWQSG_NDSDlg �Ի���
class CWQSG_NDSDlg : public CDialog
{
// ����
public:
	CWQSG_NDSDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_WQSG_NDS_DIALOG };

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
public:
	afx_msg void OnClose();
protected:
	virtual void OnOK();
	virtual void OnCancel();

	CListCtrl m_NdsFSI;
	HIMAGELIST m_hImageList;

	CNdsRom m_Rom;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHdnGetdispinfoFsilist(NMHDR *pNMHDR, LRESULT *pResult);

	void OnLoadFSI(void);

	int GetCurSel()const
	{
		POSITION pos = m_NdsFSI.GetFirstSelectedItemPosition();
		return m_NdsFSI.GetNextSelectedItem(pos);
	}

	afx_msg void OnRomopen();
private:
	CStringA m_strPath;
public:
	afx_msg void OnLvnItemActivateFsilist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnDeleteitemFsilist(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL DestroyWindow();
	afx_msg void OnRomclose();
	afx_msg void OnBnClickedButtonUpdir();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
private:
	bool WFile( CString a_strPathFile , const SNdsFindData& a_DirData , CStringA a_strFile );
	bool WDir( CString a_strPathFile , const CStringA& a_strDirPath );

	void SetTitle(BOOL* a_bCanWrite);
public:
	afx_msg void OnAbout();
	afx_msg void OnQuit();
};
