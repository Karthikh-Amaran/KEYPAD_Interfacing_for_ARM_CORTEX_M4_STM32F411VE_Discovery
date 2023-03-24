#include <stdint.h>
#include <stdio.h>
int main(void)
{

	// Here we are using PA1,PA2,PA3,PA4 for R1,R2,R3,R4
	// Here we are using PD1,PD2,PD3,PD4 for C1,C2,C3,C4

	// 1) Activate the GPIO peripheral Clock (RCC)

	// Base address of RCC - 0x4002 3800
	// Address Offset value for Peripheral Clock enable register - 0x30
	// Final required address for enabling the GPIo is
	// 0x4002 3800 + 0x30 = (0x40023800+0x30)+
	// Data to be given at that address is 0x1001 = 9;
	// Data |= 0x1001<<0 (Or used for setting the bits)
    int32_t volatile *RCC_ENABLE = (int32_t*)(0x40023800+0x30);
    *RCC_ENABLE |= 0x0001<<0; // Enabling the clock for GPIO A and GPIO D
    *RCC_ENABLE |= 0x0001<<3; // Enabling the clock for GPIO A and GPIO D
    // 2) Defining the mode of the GPIO used here

    // We are using PA (rows) as output and PD (column) as Output
    // Base Address of Port A = 0x4002 0000 - OUTPUT
    // Address Offset of Mode Register of GPIO is 0x00
    // Therefore the final Address is (0x40020000+0x00)
    // Data to be inserted into the register is 0X01010101<<0 (Using |)
    int32_t volatile *MODE_A = (int32_t*)(0x40020000+0x00);
    *MODE_A |= 0x0001<<0;
    *MODE_A |= 0x0001<<2;
    *MODE_A |= 0x0001<<4;
    *MODE_A |= 0x0001<<6;


    // Defining the mode of PD - INPUT
    // Base Address of Port D = 0x4002 0C00
    // Address Offset of Mode Register of GPIO is 0x00
    // Therefore the final Address is (0x40020C00+0x00)
    // Data to be inserted into the register is 0X00000000 (Using &)
    int32_t volatile *MODE_D = (int32_t*)(0x40020C00+0x00);
    *MODE_D &= 0x0000<<0;

    // 3) Writing to the PA port

    // Address of Output register =  0x40020000+0x14
    int32_t volatile *OUTPUT_A = (int32_t*)(0x40020000+0x14);
    int8_t volatile i = 0;

    // 4) Reading to the PD port

    // Address of Output register =  0x40020C00+0x10
    int32_t volatile *INPUT_D = (int32_t*)(0x40020C00+0x10);
    int32_t input_data;
    int32_t output_data;
    uint32_t delay=0;

//----------------------------------------------------------------------------------------------------------

    while(1)
    {
    // 5) Write output to the port A
    for(i=0;i<4;i++)
    {
    	*OUTPUT_A |= 0x0001<<i;
    	//printf("The value of i is %d\n",*OUTPUT_A);
    	//printf("*INPUT_D = %d\n",*INPUT_D);
    	output_data = (*OUTPUT_A);
    	output_data &= 0x000f;
    	input_data =  (*INPUT_D);
    	input_data &= 0x000f;
    	//printf("input_data = %d\n",input_data);
    // 6) Read input from the port D
    	if(input_data !=0)
    	{
    	switch(input_data)
    	{
    	case 1:
    		switch(output_data)
    		{
    		 case 1: printf("ROW:1 COL:1 CHAR:1 \n"); for(delay=0;delay<30000;delay++); break;
    		 case 2: printf("ROW:2 COL:1 CHAR:4 \n"); for(delay=0;delay<30000;delay++); break;
    		 case 4: printf("ROW:3 COL:1 CHAR:7 \n"); for(delay=0;delay<30000;delay++); break;
    		 case 8: printf("ROW:4 COL:1 CHAR:* \n"); for(delay=0;delay<30000;delay++); break;
    		}
    		break;
    	case 2:
    		switch(output_data)
    		{
    		 case 1: printf("ROW:1 COL:2 CHAR:2 \n"); for(delay=0;delay<30000;delay++); break;
    		 case 2: printf("ROW:2 COL:2 CHAR:5 \n"); for(delay=0;delay<30000;delay++); break;
    		 case 4: printf("ROW:3 COL:2 CHAR:8 \n"); for(delay=0;delay<30000;delay++); break;
    		 case 8: printf("ROW:4 COL:2 CHAR:0 \n"); for(delay=0;delay<30000;delay++); break;
    		}
    		break;
    	case 4:
    		switch(output_data)
    		{
    		 case 1: printf("ROW:1 COL:3 CHAR:3 \n"); for(delay=0;delay<30000;delay++); break;
    		 case 2: printf("ROW:2 COL:3 CHAR:6 \n"); for(delay=0;delay<30000;delay++); break;
    		 case 4: printf("ROW:3 COL:3 CHAR:9 \n"); for(delay=0;delay<30000;delay++); break;
    		 case 8: printf("ROW:4 COL:3 CHAR:# \n"); for(delay=0;delay<30000;delay++); break;
    		}
    		break;
    	case 8:
    		switch(output_data)
    		{
    		 case 1: printf("ROW:1 COL:4 CHAR:A \n"); for(delay=0;delay<30000;delay++); break;
    		 case 2: printf("ROW:2 COL:4 CHAR:B \n"); for(delay=0;delay<30000;delay++); break;
    		 case 4: printf("ROW:3 COL:4 CHAR:C \n"); for(delay=0;delay<30000;delay++); break;
    		 case 8: printf("ROW:4 COL:3 CHAR:D \n"); for(delay=0;delay<30000;delay++); break;
    		}
    		break;
    	}
    	*OUTPUT_A &= 0x0000;
    	*INPUT_D &= 0x0000;
    	}
    }


    }
}
