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
	    Node *link;

    } Node;
    typedef struct List {
        Node *first;
	    Node *last;
    } List;
int main(){

}