// bm_play.h : Haupt-Header-Datei f�r die Anwendung BM_PLAY
//

#if !defined(AFX_BM_PLAY_H__960A15C0_3A29_4EF2_8094_4C275863E457__INCLUDED_)
#define AFX_BM_PLAY_H__960A15C0_3A29_4EF2_8094_4C275863E457__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CBm_playApp:
// Siehe bm_play.cpp f�r die Implementierung dieser Klasse
//

class CBm_playApp : public CWinApp
{
public:
	CBm_playApp();

// �berladungen
	// Vom Klassenassistenten generierte �berladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CBm_playApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung

	//{{AFX_MSG(CBm_playApp)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingef�gt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VER�NDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // !defined(AFX_BM_PLAY_H__960A15C0_3A29_4EF2_8094_4C275863E457__INCLUDED_)
