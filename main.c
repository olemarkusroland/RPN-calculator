#include <stdio.h>
#include <stdlib.h>

#define EMPTY_TOS -1
#define MIN_STACK_SIZE 5
#define FALSE 0
#define TRUE 1
#define ARRAY_SIZE 30


struct StackRecord {
    int capacity;
    int topOfStack;
    int *array;
};

typedef struct StackRecord *Stack;


Stack CreateStack(int);
void MakeEmptyStack(Stack);
void PushStack(int, Stack);
int PopStack(Stack);
int TopOfStack(Stack);
int IsFullStack(Stack);
int IsEmptyStack(Stack);
void DisplayStack(Stack);
int two_ints(Stack);


int main() {
    int stackSize = 1000;
    Stack myStack;
    char string[ARRAY_SIZE];
    char *ptr;
    int top;

    myStack = CreateStack(stackSize);
    MakeEmptyStack(myStack);

    while (TRUE) {
        fflush(stdin);
        printf(":");
        scanf("%s", string);
        fflush(stdin);
        int integer = strtol(string, &ptr, 10);

        if (*ptr == '\0' || ptr != string) //If number
            PushStack(integer, myStack);

        else if (string[0] == '+') {
            if (two_ints(myStack))
                PushStack(PopStack(myStack) + PopStack(myStack), myStack);
        } else if (string[0] == '-') {
            if (two_ints(myStack)) {
                top = PopStack(myStack);
                PushStack(PopStack(myStack) - top, myStack);
            }
        } else if (string[0] == '*') {
            if (two_ints(myStack))
                PushStack(PopStack(myStack) * PopStack(myStack), myStack);
        } else if (string[0] == '/') {
            if (two_ints(myStack)) {
                top = PopStack(myStack);
                if (TopOfStack(myStack) == 0) {
                    printf("ERROR: Division by 0\n");
                    PushStack(top, myStack);
                } else
                    PushStack(PopStack(myStack) / top, myStack);
            }
        }

        DisplayStack(myStack);
    }
}

int two_ints(Stack s) {
    int top = PopStack(s);
    if (top == EMPTY_TOS) {
        return FALSE;
    } else if (s->topOfStack == EMPTY_TOS) {
        printf("ERROR: Insufficient number of operands\n");
        PushStack(top, s);
        return FALSE;
    } else {
        PushStack(top, s);
        return TRUE;
    }
}

Stack CreateStack(int maxElements) {
    Stack s;

    if (maxElements < MIN_STACK_SIZE)
        printf("Stack size is too small\n");

    s = malloc(sizeof(struct StackRecord));
    if (s == NULL)
        printf("Out of memory space\n");

    s->array = malloc(sizeof(int) * maxElements);
    if (s->array == NULL)
        printf("Out of memory space\n");

    s->capacity = maxElements;
    MakeEmptyStack(s);
    return s;
}


void MakeEmptyStack(Stack s) {
    s->topOfStack = EMPTY_TOS;
}


int IsEmptyStack(Stack s) {
    return s->topOfStack == EMPTY_TOS;
}


int IsFullStack(Stack s) {
    return s->topOfStack == s->capacity;
}


void PushStack(int x, Stack s) {
    if (IsFullStack(s))
        printf("Stack is full\n");
    else
        s->array[++s->topOfStack] = x;
}


int PopStack(Stack s) {
    if (!IsEmptyStack(s))
        return s->array[s->topOfStack--];
    else {
        printf("The stack is empty\n");
        return -1;
    }
}


int TopOfStack(Stack s) {
    if (!IsEmptyStack(s))
        return s->array[s->topOfStack];
    else {
        printf("The stack is empty\n");
        return -1;
    }
}


void DisplayStack(Stack s) {
    int i;

    printf("Stack content:\n");
    for (i = s->topOfStack; i >= 0; i--)
        printf("\t--> %d\n", s->array[i]);
}