/*  OpenWQSG - WQSG 导出(导入)
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
// IPS自解压GUI.cpp : 定义应用程序的入口点。
#include "stdafx.h"
#include "IPS自解压GUI.h"
#include <wchar.h>

//#include "..\..\..\WQSG库\WQSG_IPS.h"
#include <WQSG_IPS.h>
#include <WQSG_xFile.h>
#include <wqsg_filedlg.h>
#define MAX_LOADSTRING 100
//BOOL 读入IPS信息();
// 全局变量:
HINSTANCE hInst;								// 当前实例
INT_PTR CALLBACK	MainDlg(HWND, UINT, WPARAM, LPARAM);
TCHAR szTitle[MAX_LOADSTRING];		// 标题栏文本
s64 W_基础地址(0x88776655);

#if 0
#define WQSG_MSG( mes ) MessageBox( NULL , mes , NULL , 0 )
#else
#define WQSG_MSG( mes ) 
#endif
class WIPS联合
{
	s64	m_基础地址;
	u8	m_buf[0xFFFF];
	BOOL 打补丁30( ::CWQSG_File& IPS_File , ::CWQSG_File& ROM_File , HWND hwnd )
	{
		DWORD 长度;
		s64 指针位置 = 0;
		while(TRUE)
		{
			if( IPS_File.Read( m_buf , 1 ) != 1)
			{
				::MessageBox(hwnd,_T("打补丁失败\n补丁文件已损坏(5)"),szTitle,MB_OK);
				return FALSE;
			}
			switch( *m_buf )
			{
			case 0x01://相对偏移
				if( IPS_File.Read( m_buf , 4 ) != 4 )
				{
					::MessageBox(hwnd,_T("打补丁失败\n补丁文件已损坏(6.1)"),szTitle,MB_OK);
					return FALSE;
				}
				指针位置 += *((u32*)m_buf );
				break;
			case 0x02://绝对偏移
				if(IPS_File.Read( &指针位置 , 8 ) != 8)
				{
					::MessageBox(hwnd,_T("打补丁失败\n补丁文件已损坏(6.2)"),szTitle,MB_OK);
					return FALSE;
				}
				break;
			case 0xFF:
				return TRUE;
				break;
			default:
				::MessageBox(hwnd,_T("非法的WIPS补丁文件(2)"),szTitle,MB_OK);
				return FALSE;
			}
			长度 = 0;
			if( IPS_File.Read(&长度,2) != 2 )
			{
				::MessageBox(hwnd,_T("打补丁失败\n补丁文件已损坏(7))"),szTitle,MB_OK);
				return FALSE;
			}
			if( IPS_File.Read( m_buf , 长度 ) != 长度 )
			{
				::MessageBox(hwnd,_T("打补丁失败\n补丁文件已损坏(8)"),szTitle,MB_OK);
				return FALSE;
			}
			if( !ROM_File.Seek(指针位置) )
			{
				::MessageBox(hwnd,_T("打补丁失败\n设置ROM文件位置失败"),szTitle,MB_OK);
				return FALSE;
			}
			if( 长度 != ROM_File.Write( m_buf , 长度 ) )
			{
				::MessageBox(hwnd,_T("打补丁失败\n写数据失败"),szTitle,MB_OK);
				return FALSE;
			}
		}
	}
public:
	WCHAR m_信息[65536];
	CWD_WIPS信息 m_总联合头;
	WIPS联合()		:m_基础地址(W_基础地址)	{}
	~WIPS联合(){	}
	BOOL 读入IPS信息()
	{
		::memset(m_信息,0,sizeof(m_信息));
		TCHAR exeFullPath[MAX_PATH];
		{
			DWORD XXX = ::GetModuleFileName(NULL,exeFullPath,MAX_PATH);
			if(0 == XXX || 260 == XXX)
			{
				WQSG_MSG( L"获取路径失败" );
				return FALSE;
			}
		}

		CWQSG_File IPS_File;
		if( !IPS_File.OpenFile( exeFullPath , 1 , 3 ) )
		{
			WQSG_MSG( L"打开自己失败" );
			return FALSE;
		}

		if( !IPS_File.Seek( m_基础地址 ) )
		{
			WQSG_MSG( L"移动到 base 失败" );
			return FALSE;
		}

		m_基础地址 = IPS_File.Tell();

		UCHAR tmp0[17];

		if( IPS_File.Read(tmp0,16) != 16 )
		{
			WQSG_MSG( L"读取文件头失败" );
			return FALSE;
		}

		tmp0[16] = 0;
		///////////////////////////////
		int X,Y;
		if( 2 != ::sscanf_s((CHAR*)tmp0,"WQSG-PATCH%d.%d",&X,&Y) )
		{
			WQSG_MSG( L"转换文件头失败" );
			return FALSE;
		}

		{
			WCHAR*const tmp2 = ::WQSG_char_W((char*)tmp0);
			::WQSG_strcpy( tmp2 , m_总联合头.补丁标识 );
			delete[]tmp2;
		}

		switch(X)
		{
		case 1:
			WQSG_MSG( L"不支持 1.x" );
			return FALSE;
			break;
		case 2:
			WQSG_MSG( L"不支持2.x" );
			return FALSE;
			break;
		case 3:
			switch(Y)
			{
			case 0:
				if( IPS_File.Read( &m_总联合头.目标大小 , 8 ) != 8 )
				{
					WQSG_MSG( L"读目标大小失败" );
					return FALSE;
				}
				if( IPS_File.Read( &m_总联合头.验证CRC32 , 4 ) != 4 )
				{
					WQSG_MSG( L"读CRC失败" );
					return FALSE;
				}
				//取数据指针
				{
					s64 数据指针 = 0;
					if( IPS_File.Read( &数据指针 , 4 ) != 4 )
					{
						WQSG_MSG( L"读数据指针失败" );
						return FALSE;
					}

					s64 size = IPS_File.GetFileSize();
					if( 数据指针 < 40 || size <= 数据指针 )
					{
						WQSG_MSG( L"数据指针错误" );
						return FALSE;
					}
				}
				//取说明文本
				{
					s64 文件大小;
					if( IPS_File.Read( &文件大小 , 8 ) != 8 )
					{
						WQSG_MSG( L"读文本指针失败" );
						return FALSE;
					}

					if(文件大小)
					{
						IPS_File.Seek( m_基础地址 + 文件大小 );
						IPS_File.Read( m_总联合头.说明文本 , 65536 );
					}
				}
				break;
			default:
				return FALSE;
			}
			break;
		default:
			return FALSE;
		}
		if( m_总联合头.验证CRC32 != 0 )
		{
			::swprintf_s(m_信息,sizeof(m_信息),L"补丁版本: %s\r\n目标文件的CRC32验证: %08X\r\n打补丁后的文件大小: %lld",
				m_总联合头.补丁标识,
				m_总联合头.验证CRC32,
				m_总联合头.目标大小);
		}
		else
		{
			::swprintf_s(m_信息,sizeof(m_信息),L"补丁版本: %s\r\n目标文件的CRC32验证: 无\r\n打补丁后的文件大小: %lld",
				m_总联合头.补丁标识,
				m_总联合头.目标大小);
		}
		return TRUE;
	}
	BOOL 开始补丁(HWND hwnd)
	{
		WCHAR 补丁文件[MAX_PATH];
		{
			WCHAR* TMP = GetCommandLine();
			WCHAR* tmp = 补丁文件;

			if(*TMP == L'\"')
			{
				TMP++;
				while((*(tmp++) = *(TMP++)) != L'\"');
				*(--tmp) = '\0';
			}
			else
			{
				while((*(tmp++) = *(TMP++)) != L' ');
				*(--tmp) = '\0';
			}
		}
		WQSG_FileDlgW WQSG( FALSE , NULL , NULL , L"要打补丁的文件|*.*|" );
		if( WQSG.DoModal() != IDOK )
			return FALSE;

		WCHAR 目标文件[MAX_PATH+1];

		if(!WQSG.GetPathName(目标文件))
		{
			::MessageBox( hwnd , _T("失败代号01") , szTitle , MB_OK );
			return FALSE;
		}

		::CWQSG_File IPS_File,ROM_File;
		if( !IPS_File.OpenFile( 补丁文件 , 1 , 3 ) )
		{
			::MessageBox(hwnd,_T("补丁文件打开失败"),szTitle,MB_OK);
			return FALSE;
		}
		if( !ROM_File.OpenFile( 目标文件 , 3 , 3 ) )
		{
			::MessageBox(hwnd,_T("目标文件打开失败"),szTitle,MB_OK);
			return FALSE;
		}

		IPS_File.Seek( m_基础地址 );

		if( IPS_File.Read( m_buf , 16 ) != 16 )
		{
			::MessageBox(hwnd,_T("WIPS补丁文件已经损坏(1)"),szTitle,MB_OK);
			return FALSE;
		}

		m_buf[16] = 0;
		int X,Y;
		if(2 != ::sscanf_s((CHAR*)m_buf,"WQSG-PATCH%d.%d",&X,&Y) )
		{
			::MessageBox(hwnd,_T("WIPS补丁文件已经损坏(2)"),szTitle,MB_OK);
			return FALSE;
		}

		switch(X)
		{
		case 1:
			::MessageBox(hwnd,_T("暂不支持老版本的WIPS补丁文件"),szTitle,MB_OK);
			return FALSE;
			break;
		case 2:
			::MessageBox(hwnd,_T("暂不支持老版本的WIPS补丁文件"),szTitle,MB_OK);
			return FALSE;
			break;
		case 3:
			switch(Y)
			{
			case 0:
				{
					s64 文件大小;
					if( (IPS_File.Read(&文件大小,8) != 8) || ( 文件大小 < 0 ) )
					{
						::MessageBox(hwnd,_T("补丁文件已损坏(1)"),szTitle,MB_OK);
						return FALSE;
					}
					//CRC
					{
						u32 CRC32;
						if(IPS_File.Read( &CRC32 , 4 ) != 4)
						{
							::MessageBox(hwnd,_T("补丁文件已损坏(2)"),szTitle,MB_OK);
							return FALSE;
						}
						if(CRC32 != 0)
						{
							if(CRC32 != ROM_File.GetCRC32())
							{
								//if(IDOK != ::MessageBox(hwnd,_T("目标文件没有通过CRC32验证,要继续吗?"),szTitle,MB_OKCANCEL)){
								::MessageBox(hwnd,_T("目标文件没有通过CRC32验证"),szTitle,MB_OK);
								return FALSE;
								//}
							}
						}
					}
					//取数据指针
					{
						s64 数据指针 = 0;
						if(IPS_File.Read( &数据指针 ,4 ) != 4 )
						{
							::MessageBox(hwnd,_T("补丁文件已损坏(3)"),szTitle,MB_OK);
							return FALSE;
						}
						{
							s64 size = IPS_File.GetFileSize();
							if( 数据指针 < 40 || size <= 数据指针 )
							{
								::MessageBox(hwnd,_T("补丁文件已损坏(4)"),szTitle,MB_OK);
								return FALSE;
							}
						}
						if( ! ROM_File.SetFileLength(文件大小) )
						{
							::MessageBox(hwnd,_T("改变文件大小失败,可能是磁盘容量不足"),szTitle,MB_OK);
							return FALSE;
						}
						if( ! IPS_File.Seek( m_基础地址 + 数据指针) )
						{
							::MessageBox(hwnd,_T("设置文件指针错误(1)"),szTitle,MB_OK);
							return FALSE;
						}
					}
				}
				if( 打补丁30( IPS_File , ROM_File , hwnd ) )
				{
					::MessageBox(hwnd,_T("补丁成功"),szTitle,MB_OK);
					return TRUE;
				}
				return FALSE;
				break;
			default:
				::MessageBox(hwnd,_T("未知版本的WIPS补丁文件"),szTitle,MB_OK);
				return FALSE;
			}
			break;
		default:
			::MessageBox(hwnd,_T("未知版本的WIPS补丁文件"),szTitle,MB_OK);
			return FALSE;
		}
	}
} WQSG_WIPS联合;			// WIPS对象

int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 在此放置代码。

	// 初始化全局字符串
	hInst = hInstance;
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);


	return (int) DialogBox(hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), NULL, MainDlg);
}
INT_PTR CALLBACK MainDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		::SendMessage(hDlg,WM_SETICON,ICON_BIG,(LPARAM)::LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON2)));
		::SendMessage(hDlg,WM_SETICON,ICON_SMALL,(LPARAM)::LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON2)));
		SetWindowText(hDlg,szTitle);
#ifndef _DEBUG
		/////////////////////////////////
		if(!WQSG_WIPS联合.读入IPS信息())
		{
			MessageBox(hDlg,_T("初始化失败"),szTitle,MB_OK);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		/////////////////////////////////
		SetDlgItemText(hDlg,IDC_EDIT1,WQSG_WIPS联合.m_总联合头.说明文本);
#else
		SetDlgItemText(hDlg,IDC_EDIT1,L"123456");
#endif
		SendMessage( GetDlgItem( hDlg ,IDC_EDIT1 ) , EM_SETSEL , (WPARAM)2 , (LPARAM)2);
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		switch(LOWORD(wParam)){
	case IDOK:
		break;
	case IDCANCEL:
		if(IDOK == MessageBox(hDlg,_T("要退出?"),szTitle,MB_OKCANCEL)){
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	case IDC_CLOSE:
		MessageBox(NULL,szTitle,szTitle,MB_OK);
		break;
	case IDC_XINXI:
		MessageBox(hDlg,WQSG_WIPS联合.m_信息,szTitle,MB_OK);
		break;
	case IDC_BUTTON2:
		WQSG_WIPS联合.开始补丁(hDlg);
		break;
	default:
		break;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
