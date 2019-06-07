// AscToHexConv.h: interface for the CAscToHexConv class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ASCTOHEXCONV_H__80EF3576_93EB_45D9_9BC7_37F9838C2D46__INCLUDED_)
#define AFX_ASCTOHEXCONV_H__80EF3576_93EB_45D9_9BC7_37F9838C2D46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef CASCTOHEXCONV_EXPORTS
	#define CASCTOHEXCONV_API __declspec(dllexport)
#else
	#define CASCTOHEXCONV_API __declspec(dllimport)
#endif

class CASCTOHEXCONV_API CAscToHexConv  
{
// Constructor, Destructor
public:
	CAscToHexConv();
	virtual ~CAscToHexConv();

// Variables
private:
	BYTE m_byStart;		// The character that starting Hexa value
	BYTE m_byEnd;		// The character that ending Hexa value
	
// Functions
public:
	// Set start and end character of Hexa value
	void SetHexChar(IN BYTE byStart, IN BYTE byEnd);
	bool ConvAsc2Hex(IN BYTE* bySource, IN UINT nLength, OUT BYTE* byDest, IN UINT nOutBufLen, OUT UINT* pnNumberOfByteWritten);		// Ascii 값을 Hexa로 변환
	
private:
	bool ASCii2Hex(IN PUCHAR pbyData, OUT PUCHAR pbyResult);
	BYTE ASCii2Nibble(IN BYTE ch);
	
};

#endif // !defined(AFX_ASCTOHEXCONV_H__80EF3576_93EB_45D9_9BC7_37F9838C2D46__INCLUDED_)
