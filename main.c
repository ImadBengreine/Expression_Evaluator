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
int apply_op(char op);
int evaluate(char *expr);

int main() {
    char expr[100];
    
    printf("Calculator (type 'exit' to quit)\n");
    
    while (1) {
        printf("> ");
        fflush(stdout);
        
        if (fgets(expr, sizeof(expr), stdin) == NULL) {
            printf("\n");
            break;  // EOF (Ctrl+D / Ctrl+Z)
        }
        
        // Remove trailing newline
        expr[strcspn(expr, "\n")] = '\0';
        
        // Exit condition
        if (strcmp(expr, "exit") == 0 || strcmp(expr, "quit") == 0) {
            printf("Goodbye!\n");
            break;
        }
        
        // Skip empty lines
        if (strlen(expr) == 0) continue;
        
        int result = evaluate(expr);
        printf("= %d\n", result);
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

int apply_op(char op) {
    int b = pop_num();
    int a = pop_num();
    
    switch(op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b == 0) {
                printf("Error: Division by zero\n");
                return 0;
            }
            return a / b;
        default: return 0;
    }
}

int evaluate(char *expr) {
    int len = strlen(expr);
    
    for (int i = 0; i < len; i++) {
        if (expr[i] == ' ') continue;
        
        if (expr[i] >= '0' && expr[i] <= '9') {
            int num = 0;
            while (i < len && expr[i] >= '0' && expr[i] <= '9') {
                num = num * 10 + (expr[i] - '0');
                i++;
            }
            i--;
            push_num(num);
        }
        else if (expr[i] == '(') {
            push_op(expr[i]);
        }
        else if (expr[i] == ')') {
            while (ops_top != -1 && ops[ops_top] != '(') {
                push_num(apply_op(pop_op()));
            }
            if (ops_top != -1) pop_op();
        }
        else if (expr[i] == '+' || expr[i] == '-' || 
                 expr[i] == '*' || expr[i] == '/') {
            while (ops_top != -1 && priority(ops[ops_top]) >= priority(expr[i])) {
                push_num(apply_op(pop_op()));
            }
            push_op(expr[i]);
        }
    }
    
    while (ops_top != -1) {
        push_num(apply_op(pop_op()));
    }
    
    return pop_num();
}