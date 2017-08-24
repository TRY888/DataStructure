#include "linkStack.h"

//将后缀表达式入栈 
#include "linkQueue.h" 

int comparePrior(char top, char c)
{
	if(top == '*' || top == '/'){
		return 1;
	}
	if(top == '('){
		return 0;
	}
	if(c == '+' || c == '-'){
		return 1;
	}
	if((top == '+' || top == '-') && (c == '*' || c == '/')){
		return 0;
	}	
}

//中缀表达式转化为后缀表达式的步骤
//1.遇见操作数，直接输出
//2.遇见运算符，如果栈为空，则入栈
//3.遇见左括号，则入栈
//4.遇见右括号，则依次弹出栈顶元素并输出，直到遇见左括号，左括号不输出
//5.遇见其他运算符，若栈顶元素优先级大于等于该运算符，则弹出并且输出，
//  然后将该运算符入栈
//6.等到表达式输入完毕，将栈中元素弹出并且输出 
LinkQueue linkQueue;
LinkQueue *lQHead, *lQTail; 
void infixToPostfix(const char *express)
{
	LinkStack *stack;
	initLinkStack(&stack);
	
		//初始化链式队列
	initLinkQueue(&linkQueue, &lQHead, &lQTail);
	
	DataType output;
	int len = strlen(express);
	int i = 0;
	while(i<len)
	{
		if(express[i] <= '9' && express[i] >='0'){
			printf("%c ", express[i]);
			
			pushLinkQueue(&lQTail, express[i]);//将输出值依次入队 
			
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
				if(output == '('){
					popLinkStack(&stack, &output);
					break;
				}
				printf("%c ", output);
				
				pushLinkQueue(&lQTail, output);//将输出值依次入队
				
				popLinkStack(&stack, &output);	
			}
			i++;
			continue;
		}
		while(frontLinkStack(&stack, &output))
		{
			if(comparePrior(output, express[i])){
				popLinkStack(&stack, &output);
				printf("%c ", output);
				
				pushLinkQueue(&lQTail, output);//将输出值依次入队 
				
			}else{
				pushLinkStack(&stack, express[i]);
				i++;
				break;
			}
		} 	
	}
	while(frontLinkStack(&stack, &output))
	{
		popLinkStack(&stack, &output);
		printf("%c ", output);
		
		pushLinkQueue(&lQTail, output);//将输出值依次入队 
		
	}	
}

void testInfixToPostfix()
{
	const char *express = "1+2*(4+5)+8/2";
	infixToPostfix(express);
}

int calculateByOperator(DataType value1, DataType value2, DataType operator)
{
	int v1 = value1;
	int v2 = value2;
	int result;
	switch(operator)
	{
		case '+': result = v1 + v2; break;
		case '-': result = v1 - v2; break; 
		case '*': result = v1 * v2; break;
		case '/': result = v1 / v2; break;
		default: break;
 	}
 	return result;
}

//1.遇见数字则入栈
//2.遇见运算符，则从栈顶依次弹出两个数字，完成相关计算，并将计算值入栈
//3.直到输入表达式完毕，则栈顶元素即为表达式的值 
void postfixCalculate()
{
    LinkStack *stack;
	initLinkStack(&stack);
	DataType fromQueue;
	DataType fSValue1, fSValue2;
	DataType expressValue;
	
	while(popLinkQueue(&lQHead, &lQTail, &fromQueue))
	{
		if(fromQueue >= '0' && fromQueue <='9'){
			pushLinkStack(&stack, fromQueue-48);
		}else{
			popLinkStack(&stack, &fSValue1);
			popLinkStack(&stack, &fSValue2);
			pushLinkStack(&stack, calculateByOperator(fSValue2, fSValue1, fromQueue));
		}
	} 
	popLinkStack(&stack, &expressValue);
	printf("\n--------express value:%d--------\n", expressValue);
} 

void calculateExpression()
{
	const char *express = "1+2*(4+5)+8/2";
	infixToPostfix(express);
	postfixCalculate();
}
