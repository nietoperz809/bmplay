// bm_playDlg.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "bm_play.h"
#include "bm_playDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define HEADLINE "Pittbull's BLM Player "

/////////////////////////////////////////////////////////////////////////////
// CBm_playDlg Dialogfeld

CBm_playDlg::CBm_playDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBm_playDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBm_playDlg)
		// HINWEIS: Der Klassenassistent fügt hier Member-Initialisierung ein
	//}}AFX_DATA_INIT
	// Beachten Sie, dass LoadIcon unter Win32 keinen nachfolgenden DestroyIcon-Aufruf benötigt
}

void CBm_playDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBm_playDlg)
	DDX_Control(pDX, IDC_HOUSE, m_house);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBm_playDlg, CDialog)
	//{{AFX_MSG_MAP(CBm_playDlg)
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_COPYDATA()
	ON_COMMAND(ID_OPENMOVIE, OnOpenmovie)
	ON_COMMAND(ID_FULLSCREEN, OnFullscreen)
	ON_COMMAND(ID_PLAYDIRECTORY, OnPlaydirectory)
	ON_COMMAND(ID_STOP, OnStop)
	ON_COMMAND(ID_REPEAT, OnRepeat)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*
void Tp (CBm_playDlg *dlg)
{
	BYTE arr[144];
	int idx = 0;
	COPYDATASTRUCT cpd;

	while(1)
	{
		arr[idx++] = '1';
		if (idx > 1)
			arr[idx-2] = '0';
		else
			arr[143] = '0';
		if (idx == 144)
			idx = 0;

		HWND hwnd = dlg->GetSafeHwnd();
		cpd.lpData = arr;
		cpd.cbData = 144;
		SendMessage (hwnd, WM_COPYDATA, (UINT)0, (long)&cpd);
		Sleep (10);
	}
}
*/

/////////////////////////////////////////////////////////////////////////////
// CBm_playDlg Nachrichten-Handler

BOOL CBm_playDlg::OnInitDialog()
{
	//AfxBeginThread ((AFX_THREADPROC)Tp, this);

	CDialog::OnInitDialog();
	MoveWindow (100,100, 554,616);
	return TRUE; 
}

// Wollen Sie Ihrem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie 
//  den nachstehenden Code, um das Symbol zu zeichnen. Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch für Sie erledigt.

void CBm_playDlg::OnPaint() 
{
	CDialog::OnPaint();
}

// Enter pressed
void CBm_playDlg::OnOK() 
{
}

// ESC pressed
void CBm_playDlg::OnCancel() 
{
	SetWindowLong (GetSafeHwnd(), GWL_STYLE, m_style);
	SetMenu (m_menu);
	ShowCursor (TRUE);
	MoveWindow (100,100, 554,616);
}

void CBm_playDlg::OnClose() 
{
	ExitProcess(0);
}

// Window size changed
void CBm_playDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	if (m_house.GetSafeHwnd())
	{
		SingleShot();
		SizeThemAll (cx, cy);
	}
}

//////////////////////////////////////////////////////////////////////

// Does initialization...
void CBm_playDlg::SingleShot()
{
	// Only execute once if called many times
	static BOOL shot = FALSE;
	if (shot == TRUE)
		return;
	shot = TRUE;

	// Create the engine
	m_engine = new CPlayerEngine (GetSafeHwnd());
	SetWindowText (HEADLINE);

	// Save various window parameters
	m_style = WS_VISIBLE | GetWindowLong (GetSafeHwnd(), GWL_STYLE);
	m_menu = GetMenu();

	// Make all windows children of the house
	// and store them ...
	// and switch them off ...
	CWnd *wnd = GetWindow (GW_CHILD);
	CWnd *next = wnd;
	int idx = 0;
	for (;;)
	{
		if (wnd == NULL)
			break;
		next = wnd->GetWindow (GW_HWNDNEXT);
		if (wnd != &m_house)
		{
			wnd->ShowWindow (SW_HIDE);
			wnd->SetParent (&m_house);
			m_windows[idx++] = wnd;
		}
		wnd = next;
	}
}

void CBm_playDlg::SizeThemAll (int cx, int cy)
{
	// Relative offsets of windows
	static int xp[] = {23, 36, 49, 62, 75, 88, 101, 114, 127, 140, 153, 166, 179, 192, 205, 218, 231, 244};
	static int yp[] = {46, 70, 94, 118, 142, 166, 190, 214};

	// Resize the house 
	m_house.MoveWindow (0,0, cx, cy);

	// Calculate window size and stepwidth
	RECT rect;
	m_house.GetClientRect (&rect);
	double stepx = (double)rect.right / 277.0;
	double stepy = (double)rect.bottom / 308.0;
	int wx = (int)(11.5 * stepx);
	int wy = (int)(15.5 * stepy);
		
	// Move all the windows to their positions
	int s,l;
	for (s=0; s<8; s++)
	{
		int yy = (int)((double)yp[s] * stepy);
		for (l=0; l<18; l++)
		{
			int xx = (int)((double)xp[l] * stepx); 
			CWnd *wnd = m_windows[s*18+l];
			wnd->MoveWindow (xx, yy, wx, wy, FALSE);
			wnd->InvalidateRect (NULL);
			wnd->UpdateWindow();
		}
	}

	// Update the entire view
	m_house.InvalidateRect (NULL);
	m_house.UpdateWindow();
}

// Toggle lights with the mouse
void CBm_playDlg::OnLButtonDown (UINT nFlags, CPoint point) 
{
	ClientToScreen (&point);
	for (int s=0; s<144; s++)
	{
		CWnd *wnd = m_windows[s];
		RECT rect;
		wnd->GetClientRect (&rect);
		wnd->ClientToScreen (&rect);
	
		if (rect.left < point.x && rect.right > point.x && rect.top < point.y && rect.bottom > point.y)
		{
			if (wnd->IsWindowVisible())
				HideWnd (wnd);
			else
				ShowWnd (wnd);
			break;
		}
	}
}

// Switch on lights from WM_COPYDATA
BOOL CBm_playDlg::OnCopyData (CWnd* pWnd, COPYDATASTRUCT* cpd) 
{

	switch (cpd->dwData)
	{

		case BLC_FRAME:
		{
			for (int s=0; s<144; s++)
			{
				if (((BYTE*)cpd->lpData)[s] == '1')
					ShowWnd (m_windows[s]);
				else
					HideWnd (m_windows[s]);
			}											    
		}
		break;

		case BLC_COMPLETE:
		//MessageBox ("complete");
		break;
	
		case BLC_NEXTFILE:
		m_engine->PlayNextFile();
		break;
	
		case BLC_FILENAME:
		UpdateHeadline ((char*)(cpd->lpData));
		break;
	}

	return TRUE;
}


void CBm_playDlg::ShowWnd (CWnd *wnd)
{
	if (wnd->IsWindowVisible() == TRUE)
		return;
	wnd->ShowWindow (SW_SHOW);
	wnd->InvalidateRect(NULL);
	wnd->UpdateWindow();
}

void CBm_playDlg::HideWnd (CWnd *wnd)
{
	if (wnd->IsWindowVisible() == FALSE)
		return;
	wnd->ShowWindow (SW_HIDE);
	wnd->InvalidateRect(NULL);
	wnd->UpdateWindow();
}

void CBm_playDlg::OnOpenmovie() 
{
	if (m_engine->IsRunning() == TRUE)
	{
		MessageBox ("Busy... Please wait until the movie ends");
		return;
	}

	CString title;
	char filter[] = "Blinkenlights Movies\0*.blm\0";
	if (m_engine->IsDirectoryMode())
		title = "Directory Mode: Select any blm from directory.";
	else
		title = "Please choose a blm."; 
	CFileDialog dlg(TRUE);
	dlg.m_ofn.lpstrTitle = (LPCTSTR)title;
	dlg.m_ofn.lpstrFilter = (LPCTSTR)filter;
	if (IDOK == dlg.DoModal())
		if (dlg.GetFileExt() != CString("blm"))
			MessageBox ("Sorry, this is not a blinkenlights movie");
		else
			m_engine->PlayFile (dlg.GetPathName());
}

void CBm_playDlg::OnFullscreen() 
{
	SetWindowLong (GetSafeHwnd(), GWL_STYLE, WS_VISIBLE); 
	SetMenu (NULL);
	ShowWindow (SW_SHOWMAXIMIZED);
	ShowCursor (FALSE);
}

void CBm_playDlg::OnPlaydirectory() 
{
	m_engine->DirectoryMode();
	UpdateHeadline(NULL);
}

void CBm_playDlg::OnStop() 
{
	m_engine->Stop();
	UpdateHeadline(NULL);
}

void CBm_playDlg::OnRepeat() 
{
	m_engine->Repeat();
	UpdateHeadline(NULL);
}

void CBm_playDlg::UpdateHeadline (char *filename)
{
	CString cs = "";
	if (m_engine->IsRepeating())
		cs += "(R=ON) ";
	else
		cs += "(R=OFF) ";
	if (m_engine->IsDirectoryMode())
		cs += "(D=ON) ";
	else
		cs += "(D=OFF) ";
	if (filename)
	{
		cs += "Now playing: ";
		cs += filename;
	}
	SetWindowText (cs);
}
