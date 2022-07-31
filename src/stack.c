#include <stdlib.h>
#include <stdio.h>

int* stack_size;
int* n_stack_elements;
int* stack;

void push(int val){
    // printf("%p\n", stack);
    // printf("%d\n", *n_stack_elements);
    stack[*n_stack_elements] = val;
    (*n_stack_elements) ++;

    if(*n_stack_elements >= *stack_size){
        (*stack_size) += 100;
        stack = reallocarray(stack, *stack_size, sizeof(int));
    }
}

int pop(){
    (*n_stack_elements) --;
    int val = stack[*n_stack_elements];
    stack[*n_stack_elements] = 0;
    return val;
}

int init_stack(){
    stack_size = (int*)malloc(sizeof(int));
    n_stack_elements = (int*)malloc(sizeof(int));

    if (stack_size == NULL || n_stack_elements == NULL){
        return 1;
    }
    *stack_size = 100;
    *n_stack_elements = 0;

    stack = (int*)calloc(*stack_size, sizeof(int));
    if (stack == NULL){
        return 1;
    }

    return 0;
}