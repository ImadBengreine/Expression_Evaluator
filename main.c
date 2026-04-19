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
        case '+':
            return a + b;
            break  
        case '-':
            return a - b;
            break
        case '*':
            return a * b;
            break
        case '/':
            if (b == 0) {
                printf("Error: Division by zero\n");
                return 0;
            }
            return a / b;
            break

        default: return 0;
    }
}

int evaluate(char *expr) {
    
}