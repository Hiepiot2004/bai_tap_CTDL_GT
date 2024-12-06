#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char type[20];    // Loại gỗ
    float size;       // Kích thước (cm)
    int age;          // Tuổi gỗ (năm)
} Wood;

// Định nghĩa node cho stack
typedef struct Node {
    Wood wood;
    struct Node* next;
} Node;

// Hàm tạo node mới
Node* createNode(Wood wood) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->wood = wood;
    newNode->next = NULL;
    return newNode;
}

// Hàm thêm gỗ vào stack
void push(Node** top, Wood wood) {
    Node* newNode = createNode(wood);
    newNode->next = *top;
    *top = newNode;
}

// Hàm loại bỏ gỗ từ stack
Wood pop(Node** top) {
    if (*top == NULL) {
        printf("Stack is empty.\n");
        exit(1);
    }
    Node* temp = *top;
    Wood wood = temp->wood;
    *top = (*top)->next;
    free(temp);
    return wood;
}

// Hàm kiểm tra stack rỗng
int isEmpty(Node* top) {
    return top == NULL;
}

// Hàm đếm số lượng thanh gỗ có cùng tuổi
int countWoodByAge(Node* top, int age) {
    int count = 0;
    Node* current = top;
    while (current != NULL) {
        if (current->wood.age == age) {
            count++;
        }
        current = current->next;
    }
    return count;
}

// Hàm hiển thị thông tin kho gỗ
void displayStack(Node* top) {
    Node* current = top;
    while (current != NULL) {
        printf("Loai go: %s, kich thuoc: %.2f cm, Tuoi go: %d nam\n", current->wood.type, current->wood.size, current->wood.age);
        current = current->next;
    }
}

//kiểm tra rỗng 



int main() {
    Node* woodStack = NULL;  // Stack quản lý kho gỗ

    // Thêm một số thanh gỗ vào kho
    Wood wood1 = {"Go Nhan", 15.5, 10};
    Wood wood2 = {"Go Thong", 12.0, 8};
    Wood wood3 = {"Go Soi", 10.5, 10};
    Wood wood4 = {"Go Do", 20.0, 5};

    push(&woodStack, wood1);
    push(&woodStack, wood2);
    push(&woodStack, wood3);
    push(&woodStack, wood4);

    printf("Danh sach go trong kho (sap xep theo kieu stack):\n");
    displayStack(woodStack);

    int ageToCount = 10;
    int count = countWoodByAge(woodStack, ageToCount);
    printf("\nSo luong thanh go co tuoi %d nam: %d\n", ageToCount, count);

    return 0;
}
