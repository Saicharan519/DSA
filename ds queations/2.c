#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coeff;
    int exp;
    struct Node* next;
};

struct Node* createNode(int coeff, int exp) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = newNode;
    return newNode;
}

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
        newNode->next = *head;
    }
}

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

void removeOddCoefficients(struct Node** head) {
    if (*head == NULL) {
        printf("Polynomial is empty.\n");
        return;
    }

    struct Node* temp = *head;
    struct Node* prev = NULL;

    do {
        if (temp->coeff % 2 != 0) {
            if (prev == NULL) {
                struct Node* last = *head;
                while (last->next != *head) {
                    last = last->next;
                }
                if (*head == (*head)->next) {
                    free(*head);
                    *head = NULL;
                } else {
                    *head = temp->next;
                    last->next = *head;
                    free(temp);
                }
                temp = *head;
            } else {
                prev->next = temp->next;
                free(temp);
                temp = prev->next;
            }
        } else {
            prev = temp;
            temp = temp->next;
        }
    } while (temp != *head);
}

int main() {
    struct Node* poly = NULL;

    insertAtEnd(&poly, 3, 3);
    insertAtEnd(&poly, 4, 2);
    insertAtEnd(&poly, 5, 1);
    insertAtEnd(&poly, 2, 0);

    printf("Original Polynomial: ");
    printPolynomial(poly);

    removeOddCoefficients(&poly);

    printf("Polynomial after removing terms with odd coefficients: ");
    printPolynomial(poly);

    return 0;
}
