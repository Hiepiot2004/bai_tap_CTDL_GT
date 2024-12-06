#include <stdio.h>

// Dinh nghia mot nut trong cay
typedef struct Node {
    char data;               // Toan tu hoac toan hang
    struct Node* left;       // Con trai
    struct Node* right;      // Con phai
} Node;

// Ham tao mot nut moi
Node* createNode(char data) {
    static Node memoryPool[100]; // Bo nho tinh de luu tru cac nut
    static int currentIndex = 0;

    if (currentIndex >= 100) {
        printf("Het bo nho!\n");
        return NULL;
    }

    Node* newNode = &memoryPool[currentIndex++];
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Ham kiem tra xem ky tu co phai toan tu khong
int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Ham kiem tra ky tu co phai chu cai hoac chu so khong
int isAlnum(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

// Ham dung cay bieu thuc tu bieu thuc hau to
Node* buildExpressionTree(char* postfix) {
    Node* stack[100];
    int top = -1;

    for (int i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];

        // Bo qua khoang trang
        if (c == ' ' || c == '\t') {
            continue;
        }

        if (isOperator(c)) {
            // Tao nut voi toan tu
            Node* newNode = createNode(c);

            // Lay 2 toan hang tu ngan xep
            newNode->right = stack[top--];
            newNode->left = stack[top--];

            // Day nut moi vao ngan xep
            stack[++top] = newNode;
        } else if (isAlnum(c)) {
            // Tao nut voi toan hang va day vao ngan xep
            stack[++top] = createNode(c);
        }
    }

    // Phan tu cuoi cung trong ngan xep la goc cua cay
    return stack[top];
}

// Ham duyet cay theo thu tu trung to (infix)
void inorderTraversal(Node* root) {
    if (root != NULL) {
        if (isOperator(root->data)) printf("(");
        inorderTraversal(root->left);
        printf("%c", root->data);
        inorderTraversal(root->right);
        if (isOperator(root->data)) printf(")");
    }
}

int main() {
    char postfix[] = "ab+c*de/-"; // Bieu thuc hau to
    Node* root = buildExpressionTree(postfix);

    printf("Bieu thuc trung to: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}
