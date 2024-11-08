#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int coeff;       // Hệ số
    int exp;         // Số mũ
    struct Node* next; // Con trỏ tới đơn thức tiếp theo
} Node;

Node* createNode(int coeff, int exp) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}

void insertTerm(Node** head, int coeff, int exp) {
    Node* newNode = createNode(coeff, exp);
    if (*head == NULL || (*head)->exp < exp) {
        newNode->next = *head;
        *head = newNode;
        return;
    }
    Node* current = *head;
    while (current->next != NULL && current->next->exp > exp) {
        current = current->next;
    }
    if (current->exp == exp) {
        current->coeff += coeff;
        free(newNode);
        if (current->coeff == 0) { // Xóa nếu hệ số trở về 0
            Node* temp = *head;
            if (temp == current) {
                *head = current->next;
                free(current);
            } else {
                while (temp->next != current) {
                    temp = temp->next;
                }
                temp->next = current->next;
                free(current);
            }
        }
    } else {
        newNode->next = current->next;
        current->next = newNode;
    }
}

void printPolynomial(Node* head) {
    if (!head) {
        printf("0\n");
        return;
    }
    while (head != NULL) {
        printf("%d", head->coeff);
        if (head->exp != 0) {
            printf(".x^%d", head->exp);
        }
        if (head->next != NULL && head->next->coeff > 0) {
            printf(" + ");
        } else if (head->next != NULL) {
            printf(" ");
        }
        head = head->next;
    }
    printf("\n");
}

Node* addPolynomials(Node* f, Node* g) {
    Node* result = NULL;
    while (f != NULL) {
        insertTerm(&result, f->coeff, f->exp);
        f = f->next;
    }
    while (g != NULL) {
        insertTerm(&result, g->coeff, g->exp);
        g = g->next;
    }
    return result;
}

void inputPolynomial(Node** head) {
    int n, coeff, exp;
    printf("Nhap so luong don thuc: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Nhap he so va so mu (coeff exp): ");
        scanf("%d %d", &coeff, &exp);
        insertTerm(head, coeff, exp);
    }
}

int main() {
    Node* f = NULL;
    Node* g = NULL;
    printf("Nhap da thuc f(x):\n");
    inputPolynomial(&f);
    printf("Da thuc f(x) = ");
    printPolynomial(f);
    printf("Nhap da thuc g(x):\n");
    inputPolynomial(&g);
    printf("Da thuc g(x) = ");
    printPolynomial(g);
    Node* h = addPolynomials(f, g);
    printf("Tong h(x) = f(x) + g(x) = ");
    printPolynomial(h);
    return 0;
}
