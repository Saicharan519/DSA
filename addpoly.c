#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coeff;
    int exp;
    struct Node* next;
    struct Node* prev;
};

struct Node* createNode(int coeff, int exp) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void insertAtEnd(struct Node** head, int coeff, int exp) {
    struct Node* newNode = createNode(coeff, exp);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
}

struct Node* addPolynomials(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;
    struct Node* temp1 = poly1;
    struct Node* temp2 = poly2;

    while (temp1 != NULL && temp2 != NULL) {
        if (temp1->exp > temp2->exp) {
            insertAtEnd(&result, temp1->coeff, temp1->exp);
            temp1 = temp1->next;
        } else if (temp1->exp < temp2->exp) {
            insertAtEnd(&result, temp2->coeff, temp2->exp);
            temp2 = temp2->next;
        } else {
            int sumCoeff = temp1->coeff + temp2->coeff;
            if (sumCoeff != 0) {
                insertAtEnd(&result, sumCoeff, temp1->exp);
            }
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }

    while (temp1 != NULL) {
        insertAtEnd(&result, temp1->coeff, temp1->exp);
        temp1 = temp1->next;
    }

    while (temp2 != NULL) {
        insertAtEnd(&result, temp2->coeff, temp2->exp);
        temp2 = temp2->next;
    }

    return result;
}

void printPolynomial(struct Node* poly) {
    if (poly == NULL) {
        printf("Polynomial is empty.\n");
        return;
    }

    struct Node* temp = poly;
    while (temp != NULL) {
        if (temp->coeff > 0 && temp != poly) {
            printf("+");
        }
        printf("%dx^%d ", temp->coeff, temp->exp);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    struct Node* poly1 = NULL;
    struct Node* poly2 = NULL;
    struct Node* result = NULL;

    insertAtEnd(&poly1, 3, 3);
    insertAtEnd(&poly1, 2, 2);
    insertAtEnd(&poly1, 5, 0);

    insertAtEnd(&poly2, 4, 3);
    insertAtEnd(&poly2, 1, 2);
    insertAtEnd(&poly2, 2, 1);
    insertAtEnd(&poly2, 7, 0);

    printf("Polynomial 1: ");
    printPolynomial(poly1);
    printf("Polynomial 2: ");
    printPolynomial(poly2);

    result = addPolynomials(poly1, poly2);

    printf("Resultant Polynomial after addition: ");
    printPolynomial(result);

    return 0;
}
