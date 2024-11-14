#include <stdio.h>
#include <stdlib.h>

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

// Function to print a polynomial
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

// Function to subtract two polynomials
struct Node* subtractPolynomials(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;
    struct Node *temp1 = poly1, *temp2 = poly2;

    while (temp1 != poly1 || temp2 != poly2) {
        if (temp1->exp > temp2->exp) {
            insertAtEnd(&result, temp1->coeff, temp1->exp);
            temp1 = temp1->next;
        } else if (temp1->exp < temp2->exp) {
            insertAtEnd(&result, -temp2->coeff, temp2->exp);
            temp2 = temp2->next;
        } else {
            int diffCoeff = temp1->coeff - temp2->coeff;
            if (diffCoeff != 0) {
                insertAtEnd(&result, diffCoeff, temp1->exp);
            }
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }

    while (temp1 != poly1) {
        insertAtEnd(&result, temp1->coeff, temp1->exp);
        temp1 = temp1->next;
    }

    while (temp2 != poly2) {
        insertAtEnd(&result, -temp2->coeff, temp2->exp);
        temp2 = temp2->next;
    }

    return result;
}

int main() {
    struct Node* poly1 = NULL;
    struct Node* poly2 = NULL;
    struct Node* result = NULL;

    insertAtEnd(&poly1, 5, 3);  // 5x^3
    insertAtEnd(&poly1, 4, 2);  // 4x^2
    insertAtEnd(&poly1, 3, 1);  // 3x^1
    insertAtEnd(&poly1, 2, 0);  // 2x^0

    insertAtEnd(&poly2, 3, 3);  // 3x^3
    insertAtEnd(&poly2, 2, 2);  // 2x^2
    insertAtEnd(&poly2, 1, 1);  // 1x^1
    insertAtEnd(&poly2, 5, 0);  // 5x^0

    printf("Polynomial 1: ");
    printPolynomial(poly1);
    printf("Polynomial 2: ");
    printPolynomial(poly2);

    result = subtractPolynomials(poly1, poly2);

    printf("Resultant Polynomial after subtraction: ");
    printPolynomial(result);

    return 0;
}
