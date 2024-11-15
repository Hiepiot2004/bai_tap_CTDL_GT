#include <iostream>

struct FileNode {
    char fileName[50]; // Ten file toi da 50 ky tu
    double fileSize;    // Kich thuoc file tinh bang MB
    char creationTime[20]; // Thoi gian tao (dang chuoi "YYYY-MM-DD HH:MM")

    FileNode* next; // Con tro toi node tiep theo

    FileNode(const char* name, double size, const char* time) : fileSize(size), next(nullptr) {
        // Sao chep chuoi ten file
        int i = 0;
        while (name[i] != '\0' && i < 49) {
            fileName[i] = name[i];
            i++;
        }
        fileName[i] = '\0';

        // Sao chep chuoi thoi gian tao
        i = 0;
        while (time[i] != '\0' && i < 19) {
            creationTime[i] = time[i];
            i++;
        }
        creationTime[i] = '\0';
    }
};

class FileLinkedList {
private:
    FileNode* head;

public:
    FileLinkedList() : head(nullptr) {}

    // Ham so sanh hai chuoi thoi gian
    bool compareTime(const char* time1, const char* time2) {
        for (int i = 0; i < 19; ++i) {
            if (time1[i] < time2[i]) return true;
            if (time1[i] > time2[i]) return false;
        }
        return false;
    }

    // Ham them file vao danh sach theo thu tu thoi gian
    void addFile(const char* name, double size, const char* time) {
        FileNode* newFile = new FileNode(name, size, time);

        if (!head || compareTime(time, head->creationTime)) {
            newFile->next = head;
            head = newFile;
        } else {
            FileNode* current = head;
            while (current->next && !compareTime(time, current->next->creationTime)) {
                current = current->next;
            }
            newFile->next = current->next;
            current->next = newFile;
        }
    }

    // Ham tinh tong kich thuoc file trong thu muc
    double calculateTotalSize() {
        double totalSize = 0;
        FileNode* current = head;
        while (current) {
            totalSize += current->fileSize;
            current = current->next;
        }
        return totalSize;
    }

    // Ham xoa file co kich thuoc nho nhat
    void removeSmallestFile() {
        if (!head) return;

        FileNode* minFile = head;
        FileNode* minPrev = nullptr;
        FileNode* current = head;
        FileNode* prev = nullptr;

        while (current) {
            if (current->fileSize < minFile->fileSize) {
                minFile = current;
                minPrev = prev;
            }
            prev = current;
            current = current->next;
        }

        if (minPrev) {
            minPrev->next = minFile->next;
        } else {
            head = head->next;
        }
        delete minFile;
    }

    // Ham sao luu vao USB, loai bo cac file nho nhat neu can
    void backupToUSB(double usbSize) {
        while (calculateTotalSize() > usbSize) {
            removeSmallestFile();
        }
    }

    // Ham hien thi danh sach cac file
    void displayFiles() {
        FileNode* current = head;
        while (current) {
            std::cout << "File: " << current->fileName
                      << ", Size: " << current->fileSize << " MB"
                      << ", Creation Time: " << current->creationTime << std::endl;
            current = current->next;
        }
    }
};

int main() {
    FileLinkedList folder;

    // Them cac file vao danh sach
    folder.addFile("File1.txt", 500, "2024-11-10 10:00");
    folder.addFile("File2.txt", 1000, "2024-11-12 12:30");
    folder.addFile("File3.txt", 200, "2024-11-11 15:45");

    std::cout << "Danh sach cac file trong thu muc:\n";
    folder.displayFiles();

    // Tinh tong kich thuoc file trong thu muc
    std::cout << "\nTong kich thuoc file trong thu muc: " << folder.calculateTotalSize() << " MB\n";

    // Sao luu cac file vao USB 32GB
    folder.backupToUSB(32 * 1024); // 32 GB = 32768 MB

    std::cout << "\nDanh sach cac file sau khi sao luu vao USB:\n";
    folder.displayFiles();

    return 0;
}
