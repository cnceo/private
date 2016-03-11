#include "stdafx.h"
#include "game/fwd.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int SetShort(int where,short sData,char *msg)
{
	if(where>0)
	{
		*(short *)(msg+sizeof(short)*(where-1)) = sData;
		return 1;
	}
	else
	{
		return 0;
	}
}

int SetString(int where,char *pData,char *msg,unsigned char shortNum)
{
	if(where>0)
	{
		int nlen;
		char *pch;
		int s;
		nlen = shortNum*sizeof(short);
		pch = msg+nlen;
		for(s=1;s<where;s++)
		{
			nlen = nlen + strlen(pch)+1;
			pch=pch+strlen(pch)+1;
		}
		strcpy(msg+nlen,pData);
		return 1;
	}
	else
	{
		return 0;
	}
}
int GetShort(int where,short *pshort,char *msg)
{
	if(where>0)
	{
		*pshort = *(short*)(msg + (where-1)*sizeof(short));
		return 1;
	}
	else
	{
		pshort = 0;
		return 0;
	}
}

int GetString(int where,char* ppc,char *msg,unsigned char shortNum)
{
	if(where>0)
	{
		int nlen;
		char* pch;
		int s;
		nlen = shortNum*sizeof(short);
		pch = msg + nlen;
		for(s=1;s<where;s++)
		{
			pch = pch+strlen(pch)+1;
		}
		strcpy(ppc,pch);
        return 1;
	}
	else
	{
		return 0;
	}
}
