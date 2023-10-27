/*
 * stringlib.c
 *
 *  Created on: Oct 19, 2023
 *      Author: Ebram Habib
 */

#include "std_types.h"
#include <stdio.h>
#include "stringlib.h"

s8 string_get(s8* s)
{
	s8 i = 0, ch;

	while(i < BUFF_MAX-1)
	{
		scanf("%c", &ch);
		if(ch != '\n')
		{
			s[i] = ch;
			i++;
		}
		else
		{
			break;
		}
	}
	s[i] = '\0';

	return 1;
}

s32 string_ascii_to_int(const s8* s)
{
	u64 i = 0;
	s64 num = 0;
	u8 negative_flag = 0;

	if(s[i] == '-')
	{
		negative_flag = 1;
		i++;
	}

	while((s[i] != '\0') && (s[i] >= '0') && (s[i] <= '9'))
	{
		num = (num * 10) + (s[i] - 48);
		i++;
	}

	if(negative_flag == 1)
	{
		return num * -1;
	}
	else
	{
		return num;
	}
}

s32 string_compare(const s8* s1,const s8* s2)
{
	u64 i=0;

	while((s1[i] != '\0')|| (s2[i] != '\0'))
	{
		if(s1[i] > s2[i])
		{
			return 1;
		}
		else if(s1[i] < s2[i])
		{
			return -1;
		}
		i++;
	}
	return 0;
}

s8 string_copy(s8* s1,const s8* s2)
{
	u64 i=0;

	if(string_len(s1)<string_len(s2))
	{
		return 0;
	}
	else
	{
		while(s2[i] != '\0')
		{
			s1[i] = s2[i];
			i++;
		}
		s1[i]='\0';
	}
	return 1;
}

s32 string_len(const s8* s)
{
	s32 i=0,count=0;

	while(s[i] != '\0')
	{
		count++;
		i++;
	}
	return count;
}
