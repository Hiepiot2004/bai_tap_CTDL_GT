#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Dinh nghia cau truc san pham
typedef struct Product {
    char name[50];
    int quantity;
    float price; // Gia cua mot san pham
    struct Product* next;
} Product;

// Dinh nghia cau truc gio hang (node trong hang doi)
typedef struct Cart {
    int cart_id; // Ma gio hang
    Product* products; // Danh sach san pham trong gio
    struct Cart* next;
} Cart;

// Dinh nghia cau truc hang doi
typedef struct Queue {
    Cart* front; // Phan dau hang doi
    Cart* rear;  // Phan cuoi hang doi
} Queue;

// Khoi tao hang doi
void initQueue(Queue* q) {
    q->front = q->rear = NULL;
}

// Them mot gio hang vao hang doi (enqueue)
void enqueue(Queue* q, Cart* newCart) {
    if (q->rear == NULL) { // Neu hang doi trong
        q->front = q->rear = newCart;
    } else {
        q->rear->next = newCart;
        q->rear = newCart;
    }
    newCart->next = NULL; // Dam bao gio hang moi khong tro den phan tu khac
}

// Loai bo mot gio hang khoi hang doi (dequeue)
void dequeue(Queue* q) {
    if (q->front == NULL) {
        printf("Hang doi trong.\n");
        return;
    }
    Cart* temp = q->front;
    q->front = q->front->next;

    // Giai phong bo nho cac san pham trong gio hang
    Product* p = temp->products;
    while (p != NULL) {
        Product* del = p;
        p = p->next;
        free(del);
    }

    free(temp);
    printf("Mot khach hang da thanh toan xong va roi khoi hang doi.\n");

    if (q->front == NULL) // Neu hang doi trong, cap nhat rear
        q->rear = NULL;
}

// Tinh tong so tien thu duoc tai quay
float calculateTotalRevenue(Queue* q) {
    float total = 0.0;
    Cart* current = q->front;
    while (current != NULL) {
        Product* p = current->products;
        while (p != NULL) {
            total += p->quantity * p->price;
            p = p->next;
        }
        current = current->next;
    }
    return total;
}

// Xac dinh so luong mot san pham da ban
int countProductA(Queue* q, const char* productName) {
    int count = 0;
    Cart* current = q->front;
    while (current != NULL) {
        Product* p = current->products;
        while (p != NULL) {
            if (strcmp(p->name, productName) == 0) {
                count += p->quantity;
            }
            p = p->next;
        }
        current = current->next;
    }
    return count;
}

// Tao san pham moi
Product* createProduct(const char* name, int quantity, float price) {
    Product* newProduct = (Product*)malloc(sizeof(Product));
    strcpy(newProduct->name, name);
    newProduct->quantity = quantity;
    newProduct->price = price;
    newProduct->next = NULL;
    return newProduct;
}

// Tao gio hang moi
Cart* createCart(int cart_id, Product* products) {
    Cart* newCart = (Cart*)malloc(sizeof(Cart));
    newCart->cart_id = cart_id;
    newCart->products = products;
    newCart->next = NULL;
    return newCart;
}

// Chuong trinh chinh
int main() {
    Queue q;
    initQueue(&q);

    // Them khach hang vao hang doi
    Product* products1 = createProduct("San pham A", 2, 10000);
    products1->next = createProduct("San pham B", 1, 20000);
    enqueue(&q, createCart(1, products1));

    Product* products2 = createProduct("San pham A", 3, 15000);
    enqueue(&q, createCart(2, products2));

    // Loai bo khach hang ra khoi hang doi
    dequeue(&q);

    // Tinh tong so tien thu duoc
    float total = calculateTotalRevenue(&q);
    printf("Tong so tien thu duoc: %.2f\n", total);

    // Xac dinh so luong 'San pham A' da ban
    int productCount = countProductA(&q, "San pham A");
    printf("So luong 'San pham A' da ban: %d\n", productCount);

    return 0;
}
