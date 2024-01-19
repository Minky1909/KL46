  #include  "Handle_Srec.h"
  #include "Parse_Srec.h"
  
int main()
  {
  	FILE *file = fopen("MKL46_BlinkLed_1S.srec", "r"); // Replace with the actual file path
    if (file == NULL)
	{
        perror("Error opening file");
        return -1;
    }

   	int8_t line[80];

    while (fgets(line, sizeof(line), file) != NULL)
	{
	
		if(Total_Check(line) == CHECK_OK)
		{
			printf("Address: 0x%04X  Data: ", GetAddress(line));
			
			uint8_t i;
			
			for(i = 0 ; i < 16;i++)
			{
				printf("%x", GetData(line,i));
			}
			printf("\n");
		
		}

}
        
    fclose(file);
    return 0;
  }
  
