/********************************************************************************
  * @file           : Handle_Srec.h
  * @brief          : Handle_File Header File
  ******************************************************************************
  * @author         : Le Nguyen Van Duong
  *
  * Copyright (c) Dev-C++.
  * All rights reserved.
  ******************************************************************************/

#ifndef _HANDLE_SREC_                                           /* Header guard */
#define _HANDLE_SREC_

#include <stdio.h>
#include <stdint.h>

typedef enum
{
	CHECK_OK = 0U,
	CHECK_ERROR = 1U,

}SRec_State;

  SRec_State Check_StartCode(uint8_t * line);

  SRec_State Check_Type(uint8_t * line);

  SRec_State Check_Syntax(uint8_t * line);

  SRec_State Check_ByCount(uint8_t * line);
  SRec_State Check_Sum(uint8_t * line);
  SRec_State Total_Check(uint8_t * line);

#endif                               
