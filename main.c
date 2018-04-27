/* -------------------------------------------------
*  To Do: determine whether input is given with 
*         properly balanced symbols
*  -------------------------------------------------
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int debugMode;

//Initializing the stack data type
typedef struct Stack 
{
    char* array;
    int current_size;
    int top;
} Stack;

void grow(Stack* stack) 
{
    char *tempArray =(char *) malloc(sizeof(char)*(stack->current_size+2));
    int i;
    
    for(i=0;i<stack->current_size;i++)
    {
        tempArray[i]=stack->array[i];
    }
    
    free(stack->array);
    stack->array=tempArray;
    stack->current_size += 2;
}

//Initializing the actual Stack
void initializeStack(Stack* stack) 
{
    if(stack==NULL)
    {
        stack=(Stack *)malloc(sizeof(Stack));
    }
    
    stack->array = (char *)malloc(sizeof(char)*2);
    stack->current_size=2;
    stack->top=-1;// empty stack
}

//Pushes given value onto the Stack and updates top which is a place holder of where the last element is
void push(Stack* stack, char input) 
{
    if(stack->top == stack->current_size - 1) 
    {
        grow(stack);
        
        if(debugMode == 1) 
        {
            printf("new current_size of Stack: %d\n", stack->current_size);
        }
    }
    
    if(debugMode == 1) 
    {
        printf("pushing: %c\n", input);
    }
    
    (stack->top)++;
    stack->array[stack->top] = input;
}

//Pops removes the last value to be pushed onto the Stack and returns it. Returns 'e' if the Stack is empty
char pop(Stack* stack) 
{
    if(stack->top == -1) 
    {
        return 'e';
    }
    
    char temp = stack->array[stack->top];
    (stack->top)--;
    
    if(debugMode == 1) 
    {
        printf("popping: %c\n", temp);
    }
    
    return temp;
}

//Returns the value on the top of the Stack, allows for the program to peek at the next value to be popped
char peek(Stack* stack) 
{
    return stack->array[stack->top];
}

//Returns 1 if the Stack is empty and returns 0 other wise
int isEmpty(Stack* stack) 
{
    if(stack->top == -1) 
    {
      return 1;
    }
    else 
    {
      return 0;
    }
}

void reset(Stack* stack) 
{
    free(stack->array);
    initializeStack(stack);
}

char otherSymbol(char symbol) 
{
    switch(symbol) 
    {
        case '<': return '>';
        case '(': return ')';
        case '{': return '}';
        case '[': return ']';
        case '>': return '<';
        case ')': return '(';
        case '}': return '{';
        case ']': return '[';
    }
    return 'z';
}

/********************************************************************************************************/

int main(int argc, char** argv) 
{
    debugMode = 0;
    int i;
    
    for(i = 0; i < argc; i++) 
    {
        if(strcmp(argv[i], "-d") == 0) 
        {
          debugMode = 1;
        }
    }

    Stack stk;
    initializeStack(&stk);

    char line[301]; // the 301 is for the max length of the input
    int pos = 0;
    char current;
    printf ("\n\t\tWelcome to Balanced Symbol Checker Program.\n\n");
    printf("Enter an equation (max 300 characters):\n");
    
    while(fgets( line, 300, stdin) != NULL) 
    {
        if(strcmp(line,"Q\n") == 0 || strcmp(line,"q\n") == 0) 
        {
            printf("Quitting\n");
            return 0;
        }
        
        pos = 0;
        current = '?';
        while(current != '\n') 
        {
            current = line[pos];

            if(stk.top == -1 && (current == ')' || current == '}' || current == ']' || current == '>')) 
            {
                printf("%s\n", line);
        
                for(i = 0; i < pos; i++) 
                {
                  printf(" ");
                }
            
            printf("^ missing %c \n", otherSymbol(current));
            break;
            }
            else if(current == '(' || current == '{' || current == '<' || current == '[') {
              push(&stk, current);
            }
            else if(current == ')' && stk.array[stk.top] == '(') {
              pop(&stk);
            }
            else if(current == '>' && stk.array[stk.top] == '<') {
              pop(&stk);
            }
            else if(current == '}' && stk.array[stk.top] == '{') {
              pop(&stk);
            }
            else if(current == ']' && stk.array[stk.top] == '[') {
              pop(&stk);
            }
            else 
            {
                if(current == ')' && stk.array[stk.top] != '(') 
                {
                    for(i = 0; i < pos; i++) 
                    {
                        printf(" ");
                    } 
                    printf("^ missing %c \n", otherSymbol(stk.array[stk.top]));
                    printf("Equation Unbalanced\n");
                    break;
                }
                else if(current == '>' && stk.array[stk.top] != '<') 
                {
                  for(i = 0; i < pos; i++) 
                  {
                      printf(" ");
                  }
                  printf("^ missing %c \n", otherSymbol(stk.array[stk.top]));
                  printf("Equation Unbalanced\n");
                  break;
                }
                else if(current == '}' && stk.array[stk.top] != '{') 
                {
                  for(i = 0; i < pos; i++) 
                  {
                      printf(" ");
                  }
                  printf("^ missing %c \n", otherSymbol(stk.array[stk.top]));
                  printf("Equation Unbalanced\n");
                  break;
                }
                else if(current == ']' && stk.array[stk.top] != '[') 
                {
                  for(i = 0; i < pos; i++) 
                  {
                      printf(" ");
                  }
                  printf("^ missing %c \n", otherSymbol(stk.array[stk.top]));
                  printf("Equation Unbalanced\n");
                  break;
                }
                else {
                }
            }
                pos++;
        }
    
        if(current == '\n') 
        {
            if(stk.top == -1) 
            {
                printf("%s \n", line);
                printf("Expression is balanced\n"); 
            }
            else if(stk.top != -1) 
            {
                printf("%s \n", line);
        
                for(i = 0; i < pos - 1; i++) 
                {
                    printf(" ");
                }
                printf("^ Expected %c\n", otherSymbol(stk.array[stk.top]));
            }
        }
        
        reset(&stk);
        int j;
        for(j = 0; j < 301; j++) 
        {
            line[j] = '\0';
        }
        printf("Enter another one or enter q to quit\n"); 
    }
}
