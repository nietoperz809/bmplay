// BlinkenParse.cpp: Implementierung der Klasse CBlinkenParse.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BlinkenParse.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CBlinkenParse::CBlinkenParse()
{
	Reset();
}

CBlinkenParse::~CBlinkenParse()
{

}

BLPSTATE CBlinkenParse::ParseFSM (char b)
{
	// Last byte of file is always 0 -> Parsing is over
	if (b == 0)
		return BLP_END;
	
	// Perform the state machine
	switch (m_state)
	{
		// Initial or next frame:
		// Wait for the @
		case BLP_START:
		case BLP_READY:
		m_count = 0;
		if (b == '@')
			m_state = BLP_DELAY;
		else
			m_state = BLP_START;
		break;
	
		// Collect digits of delay value
		case BLP_DELAY:
		if (isdigit(b))
			m_array[m_count++] = b;
		else
		{
			m_array[m_count] = 0;
			m_delay = atoi (m_array);
			m_state = BLP_READBYTES;
			m_count = 0;
		}
		break;

		// Read the pixels
		case BLP_READBYTES:
		if (b == '1')
			m_array[m_count++] = '1';
		else if (b == '0')
			m_array[m_count++] = '0';
		if (m_count == 144)
			m_state = BLP_READY;
		break;
	}

	return m_state;
}

void CBlinkenParse::Reset()
{
	// Initialize the state variable
	m_state = BLP_START;
}
