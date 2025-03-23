# UTS_PraktikumSDA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

char stack[MAX];
int top = -1;

// Fungsi untuk memeriksa apakah karakter adalah operand 
int isOperand(char ch) {
    return (ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

// Fungsi untuk memeriksa apakah karakter adalah operator 
int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

// Fungsi untuk menentukan prioritas operator
int precedence(char operator) {
    if (operator == '+' || operator == '-') {
        return 1;
    } else if (operator == '*' || operator == '/') {
        return 2;
    } else if (operator == '^') {
        return 3;
    } else {
        return 0; // Non-operator
    }
}

// Fungsi push ke stack
void push(char item) {
    if (top >= MAX - 1) {
        printf("Stack Penuh\n");
    } else {
        stack[++top] = item;
    }
}

// Fungsi pop dari stack
char pop() {
    if (top < 0) {
        printf("Stack Kosong\n");
        return -1;
    } else {
        return stack[top--];
    }
}

// Fungsi untuk mengonversi infiks ke postfiks
void inToPost(char infix[], char postfix[]) {
    int i = 0, j = 0;
    char temp;

    while (infix[i] != '\0') {
        if (isOperand(infix[i])) { // Memeriksa operand secara manual
            postfix[j++] = infix[i];
        } else if (infix[i] == '(') {
            push(infix[i]);
        } else if (infix[i] == ')') {
            while ((temp = pop()) != '(') {
                postfix[j++] = temp;
            }
        } else if (isOperator(infix[i])) {
            while (top != -1 && precedence(stack[top]) >= precedence(infix[i])) {
                postfix[j++] = pop();
            }
            push(infix[i]);
        }
        i++;
    }

    while (top != -1) {
        postfix[j++] = pop();
    }
    postfix[j] = '\0';
}

//fungsi untuk membalikkan string
void reverse(char str[]){
    int i = 0;
    int j = strlen(str) - 1;
    char temp;

    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

void inToPre(char infix[], char Prefix[]) {
    int i = 0, j = 0;
    char temp;

    reverse(infix); // membalik infix
    
    while (infix[i] != '\0') {
        if (isOperand(infix[i])) { // Memeriksa operand secara manual
            Prefix[j++] = infix[i];
        } else if (infix[i] == ')') {
            push(infix[i]);
        } else if (infix[i] == '(') {
            while ((temp = pop()) != ')') {
                Prefix[j++] = temp;
            }
        } else if (isOperator(infix[i])) {
            while (top != -1 && precedence(stack[top])  >= precedence(infix[i])) {
                Prefix[j++] = pop();
            }
            push(infix[i]);
        }
        i++;
    }

    while (top != -1) {
        Prefix[j++] = pop();
    }
    Prefix[j] = '\0';
    reverse(Prefix);
}

int main() {
    char infix[MAX], postfix[MAX], Prefix[MAX];
    int choice;
    while (1) {
        printf("\nMenu for Stack\n1. Infix to Postfix\n2. Postfix to Infix\n3. Infix to Prefix\n4. Prefix to Infix\n5.Prefix to Postfix\n6.Postfix to Prefix");
        printf("Enter your choice (1-4): ");
        scanf("%d", &choice);
      
          //perulangan untuk menjalankan operasi sesuai pilihan pada Menu
          switch(choice) {
          case 1 :
              printf("Masukkan Infix : ");
              scanf("%s", &infix);
              inToPost(infix, postfix);
              printf("Ekspresi postfiks: %s\n", postfix);
              break;
          case 2 :
              break;
          case 3 :
             printf("Masukkan Infix : ");
             scanf("%s", &infix);
             inToPre(infix, Prefix);
             printf("Ekspresi prefiks: %s\n", Prefix);
              break;
          case 4 :
              break;
         // case 5 :
          //printf("Masukkan Prefix : ");
          //scanf("%s", &Prefix); 
          //preToPost(Prefix, postfix);
          //printf("Ekspresi postfiks: %s\n", postfix);
            //break;
          default:
              printf("pilihan tidak valid\n");
          }
    
    return 0;
    }
}
