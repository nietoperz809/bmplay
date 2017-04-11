// bm_playDlg.h : Header-Datei
//

#include "house.h"

#if !defined(AFX_BM_PLAYDLG_H__A3C279FD_B7A5_4091_AB39_CEFD48713764__INCLUDED_)
#define AFX_BM_PLAYDLG_H__A3C279FD_B7A5_4091_AB39_CEFD48713764__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "playerengine.h"

/////////////////////////////////////////////////////////////////////////////
// CBm_playDlg Dialogfeld


class CBm_playDlg : public CDialog
{
// Konstruktion
public:
	void UpdateHeadline (char *);
	void HideWnd (CWnd *wnd);
	void ShowWnd (CWnd *wnd);
	CBm_playDlg(CWnd* pParent = NULL);	// Standard-Konstruktor
	char *m_filebuff;
	LONG m_style;
	CMenu *m_menu;
	CPlayerEngine *m_engine;

// Dialogfelddaten
	//{{AFX_DATA(CBm_playDlg)
	enum { IDD = IDD_BM_PLAY_DIALOG };
	CHouse	m_house;
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CBm_playDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	void SizeThemAll (int cx, int cy);
	CWnd *m_windows[144];
	void SingleShot (void);
	// Generierte Message-Map-Funktionen
	//{{AFX_MSG(CBm_playDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnOpenmovie();
	afx_msg void OnFullscreen();
	afx_msg void OnPlaydirectory();
	afx_msg void OnStop();
	afx_msg void OnRepeat();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_BM_PLAYDLG_H__A3C279FD_B7A5_4091_AB39_CEFD48713764__INCLUDED_)
