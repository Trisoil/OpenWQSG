/*  OpenWQSG - Ps2MemoryCard
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

// Ps2MemoryCardDlg.h : ͷ�ļ�
//

#pragma once

#include "VPscMc.h"
#include "afxcmn.h"
#include <hash_map>
#include <string>

typedef stdext::hash_map<std::string,std::vector<u8>> TPsuFile;

struct SPsuData
{
	CStringA m_strName;
	TPsuFile m_files;
};
// CPs2MemoryCardDlg �Ի���
class CPs2MemoryCardDlg : public CDialog
{
// ����
public:
	CPs2MemoryCardDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PS2MEMORYCARD_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	CVPscMc m_Mc;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonOpenMc();
	afx_msg void OnBnClickedButtonSaveMc();
	afx_msg void OnBnClickedButtonImportPsu();

	void UpdateUI();
private:
	CListCtrl m_cList;
public:
	afx_msg void OnBnClickedButtonExportPsu();
	afx_msg void OnBnClickedButtonAbout();

	bool Load_Psu( const CStringW& a_strFile , SPsuData& a_Files );
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonSaveBin();
};
