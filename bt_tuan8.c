#include <stdio.h>
// 1. khai báo cấu trúc dữ lệu cho bài toán 
    typedef struct Ngay
    {
	    int ngay, thang, nam;
    } Ngay;
    typedef struct SinhVien
    {
        char maSV[8];
	    char hoTen[50];
	    int gioiTinh;
	    Ngay ngaySinh;
	    char diaChi[100];
	    char lop[12];
	    char khoa[7];

    } SinhVien;
    typedef struct Node {
        SinhVien data;
	    struct Node *link;

    } Node;
    typedef struct List {
        Node *first;
	    Node *last;
    } List;
// 2. Viết hàm thêm một sinh viên mới vào danh sách ListSV  đã sắp xếp và SV được sắp xếp theo đúng thứ tự ở DS mới vếit hàm thêm một sinh viên mới vào danh sách ListSV  đã sắp xếp và SV được sắp xếp theo đúng thứ tự ở DS mới
//hàm khởi tạo danh sách 
void khoiTaoDanhSach(List* list) {
    list->first = NULL;
    list->last = NULL;
}

// hàm nhập thông tin sinh viên 
 SinhVien NhapSV(){  
    SinhVien sv;
    printf("Nhap ma SV: ");
    scanf("%s", sv.maSV);
    printf("Nhap ho ten ");
    scanf(" %[^\n]", sv.hoTen);
    printf("Nhap gioi tinh (0: Nam, 1: Nu): "); 
    scanf("%d", &sv.gioiTinh);
    printf("Nhap ngay sinh (ngay thang nam): ");
    scanf("%d %d %d", &sv.ngaySinh.ngay, &sv.ngaySinh.thang, &sv.ngaySinh.nam);
    printf("Nhap dia chi: "); 
    scanf(" %[^\n]", sv.diaChi);
    printf("Nhap lop: "); 
    scanf("%s", sv.lop);
    printf("Nhap khoa: "); 
    scanf("%s", sv.khoa);
    return sv;
 }
 // Hàm thêm sinh viên vào danh sách và dữ nguyên thứ tự trong danh sách sinh viên 
 void themSV(List* list, SinhVien sv, Node nodes[], int *nodeIndex) {
    if (*nodeIndex >= 100) {  // Giả sử tối đa 100 sinh viên
        printf("Danh sach sinh vien da day.\n");
        return;
    }

    Node* newNode = &nodes[(*nodeIndex)++];
    newNode->data = sv;
    newNode->link = NULL;

    if (list->first == NULL || strcmp(sv.maSV, list->first->data.maSV) < 0) {
        newNode->link = list->first;
        list->first = newNode;
        if (list->last == NULL) {
            list->last = newNode;
        }
    } else {
        Node* curr = list->first;
        while (curr->link != NULL && strcmp(sv.maSV, curr->link->data.maSV) < 0) {
            curr = curr->link;
        }
        newNode->link = curr->link;
        curr->link = newNode;
        if (curr == list->last) {
            list->last = newNode;
        }
    }
}

// In danh sách sinh viên
void inDanhSach(List list) {
    Node* curr = list.first;
    while (curr != NULL) {
        SinhVien sv = curr->data;
        printf("\nMa SV: %s\nHo ten: %s\nGioi tinh: %s\nNgay sinh: %02d/%02d/%04d\n",
               sv.maSV, sv.hoTen, sv.gioiTinh ? "Nu" : "Nam",
               sv.ngaySinh.ngay, sv.ngaySinh.thang, sv.ngaySinh.nam);
        printf("Dia chi: %s\nLop: %s\nKhoa: %s\n", sv.diaChi, sv.lop, sv.khoa);
        curr = curr->link;
    }
}

// In các sinh viên có cùng ngày sinh

int main() {
    List list;
    khoiTaoDanhSach(&list);
    
    // Tạo một mảng nodes để lưu các phần tử mà không cần cấp phát động
    Node nodes[100]; // Giả sử tối đa 100 sinh viên
    int nodeIndex = 0;

    int n;
    printf("Nhap so luong sinh vien: ");
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        printf("Nhap thong tin sinh vien %d:\n", i + 1);
        SinhVien sv = NhapSV();
        themSV(&list, sv, nodes, &nodeIndex);
    }

    printf("\nDanh sach sinh vien da sap xep theo ma SV:\n");
    inDanhSach(list);
    return 0;
}