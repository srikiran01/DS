#include<stdio.h>
#include<ctype.h>
#include<string.h>

#define MAX 100

char stack[MAX];
int top = -1;

//push functon
void push(char c)
{
	if(top < MAX -1)
	{
		stack[++top] = c;
	}
}

//pop function
char pop()
{
	if (top >= 0)
	{
		return stack[top--];
	}
	return -1;
}

//peek funtion
char peek()
{
	if (top>=0)
	{
		return stack[top];
	}
	return -1;
}

//Funtion to define operator precedence
int precedence(char op)
{
	switch (op)
	{
		case '*':
		case '/':
		case '%': return 2;
		case '+':
		case '-': return 1;
		default: return 0;
	}
}

// Function to check if character is operator
int isoperator(char c) 
{
	return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%');
}

//Infix to postfix conversation
void infixtoPostfix(char infix[],char postfix[])
{
	int i, k = 0;
	char symbol;

	for (i = 0; i < strlen(infix); i++)
	{
		symbol = infix[i];

		//operand ? directly add to postfix
		if (isalnum(symbol))
		{
			postfix[k++] = symbol;
		}
		// Left parenthesis ? push to stack
		else if (symbol == '(')
		{
			push(symbol);
		}
		// Right parenthesis ? pop until '('
		else if (symbol == ')')
		{
			while (top != -1 && peek() != '(')  // FIXED HERE
			{
				postfix[k++] = pop();
			}
			pop(); // remove '('
		}
		//operator
		else if (isoperator(symbol))
		{
			while (top != -1 && precedence(peek()) >= precedence(symbol))
			{
				postfix[k++] = pop();
			}
			push(symbol);
		}
	}

	while (top != -1)
	{
		postfix[k++] = pop();
	}
	postfix[k] = '\0'; // Null terminate string
}

int main()
{
	char infix[MAX], postfix[MAX];

	printf("Enter an infix expression: ");
	scanf("%s", infix);

	infixtoPostfix(infix, postfix);

	printf("Postfix expression: %s\n", postfix);

	return 0;
}

