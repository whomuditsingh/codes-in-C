#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Stack structure for characters
typedef struct {
    int top;
    char items[MAX];
} Stack;

void init(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, char c) {
    if (s->top < MAX - 1) {
        s->items[++(s->top)] = c;
    }
}

char pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->items[(s->top)--];
    }
    return '\0';
}

char peek(Stack *s) {
    if (!isEmpty(s)) {
        return s->items[s->top];
    }
    return '\0';
}

int precedence(char op) {
    switch (op) {
        case '^':
            return 3;
        case '*':
        case '/':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            return 0;
    }
}

// Check associativity
int isRightAssociative(char op) {
    return (op == '^');
}

void reverseString(char *str) {
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}

// Convert Infix to Postfix
void infixToPostfix(const char *infix, char *postfix) {
    Stack s;
    init(&s);
    int k = 0;

    for (int i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        if (isalnum(ch)) {
            postfix[k++] = ch;
        } else if (ch == '(') {
            push(&s, ch);
        } else if (ch == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                postfix[k++] = pop(&s);
            }
            pop(&s); // Remove '('
        } else {
            // Operator encountered
            while (!isEmpty(&s) && peek(&s) != '(') {
                int precCurr = precedence(ch);
                int precStack = precedence(peek(&s));

                if (precStack > precCurr || (precStack == precCurr && !isRightAssociative(ch))) {
                    postfix[k++] = pop(&s);
                } else {
                    break;
                }
            }
            push(&s, ch);
        }
    }

    while (!isEmpty(&s)) {
        postfix[k++] = pop(&s);
    }
    postfix[k] = '\0';
}

// Convert Infix to Prefix
void infixToPrefix(const char *infix, char *prefix) {
    int len = strlen(infix);
    char revInfix[MAX];
    char modifiedPostfix[MAX];

    strcpy(revInfix, infix);
    reverseString(revInfix);

    for (int i = 0; i < len; i++) {
        if (revInfix[i] == '(') {
            revInfix[i] = ')';
        } else if (revInfix[i] == ')') {
            revInfix[i] = '(';
        }
    }

    Stack s;
    init(&s);
    int k = 0;

    for (int i = 0; revInfix[i] != '\0'; i++) {
        char ch = revInfix[i];

        if (isalnum(ch)) {
            modifiedPostfix[k++] = ch;
        } else if (ch == '(') {
            push(&s, ch);
        } else if (ch == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                modifiedPostfix[k++] = pop(&s);
            }
            pop(&s);
        } else {
            while (!isEmpty(&s) && peek(&s) != '(') {
                int precCurr = precedence(ch);
                int precStack = precedence(peek(&s));

                if (precStack > precCurr || (precStack == precCurr && isRightAssociative(ch))) {
                    modifiedPostfix[k++] = pop(&s);
                } else {
                    break;
                }
            }
            push(&s, ch);
        }
    }

    while (!isEmpty(&s)) {
        modifiedPostfix[k++] = pop(&s);
    }
    modifiedPostfix[k] = '\0';

    strcpy(prefix, modifiedPostfix);
    reverseString(prefix);
}

int main() {
    char infix[] = "(A+B)*C-(D-E)*(F+G)";
    char postfix[MAX];
    char prefix[MAX];

    infixToPostfix(infix, postfix);
    infixToPrefix(infix, prefix);

    printf("Infix Expression   : %s\n", infix);
    printf("Postfix Expression : %s\n", postfix);
    printf("Prefix Expression  : %s\n", prefix);

    return 0;
}
