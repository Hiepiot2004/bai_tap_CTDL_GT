#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

typedef struct {
    char filename[256];
    long size;
} FileInfo;

// Hàm so sánh để sắp xếp theo dung lượng
int compare(const void *a, const void *b) {
    FileInfo *fileA = (FileInfo *)a;
    FileInfo *fileB = (FileInfo *)b;
    return (fileA->size - fileB->size);
}

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;
    FileInfo files[1000];
    int count = 0;

    // Mở thư mục hiện tại
    dir = opendir(".");
    if (dir == NULL) {
        perror("Unable to open directory");
        return 1;
    }

    // Đọc tất cả các file trong thư mục
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {  // Kiểm tra nếu là file thường
            // Lấy thông tin file
            stat(entry->d_name, &fileStat);
            strcpy(files[count].filename, entry->d_name);
            files[count].size = fileStat.st_size;
            count++;
        }
    }
    closedir(dir);

    // Sắp xếp các file theo dung lượng
    qsort(files, count, sizeof(FileInfo), compare);

    // In danh sách các file đã sắp xếp
    for (int i = 0; i < count; i++) {
        printf("%s - %ld bytes\n", files[i].filename, files[i].size);
    }

    return 0;
}
