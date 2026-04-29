#include <stdio.h>
#include <string.h>

#define MAX_FILES 20
#define NAME_LEN  30

typedef struct {
    char name[NAME_LEN];
    int  size;
} File;

File dir[MAX_FILES];
int count = 0;

void create() {
    if (count >= MAX_FILES) { printf("Directory full!\n"); return; }
    char name[NAME_LEN]; int size;
    printf("Enter file name: "); scanf("%s", name);
    for (int i = 0; i < count; i++)
        if (strcmp(dir[i].name, name) == 0) { printf("File already exists!\n"); return; }
    printf("Enter file size (bytes): "); scanf("%d", &size);
    strcpy(dir[count].name, name);
    dir[count].size = size;
    count++;
    printf("File '%s' created.\n", name);
}

void delete() {
    char name[NAME_LEN];
    printf("Enter file name to delete: "); scanf("%s", name);
    for (int i = 0; i < count; i++) {
        if (strcmp(dir[i].name, name) == 0) {
            for (int j = i; j < count - 1; j++) dir[j] = dir[j+1];
            count--;
            printf("File '%s' deleted.\n", name); return;
        }
    }
    printf("File not found!\n");
}

void search() {
    char name[NAME_LEN];
    printf("Enter file name to search: "); scanf("%s", name);
    for (int i = 0; i < count; i++)
        if (strcmp(dir[i].name, name) == 0) {
            printf("Found! Name: %s | Size: %d bytes\n", dir[i].name, dir[i].size); return;
        }
    printf("File not found!\n");
}

void display() {
    printf("\n===== SINGLE LEVEL DIRECTORY =====\n");
    if (count == 0) { printf("Directory is empty.\n"); return; }
    printf("%-5s %-20s %-10s\n", "No.", "File Name", "Size(bytes)");
    printf("------------------------------------\n");
    for (int i = 0; i < count; i++)
        printf("%-5d %-20s %-10d\n", i+1, dir[i].name, dir[i].size);
}

int main() {
    int ch;
    while (1) {
        printf("\n--- Single Level Directory ---\n");
        printf("1. Create File\n2. Delete File\n3. Search File\n4. Display\n5. Exit\n");
        printf("Choice: "); scanf("%d", &ch);
        switch(ch) {
            case 1: create();  break;
            case 2: delete();  break;
            case 3: search();  break;
            case 4: display(); break;
            case 5: return 0;
            default: printf("Invalid!\n");
        }
    }
}
