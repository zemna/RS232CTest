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
	UINT iCurDestIdx = 0;					// Destination ������ �����͸� ����� ��ġ ����
	BYTE byData[1] = {0x00};				// Hexa �����͸� �ӽ� ������ ����
	BYTE byteTmpResult;						// Hexa ��� ����� �ӽ� ������ ����

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
					if (j==2)					// m_chHexStart �� m_chHexEnd ���̿� 2�� �̻��� character�� ������
						return FALSE;

					byData[j++] = bySource[i++];	//chData �迭�� ������ character ����
				}

				if (j == 0)						// m_chHexStart �� m_chHexEnd ���̿� �ƹ��� �����Ͱ� ������
				{					
					return FALSE;
				} 
				else if (j == 1)				// m_chHexStart�� �����ؼ� 1�ڸ��� ���������
				{			
					byData[1] = byData[0];		// �Էµ� ���� lower ������ ó���ϱ� ���� �迭�� ġȯ
					byData[0] = '0';			// ù��° �迭 �ʱ�ȭ
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
	BYTE byteHigh;		// ���� 4bit ��
	BYTE byteLow;		// ���� 4bit ��

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
	} //--- �����϶��� �׳� �����Ϻ� 0000���� �ٲ��ָ� �ȴ�.
	else if(ch >= '0' && ch <= '9')
	{
		ch &= 0x0F;
	}

	return ch;
}
