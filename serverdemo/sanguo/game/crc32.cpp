#include "stdafx.h"
#include "game/fwd.h"

unsigned long m_Crc32Table[256];

//////////////////////////////////////////////////////////////////////////
//  CCrc32::Reflect
//		将ref数据的每个位颠倒,高位到低位,低位到高位  
//
//	Parameters:
//		ref [in]    要颠倒的数据
//		ch  [in]	要移动的位数
//
//	Return:
//		颠倒后的数据
//////////////////////////////////////////////////////////////////////////
unsigned long Reflect( unsigned long ref, char ch )
{
	unsigned long nValue = 0;

	// Swap bit 0 for bit 7
	// bit 1 for bit 6, etc.
	int i;
	for(i = 1; i < (ch + 1); i++)
	{
		if (ref & 1)
			nValue |= 1 << (ch - i);
		ref >>= 1;
	}

	return nValue;
}

//////////////////////////////////////////////////////////////////////////
//	CCrc32::InitCrc32Table
//		初始化Crc32的正规查询表
//////////////////////////////////////////////////////////////////////////
void InitCrc32Table()
{
	memset(m_Crc32Table,0,sizeof(m_Crc32Table));

	//CRC-32多项式(跟WinRAR使用的同一种标准)
	unsigned long ulPolynomial = 0x04C11DB7;

	// 256 values representing ASCII character codes.
	int i,j;
	for (i = 0; i <= 0xFF; i++)
	{
		m_Crc32Table[i] = Reflect(i, 8) << 24;

		for (j = 0; j < 8; j++)
			m_Crc32Table[i] = (m_Crc32Table[i] << 1) ^ (m_Crc32Table[i] & (1 << 31) ? ulPolynomial : 0);

		m_Crc32Table[i] = Reflect(m_Crc32Table[i], 32);
	}
}

//////////////////////////////////////////////////////////////////////////
//	CCrc32::CalculateCrc32
//		计算crc32
//
//	Parameters
//		pbuffer	[in]	要计算Crc32的数据指针
//		size	[in]	pbuffer的大小
//
//	Return
//		计算的Crc32值
//////////////////////////////////////////////////////////////////////////
unsigned long CalculateCrc32( const unsigned char* pbuffer, unsigned long size )
{
	const unsigned char* pbyte = pbuffer;
	unsigned long Crc32 = 0xFFFFFFFF;
	while (size--)
		Crc32 = (Crc32 >> 8) ^ m_Crc32Table[(Crc32 & 0xFF) ^ *pbyte++];
	Crc32 ^= 0xFFFFFFFF;

	return Crc32;
}