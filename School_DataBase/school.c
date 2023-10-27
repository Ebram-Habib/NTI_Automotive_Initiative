/*
 * school.c
 *
 *  Created on: Oct 19, 2023
 *      Author: Ebram Habib
 */

#include "std_types.h"
#include <stdio.h>
#include <stdlib.h>
#include "school.h"
#include "ErrorState.h"
#include "stringlib.h"
#include "string.h"

List_t* KG1 = NULL_PTR;
List_t* KG2 = NULL_PTR;
ListNode_t* KG1_Node = NULL_PTR;
ListNode_t* KG2_Node = NULL_PTR;
ListNode_t* pStudent = NULL_PTR;
ListNode_t* pSearch = NULL_PTR; /* Pointer to check each node's data */

ErrorState_t  List_create(void)
{
	int choice = 0;

	DPRINTF(" Please choose the list that you want to create:\n");
	DPRINTF(" 1. KG1 List \n");
	DPRINTF(" 2. KG2 List \n");
	scanf("%d", &choice);

	switch(choice)
	{
	case 1:
		if(KG1 != NULL_PTR)
		{
			return ALREADY_EXISTS;
		}
		KG1 = (List_t*) malloc(1*sizeof(List_t));
		if(KG1 == NULL_PTR)
			return PTR_EQUAL_NULL;
		List_init(KG1);
		break;
	case 2:
		KG2 = (List_t*) malloc(1*sizeof(List_t));
		if(KG2 == NULL_PTR)
			return PTR_EQUAL_NULL;
		List_init(KG2);
		break;
	default:
		return OUT_OF_RANGE_ERR;
	}
	return SUCCESS;
}

ErrorState_t  List_init(List_t* pl)			// init head = tail = NULL
{
	pl->pHead = NULL_PTR;
	pl->pTail = NULL_PTR;
	pl->ListSize = 0;

	return SUCCESS;
}

ErrorState_t  Node_create(List_t* pl)
{
	if(pl == KG1)
	{
		KG1_Node = (ListNode_t*) malloc(1*sizeof(ListNode_t));
		if(KG1_Node == NULL_PTR)
		{
			return PTR_EQUAL_NULL;
		}
		else
		{
			List_insertStudent(KG1, KG1_Node);
		}
	}
	else if(pl == KG2)
	{
		KG2_Node = (ListNode_t*) malloc(1*sizeof(ListNode_t));
		if(KG2_Node == NULL_PTR)
		{
			return PTR_EQUAL_NULL;
		}
		else
		{
			List_insertStudent(KG2, KG2_Node);
		}
	}
	else
	{
		return OUT_OF_RANGE_ERR;
	}
	return SUCCESS;
}

ErrorState_t  List_insertStudent( List_t* pl , ListNode_t * pNode)
{
	s8 i, incrementFlag = 0, res, input[40]={0};	/* String to Read the information from the user */


	/* Read Student Data From User */
	DPRINTF("Please Enter Student ID:\n");
	gets(input);
	if((List_searchStudent(pl,atoi(input) , &pStudent) == SUCCESS) && (pl->ListSize > 0))
	{
		DPRINTF("ID Already Exists, returning to the main page...");
		return ALREADY_EXISTS;
	}
	else
	{
		pNode->entry.ID = atoi(input);

		DPRINTF("Please Enter Student Full Name:\n");
		gets(input);
		strcpy(pNode->entry.Name, input);

		DPRINTF("Please Enter Student Age:\n");
		gets(input);
		pNode->entry.age = atoi(input);

		DPRINTF("Please Enter Student Phone Number:\n");
		gets(input);
		pNode->entry.data.phone = atoi(input);

		DPRINTF("Please Enter Student Address:\n");
		gets(input);
		strcpy(pNode->entry.data.address, input);

		DPRINTF("Please Enter Student Grades:\n");
		DPRINTF("Math:\n");
		gets(input);
		pNode->entry.degress.math_deg = atoi(input);
		DPRINTF("English:\n");
		gets(input);
		pNode->entry.degress.english_deg = atoi(input);
		DPRINTF("Arabic:\n");
		gets(input);
		pNode->entry.degress.arabic_deg = atoi(input);

		/* Analyzing The New Student's Data to Determine The Student's Position On The List */
		if(pl->ListSize == 0)
		{
			pl->pHead = pNode;
			pl->pTail = pNode;
			pNode->pNext = NULL_PTR;
			pNode->pPrev = NULL_PTR;
		}
		else
		{
			pSearch = pl->pHead;

			for(i=0; i<pl->ListSize;i++)
			{
				res = strcmp(pSearch->entry.Name, pNode->entry.Name);

				if((res == 0) || (res == 1))	/* 2 strings are equal or the new name is less in value as ascii */
				{
					if(i == 0)
					{
						pl->pHead = pNode;
						pNode->pNext = pSearch;
						pNode->pPrev = NULL_PTR;
						pSearch->pPrev = pNode;
						incrementFlag++;
					}
					else
					{
						pNode->pPrev = pSearch->pPrev;
						pNode->pNext = pSearch;
						pSearch->pPrev->pNext = pNode;
						pSearch->pPrev = pNode;
						incrementFlag++;
					}
				}
				else
				{

				}
				if(pSearch->pNext != NULL_PTR)
				{
					pSearch = pSearch->pNext;
				}
			}
			if(incrementFlag == 0)
			{
				pl->pTail = pNode;
				pSearch->pNext = pNode;
				pNode->pPrev = pSearch;
				pNode->pNext = NULL_PTR;
			}

		}

		pl->ListSize++;
		DPRINTF("Student Added Successfully\n");
		return SUCCESS;
	}
}
ErrorState_t  List_searchStudent(const List_t* pl , u8 copy_u8ID,ListNode_t ** pFoundStudent )
{
	if(pl->ListSize == 0)
	{
		return (DPRINTF("The List is empty\n"));
	}

	else if(pl->ListSize > 0)
	{

		u8 i;
		ListNode_t* pSearch = NULL_PTR; /* Pointer to check each node's data */

		pSearch = pl->pHead;

		for(i=0; i<pl->ListSize;i++)
		{
			if(pSearch->entry.ID == copy_u8ID)
			{
				*pFoundStudent = pSearch;
				DPRINTF("Student Found\n");
				return SUCCESS;
			}
			else
			{

			}
			if(pSearch->pNext != NULL_PTR)
			{
				pSearch = pSearch->pNext;
			}
		}
		DPRINTF("Student Not Found\n");
		return DOES_NOT_EXIST;
	}
}

ErrorState_t  List_deleteStudent(List_t* pl , u8 copy_u8ID)
{
	if(pl->ListSize == 0)
	{
		return (DPRINTF("The List is empty\n"));
	}

	else if(pl->ListSize > 0)
	{

		u8 status = 0;

		status = List_searchStudent(pl, copy_u8ID, &pStudent);
		if(status == SUCCESS)
		{
			if(pl->ListSize == 1)
			{
				pl->pHead = NULL_PTR;
				pl->pTail = NULL_PTR;
				pl->ListSize = 0;
				free(pStudent);
				DPRINTF("The Student Has Been Deleted Successfully\n");
				return SUCCESS;
			}
			else
			{
				if(pl->pHead == pStudent)
				{
					pl->pHead = pStudent->pNext;
					pStudent->pNext->pPrev = NULL_PTR;
					pl->ListSize--;
					free(pStudent);
					DPRINTF("The Student Has Been Deleted Successfully\n");
					return SUCCESS;
				}
				else if(pl->pTail == pStudent)
				{
					pl->pTail = pStudent->pPrev;
					pStudent->pPrev->pNext = NULL_PTR;
					pl->ListSize--;
					free(pStudent);
					DPRINTF("The Student Has Been Deleted Successfully\n");
					return SUCCESS;
				}
				else
				{
					pStudent->pPrev->pNext = pStudent->pNext;
					pStudent->pNext->pPrev = pStudent->pPrev;
					pl->ListSize--;
					free(pStudent);
					DPRINTF("The Student Has Been Deleted Successfully\n");
					return SUCCESS;
				}
			}
		}
		else
		{
			DPRINTF("Student Not Found\n");
			return DOES_NOT_EXIST;
		}
	}
}

ErrorState_t  List_editStudent(const List_t* pl , u8 copy_u8ID)
{
	if(pl->ListSize == 0)
	{
		return (DPRINTF("The List is empty\n"));
	}
	else if(pl->ListSize > 0)
	{

		int choice = 0;
		u8 input[40] = {0};

		if(List_searchStudent(pl, copy_u8ID, &pStudent) == SUCCESS)
		{
			DPRINTF("Please Choose The Information To Be Edited:\n");
			DPRINTF("1. Age\n");
			DPRINTF("2. Phone Number\n");
			DPRINTF("3. Address\n");
			scanf("%d",&choice);
			switch(choice)
			{
			case 1:
				DPRINTF("Please Enter The Age:\n");
				gets(input);
				pStudent->entry.age = atoi(input);
				break;
			case 2:
				DPRINTF("Please Enter The Phone Number:\n");
				gets(input);
				pStudent->entry.data.phone = atoi(input);
				break;
			case 3:
				DPRINTF("Please Enter The Address:\n");
				gets(input);
				strcpy(pStudent->entry.data.address, input);
				break;
			}
			return SUCCESS;
		}
		else
		{
			DPRINTF("The Student Does Not Exist On This List\n");
			return DOES_NOT_EXIST;
		}
	}
}

ErrorState_t  List_updateScore(const List_t* pl , u8 copy_u8ID)
{
	if(pl->ListSize == 0)
	{
		return (DPRINTF("The List is empty\n"));
	}
	else if(pl->ListSize > 0)
	{
		int choice = 0;
		u8 input[40] = {0};

		if(List_searchStudent(pl, copy_u8ID, &pStudent) == SUCCESS)
		{
			DPRINTF("Please Choose The Subject To Be Updated:\n");
			DPRINTF("1. Arabic\n");
			DPRINTF("2. English\n");
			DPRINTF("3. Math\n");
			scanf("%d",&choice);
			switch(choice)
			{
			case 1:
				DPRINTF("Please Enter The Score:\n");
				gets(input);
				pStudent->entry.degress.arabic_deg = atoi(input);
				break;
			case 2:
				DPRINTF("Please Enter The Score:\n");
				gets(input);
				pStudent->entry.degress.english_deg = atoi(input);
				break;
			case 3:
				DPRINTF("Please Enter The Score:\n");
				gets(input);
				pStudent->entry.degress.math_deg = atoi(input);
				break;
			}
			return SUCCESS;
		}

		else
		{
			DPRINTF("The Student Does Not Exist On This List\n");
			return DOES_NOT_EXIST;
		}
	}
}

ErrorState_t  List_printStudent(const List_t* pl, u8 copy_u8ID )
{
	//int i;

	if(pl->ListSize == 0)
	{
		return (DPRINTF("The List is empty\n"));
	}
	else
	{

		if(List_searchStudent(pl, copy_u8ID, &pStudent) == SUCCESS)
		{

			DPRINTF("ID: %d\n",pStudent->entry.ID);
			//DPRINTF("Name: %s\n\n",pStudent->entry.Name);
			puts((char*)pStudent->entry.Name);

		}
		return SUCCESS;
	}
}

ErrorState_t  List_printList(const List_t* pl )
{

	u8 i;

	if(pl->ListSize == 0)
	{
		return (DPRINTF("The List is empty\n"));
	}
	else
	{
		ListNode_t* ptemp = NULL_PTR; /* Pointer to print each node's data */

		ptemp = pl->pHead;

		for(i=0; i<pl->ListSize;i++)
		{
			DPRINTF("Student No.%d\n",i+1);
			DPRINTF("ID: %d\n",ptemp->entry.ID);
			DPRINTF("Name: %s\n\n",ptemp->entry.Name);
			//puts((char*)ptemp->entry.Name);
			if(ptemp->pNext != NULL_PTR)
			{
				ptemp = ptemp->pNext;
			}
		}
		return SUCCESS;
	}
}

ErrorState_t  List_listSize(const List_t* pl ,u32 * pSize)
{
	*pSize = pl->ListSize;
	return SUCCESS;
}

ErrorState_t  List_freeList(List_t* pl)
{
	if(pl->ListSize == 0)
	{
		return (DPRINTF("The List is empty\n"));
	}
	else
	{
		pl->pHead = NULL_PTR;
		pl->pTail = NULL_PTR;
		pl->ListSize = 0;
		pl = NULL_PTR;
		DPRINTF("The List Has Been  Successfully\n");
		return SUCCESS;
	}
}

