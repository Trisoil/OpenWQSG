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
#include "afxcmn.h"
#include "afxwin.h"


//#include<2/WQSG_INI.h>
// CWQSG_MAIN �Ի���
#define WM_WQSG_SetText	( WM_USER + 4444 )
#define WM_WQSG_SetLogText	( WM_WQSG_SetText + 1 )


extern CWnd*			g_pMAIN_CWND;

#include "WQSG_cfg.h"

class CWQSG_MAIN : public CDialog
{
	DECLARE_DYNAMIC(CWQSG_MAIN)

	std::vector<CBaseDialog*> m_TabWnd;
	CBaseDialog* m_SelWnd;

	CString m_strWindowMsg;
	CString m_LOG;
	CEdit m_CEDIT_LOG;
	CTabCtrl m_TAB;
public:
	CWQSG_MAIN(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWQSG_MAIN();

// �Ի�������
	enum { IDD = IDD_MAIN };
protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnOK(){}
	virtual void OnCancel(){}
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
private:
	afx_msg LRESULT SetText( WPARAM ���� , LPARAM �ı� );
	afx_msg LRESULT SetLogText( WPARAM ���� , LPARAM �ı� );

	template< typename BaseType >
	BOOL AddDlg( BaseType* a_pDlg , const CString& a_strTabName , const CRect& a_rect );

	void SelTab(void);
};
#if 0
class CWQSG_TXT_Check : private CWQSG_MapTbl_IN
{
public:
	CWQSG_TXT_Check( )
		: CWQSG_MapTbl_IN( )
	{}
	~CWQSG_TXT_Check(){}
	u32	GetLen( WCHAR* pStrTXT )
	{
		WCHAR* line = pStrTXT;
		u32 TotalLen = 0;
		WCHAR wCh;
		while( wCh = *line )
		{
			switch( wCh )
			{
			case L'{':
				{
					++line;

					u32 kzL = 1 ;
					INT posL = WQSG_strchr( line , L'{' )
						, posR = WQSG_strchr( line , L'}' );


					if( posR < 0 )
					{//����
						return TotalLen;
					}
					u32 kzR = 1 ;

					if( ( posL >= 0 ) && ( ( posL ) < posR ) )
						++kzL;

					INT posTmp;
					while( kzL != kzR )
					{
						posTmp = WQSG_strchr( line + posR + 1 , L'}' );
						if( posTmp++ < 0 )
						{//����
							return TotalLen;
						}
						posR += posTmp;
						++kzR;
						//
						while( posL < posR )
						{
							posTmp = WQSG_strchr( line + posL + 1 , L'{' );
							if( posTmp++ < 0 )
								posL = posR;
							else
							{
								posL += posTmp;
								if( posL < posR )
									++kzL;
							}
						}
					}
					WCHAR* strKz = ::WQSG_getstrL( line , posR );
					if( NULL == strKz )
					{//�ڴ治��
						return TotalLen;
					}
					CWD_BIN* bin = m_MB2.get( (u8*)strKz , posR<<2 );

					if( NULL == bin )
					{//����
					}
					else
						TotalLen += bin->LEN ;

					delete[]strKz;

					line += (++posR);
				}
				break;
			case L'}'://��ʾ������
				++line;
				break;
			case L'\r'://��ʾ�س�
				++line;
				break;
			case L'\n'://��ʾ����
				++line;
				break;
			case L'\t'://��ʾ�Ʊ�
				++line;
				break;
			default:
				if( m_MB[ wCh ] )
				{
					TotalLen += m_MB[ wCh ]->LEN ;
				}
				else
				{//������ʾ
					TotalLen += ( (wCh <= 0xFF)?1:2 );
				}
				++line;
			}
		}
		return TotalLen;
	}
};
#endif
