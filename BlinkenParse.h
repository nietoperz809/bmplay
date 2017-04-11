// BlinkenParse.h: Schnittstelle für die Klasse CBlinkenParse.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BLINKENPARSE_H__64FE4DB3_9A33_4559_ADBE_82552CCB8C33__INCLUDED_)
#define AFX_BLINKENPARSE_H__64FE4DB3_9A33_4559_ADBE_82552CCB8C33__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef enum
{
	BLP_START,
	BLP_DELAY,
	BLP_READBYTES,
	BLP_END,
	BLP_READY,
} BLPSTATE;

class CBlinkenParse  
{
public:
	void Reset (void);
	BLPSTATE m_state;
	int m_count;
	BLPSTATE ParseFSM (char b);
	DWORD m_delay;
	char m_array[144];
	CBlinkenParse();
	virtual ~CBlinkenParse();
};

#endif // !defined(AFX_BLINKENPARSE_H__64FE4DB3_9A33_4559_ADBE_82552CCB8C33__INCLUDED_)
