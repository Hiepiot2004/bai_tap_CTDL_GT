#include <stdio.h>
#include <string.h>

#define MAX 10  // Số lượng tối đa của ngăn xếp

// Định nghĩa kiểu dữ liệu cho mỗi loại gỗ
typedef struct {
    char loai_go[20];
    char kich_thuoc[10];
    char tuoi[10];
} Go;

// Khai báo ngăn xếp
Go kho_go[MAX];
int top = -1;  // Biến lưu trữ chỉ số của phần tử trên đỉnh ngăn xếp

// Hàm thêm một khối gỗ vào ngăn xếp
void push(Go go) {
    if (top < MAX - 1) {
        top++;
        kho_go[top] = go;
    } else {
        printf("Ngăn xếp đã đầy!\n");
    }
}

// Hàm in danh sách các loại gỗ trong ngăn xếp
void print_stack() {
    for (int i = top; i >= 0; i--) {
        printf("%d: Loại gỗ: %s, Kích thước: %s, Tuổi: %s\n", i+1, kho_go[i].loai_go, kho_go[i].kich_thuoc, kho_go[i].tuoi);
    }
}

int main() {
    // Khởi tạo các loại gỗ trong kho
    Go go1 = {"Gụ", "10cm", "10 năm"};
    Go go2 = {"Lim", "20cm", "20 năm"};
    Go go3 = {"Sến", "30cm", "10 năm"};
    Go go4 = {"Sồi", "15cm", "35 năm"};
    
    // Đưa các loại gỗ vào ngăn xếp theo thứ tự 4, 3, 2, 1
    push(go4);
    push(go3);
    push(go2);
    push(go1);
    
    // Thêm khối gỗ mới vào đáy ngăn xếp
    Go go_moi = {"Óc chó", "10cm", "5 năm"};
    
    // Tạo một ngăn xếp mới để chèn go_moi vào đáy ngăn xếp
    Go kho_go_moi[MAX];
    int new_top = -1;

    // Thêm khối gỗ "óc chó" vào ngăn xếp mới trước
    kho_go_moi[++new_top] = go_moi;

    // Thêm các loại gỗ cũ vào ngăn xếp mới
    for (int i = 0; i <= top; i++) {
        kho_go_moi[++new_top] = kho_go[i];
    }

    // In ra Kho go moi
    printf("Kho go moi:\n");
    for (int i = new_top; i >= 0; i--) {
        printf("%d: Loại gỗ: %s, Kích thước: %s, Tuổi: %s\n", i+1, kho_go_moi[i].loai_go, kho_go_moi[i].kich_thuoc, kho_go_moi[i].tuoi);
    }
    
    return 0;
}
