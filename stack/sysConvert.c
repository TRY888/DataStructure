#include "linkStack.h" 

char decimalToABCDEF(int decimal)
{	
	return (char)(decimal + 55);
}

void testSysConvert()
{
	
	printf("-----system convert and print-----\n");
	LinkStack *stack;
	initLinkStack(&stack);
	int choose = 1; 
	DataType input;
	DataType output;
	int system;
	while(choose)
	{
		printf("1-push\n0-exit\n");
		scanf("%d", &choose);
		if(choose == 1){
			printf("input the decimal number:\n");
			scanf("%d", &input);
			printf("input the system to convert\n");
			scanf("%d", &system);
			while(input != 0)
			{
				pushLinkStack(&stack, input%system);
				input = input / system;
			}
			printf("----------------\n");
			while(frontLinkStack(&stack, &output))
			{
				if(system >10 && (output >=10 && output <=15))
					printf("%c", decimalToABCDEF(output));
				else
				 	printf("%d", output);
				popLinkStack(&stack, &output);
			}
			printf("\n----------------\n");
		}
	}
}
