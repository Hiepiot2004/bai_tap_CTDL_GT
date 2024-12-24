#include <stdio.h>
#include <stdlib.h>

// Khai bao cau truc node cho cay AVL
typedef struct AVLNode {
    int data;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
} AVLNode;

// Ham lay chieu cao cua mot node
int height(AVLNode *node) {
    return node ? node->height : 0;
};
// Ham tinh gia tri lon hon giua hai so nguyen
int maximum(int a, int b) {
    return (a > b) ? a : b;
}

// Tao mot node moi
AVLNode *createNode(int data) {
    AVLNode *node = (AVLNode *)malloc(sizeof(AVLNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // Ban dau node moi co chieu cao la 1
    return node;
}

// Xoay phai
AVLNode *rotateRight(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T = x->right;

    x->right = y;
    y->left = T;

    y->height = maximum(height(y->left), height(y->right)) + 1;
    x->height = maximum(height(x->left), height(x->right)) + 1;

    return x;
}

// Xoay trai
AVLNode *rotateLeft(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T = y->left;

    y->left = x;
    x->right = T;

    x->height = maximum(height(x->left), height(x->right)) + 1;
    y->height = maximum(height(y->left), height(y->right)) + 1;

    return y;
}

// Lay he so can bang cua mot node
int getBalance(AVLNode *node) {
    return node ? height(node->left) - height(node->right) : 0;
}

// Ham them mot phan tu vao cay AVL
AVLNode *insertNode(AVLNode *node, int data) {
    // Buoc 1: Thuc hien chen thong thuong cua cay nhi phan tim kiem
    if (!node) return createNode(data);

    if (data < node->data) {
        node->left = insertNode(node->left, data);
    } else if (data > node->data) {
        node->right = insertNode(node->right, data);
    } else {
        return node; // Khong cho phep cac phan tu trung lap
    }

    // Buoc 2: Cap nhat chieu cao cua node hien tai
    node->height = 1 + maximum(height(node->left), height(node->right));

    // Buoc 3: Tinh he so can bang de kiem tra xem node co bi mat can bang khong
    int balance = getBalance(node);

    // Truong hop mat can bang va thuc hien cac phep xoay

    // Left Left
    if (balance > 1 && data < node->left->data)
        return rotateRight(node);

    // Right Right
    if (balance < -1 && data > node->right->data)
        return rotateLeft(node);

    // Left Right
    if (balance > 1 && data > node->left->data) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Left
    if (balance < -1 && data < node->right->data) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Ham duyet cay theo thu tu giua (In-order)
void inOrder(AVLNode *root) {
    if (root) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

// Ham chinh
int main() {
    AVLNode *root = NULL;
    int arr[] = {10, 20, 30, 40, 50, 25}; // Mang dau vao
    int n = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < n; i++) {
        root = insertNode(root, arr[i]);
        printf("Cay AVL sau khi them %d:\n", arr[i]);
        inOrder(root);
        printf("\n");
    }

    printf("Cay AVL cuoi cung (duyet in-order):\n");
    inOrder(root);

    return 0;
}
