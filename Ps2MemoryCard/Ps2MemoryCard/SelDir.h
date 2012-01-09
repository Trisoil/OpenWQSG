#pragma once
#include "afxwin.h"


// CSelDir �Ի���

class CSelDir : public CDialog
{
	DECLARE_DYNAMIC(CSelDir)

	CString m_strDefSel;
	CString m_strExeDir;
public:
	CSelDir( const CString& a_strDefSel , CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSelDir();

// �Ի�������
	enum { IDD = IDD_DIALOG_SEL_DIR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
	const CString& GetSel()const
	{
		return m_strDefSel;
	}
private:
	CListBox m_cDir;
};
