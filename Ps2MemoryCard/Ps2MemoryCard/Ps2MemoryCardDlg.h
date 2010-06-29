
// Ps2MemoryCardDlg.h : ͷ�ļ�
//

#pragma once

#include "VPscMc.h"
#include "afxcmn.h"

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
};
