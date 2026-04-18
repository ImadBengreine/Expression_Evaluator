#include<stdio.h>
#include <stdlib.h>

int nums[100];
int nums_top = -1;

char ops[100];
int ops_top = -1;

void push_num(int n);
int pop_num();
void push_op(char op);
char pop_op();
int priority(char op);


int main() {
    printf("woorks!\n");
}

void push_num(int n) {
    if (nums_top >= 99)
    {
        return;
    }
    nums_top++;
    nums[nums_top] = n;
}

int pop_num() {
    int num = nums[nums_top];
    nums_top--;
    return num;
}

void push_op(char op) {
    if (ops_top >= 99)
    {
        return;
    }
    ops_top++;
    ops[ops_top] = op;
}

char pop_op() {
    char op = ops[ops_top];
    ops_top--;
    return op;
}

int priority(char op) {
    if(op == '*' || op == '/') return 2;
    else if(op == '+' || op == '-') return 1;
    else return 0;
}
