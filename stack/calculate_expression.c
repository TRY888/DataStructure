#include "linkStack.h"

//����׺���ʽ��ջ 
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

//��׺���ʽת��Ϊ��׺���ʽ�Ĳ���
//1.������������ֱ�����
//2.��������������ջΪ�գ�����ջ
//3.���������ţ�����ջ
//4.���������ţ������ε���ջ��Ԫ�ز������ֱ�����������ţ������Ų����
//5.�����������������ջ��Ԫ�����ȼ����ڵ��ڸ���������򵯳����������
//  Ȼ�󽫸��������ջ
//6.�ȵ����ʽ������ϣ���ջ��Ԫ�ص���������� 
LinkQueue linkQueue;
LinkQueue *lQHead, *lQTail; 
void infixToPostfix(const char *express)
{
	LinkStack *stack;
	initLinkStack(&stack);
	
		//��ʼ����ʽ����
	initLinkQueue(&linkQueue, &lQHead, &lQTail);
	
	DataType output;
	int len = strlen(express);
	int i = 0;
	while(i<len)
	{
		if(express[i] <= '9' && express[i] >='0'){
			printf("%c ", express[i]);
			
			pushLinkQueue(&lQTail, express[i]);//�����ֵ������� 
			
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
				
				pushLinkQueue(&lQTail, output);//�����ֵ�������
				
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
				
				pushLinkQueue(&lQTail, output);//�����ֵ������� 
				
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
		
		pushLinkQueue(&lQTail, output);//�����ֵ������� 
		
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

//1.������������ջ
//2.��������������ջ�����ε����������֣������ؼ��㣬��������ֵ��ջ
//3.ֱ��������ʽ��ϣ���ջ��Ԫ�ؼ�Ϊ���ʽ��ֵ 
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
