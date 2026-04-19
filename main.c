#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nums[100];
int nums_top = -1;

char ops[100];
int ops_top = -1;

void push_num(int n);
int pop_num();
void push_op(char op);
char pop_op();
int priority(char op);
void apply_op(char op);
int evaluate(char *expr);

int main() {
    char expr[256];

    while(1)
    {
        printf("> ");
        if (fgets(expr,sizeof(expr), stdin) == NULL) break;
        expr[strcspn(expr, "\n")] = '\0';
        if (strcmp(expr, "exit") == 0) break;
        
        printf("%d\n", evaluate(expr));
    }

    return 0;
}

void push_num(int n) {
    if (nums_top >= 99) return;
    nums[++nums_top] = n;
}

int pop_num() {
    if (nums_top < 0) return 0;
    return nums[nums_top--];
}

void push_op(char op) {
    if (ops_top >= 99) return;
    ops[++ops_top] = op;
}

char pop_op() {
    if (ops_top < 0) return '\0';
    return ops[ops_top--];
}

int priority(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

void apply_op(char op) {
    int b = pop_num();
    int a = pop_num();
    switch(op) {
        case '+': push_num(a + b); break;
        case '-': push_num(a - b); break;
        case '*': push_num(a * b); break;
        case '/':
            if (b == 0) { printf("Error: Division by zero\n"); return; }
            push_num(a / b); break;
    }
}

int evaluate(char *expr) {
    nums_top = -1;  // reset number stack
    ops_top = -1;   // reset operator stack
    int len = strlen(expr);


    for (int i = 0; i < len; ++i)
    {
        char c = expr[i];

        if (c == ' ') continue;
        if (expr[i] >= '0' && expr[i] <= '9')
        {
            int num = 0;
            while(i < len && expr[i] >= '0' && expr[i] <= '9') {
                num = num * 10 + (expr[i] - '0');
                i++;
            }
            i--;
            push_num(num);
        }
        if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            
            while (ops_top >= 0 && priority(ops[ops_top]) >= priority(c))
            {
                apply_op(pop_op());
            }
            push_op(c);
        }
        if (c == '(')
        {
            push_op(c);    
        }
        
        if (c == ')')
        {
            while (ops_top >= 0 && ops[ops_top] != '(')
            {
                apply_op(pop_op());
            }
            pop_op(); //discard '('
        }
    }

    while (ops_top >= 0)
    {
        apply_op(pop_op());
    }

    return pop_num();

}