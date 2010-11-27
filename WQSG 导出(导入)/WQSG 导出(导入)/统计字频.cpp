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
// ͳ����Ƶ.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WQSG ����(����).h"
#include "ͳ����Ƶ.h"

#include <vector>
#include <list>
// Cͳ����Ƶ �Ի���
class CChars
{
public:
	struct SCharInfo
	{
		WCHAR m_char;
		BOOL m_bUnTbl;
	};

	struct SChars
	{
		u32 m_uCount;
		std::vector<SCharInfo> m_Chars;
	};

	std::list<SChars> m_Chars;

	void AddCharS2B( u32 a_uCount , WCHAR a_Ch , BOOL a_bUnTbl )
	{
		std::list<SChars>::iterator it = m_Chars.begin();

		for( ; it != m_Chars.end() ; ++it )
		{
			SChars& data = *it;

			if( data.m_uCount == a_uCount )
			{
				SCharInfo tmpInfo;
				tmpInfo.m_char = a_Ch;
				tmpInfo.m_bUnTbl = a_bUnTbl;

				data.m_Chars.push_back( tmpInfo );
				return;
			}
			else if( data.m_uCount > a_uCount )
			{
				SCharInfo tmpInfo;
				tmpInfo.m_char = a_Ch;
				tmpInfo.m_bUnTbl = a_bUnTbl;

				SChars tmp;
				tmp.m_uCount = a_uCount;
				tmp.m_Chars.push_back( tmpInfo );
				m_Chars.insert( it , tmp );
				return;
			}
		}

		SCharInfo tmpInfo;
		tmpInfo.m_char = a_Ch;
		tmpInfo.m_bUnTbl = a_bUnTbl;

		SChars tmp;
		tmp.m_uCount = a_uCount;
		tmp.m_Chars.push_back( tmpInfo );
		m_Chars.push_back( tmp );
	}
	void AddCharB2S( u32 a_uCount , WCHAR a_Ch , BOOL a_bUnTbl )
	{
		std::list<SChars>::iterator it = m_Chars.begin();

		for( ; it != m_Chars.end() ; ++it )
		{
			SChars& data = *it;

			if( data.m_uCount == a_uCount )
			{
				SCharInfo tmpInfo;
				tmpInfo.m_char = a_Ch;
				tmpInfo.m_bUnTbl = a_bUnTbl;

				data.m_Chars.push_back( tmpInfo );
				return;
			}
			else if( data.m_uCount < a_uCount )
			{
				SCharInfo tmpInfo;
				tmpInfo.m_char = a_Ch;
				tmpInfo.m_bUnTbl = a_bUnTbl;

				SChars tmp;
				tmp.m_uCount = a_uCount;
				tmp.m_Chars.push_back( tmpInfo );
				m_Chars.insert( it , tmp );
				return;
			}
		}

		SCharInfo tmpInfo;
		tmpInfo.m_char = a_Ch;
		tmpInfo.m_bUnTbl = a_bUnTbl;

		SChars tmp;
		tmp.m_uCount = a_uCount;
		tmp.m_Chars.push_back( tmpInfo );
		m_Chars.push_back( tmp );
	}
};

void ȡ���ֽڱ���(int*��λ,int*��λ,WCHAR*λ��)
{
	::swprintf(λ��,3,L"%02x",(*��λ)++);
	if(*��λ > 255)
		*��λ = 0;
}
void ȡ˫�ֽڱ���_��(int*��λ,int*��λ,WCHAR*λ��)
{
	::swprintf(λ��++,3,L"%02x",*��λ);
	::swprintf(++λ��,3,L"%02x",(*��λ)++);
	if(*��λ > 255)
	{
		*��λ = 0;(*��λ)++;
		if(*��λ > 255)
			*��λ = 0;
	}
}
void ȡ˫�ֽڱ���_��(int*��λ,int*��λ,WCHAR*λ��)
{
	::swprintf(λ��++,3,L"%02x",(*��λ)++);
	::swprintf(++λ��,3,L"%02x",*��λ);
	if(*��λ > 255)
	{
		*��λ = 0;
		(*��λ)++;
		if(*��λ > 255)
			*��λ = 0;
	}
}
void ��ʼ����(::CWQSG_File * TBL_File,const WCHAR*�ı�,int ��λ,int ��λ,void(*ȡ������)(int*��λ,int*��λ,WCHAR*λ��))
{
	TBL_File->Write("\xff\xfe",2);
	WCHAR ������[5];
	CStringW ���;
	while(*�ı�)
	{
		if(0x20 > *�ı�)
		{
			�ı�++;
			continue;
		}
		ȡ������(&��λ,&��λ,������);
		��� = ������;
		��� += L'=';
		��� += *(�ı�++);
		��� += L"\15\12";
		TBL_File->Write(���.GetString(),(���.GetLength()<<1));
	}
}
IMPLEMENT_DYNAMIC(Cͳ����Ƶ, CBaseDialog)

void Cͳ����Ƶ::����()
{
	for( int i = 0 ; i < (sizeof(m_Info)/sizeof(*m_Info)) ; i++ )
		m_Info[i].Clean();
}
void Cͳ����Ƶ::ͳ��һ����Ƶ_���˿��Ʒ�(const WCHAR* TXT)
{
	while(*TXT)
	{
		if(W_KZF_L == *TXT)
		{
			UINT ���������� = 1,�ұ��������� = 0;
			TXT++;
			while(���������� != �ұ���������
				&& NULL != *TXT)
			{
				if(W_KZF_L == *TXT)
				{
					����������++;
				}
				else if(W_KZF_R == *TXT)
				{
					�ұ���������++;
				}
				TXT++;
			}
		}
		else if(W_KZF_R == *TXT)
		{
			TXT++;
		}
		else if(0x20 > *TXT)
		{
			TXT++;
		}
		else
		{
			m_Info[*TXT].m_uCount++;

			TXT++;
		}
	}
}
void Cͳ����Ƶ::ͳ��һ����Ƶ_���ı�(const WCHAR* TXT)
{
	while(*TXT)
	{
		if(0x20 > *TXT)
		{
			TXT++;
		}
		else
		{
			m_Info[*TXT].m_uCount++;

			TXT++;
		}
	}
}
BOOL Cͳ����Ƶ::�������()
{
	::CMemTextW WQSG;
	if(FALSE == WQSG.Load(W_����ַ.GetString(),(DWORD)10485760))
	{
		MessageBoxW( W_����ַ + L"\r\n" + WQSG.GetErrTXT() );
		return FALSE;
	}

	while(const WCHAR* _line = WQSG.GetLine() )
	{
		WCHAR* tmp = ::WQSG_DelSP_L(_line);
		delete[]_line;
		if(0 == *tmp)
		{
			delete[]tmp;
			continue;
		}
		/////////////////////////////
		INT I = ::WQSG_strchr(tmp,L'=');
		if(-1 == I)
		{
			CStringW message(L"����,�Ҳ��� =\n\n");
			message += tmp;
			delete[]tmp;
			MessageBoxW(message);
			return FALSE;
		}
		//////////////////////////////////
		_line = ::WQSG_getstrL(tmp + I + 1,-1);
		if(0 == ::WQSG_strlen(_line))
		{
			CStringW message(L"����,����ұ�ֻ����һ����\n\n");
			message += tmp;
			delete[]tmp;
			MessageBoxW(message);
			return FALSE;
		}
		delete[]tmp;
		////////////////////////////////
		m_Info[*_line].m_bUnTbl = FALSE;
		delete[]_line;
	}
	return TRUE;
}
void Cͳ����Ƶ::OnOK()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
void Cͳ����Ƶ::OnCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

INT_PTR Cͳ����Ƶ::DoModal()
{
	if(0 == W_��������)
	{
		W_�������� = 1;
		return CBaseDialog::DoModal();
	}
	return IDCANCEL;
}
BOOL Cͳ����Ƶ::Create(UINT nIDTemplate, CWnd* pParentWnd)
{
	if(0 == W_��������)
	{
		W_�������� = 2;
		return CBaseDialog::Create(nIDTemplate,pParentWnd);
	}
	return FALSE;
}
Cͳ����Ƶ::Cͳ����Ƶ(CWnd* pParent /*=NULL*/)
	: CBaseDialog(Cͳ����Ƶ::IDD, pParent)
	, W_����ַ(_T(""))
	, W_��ʾ��(_T(""))
	, W_���Ʒ�����(0)
	, W_�������(FALSE)
	, W_ͳ��ģʽ(FALSE)
	, W_�ȴ��������(_T(""))
	, W_��һ������(_T(""))
	, W_�ߵͽ���(FALSE)
	, W_��������(0)
	, W_�����(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_WQSG);
	����();
}

Cͳ����Ƶ::~Cͳ����Ƶ()
{
	switch(W_��������)
	{
	case 1://ģ̬
		W_�������� = 0;
		CBaseDialog::OnCancel();
		break;
	case 2://��ģ̬
		W_�������� = 0;
		DestroyWindow();
		break;
	default://������
		break;
	}
}

void Cͳ����Ƶ::DoDataExchange(CDataExchange* pDX)
{
	CBaseDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TBL_TBL, W_����ַ);
	DDV_MaxChars(pDX, W_����ַ, MAX_PATH);
	DDX_Text(pDX, IDC_EDIT_TBL_1, W_��ʾ��);
	DDX_CBIndex(pDX, IDC_COMBO_TBL_1, W_���Ʒ�����);
	DDX_Check(pDX, IDC_CHECK_TBL_TBL, W_�������);
	DDX_Radio(pDX, IDC_RADIO_TBL_1, W_ͳ��ģʽ);
	DDX_Text(pDX, IDC_EDIT_TBL_2, W_�ȴ��������);
	DDX_Text(pDX, IDC_EDIT_TBL_3, W_��һ������);
	DDV_MaxChars(pDX, W_��һ������, 4);
	DDX_Check(pDX, IDC_CHECK_TBL_1, W_�ߵͽ���);
	DDX_Text(pDX, IDC_EDIT1, W_�����);
	DDV_MaxChars(pDX, W_�����, MAX_PATH);
	DDX_Control(pDX, IDC_COMBO_OUT, m_OutType);
}


BEGIN_MESSAGE_MAP(Cͳ����Ƶ, CBaseDialog)
	ON_BN_CLICKED(IDC_BUTTON_TBL_TBL, &Cͳ����Ƶ::OnBnClickedButtonTbl)
	ON_BN_CLICKED(IDC_BUTTON_TBL_2, &Cͳ����Ƶ::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_CHECK_TBL_TBL, &Cͳ����Ƶ::OnBnClickedCheckTbl)
	ON_EN_CHANGE(IDC_EDIT_TBL_3, &Cͳ����Ƶ::OnEnChangeEdit3)
	ON_BN_CLICKED(IDC_CHECK1, &Cͳ����Ƶ::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON_TBL_3, &Cͳ����Ƶ::OnBnClickedButtonTbl3)
	ON_BN_CLICKED(IDC_BUTTON3, &Cͳ����Ƶ::OnBnClickedButton3)
	ON_WM_LBUTTONDOWN()
	ON_EN_KILLFOCUS(IDC_EDIT_TBL_3, &Cͳ����Ƶ::OnEnKillfocusEditTbl3)
	ON_WM_CLOSE()
END_MESSAGE_MAP()// Cͳ����Ƶ ��Ϣ�������
BOOL Cͳ����Ƶ::OnInitDialog()
{
	CBaseDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	while( m_OutType.GetCount() )
		m_OutType.DeleteString( 0 );
	m_OutType.AddString( L"Unicode ����˳�� [Ĭ��]" );
	m_OutType.AddString( L"��Ƶ����" );
	m_OutType.AddString( L"��Ƶ����" );
	m_OutType.SetCurSel( 0 );


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ��������Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó����⽫�ɿ���Զ���ɡ�

void Cͳ����Ƶ::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CBaseDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR Cͳ����Ƶ::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cͳ����Ƶ::OnBnClickedButtonTbl()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();

	static CWQSGFileDialog_Save fopendlg( _T("����ļ�(*.TBL,*.TXT)|*.TBL;*.TXT||") );
	fopendlg.SetWindowTitle( _T("ѡ��һ�����...") );

	if(IDOK == fopendlg.DoModal())
	{
		W_����ַ = fopendlg.GetPathName();
	}
	UpdateData(FALSE);
}
void Cͳ����Ƶ::OnBnClickedCheckTbl()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	(GetDlgItem(IDC_EDIT_TBL_TBL))->EnableWindow( W_������� );
}

void Cͳ����Ƶ::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	W_�ȴ�������� = W_��ʾ�� = _T("");
	UpdateData(FALSE);
	����();
	if(W_�������)
	{
		if( !�������() )
			return;
	}

	static CWQSGFileDialog_OpenS fopendlg( _T("�ı��ļ�(*.TXT)|*.TXT||") );
	fopendlg.SetWindowTitle( _T("ѡ��Ҫͳ�Ƶ��ı�...") );

	if(IDOK == fopendlg.DoModal())
	{
		POSITION pos = fopendlg.GetStartPosition();
		UINT ���� = 0;
		CString �ļ�;
		while(fopendlg.GetNextPathName(�ļ�,pos))
		{
			::CMemTextW WQSG;
			if(FALSE == WQSG.Load(�ļ�.GetString(),(DWORD)10485760))
			{
				MessageBoxW(�ļ� + L"\r\n" + WQSG.GetErrTXT() );
				return;
			}
			if(W_���Ʒ�����)
			{
				W_KZF_L = L'[';W_KZF_R = L']';
			}
			else
			{
				W_KZF_L = L'{';W_KZF_R = L'}';
			}
			����++;
			switch(W_ͳ��ģʽ)
			{
			case 0:
				while(const WCHAR * _line = WQSG.GetLine())
				{
					///////////////////////////////////
					WCHAR* tmp = ::WQSG_DelSP_L(_line);
					delete[]_line;
					if(0 == *tmp)
					{
						delete[]tmp;
						continue;
					}
					_line = tmp;
					////////////////////////////////
					UINT k = ::WQSG_strchr(tmp,L',');
					if(-1 == k)
					{
						�ļ� += L"\n����,�Ҳ�����һ������,\n\n";
						�ļ� += _line;
						delete[]_line;
						MessageBoxW(�ļ�);
						return;
					}
					tmp += (k + 1);
					//////////////////////////////////////////
					k = ::WQSG_strchr(tmp,L',');
					if(-1 == k)
					{
						�ļ� += L"\n����,�Ҳ����ڶ�������,\n\n";
						�ļ� += _line;
						delete[]_line;
						MessageBoxW(�ļ�);
						return;
					}
					tmp += (k + 1);
					///////////////////////////////////
					tmp = ::WQSG_getstrL(tmp,-1);
					delete[]_line;
					ͳ��һ����Ƶ_���˿��Ʒ�(tmp);
					delete[]tmp;
				}
				break;
			case 1:
				while(const WCHAR* _line = WQSG.GetLine())
				{
					ͳ��һ����Ƶ_���ı�(_line);
					delete[]_line;
				}
				break;
			case 2:
				MessageBox(_T("��ʱ��֧�ִ�ͳ��ģʽ"));
				return;
				break;
			default:
				MessageBox(_T("???"));;
			}
		}
		//////////////////////////// ͳ����β
		CStringW δ����,��Ƶ��;
		UINT �ֵĸ��� = 0,δ����ĸ��� = 0;
		switch ( m_OutType.GetCurSel() )
		{
		case 1:
		case 2:
			{
				CChars info;

				if( m_OutType.GetCurSel() == 1 )
				{
					for( int i = 0x0 ; i < (sizeof(m_Info)/sizeof(*m_Info)) ; i++ )
						if( m_Info[i].m_uCount )
							info.AddCharB2S( m_Info[i].m_uCount , (WCHAR)i , m_Info[i].m_bUnTbl );
				}
				else
				{
					for( int i = 0x0 ; i < (sizeof(m_Info)/sizeof(*m_Info)) ; i++ )
						if( m_Info[i].m_uCount )
							info.AddCharS2B( m_Info[i].m_uCount , (WCHAR)i , m_Info[i].m_bUnTbl );
				}
				//=====================================================================
				 for( std::list<CChars::SChars>::iterator it = info.m_Chars.begin() ;
					 it != info.m_Chars.end() ; it++ )
				{
					const CChars::SChars& chars = *it;
					const std::vector<CChars::SCharInfo>& charInfo = chars.m_Chars;

					for( std::vector<CChars::SCharInfo>::const_iterator itInfo = charInfo.begin() ;
						itInfo != charInfo.end() ; ++itInfo )
					{
						const CChars::SCharInfo& tmpInfo = *itInfo;

						if( tmpInfo.m_bUnTbl )
						{
							δ���� += tmpInfo.m_char;
							δ����ĸ���++;
						}

						��Ƶ��.AppendFormat( L"%c     %u\r\n" , tmpInfo.m_char , chars.m_uCount );
						�ֵĸ���++;
					}
				}
			}
			break;
		default:
			for( int i = 0x0 ; i < (sizeof(m_Info)/sizeof(*m_Info)) ; i++ )
			{
				if( m_Info[i].m_uCount )
				{
					if( m_Info[i].m_bUnTbl )
					{
						δ���� += (WCHAR)i;
						δ����ĸ���++;
					}
					��Ƶ��.AppendFormat( L"%c     %u\r\n" , (WCHAR)i , m_Info[i].m_uCount );
					�ֵĸ���++;
				}
			}
		}
		///////////////////// �����Ƶ
		W_�ȴ�������� += δ����;
		W_��ʾ��.Format( L"****** ������ͳ�� ******\15\12�ֵ�����:  %u\15\12δ���������:  %u" , �ֵĸ��� , δ����ĸ��� );
		W_��ʾ�� += _T("\15\12****** ���ֵ�Ƶ�� ******\15\12");	
		W_��ʾ�� += ��Ƶ��;
		��Ƶ�� = L"";
		UpdateData(FALSE);
		δ����.Format( _T("ͳ�����\n��ͳ��%u���ļ�") , ���� );
		MessageBox( δ���� );
	}
}

void Cͳ����Ƶ::OnEnChangeEdit3()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	EditCheckHaxStr(W_��һ������,(CEdit*)GetDlgItem(IDC_EDIT_TBL_3),(CWnd*)this,0);
}

void Cͳ����Ƶ::OnEnKillfocusEdit3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(W_��һ������.GetLength()&1)
	{
		W_��һ������ = _T("0") + W_��һ������;
		UpdateData(FALSE);
		//MessageBox(_T("HEX ��λ������Ϊ 2 �ı���"));
		//(CEdit*)GetDlgItem(IDC_EDIT_TBL_3)->SetFocus();
	}
}


void Cͳ����Ƶ::OnBnClickedCheck1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BOOL ѡ�� = ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck();
	GetDlgItem(IDC_EDIT_TBL_3)->EnableWindow(!ѡ��);
	GetDlgItem(IDC_CHECK_TBL_1)->EnableWindow(!ѡ��);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(ѡ��);
	GetDlgItem(IDC_EDIT1)->EnableWindow(ѡ��);
}

void Cͳ����Ƶ::OnBnClickedButtonTbl3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	BOOL ����� = ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck();

	INT LLLEN;
	if(�����)
	{
		if(W_�����.GetLength() == 0)
		{
			MessageBox(_T("����� ����Ϊ��"));
			return;
		}
	}
	else
	{
		if(0 == (LLLEN = W_��һ������.GetLength()))
		{
			MessageBox(_T("�ױ��� ����Ϊ��"));
			return;
		}
	}
	///////////////////////////
	static CWQSGFileDialog_Save fopendlg( _T("����ļ�(*.TBL)|*.TBL||") , _T("TBL") );
	fopendlg.SetWindowTitle( _T("����浽...") );
 
	if(IDOK == fopendlg.DoModal())
	{
		::CWQSG_File TBL_File;
		if(! TBL_File.OpenFile(fopendlg.GetPathName().GetString() , 4 , 3 ))
		{
			MessageBox(_T("�������ʧ��"));
			return;
		}
		if(�����)
		{
			if(!��������(&TBL_File))
			{
				return;
			}
		}
		else
		{
			int ��λ,��λ;
			const TCHAR* s1 = W_��һ������.GetString();
			switch(LLLEN)
			{
			case 2:
				::_stscanf_s(s1,_T("%2x"),&��λ);
				��λ = 0;
				��ʼ����(&TBL_File,W_�ȴ��������.GetString(),��λ,��λ,&::ȡ���ֽڱ���);
				break;
			case 4:
				::_stscanf_s(s1++,_T("%2x"),&��λ);
				::_stscanf_s(++s1,_T("%2x"),&��λ);
				if(W_�ߵͽ���)
					��ʼ����(&TBL_File,W_�ȴ��������.GetString(),��λ,��λ,&::ȡ˫�ֽڱ���_��);
				else
					��ʼ����(&TBL_File,W_�ȴ��������.GetString(),��λ,��λ,&::ȡ˫�ֽڱ���_��);
				break;
			default:
				MessageBox(_T("??? 2"));
				return;
			}
		}
		MessageBox(_T("���"));
	}
	UpdateData(FALSE);
}

void Cͳ����Ƶ::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();

	static CWQSGFileDialog_Open fopendlg( _T("�����(*.TBL,*.TXT)|*.TBL;*.TXT||") );
	fopendlg.SetWindowTitle( _T("ѡ��һ��������...") );

	if(IDOK == fopendlg.DoModal())
	{
		W_����� = fopendlg.GetPathName();
	}
	UpdateData(FALSE);
}

BOOL Cͳ����Ƶ::��������(::CWQSG_File * TXT_File)
{
	UpdateData();
	if(W_�����.GetLength() == 0)
	{
		MessageBox(_T("����ѡ��һ�������."));
		return FALSE;
	}
	::CMemTextW WQSG;
	if( !WQSG.Load( W_�����.GetString() , 33554432 ) )
	{
		MessageBox(W_����� + L"\r\n" + WQSG.GetErrTXT() ,L"��������");
		return FALSE;
	}
	::CWQSG_MSG_W �Ի���(m_hWnd,L"��������");
	const WCHAR * �ַ��� = W_�ȴ��������.GetString();

	const WCHAR* pLine;
	WCHAR * tmp, * tmp2;
	CString �ı�;
	TXT_File->Write("\377\376",2);
	while(*�ַ���)
	{
		if(*�ַ��� < 0x20)
		{
			�ַ���++;
			continue;
		}
		pLine = WQSG.GetLine();
		if(NULL == pLine)
		{
			�ı� = *�ַ���;
			�Ի���.show( �ı�.GetString() , L"������������" );
			return FALSE;
		}

		tmp = ::WQSG_DelSP_L(pLine);
		if(0 == *tmp)
		{
			delete[]pLine;
			delete[]tmp;
			continue;
		}
		UINT λ�� = ::WQSG_strchr(tmp,L'=');
		if(-1 == λ��)
		{
			delete[]tmp;
			if(IDOK != �Ի���.show(pLine,L"�Ҳ����Ⱥ�,��������,Ҫ������?",MB_YESNO))
			{
				delete[]pLine;
				return FALSE;
			}
			delete[]pLine;
			continue;
		}
		tmp2 = ::WQSG_getstrL(tmp,λ��);
		delete[]tmp;
		λ�� = ::WQSG_strlen(tmp2);
		if( λ�� & 1//Ϊ����
			|| 0 == λ��
			|| !::WQSG_IsHexText(tmp2)
		)
		{
			delete[]tmp2;
			if(IDOK != �Ի���.show( pLine , L"�Ⱥ���߲�����Ч��ʮ�������ı�,��������,Ҫ������?" , MB_YESNO) )
			{
				delete[]pLine;
				return FALSE;
			}
			delete[]pLine;
			continue;
		}
		�ı� = tmp2;
		�ı� += L'=';
		�ı� += *(�ַ���++);
		�ı� += L"\r\n";
		TXT_File->Write( �ı�.GetString() , �ı�.GetLength()*sizeof(*�ı�.GetString()) );
		delete[]pLine;
		delete[]tmp2;
	}
	return FALSE;
}
void Cͳ����Ƶ::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));

	CBaseDialog::OnLButtonDown(nFlags, point);
}

void Cͳ����Ƶ::OnEnKillfocusEditTbl3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(W_��һ������.GetLength()&1)
	{
		W_��һ������.Insert(0,L'0');
		UpdateData(FALSE);
	}
}

void Cͳ����Ƶ::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CBaseDialog::OnClose();
//	if( IDOK == MessageBox(_T("�Ƿ�Ҫ�˳�?"),NULL,MB_OKCANCEL) )
//	{
		//ReleaseMutex(WQSG_Mutex);
		switch(W_��������)
		{
		case 1://ģ̬
			W_�������� = 0;
			CBaseDialog::OnCancel();
			break;
		case 2://��ģ̬
			W_�������� = 0;
			DestroyWindow();
			break;
		default://������
			break;
		}
//	}
}
