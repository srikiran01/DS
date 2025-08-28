#include <stdio.h>
#include <ctype.h>
#define MAX 100

float st[MAX];
int top = -1;

void push(float st[], float val);
float pop(float st[]);
float evaluatePostfixExp(char exp[]);

int main() {
    float val;
    char exp[100];

    printf("\nEnter any postfix expression: ");
    fgets(exp, sizeof(exp), stdin);  // Safe input

    val = evaluatePostfixExp(exp);
    printf("\nValue of the postfix expression = %.2f\n", val);

    return 0;
}

float evaluatePostfixExp(char exp[]) {
    int i = 0;
    float op1, op2, value;

    while (exp[i] != '\0' && exp[i] != '\n') {
        if (isdigit(exp[i])) {
            // Convert char digit to float and push
            push(st, (float)(exp[i] - '0'));
        } else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' ||
                   exp[i] == '/' || exp[i] == '%') {

            op2 = pop(st);
            op1 = pop(st);

            switch (exp[i]) {
                case '+':
                    value = op1 + op2;
                    break;
                case '-':
                    value = op1 - op2;
                    break;
                case '*':
                    value = op1 * op2;
                    break;
                case '/':
                    if (op2 == 0) {
                        printf("Error: Division by zero\n");
                        return 0;
                    }
                    value = op1 / op2;
                    break;
                case '%':
                    value = (int)op1 % (int)op2;
                    break;
            }

            push(st, value);
        }
        // Ignore spaces
        i++;
    }
    return pop(st);
}

void push(float st[], float val) {
    if (top == MAX - 1)
        printf("\nSTACK OVERFLOW\n");
    else {
        top++;
        st[top] = val;
    }
}

float pop(float st[]) {
    float val = -1;
    if (top == -1)
        printf("\nSTACK UNDERFLOW\n");
    else {
        val = st[top];
        top--;
    }
    return val;
}

