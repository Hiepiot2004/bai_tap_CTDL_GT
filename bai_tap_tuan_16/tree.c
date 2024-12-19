#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char title[100];
    int pages;
    struct Node *firstChild;
    struct Node *nextSibling;
} Node;

void copyString(char *dest, const char *src) {
    while (*src) {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

int compareString(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

Node *createNode(const char *title, int pages) {
    Node *node = (Node *)malloc(sizeof(Node));
    copyString(node->title, title);
    node->pages = pages;
    node->firstChild = NULL;
    node->nextSibling = NULL;
    return node;
}

void addChild(Node *parent, Node *child) {
    if (!parent->firstChild) {
        parent->firstChild = child;
    } else {
        Node *sibling = parent->firstChild;
        while (sibling->nextSibling) {
            sibling = sibling->nextSibling;
        }
        sibling->nextSibling = child;
    }
}

int countChapters(Node *root) {
    if (!root) return 0;
    int count = 0;
    Node *current = root->firstChild;
    while (current) {
        count++;
        current = current->nextSibling;
    }
    return count;
}

Node *findLongestChapter(Node *root) {
    if (!root) return NULL;
    Node *longest = NULL;
    int maxPages = 0;
    Node *current = root->firstChild;
    while (current) {
        if (current->pages > maxPages) {
            maxPages = current->pages;
            longest = current;
        }
        current = current->nextSibling;
    }
    return longest;
}

int deleteNode(Node *parent, const char *title) {
    if (!parent || !parent->firstChild) return 0;

    Node *current = parent->firstChild;
    Node *prev = NULL;
    
    while (current) {
        if (compareString(current->title, title) == 0) {
            if (prev) {
                prev->nextSibling = current->nextSibling;
            } else {
                parent->firstChild = current->nextSibling;
            }

            parent->pages -= current->pages;

            Node *child = current->firstChild;
            while (child) {
                Node *temp = child;
                child = child->nextSibling;
                deleteNode(current, temp->title);
            }

            free(current);
            return 1;
        }

        prev = current;
        current = current->nextSibling;
    }

    current = parent->firstChild;
    while (current) {
        if (deleteNode(current, title)) {
            return 1;
        }
        current = current->nextSibling;
    }

    return 0;
}

void printTree(Node *root, int level) {
    if (!root) return;

    for (int i = 0; i < level; i++) printf("  ");
    printf("%s (%d pages)\n", root->title, root->pages);

    Node *child = root->firstChild;
    while (child) {
        printTree(child, level + 1);
        child = child->nextSibling;
    }
}

int main() {
    Node *book = createNode("Book", 0);

    Node *chapter1 = createNode("Chapter 1", 50);
    Node *chapter2 = createNode("Chapter 2", 30);
    Node *chapter3 = createNode("Chapter 3", 70);

    addChild(book, chapter1);
    addChild(book, chapter2);
    addChild(book, chapter3);

    Node *section1 = createNode("Section 1.1", 20);
    Node *section2 = createNode("Section 1.2", 30);
    addChild(chapter1, section1);
    addChild(chapter1, section2);

    printf("Tree structure:\n");
    printTree(book, 0);

    printf("\nNumber of chapters: %d\n", countChapters(book));

    Node *longest = findLongestChapter(book);
    if (longest) {
        printf("Longest chapter: %s (%d pages)\n", longest->title, longest->pages);
    }

    printf("\nDeleting 'Section 1.2'...\n");
    deleteNode(book, "Section 1.2");

    printf("\nTree structure after deletion:\n");
    printTree(book, 0);

    return 0;
}
