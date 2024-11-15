#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 100

typedef struct WordNode {
    char word[MAX_WORD_LENGTH];
    int count;
    struct WordNode* next;
} WordNode;

typedef struct {
    WordNode* head;
} WordLinkedList;

void initWordLinkedList(WordLinkedList* list) {
    list->head = NULL;
}

WordNode* createWordNode(const char* w) {
    WordNode* newNode = (WordNode*)malloc(sizeof(WordNode));
    if (!newNode) {
        perror("Không thể cấp phát bộ nhớ cho node mới");
        exit(1);
    }
    strncpy(newNode->word, w, MAX_WORD_LENGTH - 1);
    newNode->word[MAX_WORD_LENGTH - 1] = '\0';
    newNode->count = 1;
    newNode->next = NULL;
    return newNode;
}

void addWord(WordLinkedList* list, const char* w) {
    WordNode* current = list->head;
    WordNode* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->word, w) == 0) {
            current->count++;
            return;
        }
        prev = current;
        current = current->next;
    }

    WordNode* newWord = createWordNode(w);
    if (!prev) {
        list->head = newWord;
    } else {
        prev->next = newWord;
    }
}

char* findMostFrequentWord(WordLinkedList* list) {
    int maxCount = 0;
    WordNode* mostFrequent = NULL;
    WordNode* current = list->head;

    while (current) {
        if (current->count > maxCount) {
            maxCount = current->count;
            mostFrequent = current;
        }
        current = current->next;
    }
    return mostFrequent ? mostFrequent->word : "";
}

void removeRepeatedWords(WordLinkedList* list) {
    WordNode* current = list->head;
    while (current && current->next) {
        if (strcmp(current->word, current->next->word) == 0) {
            WordNode* temp = current->next;
            current->next = current->next->next;
            free(temp);
        } else {
            current = current->next;
        }
    }
}

int countWords(WordLinkedList* list) {
    int totalCount = 0;
    WordNode* current = list->head;
    while (current) {
        totalCount += current->count;
        current = current->next;
    }
    return totalCount;
}

void displayWords(WordLinkedList* list) {
    WordNode* current = list->head;
    while (current) {
        printf("Tu: %s, So lan xuat hien: %d\n", current->word, current->count);
        current = current->next;
    }
}

void freeWordLinkedList(WordLinkedList* list) {
    WordNode* current = list->head;
    while (current) {
        WordNode* temp = current;
        current = current->next;
        free(temp);
    }
}

// Tách câu thành các từ dựa trên khoảng trắng và thêm vào danh sách liên kết
void splitIntoWords(const char* sentence, WordLinkedList* list) {
    char word[MAX_WORD_LENGTH];
    int index = 0;
    for (int i = 0; i <= strlen(sentence); i++) {
        if (sentence[i] == ' ' || sentence[i] == '\0') {
            if (index > 0) {
                word[index] = '\0';
                addWord(list, word);
                index = 0;
            }
        } else if (!isspace(sentence[i])) {
            word[index++] = sentence[i];
        }
    }
}

int main() {
    WordLinkedList sentence;
    initWordLinkedList(&sentence);

    // Nhập câu từ người dùng
    printf("Nhap cau tieng viet: ");
    char input[1000];
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    // Phân tách câu thành từ và thêm vào danh sách
    splitIntoWords(input, &sentence);

    // Hiển thị menu cho người dùng
    int choice;
    do {
        printf("\nChon mot chuc nang:\n");
        printf("1. Xac dinh cac tu xuat hien nhieu nhat\n");
        printf("2. Loai bo cac tu lay \n");
        printf("3. Dem so tu trong cau\n");
        printf("4. Hien thi danh sach tu va so lan xuat hien\n");
        printf("0. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);
        getchar();  // Xóa ký tự xuống dòng khỏi bộ đệm

        switch (choice) {
            case 1: {
                char* mostFrequent = findMostFrequentWord(&sentence);
                if (strlen(mostFrequent) > 0) {
                    printf("\nTu xuat hien nhieu nhat: %s\n", mostFrequent);
                } else {
                    printf("\nKhong co tu nao trong danh sach.\n");
                }
                break;
            }
            case 2: {
                removeRepeatedWords(&sentence);
                printf("\ndanh sach tu sau khi loai bo tu lay:\n");
                displayWords(&sentence);
                break;
            }
            case 3: {
                int totalWords = countWords(&sentence);
                printf("\nTong so tu trong cau: %d\n", totalWords);
                break;
            }
            case 4: {
                printf("\nDanh sach cac tu va so lan xuat hien:\n");
                displayWords(&sentence);
                break;
            }
            case 0: {
                printf("Thoat chuong trinh .\n");
                break;
            }
            default: {
                printf("Lua chon khong hop le.\n");
                break;
            }
        }
    } while (choice != 0);

    freeWordLinkedList(&sentence);
    return 0;
}
