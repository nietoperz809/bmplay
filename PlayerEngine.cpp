// PlayerEngine.cpp: Implementierung der Klasse CPlayerEngine.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "PlayerEngine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CPlayerEngine::CPlayerEngine (HWND hwnd)
{
	m_hwnd = hwnd;
	m_running = FALSE;
	m_stopevent = CreateEvent (NULL, FALSE, FALSE, "Stopper");
	m_repeat = FALSE;
	m_dirmode = FALSE;
	m_path = "";
	m_wfd_handle = NULL;
}

CPlayerEngine::~CPlayerEngine()
{

}

// Static
void CPlayerEngine::PlayerThread (CPlayerEngine *ple)
{
	DWORD idx = 0;
	COPYDATASTRUCT cpd;

	ple->m_running = TRUE;
	ple->m_parser.Reset();

	while (1)
	{
		while (1)
		{
			BLPSTATE blp = ple->m_parser.ParseFSM (ple->m_filebuff[idx++]);
			if (blp == BLP_READY)
				break;
			if (blp == BLP_END || WaitForSingleObject (ple->m_stopevent, 0) == WAIT_OBJECT_0) 
			{
				if (ple->m_dirmode == TRUE)
				{
					delete[] ple->m_filebuff;
					ple->m_running = FALSE;
					cpd.dwData = BLC_NEXTFILE;
					SendMessage (ple->m_hwnd, WM_COPYDATA, (UINT)0, (long)&cpd);
				}
				else if (ple->m_repeat == TRUE)
					AfxBeginThread ((AFX_THREADPROC)PlayerThread, ple);
				else
				{
					delete[] ple->m_filebuff;
					ple->m_running = FALSE;
					cpd.dwData = BLC_COMPLETE;
					SendMessage (ple->m_hwnd, WM_COPYDATA, (UINT)0, (long)&cpd);
				}
				return;
			}
		}
		cpd.lpData = ple->m_parser.m_array;
		cpd.cbData = 144;
		cpd.dwData = BLC_FRAME;
		SendMessage (ple->m_hwnd, WM_COPYDATA, (UINT)0, (long)&cpd);
		Sleep (ple->m_parser.m_delay);
	}
}

// Play file by name
void CPlayerEngine::InternalPlay (LPCTSTR filename)
{
	// Send filename to the mainwnd
	char fname[MAX_PATH];
	_splitpath (filename, NULL, NULL, fname, NULL);
	COPYDATASTRUCT cpd;
	cpd.dwData = BLC_FILENAME;
	cpd.cbData = strlen (fname) + 1;
	cpd.lpData = fname;
	SendMessage (m_hwnd, WM_COPYDATA, (UINT)0, (long)&cpd); 

	CFile cf (filename, CFile::modeRead);
	DWORD filesize = cf.GetLength();
	m_filebuff = new char[filesize+1];
	cf.Read (m_filebuff, filesize);
	m_filebuff[filesize] = 0;
	AfxBeginThread ((AFX_THREADPROC)PlayerThread, this);
}

BOOL CPlayerEngine::PlayNextFile()
{
	if (FALSE == FindNextFile (m_wfd_handle, &m_wfd))
	{
		FindClose (m_wfd_handle);
		if (m_repeat == TRUE)
			PlayFile (m_path);
		return FALSE;
	} 
	else
	{
		CString name = m_path + m_wfd.cFileName;
		InternalPlay (name);
	}
	return TRUE;
}

BOOL CPlayerEngine::PlayFile (LPCTSTR filename)
{
	if (m_running == TRUE)
		return FALSE;
	
	if (m_dirmode)
	{
		// Extract the path
		char drive[256];
		char dir[256];
		_splitpath (filename, drive, dir, NULL, NULL);
		m_path = drive;
		m_path += dir;
		// Play first file
		CString first = m_path + "*.blm";
		m_wfd_handle = FindFirstFile ((LPCTSTR)first, &m_wfd);
		if (m_wfd_handle == NULL)
			return FALSE;
		first = m_path + m_wfd.cFileName;
		InternalPlay (first);
	}
	else
		InternalPlay (filename);

	return TRUE;
}

BOOL CPlayerEngine::IsRunning()
{
	return m_running;
}

void CPlayerEngine::Stop()
{
	m_repeat = FALSE;
	m_dirmode = FALSE;
	SetEvent (m_stopevent);
}

BOOL CPlayerEngine::Repeat()
{
	m_repeat = !m_repeat;
	return m_repeat;
}

BOOL CPlayerEngine::DirectoryMode()
{
	m_dirmode = !m_dirmode;
	return m_dirmode;
}

BOOL CPlayerEngine::IsRepeating()
{
	return m_repeat;
}

BOOL CPlayerEngine::IsDirectoryMode()
{
	return m_dirmode;
}
