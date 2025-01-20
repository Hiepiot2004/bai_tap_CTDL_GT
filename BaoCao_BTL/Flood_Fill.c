#include <stdio.h>
#include <stdlib.h>

// Định nghĩa cấu trúc của một điểm trong ma trận
typedef struct {
    int x, y;
} Point;

// Hàng đợi
typedef struct {
    Point* data;
    int front, rear, size, capacity;
} Queue;

// Khởi tạo hàng đợi
Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->data = (Point*)malloc(queue->capacity * sizeof(Point));
    return queue;
}

// Kiểm tra hàng đợi rỗng
int isEmpty(Queue* queue) {
    return (queue->size == 0);
}

// Thêm phần tử vào hàng đợi
void enqueue(Queue* queue, int x, int y) {
    if (queue->size == queue->capacity) return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->data[queue->rear].x = x;
    queue->data[queue->rear].y = y;
    queue->size++;
}

// Lấy phần tử ra khỏi hàng đợi
Point dequeue(Queue* queue) {
    Point item = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return item;
}

// Thuật toán Flood Fill
void floodFill(int matrix[][3], int rows, int cols, int x, int y, int newColor) {
    int oldColor = matrix[x][y];
    if (oldColor == newColor) return;

    // Tạo hàng đợi
    Queue* queue = createQueue(rows * cols);
    enqueue(queue, x, y);

    // Duyệt các điểm
    while (!isEmpty(queue)) {
        Point p = dequeue(queue);
        int cx = p.x, cy = p.y;

        // Đổi màu pixel hiện tại
        matrix[cx][cy] = newColor;

        // Duyệt các pixel lân cận
        int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        for (int i = 0; i < 4; i++) {
            int nx = cx + directions[i][0];
            int ny = cy + directions[i][1];

            // Kiểm tra trong giới hạn và có cùng màu cũ
            if (nx >= 0 && ny >= 0 && nx < rows && ny < cols && matrix[nx][ny] == oldColor) {
                enqueue(queue, nx, ny);
            }
        }
    }

    // Giải phóng bộ nhớ hàng đợi
    free(queue->data);
    free(queue);
}

// Hàm in ma trận
void printMatrix(int matrix[][3], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int matrix[3][3] = {
        {1, 1, 0},
        {1, 0, 0},
        {0, 0, 1}
    };

    int rows = 3, cols = 3;
    int startX = 0, startY = 0, newColor = 2;

    printf("Matrix before flood fill:\n");
    printMatrix(matrix, rows, cols);

    floodFill(matrix, rows, cols, startX, startY, newColor);

    printf("\nMatrix after flood fill:\n");
    printMatrix(matrix, rows, cols);

    return 0;
}
