// PlayerEngine.h: Schnittstelle für die Klasse CPlayerEngine.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLAYERENGINE_H__0AD00E67_FACF_420F_B8D9_DD226B91D9C9__INCLUDED_)
#define AFX_PLAYERENGINE_H__0AD00E67_FACF_420F_B8D9_DD226B91D9C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "blinkenparse.h"

typedef enum
{
	BLC_FRAME,
	BLC_COMPLETE,
	BLC_NEXTFILE,
	BLC_FILENAME,
} BLCOMMAND;

class CPlayerEngine  
{
public:
	BOOL IsDirectoryMode();
	BOOL IsRepeating();
	BOOL PlayNextFile (void);
	void InternalPlay (LPCTSTR filename);
	BOOL DirectoryMode (void);
	BOOL m_repeat;
	BOOL Repeat(void);
	void Stop(void);
	HANDLE m_stopevent;
	BOOL IsRunning (void);
	char * m_filebuff;
	BOOL m_running;
	BOOL PlayFile (LPCTSTR filename);
	static void PlayerThread (CPlayerEngine *ple);
	CPlayerEngine (HWND hwnd);
	virtual ~CPlayerEngine();
	HWND m_hwnd;
	CBlinkenParse m_parser;
	BOOL m_dirmode;
	CString m_path;
protected:
	HANDLE m_wfd_handle;
	WIN32_FIND_DATA m_wfd;
};

#endif // !defined(AFX_PLAYERENGINE_H__0AD00E67_FACF_420F_B8D9_DD226B91D9C9__INCLUDED_)
