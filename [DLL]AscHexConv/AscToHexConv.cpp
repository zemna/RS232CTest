// AscToHexConv.cpp: implementation of the CAscToHexConv class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AscHexConv.h"

#define CASCTOHEXCONV_EXPORTS
#include "AscToHexConv.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAscToHexConv::CAscToHexConv()
{
	m_byStart = '#';
	m_byEnd = ',';
}

CAscToHexConv::~CAscToHexConv()
{

}

void CAscToHexConv::SetHexChar(BYTE byStart, BYTE byEnd)
{
	m_byStart = byStart;
	m_byEnd = byEnd;
}

bool CAscToHexConv::ConvAsc2Hex(BYTE* bySource, UINT nLength, BYTE* byDest, UINT nOutBufLen, UINT* pnNumberOfByteWritten)
{
	UINT i=0;
	UINT j=0;
	UINT iCurDestIdx = 0;					// Destination 변수에 데이터를 기록할 위치 정보
	BYTE byData[1] = {0x00};				// Hexa 데이터를 임시 저장할 변수
	BYTE byteTmpResult;						// Hexa 계산 결과를 임시 저장할 변수

	memset(byDest, 0x00, nOutBufLen);

	while (i < nLength)
	{
		if (bySource[i] == m_byStart)
		{
			i++;

			if (bySource[i] == m_byStart) {

				byDest[iCurDestIdx++] = bySource[i++];

			} else {

				while ( (bySource[i] != m_byEnd) && (i < nLength) )
				{
					if (j==2)					// m_chHexStart 와 m_chHexEnd 사이에 2개 이상의 character가 있으면
						return FALSE;

					byData[j++] = bySource[i++];	//chData 배열에 각각의 character 저장
				}

				if (j == 0)						// m_chHexStart 와 m_chHexEnd 사이에 아무런 데이터가 없으면
				{					
					return FALSE;
				} 
				else if (j == 1)				// m_chHexStart로 시작해서 1자리만 적혔을경우
				{			
					byData[1] = byData[0];		// 입력된 값을 lower 값으로 처리하기 위해 배열값 치환
					byData[0] = '0';			// 첫번째 배열 초기화
				}

				if (!ASCii2Hex(byData,&byteTmpResult))
					return FALSE;

				byDest[iCurDestIdx++] = byteTmpResult;
				memset(byData, 0x00, 2);
				j=0;
				i++;

			}

		}
		else
		{
			byDest[iCurDestIdx++] = bySource[i++];
		}
	}

	*pnNumberOfByteWritten = iCurDestIdx;
	return TRUE;	
}

bool CAscToHexConv::ASCii2Hex(PUCHAR pbyData, PUCHAR pbyResult)
{
	BYTE byteHigh;		// 상위 4bit 값
	BYTE byteLow;		// 하위 4bit 값

	for (int i=0; i<2; i++)
	{
		if ((pbyData[i] < '0' || pbyData[i] > '9') &&
			(pbyData[i] < 'A' || pbyData[i] > 'F') &&
			(pbyData[i] < 'a' || pbyData[i] > 'f'))
			return false;
	}

	byteHigh = ASCii2Nibble(*(pbyData));
	byteLow = ASCii2Nibble(*(pbyData+1));

	*pbyResult = byteHigh << 4 | byteLow;

	return true;
}

BYTE CAscToHexConv::ASCii2Nibble(BYTE ch)
{
	//--- ex) 'A':0100 0001 -> 0000 0001 -> 0000 1010 : 10
	if ((ch  >= 'A' && ch <= 'F') || (ch >= 'a' && ch <= 'f'))
	{
		ch &= 0x0F;
		ch += 9;
	} //--- 숫자일때는 그냥 상위니블만 0000으로 바꿔주면 된다.
	else if(ch >= '0' && ch <= '9')
	{
		ch &= 0x0F;
	}

	return ch;
}
