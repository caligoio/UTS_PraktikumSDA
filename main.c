#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

void preToInf(char Prefix[], char infix[]) {
    char stackpti[MAX][MAX];
    int top = -1;
    int length = strlen(Prefix);

    // memproses ekspresi prefiks dari kanan ke kiri
    for (int i = length - 1; i >= 0; i--) {
        if (isOperator(Prefix[i])) {
            char op1[MAX], op2[MAX], temp[MAX];
            strcpy(op1, stackpti[top--]);
            strcpy(op2, stackpti[top--]);
            sprintf(temp, "(%s%c%s)", op1, Prefix[i], op2);
            strcpy(stackpti[++top], temp);
        } else {
            char operand[2] = {Prefix[i], '\0'};
            strcpy(stackpti[++top], operand);
        }
    }
    strcpy(infix, stackpti[top]);
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

//Fungsi untuk mengkonversi Prefix ke Postfix
void preToPost (char Prefix[],char posfix[], char infix[]) {
    preToInf(Prefix, infix);
    inToPost(infix, posfix);
}

int main() {
    char infix[MAX], postfix[MAX], Prefix[MAX];
    int choice;
    while (1) {
        printf("\nKonversi Operasi Aritmatika :\n 1. Infix to Postfix\n 2. Postfix to Infix\n 3. Infix to Prefix\n 4. Prefix to Infix\n 5. Prefix to Postfix\n 6. Postfix to Prefix\n");
        printf("Enter your choice (1-6): ");
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
              printf("Masukkan Postfix : ");
              scanf("%s", &postfix);
              inToPost(postfix, infix);
              printf("Ekspresi infix: %s\n", infix);
              break;
          case 3 :
              printf("Masukkan Infix : ");
              scanf("%s", &infix);
              inToPre(infix, Prefix);
              printf("Ekspresi prefiks: %s\n", Prefix);
              break;
          case 4 :
              printf("Masukkan prefix : ");
              scanf("%s", &Prefix);
              preToInf(Prefix, infix);
              printf("Ekspresi infix: %s\n", infix);
              break;
        case 5 :
              printf("Masukkan Prefix : ");
              scanf("%s", &Prefix); 
              preToPost(Prefix, postfix, infix);
              printf("Ekspresi postfiks: %s\n", postfix);
              break;
        case 6 :
              printf("Masukkan postfix: ");
              scanf("%s", &postfix);
            //PosttoPre(postfix, Prefix);
              printf("Ekspresi prefiks: %s\n", Prefix);
              break;
          default:
              printf("pilihan tidak valid\n");
          }
    
    return 0;
    }
}
