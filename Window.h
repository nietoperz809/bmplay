#if !defined(AFX_WINDOW_H__7A26263D_E849_40D1_A521_FE9F8FF200E9__INCLUDED_)
#define AFX_WINDOW_H__7A26263D_E849_40D1_A521_FE9F8FF200E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Window.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Fenster CWindow 

class CWindow : public CStatic
{
// Konstruktion
public:
	CWindow();

// Attribute
public:

// Operationen
public:

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CWindow)
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CWindow();

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	//{{AFX_MSG(CWindow)
		// HINWEIS - Der Klassen-Assistent fügt hier Member-Funktionen ein und entfernt diese.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_WINDOW_H__7A26263D_E849_40D1_A521_FE9F8FF200E9__INCLUDED_
