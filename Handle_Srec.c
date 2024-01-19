/********************************************************************************
  * @file           : Handle_File.c
  * @brief          : Handle_File program body
  ******************************************************************************
  * @author         : Le Nguyen Van Duong
  *
  * Copyright (c) Dev-C++.
  * All rights reserved.
  ******************************************************************************/
#include  "Handle_Srec.h"

inline int32_t H1(int8_t x)
  {
      return x - '0';
  }

  inline int32_t H2(int8_t x)
  {
      return x - 'A' + 10;
  }

  inline int32_t CONVERT_HEX_DEC(int8_t Arr[2])
  {
      return ((((Arr[0]) >= '0') && ((Arr[0]) <= '9')) ? H1(Arr[0]) : H2(Arr[0])) << 4 |
          (((Arr[1]) >= 'A') && ((Arr[1]) <= 'F') ? H2(Arr[1]) : H1(Arr[1]));
  }

  SRec_State Check_StartCode(uint8_t * line)
  {
      SRec_State Status = CHECK_OK;
      if (line[0] != 'S')
	  {
          Status = CHECK_ERROR;
      }

      return Status;

  }

  SRec_State Check_Type(uint8_t * line)
  {
      SRec_State Status = CHECK_ERROR;

      if (line[1] >= '0' && line[1] <= '9')
	  {
          Status = CHECK_OK;
      }

      return Status;
  }

  SRec_State Check_Syntax(uint8_t * line)
  {
      SRec_State Status = CHECK_ERROR;
      
      uint8_t index = 2;
      

      while ((line[index] != '\r') && (Status = CHECK_OK))
	  {
          if (line[index] >= '0' ||  line[index] <= '9' && line[index] >= 'A' || line[index] <= 'F')
		  {
              Status = CHECK_OK;
          }
          index++;
      }

      return Status;
  }

  SRec_State Check_ByCount(uint8_t * line)
  {
      SRec_State Status = CHECK_ERROR;
      uint8_t bytecount = 0;
      int8_t hex[2] = {'0', '0'};
      uint8_t length = 0; /* length of buffer */

      while (line[length] != '\n')
	  {
          length++;
      }

      hex[0] = line[2];
      hex[1] = line[3];
      bytecount = CONVERT_HEX_DEC(hex);

      if (bytecount == ((length - 4) / 2))
	  {
          Status = CHECK_OK;
      }
      return Status;
  }

  SRec_State Check_Sum(uint8_t * line)
  {
      SRec_State Status = CHECK_ERROR;

      uint8_t Sum = 0;
      uint32_t Total = 0;

      uint8_t index;
      uint8_t length = 0; /* length of buffer */
      int8_t hex[2] = {'0', '0'};

      while (line[length] != '\n')
	  {
          length++;
      }

      hex[0] = line[length - 2];
      hex[1] = line[length - 1];

      Sum = CONVERT_HEX_DEC(hex);

      for (index = 2; index < length - 2; index = index + 2)
	  {
          hex[0] = line[index];
          hex[1] = line[index + 1];
          Total += CONVERT_HEX_DEC(hex);
      }
      if ((Sum + (Total & 0x00ff)) == 0xff)
	  {
          Status = CHECK_OK;
      }

      return Status;

  }

  SRec_State Total_Check(uint8_t * line)
  {
      SRec_State Status = CHECK_ERROR;
	  SRec_State CheckStartCode;
	  SRec_State CheckType;
	  SRec_State CheckSyntax;
	  SRec_State CheckByCount;
	  SRec_State CheckSum;
	
      CheckStartCode = Check_StartCode(line);
      CheckType = Check_Type(line);
      CheckSyntax = Check_Syntax(line);
      CheckByCount = Check_ByCount(line);
      CheckSum = Check_Sum(line);

      if ((CheckStartCode == CHECK_OK) && (CheckType == CHECK_OK) && (CheckSyntax == CHECK_OK) &&
          (CheckByCount == CHECK_OK) && (CheckSum == CHECK_OK))
		{
          Status = CHECK_OK;
      	}

      return Status;
  }
  

