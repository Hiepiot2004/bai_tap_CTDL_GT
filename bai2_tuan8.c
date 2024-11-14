#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int he_so;       // Hệ số
    int so_mu;         // Số mũ
    struct Node* next; // Con trỏ tới đơn thức tiếp theo
} Node;

Node* TaoDonThuc(int he_so, int so_mu) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->he_so = he_so;
    newNode->so_mu = so_mu;
    newNode->next = NULL;
    return newNode;
}
void ChenDonThuc(Node** head, int he_so, int so_mu) {
    Node* newNode = TaoDonThuc(he_so, so_mu);
    if (*head == NULL || (*head)->so_mu < so_mu) {
        newNode->next = *head;
        *head = newNode;
        return;
    }
    Node* current = *head;
    while (current->next != NULL && current->next->so_mu > so_mu) {
        current = current->next;
    }
    if (current->so_mu == so_mu) {
        current->he_so += he_so;
        free(newNode);
        if (current->he_so == 0) { // Xóa nếu hệ số trở về 0
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

void InDaThuc(Node* head) {
    if (!head) {
        printf("0\n");
        return;
    }
    while (head != NULL) {
        printf("%d", head->he_so);
        if (head->so_mu != 0) {
            printf(".x^%d", head->so_mu);
        }
        if (head->next != NULL && head->next->he_so > 0) {
            printf(" + ");
        } else if (head->next != NULL) {
            printf(" ");
        }
        head = head->next;
    }
    printf("\n");
}

Node* CongDaThuc(Node* f, Node* g) {
    Node* result = NULL;
    while (f != NULL) {
        ChenDonThuc(&result, f->he_so, f->so_mu);
        f = f->next;
    }
    while (g != NULL) {
        ChenDonThuc(&result, g->he_so, g->so_mu);
        g = g->next;
    }
    return result;
}

void NhapDaThuc(Node** head) {
    int n, he_so, so_mu;
    printf("Nhap so luong don thuc: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Nhap he so va so mu (he_so so_mu): ");
        scanf("%d %d", &he_so, &so_mu);
        ChenDonThuc(head, he_so, so_mu);
    }
}

int main() {
    Node* f = NULL;
    Node* g = NULL;
    printf("Nhap da thuc f(x):\n");
    NhapDaThuc(&f);
    printf("Da thuc f(x) = ");
    InDaThuc(f);
    printf("Nhap da thuc g(x):\n");
    NhapDaThuc(&g);
    printf("Da thuc g(x) = ");
    InDaThuc(g);
    Node* h = CongDaThuc(f, g);
    printf("Tong h(x) = f(x) + g(x) = ");
    InDaThuc(h);
    return 0;
}
