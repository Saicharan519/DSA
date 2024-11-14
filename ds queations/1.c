#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Node {
    int coeff;
    int exp;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int coeff, int exp) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = newNode;  // Points to itself (circular link)
    return newNode;
}

// Function to insert a node in a circular linked list
void insertAtEnd(struct Node** head, int coeff, int exp) {
    struct Node* newNode = createNode(coeff, exp);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* temp = *head;
        while (temp->next != *head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = *head;  // Make the list circular
    }
}

// Function to evaluate the polynomial at a given value of x
double evaluatePolynomial(struct Node* head, double x) {
    double result = 0.0;
    if (head == NULL) {
        printf("Polynomial is empty.\n");
        return result;
    }

    struct Node* temp = head;
    do {
        result += temp->coeff * pow(x, temp->exp);
        temp = temp->next;
    } while (temp != head);

    return result;
}

// Function to print the polynomial
void printPolynomial(struct Node* head) {
    if (head == NULL) {
        printf("Polynomial is empty.\n");
        return;
    }

    struct Node* temp = head;
    do {
        if (temp->coeff > 0 && temp != head) {
            printf("+");
        }
        printf("%dx^%d ", temp->coeff, temp->exp);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
}

int main() {
    struct Node* poly = NULL;
    double x, result;

    // Inserting terms into the polynomial
    insertAtEnd(&poly, 3, 3);  // 3x^3
    insertAtEnd(&poly, 4, 2);  // 4x^2
    insertAtEnd(&poly, 2, 1);  // 2x^1
    insertAtEnd(&poly, 5, 0);  // 5x^0 (constant term)

    // Printing the polynomial
    printf("Polynomial: ");
    printPolynomial(poly);

    // Asking the user to input a real value for x
    printf("Enter a real value for x: ");
    scanf("%lf", &x);

    // Evaluating the polynomial at the given value of x
    result = evaluatePolynomial(poly, x);

    // Printing the result of the evaluation
    printf("The result of the polynomial evaluated at x = %.2f is: %.2f\n", x, result);

    return 0;
}
