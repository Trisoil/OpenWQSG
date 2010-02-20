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
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// �� Windows ͷ���ų�����ʹ�õ�����
#endif

// ���������ʹ��������ָ����ƽ̨֮ǰ��ƽ̨�����޸�����Ķ��塣
// �йز�ͬƽ̨����Ӧֵ��������Ϣ����ο� MSDN��
#ifndef WINVER				// ����ʹ���ض��� Windows XP ����߰汾�Ĺ��ܡ�
#define WINVER 0x0501		// ����ֵ����Ϊ��Ӧ��ֵ���������� Windows �������汾��
#endif

#ifndef _WIN32_WINNT		// ����ʹ���ض��� Windows XP ����߰汾�Ĺ��ܡ�
#define _WIN32_WINNT 0x0501	// ����ֵ����Ϊ��Ӧ��ֵ���������� Windows �������汾��
#endif						

#ifndef _WIN32_WINDOWS		// ����ʹ���ض��� Windows 98 ����߰汾�Ĺ��ܡ�
#define _WIN32_WINDOWS 0x0410 // ��������Ϊ�ʺ� Windows Me ����߰汾����Ӧֵ��
#endif

#ifndef _WIN32_IE			// ����ʹ���ض��� IE 6.0 ����߰汾�Ĺ��ܡ�
#define _WIN32_IE 0x0600	// ����ֵ����Ϊ��Ӧ��ֵ���������� IE �������汾��ֵ��
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>		// MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <WQSG_LIB.h>
#include <WQSG_DirDlg.h>
#include <2/WQSG_afx.h>
#include <WQSG��������.h>

#include "WQSG_cfg.h"

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


static BOOL WQSG_Is�Ϸ�FileName( const WCHAR* FileName )
{
	if( NULL == FileName )		return FALSE;

	while( ( L' ' == *FileName ) || ( L'��' == *FileName ) )
		++FileName;

	if( L'\0' == *FileName )		return FALSE;

//	BOOL ĩβ�հ� = FALSE;
	while( *FileName )
	{
		switch( *FileName )
		{
		case L'/':
		case L'\\':
		case L':':
		case L'*':
		case L'?':
		case L'\"':
		case L'<':
		case L'>':
		case L'|':
			return FALSE;
		case L' ':
		case L'��':
//			ĩβ�հ� = TRUE;
//			break;
		default:
//			ĩβ�հ� = FALSE;
			break;
		}
		++FileName;
	}

	return TRUE;
}
inline void ɾ���׿�( CString& str )
{
	const WCHAR* tmp = str.GetString();

	while( ( L' ' == *tmp ) || ( L'��' == *tmp ) )
		++tmp;

	str = tmp;
}
static BOOL ��֤Ext( CString test )
{
	CString ext;

	WCHAR* tmp = test.GetBuffer();

	if( L'\0' == *tmp )return FALSE;

	INT pos;
	INT count = 0;
	while( *tmp )
	{
		pos = WQSG_strchr( tmp , L';' );
		if( pos >= 0 )
		{
			tmp[ pos++ ] = '\0';
			ext = tmp;
			tmp += pos;
		}
		else
		{
			ext = tmp;
			*tmp = L'\0';
		}

		if( ext.GetLength() )
		{
			if( /*( ext != L"*" ) && */( !::WQSG_Is�Ϸ�FileName( ext.GetString() ) ))
			{
				return FALSE;
			}
			++count;
		}
	}
	return ( count > 0 );
}
static void �ֽ�Ext( CString test , std::vector<CStringW>& szExt )
{
	WCHAR* tmp = test.GetBuffer();
	while( *tmp )
	{
		CString ext;
		INT pos = WQSG_strchr( tmp , L';' );
		if( pos >= 0 )
		{
			tmp[ pos++ ] = '\0';
			ext = tmp;
			tmp += pos;
		}
		else
		{
			ext = tmp;
			*tmp = L'\0';
		}

		ɾ���׿�( ext );

		if( ext.GetLength() )
			szExt.push_back( L'.' + ext.MakeUpper() );
	}
}
/*
struct tgWM_��Ϣ
{
	HWND m_hWnd;
	UINT m_message;
	void SendMSG( WPARAM wParam, LPARAM lParam )
	{
		::SendMessage( m_hWnd , m_message , wParam , lParam );
	}
}*/
#pragma warning( disable : 4482 )
#pragma warning( disable : 4996 )
//------------------------------------------------------------------------
#pragma once
#define WIN32_LEAD_AND_MEAN
#include <windows.h>

#undef  ___i___
#define ___i___
class HiResTimer
{
private:
    static  inline  bool&       s_bTimerInstalled       ( void ) { static bool bTimerInstalled; return bTimerInstalled; }
    static  inline  __int64&    s_i64Freq               ( void ) { static __int64 i64Freq; return i64Freq; }
private:
    ___i___         bool        m_bRunning;
    ___i___         __int64     m_i64Start;
    ___i___         __int64     m_i64Stop;
private:
    static  inline  void        Initialize              ( void );
    static  inline  bool        IsInitialized           ( void );
public:
    static  inline  bool        IsAvailable             ( void );
public:
    ___i___ inline              HiResTimer              ( void );
    ___i___ inline  void        Reset                   ( void );
    ___i___ inline  void        Start                   ( void );
    ___i___ inline  void        Stop                    ( void );
public:
    ___i___ inline  bool        getIsRunning            ( void );
public:
    ___i___ inline  float       getElapsedTicks         ( void );
    ___i___ inline  float       getElapsedMilliseconds  ( void );
    ___i___ inline  float       getElapsedSeconds       ( void );
    ___i___ inline  float       getElapsedMinutes       ( void );
    ___i___ inline  float       getElapsedHours         ( void );
    ___i___ inline  float       getElapsedDays          ( void );
};
inline  void    HiResTimer::Initialize              ( void )
{
    s_bTimerInstalled() = ( 0 != QueryPerformanceFrequency( (LARGE_INTEGER*) &s_i64Freq() ) );
}

inline  bool    HiResTimer::IsInitialized           ( void )
{
    return ( s_bTimerInstalled() && s_i64Freq() != 0 );
}

inline  bool    HiResTimer::IsAvailable             ( void )
{
    if ( !IsInitialized() ) Initialize();
    return IsInitialized();
}

inline          HiResTimer::HiResTimer              ( void ) : m_i64Start(0), m_i64Stop(0), m_bRunning(false)
{
    if ( !IsInitialized() ) Initialize();
}

inline  void    HiResTimer::Reset                   ( void )
{
    m_i64Start = m_i64Stop = 0;
    m_bRunning = false;
}

inline  void    HiResTimer::Start                   ( void )
{
    QueryPerformanceCounter( (LARGE_INTEGER*) &m_i64Start );
    m_bRunning = true;
}

inline  void    HiResTimer::Stop                    ( void )
{
    QueryPerformanceCounter( (LARGE_INTEGER*) &m_i64Stop );
    m_bRunning = false;
}

inline  bool    HiResTimer::getIsRunning            ( void )
{
    return m_bRunning;
}

inline  float   HiResTimer::getElapsedTicks         ( void )
{
    __int64 i64elapsed = 0;
    float elapsed = 0.0f;

    if ( IsInitialized() )
    {
        if ( m_bRunning )
        {
            QueryPerformanceCounter( (LARGE_INTEGER*) &i64elapsed );
        }
        else
        {
            i64elapsed = m_i64Stop;
        }
        elapsed = (float) ( i64elapsed - m_i64Start );
    }
    return elapsed;
}

inline  float   HiResTimer::getElapsedMilliseconds  ( void )
{
    __int64 i64elapsed = 0;
    float elapsed = 0.0f;

    if ( IsInitialized() )
    {
        if ( m_bRunning )
        {
            QueryPerformanceCounter( (LARGE_INTEGER*) &i64elapsed );
        }
        else
        {
            i64elapsed = m_i64Stop;
        }
        elapsed = (float) ( ( i64elapsed - m_i64Start ) * 1000 / (float) s_i64Freq() );
    }
    return elapsed;
}

inline  float   HiResTimer::getElapsedSeconds       ( void )
{
    __int64 i64elapsed = 0;
    float elapsed = 0.0f;

    if ( IsInitialized() )
    {
        if ( m_bRunning )
        {
            QueryPerformanceCounter( (LARGE_INTEGER*) &i64elapsed );
        }
        else
        {
            i64elapsed = m_i64Stop;
        }
        elapsed = (float) ( ( i64elapsed - m_i64Start ) / (float) s_i64Freq() );
    }
    return elapsed;
}

inline  float   HiResTimer::getElapsedMinutes       ( void )
{
    __int64 i64elapsed = 0;
    float elapsed = 0.0f;

    if ( IsInitialized() )
    {
        if ( m_bRunning )
        {
            QueryPerformanceCounter( (LARGE_INTEGER*) &i64elapsed );
        }
        else
        {
            i64elapsed = m_i64Stop;
        }
        elapsed = (float) ( ( i64elapsed - m_i64Start ) / (float) s_i64Freq() / 60.0f );
    }
    return elapsed;
}

inline  float   HiResTimer::getElapsedHours         ( void )
{
    __int64 i64elapsed = 0;
    float elapsed = 0.0f;

    if ( IsInitialized() )
    {
        if ( m_bRunning )
        {
            QueryPerformanceCounter( (LARGE_INTEGER*) &i64elapsed );
        }
        else
        {
            i64elapsed = m_i64Stop;
        }
        elapsed = (float) ( ( i64elapsed - m_i64Start ) / (float) s_i64Freq() / 360.0f );
    }
    return elapsed;
}

inline  float   HiResTimer::getElapsedDays          ( void )
{
    __int64 i64elapsed = 0;
    float elapsed = 0.0f;

    if ( IsInitialized() )
    {
        if ( m_bRunning )
        {
            QueryPerformanceCounter( (LARGE_INTEGER*) &i64elapsed );
        }
        else
        {
            i64elapsed = m_i64Stop;
        }
        elapsed = (float) ( ( i64elapsed - m_i64Start ) / (float) s_i64Freq() / 8640.0f );
    }
    return elapsed;
}
struct WQSG_tgElapsedTime
{
	WORD wDay;
	WORD wHour;
	WORD wMinute;
	WORD wSecond;
	WORD wMilliseconds;
};
inline	void	WQSG_Milliseconds2struct( const float _Milliseconds , WQSG_tgElapsedTime& _tgTime )
{
	memset( &_tgTime , 0 , sizeof( WQSG_tgElapsedTime ) );
	float milliSeconds = _Milliseconds;

	_tgTime.wDay = (WORD)( milliSeconds / 86400000.0f );
	milliSeconds -= ( _tgTime.wDay * 86400000.0f );

	_tgTime.wHour = (WORD)( milliSeconds / 3600000.0f );
	milliSeconds -= ( _tgTime.wHour * 3600000.0f );

	_tgTime.wMinute = (WORD)( milliSeconds / 60000.0f );
	milliSeconds -= ( _tgTime.wMinute * 60000.0f );

	_tgTime.wSecond = (WORD)( milliSeconds / 1000.0f );
	_tgTime.wMilliseconds = (WORD)(milliSeconds - ( _tgTime.wSecond * 1000.0f ));
}

#include "atlstr.h"
