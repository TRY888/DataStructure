#include "linkStack.h"

int comparePrior(char top, char c)
{
	if(top == '*' || top == '/'){
		return 1;
	}
	if(c == '+' || c == '-'){
		return 1;
	}
	if((top == '+' || top == '-') && (c == '*' || c == '/')){
		return 0;
	}
}


void infixToPostfix(const char *express)
{
	LinkStack *stack;
	initLinkStack(&stack);
	DataType output;
	int len = strlen(express);
	int i = 0;
	while(i<len)
	{
		if(express[i] <= '9' && express[i] >='0'){
			printf("%c ", express[i]);
			i++;
			continue;
		}
		if(isLinkStackEmpty(&stack)){
			pushLinkStack(&stack, express[i]);
			i++;
			continue;
		}
		if(express[i] == '('){
			pushLinkStack(&stack, express[i]);
			i++;
			continue;
		}
		if(express[i] == ')')
		{
			while(frontLinkStack(&stack, &output))
			{
				printf("%c ", output);
				if(output == ')'){
					popLinkStack(&stack, &output);
					break;
				}
				popLinkStack(&stack, &output);	
			}
			i++;
			continue;
		}
		while(frontLinkStack(&stack, &output))
		{
			if(comparePrior(output, express[i])){
				popLinkStack(&stack, &output);
				printf("%c", output);
			}else{
				pushLinkStack(&stack, express[i]);
				break;
			}
		} 	
	}
	while(frontLinkStack(&stack, &output))
	{
		popLinkStack(&stack, &output);
		printf("%c", output);
	}	
}

void testInfixToPostfix()
{
	const char *express = "1+2*(4+5)+8/2";
	infixToPostfix(express);
}


