// bm_play.cpp : Legt das Klassenverhalten für die Anwendung fest.
//

#include "stdafx.h"
#include "bm_play.h"
#include "bm_playDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBm_playApp

BEGIN_MESSAGE_MAP(CBm_playApp, CWinApp)
	//{{AFX_MSG_MAP(CBm_playApp)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBm_playApp Konstruktion

CBm_playApp::CBm_playApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// Das einzige CBm_playApp-Objekt

CBm_playApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CBm_playApp Initialisierung

BOOL CBm_playApp::InitInstance()
{
	CBm_playDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	return FALSE;
}
