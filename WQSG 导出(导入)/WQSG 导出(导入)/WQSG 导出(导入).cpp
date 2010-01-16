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
// MFC.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "WQSG ����(����).h"
#include "WQSG_MAIN.h"


#include <stdio.h>
#include <tchar.h>
#include <locale.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static void printCmd()
{
#if 1
	printf("\n-------------------------------\n");
	printf("��ʽ:WQSG ������ ���� ���� ...\n");
	printf("-----------------------------------�������\n");
	printf(" e �����ı�\n");
	printf(" i �����ı�\n");
	printf("-----------------------------------������\n");
	printf(" -tbl \"%%s\"     ��ѡ  ���·��\n");
	printf(" -tbl2 \"%%s\"    ��ѡ  �������·��            Ĭ��:��\n");
	printf(" -checktbl     ��ѡ  ���������            Ĭ��:�����\n");
	printf(" -rom \"%%s\"     ��ѡ  rom·��\n");
	printf(" -text \"%%s\"    ��ѡ  �ı�·��\n");
	printf(" -start %%x     ��ѡ  ������     ��ʼ��ַ     Ĭ��:0\n");
	printf(" -end %%x       ��ѡ  ������     ������ַ     Ĭ��:FFFFFFFF\n");
	printf(" -min %%u       ��ѡ  ������     ��С����     Ĭ��:2\n");
	printf(" -max %%u       ��ѡ  ������     ������     Ĭ��:9999\n");
	printf(" -sp1 %%2X      ��ѡ  ������     ���ֽ����   Ĭ��:��\n");
 	printf(" -sp2 %%4X      ��ѡ  ������     ˫�ֽ����   Ĭ��:��\n");
 #else
// 	printf("\n-------------------------------\n");
// 	printf("��ʽ:WQSG ������ ���� ���� ...\n");
// 	printf("\n-----------------------------------�������\n");
// 	printf(" e �����ı�\n");
// 	printf(" i �����ı�\n");
// 	printf("\n-----------------------------------������\n");
// 	printf(" -tbl \"%s\"     ��ѡ  ���·��\n");
// 	printf(" -tbl2 \"%s\"    ��ѡ  �������·��            Ĭ��:��\n");
// 	printf(" -checktbl   ��ѡ  ���������            Ĭ��:�����\n");
//  	printf(" -rom \"%s\"     ��ѡ  rom·��\n");
//  	printf(" -text \"%s\"    ��ѡ  �ı�·��\n");
 //	printf(" -start %x   ��ѡ  ������     ��ʼ��ַ     Ĭ��:0\n");
 //	printf(" -end %x     ��ѡ  ������     ������ַ     Ĭ��:FFFFFFFF\n");
 //	printf(" -min %u     ��ѡ  ������     ��С����     Ĭ��:2\n");
 //	printf(" -max %u     ��ѡ  ������     ������     Ĭ��:9999\n");
 //	printf(" -sp1 %2X    ��ѡ  ������     ���ֽ����   Ĭ��:��\n");
//	printf(" -sp2 %4X    ��ѡ  ������     ˫�ֽ����   Ĭ��:��\n");
#endif
}

static int WQSG_Main( int nArgs , TCHAR* szArglist[] )
{
	if( nArgs < 8 )
	{
		printCmd();
		return -1;
	}

	//------------------------------��������
	const TCHAR* pTbl = NULL;
	const TCHAR* pTbl2 = NULL;
	BOOL bCheckTbl = FALSE;

	const TCHAR* pRom = NULL;
	const TCHAR* pTxt = NULL;
	//------------------------------��������
	s64 nStartPos = 0;
	s64 nEndPos = 0xFFFFFFFF;

	UINT uMin = 2;
	UINT uMax = 9999;
	//------------------------------���벿��
	const u8* pSP1 = NULL;
	const u16* pSP2 = NULL;
	u8 SP1;
	u16 SP2;

	for( int n = 2 ; n < nArgs ; ++n )
	{
		const TCHAR*const pArg =  szArglist[n];
		if( pArg[n] == _T('-') )
		{
			if( _tcsicmp( pArg , _T("-tbl") ) == 0 )
			{
				if( (n+1) < nArgs )
					pTbl = szArglist[++n];
			}
			else if( _tcsicmp( pArg , _T("-tbl2") ) == 0 )
			{
				if( (n+1) < nArgs )
					pTbl2 = szArglist[++n];
			}
			else if( _tcsicmp( pArg , _T("-checktbl") ) == 0 )
			{
				bCheckTbl = TRUE;
			}
			else if( _tcsicmp( pArg , _T("-rom") ) == 0 )
			{
				if( (n+1) < nArgs )
					pRom = szArglist[++n];
			}
			else if( _tcsicmp( pArg , _T("-text") ) == 0 )
			{
				if( (n+1) < nArgs )
					pTxt = szArglist[++n];
			}
			else if( _tcsicmp( pArg , _T("-start") ) == 0 )
			{
				if( (n+1) < nArgs )
				{
					nStartPos = 0; 
					if( 1 != _stscanf( szArglist[++n] , _T("%X") , &nStartPos ) )
					{
						return -1;
					}
				}
			}
			else if( _tcsicmp( pArg , _T("-end") ) == 0 )
			{
				if( (n+1) < nArgs )
				{
					nEndPos = 0; 
					if( 1 != _stscanf( szArglist[++n] , _T("%X") , &nEndPos ) )
					{
						return -1;
					}
				}
			}
			else if( _tcsicmp( pArg , _T("-min") ) == 0 )
			{
				if( (n+1) < nArgs )
				{
					uMin = 0; 
					if( 1 != _stscanf( szArglist[++n] , _T("%u") , &uMin ) )
					{
						return -1;
					}
				}
			}
			else if( _tcsicmp( pArg , _T("-max") ) == 0 )
			{
				if( (n+1) < nArgs )
				{
					uMax = 0; 
					if( 1 != _stscanf( szArglist[++n] , _T("%u") , &uMax ) )
					{
						return -1;
					}
				}
			}
			else if( _tcsicmp( pArg , _T("-sp1") ) == 0 )
			{
				if( (n+1) < nArgs )
				{
					int val = 0;
					if( 1 != _stscanf( szArglist[++n] , _T("%X") , &val ) )
					{
						return -1;
					}
					if( val < 0 || val > 0xFF )
					{
						return -1;
					}
					SP1 = (u8)val;
					pSP1 = &SP1;
				}
			}
			else if( _tcsicmp( pArg , _T("-sp2") ) == 0 )
			{
				if( (n+1) < nArgs )
				{
					int val = 0;
					if( 1 != _stscanf( szArglist[++n] , _T("%X") , &val ) )
					{
						return -1;
					}
					if( val < 0 || val > 0xFFFF )
					{
						return -1;
					}
					SP2 = (u16)val;
					pSP2 = &SP2;
				}
			}
		}
	}

	if( _tcsicmp( szArglist[1] , _T("I") ) == 0 )
	{
		printf( "����ģʽ\n" );

		static WQSG_TXT_I WQSG;
		if( !WQSG.LoadTbl( pTbl , pTbl2 , bCheckTbl ) )
			return -1;

		if( !WQSG.�����ı�( pRom , pTxt , pSP1 , pSP2 ) )
		{
			return -1;
		}
	}
	else if( _tcsicmp( szArglist[1] , _T("E") ) == 0 )
	{
		printf( "����ģʽ\n" );

		static CWQSG_TXT_O WQSG;
		if( !WQSG.LoadTbl( pTbl , pTbl2 , bCheckTbl ) )
			return -1;

		if( !WQSG.�����ı�( pRom , pTxt , nStartPos , nEndPos , uMin , uMax ) )
		{
			return -1;
		}
	}
	else
	{
		printCmd();
	}

	return 0;
}

#if 1

CWinApp theApp;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	setlocale( 0 , "" );
	int nRetCode = 0;

	if( argc > 1 )
	{
		nRetCode = WQSG_Main( argc , argv );
	}
	else
	{
		// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
		if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
		{
			// TODO: ���Ĵ�������Է���������Ҫ
			_tprintf(_T("����: MFC ��ʼ��ʧ��\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: �ڴ˴�ΪӦ�ó������Ϊ��д���롣
			FreeConsole();

			//////////////////////////////////////////
			TCHAR exeFullPath[MAX_PATH]; 
			GetModuleFileName(NULL,exeFullPath,MAX_PATH);
			CString ��ǰĿ¼ = exeFullPath;
			��ǰĿ¼ = ��ǰĿ¼.Left(��ǰĿ¼.ReverseFind(_T('\\')));
			��ǰĿ¼.Replace(_T('\\'),_T('?'));	
			const HANDLE WQSG_Mutex = ::CreateMutex(NULL,TRUE,��ǰĿ¼);

			if(WQSG_Mutex)
			{
				if(ERROR_ALREADY_EXISTS == ::GetLastError())
				{
					AfxMessageBox(_T("ͬһ��Ŀ¼��,����ͬʱ������������"));
					::ReleaseMutex(WQSG_Mutex);
					return FALSE;
				}
			}
			else
			{
				DWORD II = ::GetLastError();
				AfxMessageBox(_T("���ɻ���ʧ��"));
				return FALSE;
			}
			/////////////////////////////////////////
			INITCOMMONCONTROLSEX InitCtrls;
			InitCtrls.dwSize = sizeof(InitCtrls);
			// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
			// �����ؼ��ࡣ
			InitCtrls.dwICC = ICC_WIN95_CLASSES;
			InitCommonControlsEx(&InitCtrls);
			//	AfxEnableControlContainer();

			// ��׼��ʼ��
			// ���δʹ����Щ���ܲ�ϣ����С
			// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
			// ����Ҫ���ض���ʼ������
			// �������ڴ洢���õ�ע�����
			// TODO: Ӧ�ʵ��޸ĸ��ַ�����
			// �����޸�Ϊ��˾����֯��

			//	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

			CWQSG_MAIN dlg;
			INT_PTR nResponse = dlg.DoModal();
			if (nResponse == IDOK)
			{
				// TODO: �ڴ˴����ô����ʱ�á�ȷ�������ر�
				//  �Ի���Ĵ���
			}
			else if (nResponse == IDCANCEL)
			{
				// TODO: �ڴ˷��ô����ʱ�á�ȡ�������ر�
				//  �Ի���Ĵ���
			}
			ReleaseMutex(WQSG_Mutex);
		}
	}

	return nRetCode;
}
#else

// CMFCApp
BEGIN_MESSAGE_MAP(CWQSG��������App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCApp ����
CWQSG��������App::CWQSG��������App()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CMFCApp ����

CWQSG��������App theApp;


// CMFCApp ��ʼ��


BOOL CWQSG��������App::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	m_bCmdMode = FALSE;
	m_CmdR = 0;

	int nArgs = 0;
	LPWSTR* szArglist = CommandLineToArgvW( GetCommandLineW() , &nArgs );
	if( szArglist )
	{
		if( nArgs > 1 )
		{
			m_bCmdMode = TRUE;


			FILE* fp_out;
			FILE* fp_in;
			FILE* fp_err;
			//AllocConsole();

			AttachConsole( ATTACH_PARENT_PROCESS );
			freopen_s( &fp_out , "CONOUT$" , "w+t", stdout );
			freopen_s( &fp_in , "CONIN$" , "r+t" , stdin );
			freopen_s( &fp_err , "CONERR$" , "w+t" , stderr );


			m_CmdR = WQSG_Main( szArglist , nArgs );


			fclose(fp_out);
			fclose(fp_in);
			fclose(fp_err);
 			FreeConsole();
		}
		else
		{
			//////////////////////////////////////////
			TCHAR exeFullPath[MAX_PATH]; 
			GetModuleFileName(NULL,exeFullPath,MAX_PATH);
			CString ��ǰĿ¼ = exeFullPath;
			��ǰĿ¼ = ��ǰĿ¼.Left(��ǰĿ¼.ReverseFind(_T('\\')));
			��ǰĿ¼.Replace(_T('\\'),_T('?'));	
			const HANDLE WQSG_Mutex = ::CreateMutex(NULL,TRUE,��ǰĿ¼);

			if(WQSG_Mutex)
			{
				if(ERROR_ALREADY_EXISTS == ::GetLastError())
				{
					AfxMessageBox(_T("ͬһ��Ŀ¼��,����ͬʱ������������"));
					::ReleaseMutex(WQSG_Mutex);
					return FALSE;
				}
			}
			else
			{
				DWORD II = ::GetLastError();
				AfxMessageBox(_T("���ɻ���ʧ��"));
				return FALSE;
			}
			/////////////////////////////////////////
			INITCOMMONCONTROLSEX InitCtrls;
			InitCtrls.dwSize = sizeof(InitCtrls);
			// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
			// �����ؼ��ࡣ
			InitCtrls.dwICC = ICC_WIN95_CLASSES;
			InitCommonControlsEx(&InitCtrls);

			CWinApp::InitInstance();

			//	AfxEnableControlContainer();

			// ��׼��ʼ��
			// ���δʹ����Щ���ܲ�ϣ����С
			// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
			// ����Ҫ���ض���ʼ������
			// �������ڴ洢���õ�ע�����
			// TODO: Ӧ�ʵ��޸ĸ��ַ�����
			// �����޸�Ϊ��˾����֯��

			//	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

			CWQSG_MAIN dlg;
			m_pMainWnd = &dlg;
			INT_PTR nResponse = dlg.DoModal();
			if (nResponse == IDOK)
			{
				// TODO: �ڴ˴����ô����ʱ�á�ȷ�������ر�
				//  �Ի���Ĵ���
			}
			else if (nResponse == IDCANCEL)
			{
				// TODO: �ڴ˷��ô����ʱ�á�ȡ�������ر�
				//  �Ի���Ĵ���
			}
			ReleaseMutex(WQSG_Mutex);
		}
		LocalFree( szArglist );
	}
	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

int CWQSG��������App::ExitInstance()
{
	// TODO: �ڴ����ר�ô����/����û���
	int rt = CWinApp::ExitInstance();

	if( m_bCmdMode )
		rt = m_CmdR;

	return rt;
}

#endif

