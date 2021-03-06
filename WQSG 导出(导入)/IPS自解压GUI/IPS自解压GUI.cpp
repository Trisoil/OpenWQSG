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
#include <Common/WQSG_IPS.h>

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;								// 当前实例
INT_PTR CALLBACK	MainDlg(HWND, UINT, WPARAM, LPARAM);
TCHAR szTitle[MAX_LOADSTRING];		// 标题栏文本
n64 g_nBaseOffset(0x88776655);

CString g_strDesc;
CString g_strSelf;
CWD_WipsInfo g_wipsInfo;

int APIENTRY _tWinMain(HINSTANCE hInstance ,
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
		{
			TCHAR exeFullPath[MAX_PATH] = {};

			const DWORD XXX = ::GetModuleFileName( NULL , exeFullPath , MAX_PATH );
			if( 0 == XXX || XXX == 260 || !g_wipsInfo.LoadWipsDesc( exeFullPath , g_nBaseOffset ) )
			{
				MessageBox(hDlg,_T("初始化失败"),szTitle,MB_OK);
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}

			g_strSelf = exeFullPath;

			if( g_wipsInfo.m_uCrc32 != 0 )
			{
				g_strDesc.Format( L"补丁版本: %hs\r\n目标文件的CRC32验证: %08X\r\n打补丁后的文件大小: %lld",
					g_wipsInfo.m_szMagic ,
					g_wipsInfo.m_uCrc32 ,
					g_wipsInfo.m_nTargetSize );
			}
			else
			{
				g_strDesc.Format( L"补丁版本: %hs\r\n目标文件的CRC32验证: 无\r\n打补丁后的文件大小: %lld",
					g_wipsInfo.m_szMagic,
					g_wipsInfo.m_nTargetSize );
			}
			/////////////////////////////////
			SetDlgItemText( hDlg , IDC_EDIT1 , g_wipsInfo.m_szDesc );
		}
#else
		SetDlgItemText( hDlg , IDC_EDIT1 , L"123456\r\n123456\r\n123456\r\n123456\r\n123456\r\n123456\r\n123456123456\r\n123456\r\n123456\r\n123456\r\n123456\r\n123456\r\n123456" );
#endif
		PostMessage( GetDlgItem( hDlg ,IDC_EDIT1 ) , EM_SETSEL , (WPARAM)0 , (LPARAM)0 );
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
			break;
		case IDCANCEL:
			if( IDOK == MessageBox( hDlg , _T("要退出?") , szTitle , MB_OKCANCEL ) )
			{
				EndDialog( hDlg , LOWORD(wParam) );
				return (INT_PTR)TRUE;
			}
			break;
		case IDC_CLOSE:
			MessageBox(NULL,szTitle,szTitle,MB_OK);
			break;
		case IDC_XINXI:
			MessageBox( hDlg , g_strDesc , szTitle , MB_OK );
			break;
		case IDC_BUTTON2:
			do
			{
				static CWQSGFileDialog_Open openDlg( L"要打补丁的文件|*.*||" );
				if( openDlg.DoModal() != IDOK )
					break;

				if( g_wipsInfo.m_uCrc32 )
				{
					CWQSG_File fp;
					if( g_wipsInfo.m_uCrc32 != fp.GetCRC32() )
					{
						if( MessageBox( hDlg , L"目标文件没有通过CRC32验证，要继续打补丁吗?" , szTitle , MB_YESNO ) != IDYES )
							break;
					}
				}

				CWQSG_Ips_In wipsin;
				MessageBox( hDlg , wipsin.打补丁( g_strSelf.GetString() , openDlg.GetPathName().GetString() , g_nBaseOffset )
					?L"打补丁成功":wipsin.GetMsg() , szTitle , MB_OK );
			}
			while(FALSE);
			break;
		default:
			break;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
