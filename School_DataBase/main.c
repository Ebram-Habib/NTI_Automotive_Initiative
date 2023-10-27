/*
 * main.c
 *
 *  Created on: Oct 19, 2023
 *      Author: Ebram Habib
 */

#include "std_types.h"
#include <stdio.h>
#include <stdlib.h>
#include "ErrorState.h"
#include "stringlib.h"
#include "school.h"

extern List_t* KG1;
extern List_t* KG2;
extern ListNode_t* pStudent;

int main()
{
	int choice = 0, error_status;
	unsigned int listSize = 0;

	DPRINTF("Welcome to the Student Management System\n");

	while(1)
	{
		DPRINTF("--------------------------------------------\n");
		DPRINTF("Choose The Task that you want to perform\n");
		DPRINTF("1. Create a new list\n");
		DPRINTF("2. Insert Student\n");
		DPRINTF("3. Search Student\n");
		DPRINTF("4. Delete Student\n");
		DPRINTF("5. Edit Student\n");
		DPRINTF("6. Update Student Subjects Scores\n");
		DPRINTF("7. Print The Info Of A Student\n");
		DPRINTF("8. Print The List of Students\n");
		DPRINTF("9. List Size \n");
		DPRINTF("10. Delete List\n");
		DPRINTF("11. Terminate Program\n");
		DPRINTF("--------------------------------------------\n");
		DPRINTF(" Enter your choice to perform the task\n");
		scanf("%d", &choice);
		DPRINTF("--------------------------------------------\n");
		switch(choice)
		{
		case 1:
			error_status = List_create();
			switch(error_status)
			{
			case ALREADY_EXISTS:
				DPRINTF("The List Already Exists\n");
				break;
			case PTR_EQUAL_NULL:
				DPRINTF("No enough memory to create a new list\n");
				break;
			case OUT_OF_RANGE_ERR:
				DPRINTF("Invalid choice\n");
				break;
			case SUCCESS:
				DPRINTF("The new list has been created successfully\n");
				break;
			}
			break;
			case 2:
				DPRINTF(" Please Choose The List To Insert The New Student In It\n");
				DPRINTF(" 1. KG1 List \n");
				DPRINTF(" 2. KG2 List \n");
				scanf("%d", &choice);
				switch(choice)
				{
				case 1:
					if(KG1 == NULL_PTR)
					{
						DPRINTF("KG1 Has Not Been Created Yet");
					}
					else
					{
						Node_create(KG1);
					}
					break;
				case 2:
					if(KG2 == NULL_PTR)
					{
						DPRINTF("KG2 Has Not Been Created Yet");
					}
					else
					{
						Node_create(KG2);
					}
					break;
				default:
					DPRINTF("Wrong choice ... Please try again\n");
				}
				break;
				case 3:
					DPRINTF("Please Choose The List To Search For The Student In It:\n");
					DPRINTF(" 1. KG1 List \n");
					DPRINTF(" 2. KG2 List \n");
					scanf("%d", &choice);
					switch(choice)
					{
					case 1:
						if(KG1 == NULL_PTR)
						{
							DPRINTF("This List Hasn't Been Created Yet\n");
						}
						else
						{
							DPRINTF("Please Enter Student ID:\n");
							scanf("%d", &choice);
							List_searchStudent(KG1, choice, &pStudent);
						}
						break;
					case 2:
						if(KG2 == NULL_PTR)
						{
							DPRINTF("This List Hasn't Been Created Yet\n");
						}
						else
						{
							DPRINTF("Please Enter Student ID:\n");
							scanf("%d", &choice);
							List_searchStudent(KG2, choice, &pStudent);
						}
						break;
					}
					break;
					case 4:
						DPRINTF("Please Choose The List To Delete The Student From It:\n");
						DPRINTF(" 1. KG1 List \n");
						DPRINTF(" 2. KG2 List \n");
						scanf("%d", &choice);
						switch(choice)
						{
						case 1:
							if(KG1 == NULL_PTR)
							{
								DPRINTF("This List Hasn't Been Created Yet\n");
							}
							else
							{
								DPRINTF("Please Enter Student ID:\n");
								scanf("%d", &choice);
								List_deleteStudent(KG1, choice);
							}
							break;
						case 2:
							if(KG2 == NULL_PTR)
							{
								DPRINTF("This List Hasn't Been Created Yet\n");
							}
							else
							{
								DPRINTF("Please Enter Student ID:\n");
								scanf("%d", &choice);
								List_deleteStudent(KG2, choice);
							}
							break;
						}
						break;
						case 5:
							DPRINTF("Please Choose The List To Edit The Student From It:\n");
							DPRINTF(" 1. KG1 List \n");
							DPRINTF(" 2. KG2 List \n");
							scanf("%d", &choice);
							switch(choice)
							{
							case 1:
								if(KG1 == NULL_PTR)
								{
									DPRINTF("This List Hasn't Been Created Yet\n");
								}
								else
								{
									DPRINTF("Please Enter Student ID:\n");
									scanf("%d", &choice);
									List_editStudent(KG1, choice);
								}
								break;
							case 2:
								if(KG2 == NULL_PTR)
								{
									DPRINTF("This List Hasn't Been Created Yet\n");
								}
								else
								{
									DPRINTF("Please Enter Student ID:\n");
									scanf("%d", &choice);
									List_editStudent(KG2, choice);
								}
								break;
							}
							break;
							case 6:
								DPRINTF("Please Choose The List To Edit The Student Subjects From It:\n");
								DPRINTF(" 1. KG1 List \n");
								DPRINTF(" 2. KG2 List \n");
								scanf("%d", &choice);
								switch(choice)
								{
								case 1:
									if(KG1 == NULL_PTR)
									{
										DPRINTF("This List Hasn't Been Created Yet\n");
									}
									else
									{
										DPRINTF("Please Enter Student ID:\n");
										scanf("%d", &choice);
										List_updateScore(KG1, choice);
									}
									break;
								case 2:
									if(KG2 == NULL_PTR)
									{
										DPRINTF("This List Hasn't Been Created Yet\n");
									}
									else
									{
										DPRINTF("Please Enter Student ID:\n");
										scanf("%d", &choice);
										List_updateScore(KG2, choice);
									}
									break;
								}
								break;
								case 7:
									DPRINTF("Please Choose The List To Print The Student From It:\n");
									DPRINTF(" 1. KG1 List \n");
									DPRINTF(" 2. KG2 List \n");
									scanf("%d", &choice);
									switch(choice)
									{
									case 1:
										if(KG1 == NULL_PTR)
										{
											DPRINTF("This List Hasn't Been Created Yet\n");
										}
										else
										{
											DPRINTF("Please Enter Student ID:\n");
											scanf("%d", &choice);
											List_printStudent(KG1, choice);
										}
										break;
									case 2:
										if(KG2 == NULL_PTR)
										{
											DPRINTF("This List Hasn't Been Created Yet\n");
										}
										else
										{
											DPRINTF("Please Enter Student ID:\n");
											scanf("%d", &choice);
											List_printStudent(KG2, choice);
										}
										break;
									}
									break;
									case 8:
										DPRINTF("Please Choose The List To Be Printed:\n");
										DPRINTF(" 1. KG1 List \n");
										DPRINTF(" 2. KG2 List \n");
										scanf("%d", &choice);
										switch(choice)
										{
										case 1:
											if(KG1 == NULL_PTR)
											{
												DPRINTF("This List Hasn't Been Created Yet\n");
											}
											else
											{
												List_printList(KG1);
											}
											break;
										case 2:
											if(KG2 == NULL_PTR)
											{
												DPRINTF("This List Hasn't Been Created Yet\n");
											}
											else
											{
												List_printList(KG2);
											}
											break;
										}
										break;
										case 9:
											DPRINTF("Please Choose The List To Check Its Size:\n");
											DPRINTF(" 1. KG1 List \n");
											DPRINTF(" 2. KG2 List \n");
											scanf("%d", &choice);
											switch(choice)
											{
											case 1:
												if(KG1 == NULL_PTR)
												{
													DPRINTF("This List Hasn't Been Created Yet\n");
												}
												else
												{
													List_listSize(KG1, (u32 *)&listSize);
													DPRINTF("The Size Of The List Is: %d\n", listSize);
												}
												break;
											case 2:
												if(KG2 == NULL_PTR)
												{
													DPRINTF("This List Hasn't Been Created Yet\n");
												}
												else
												{
													List_listSize(KG2, (u32 *)&listSize);
													DPRINTF("The Size Of The List Is: %d\n", listSize);
												}
												break;
											}
											break;
											case 10:
												DPRINTF("Please Choose The List To Be Freed:\n");
												DPRINTF(" 1. KG1 List \n");
												DPRINTF(" 2. KG2 List \n");
												scanf("%d", &choice);
												switch(choice)
												{
												case 1:
													if(KG1 == NULL_PTR)
													{
														DPRINTF("This List Hasn't Been Created Yet\n");
													}
													else
													{

														List_freeList(KG1);
													}
													break;
												case 2:
													if(KG2 == NULL_PTR)
													{
														DPRINTF("This List Hasn't Been Created Yet\n");
													}
													else
													{
														List_freeList(KG2);
													}
													break;
												}
												break;
												case 11:
													exit(0);
													break;
												default :
													DPRINTF("Wrong choice ... Pls try again\n");
		}
	}
}
