#include <stdio.h>
#include <string.h>

#define MAX_FILES 20
#define MAX_USERS 10
#define NAME_LEN  30

typedef struct {
    char name[NAME_LEN];
    int  size;
} File;

typedef struct {
    char username[NAME_LEN];
    File files[MAX_FILES];
    int  file_count;
} UserDir;

UserDir users[MAX_USERS];
int user_count = 0;

int find_user(char *uname) {
    for (int i = 0; i < user_count; i++)
        if (strcmp(users[i].username, uname) == 0) return i;
    return -1;
}

void create_user() {
    if (user_count >= MAX_USERS) { printf("Max users reached!\n"); return; }
    char uname[NAME_LEN];
    printf("Enter username: "); scanf("%s", uname);
    if (find_user(uname) != -1) { printf("User already exists!\n"); return; }
    strcpy(users[user_count].username, uname);
    users[user_count].file_count = 0;
    user_count++;
    printf("User '%s' created.\n", uname);
}

void create_file() {
    char uname[NAME_LEN], fname[NAME_LEN]; int size;
    printf("Enter username: "); scanf("%s", uname);
    int u = find_user(uname);
    if (u == -1) { printf("User not found!\n"); return; }
    printf("Enter file name: "); scanf("%s", fname);
    for (int i = 0; i < users[u].file_count; i++)
        if (strcmp(users[u].files[i].name, fname) == 0) { printf("File exists!\n"); return; }
    printf("Enter size: "); scanf("%d", &size);
    strcpy(users[u].files[users[u].file_count].name, fname);
    users[u].files[users[u].file_count].size = size;
    users[u].file_count++;
    printf("File '%s' created for user '%s'.\n", fname, uname);
}

void delete_file() {
    char uname[NAME_LEN], fname[NAME_LEN];
    printf("Enter username: "); scanf("%s", uname);
    int u = find_user(uname);
    if (u == -1) { printf("User not found!\n"); return; }
    printf("Enter file name: "); scanf("%s", fname);
    for (int i = 0; i < users[u].file_count; i++)
        if (strcmp(users[u].files[i].name, fname) == 0) {
            for (int j = i; j < users[u].file_count - 1; j++)
                users[u].files[j] = users[u].files[j+1];
            users[u].file_count--;
            printf("File deleted.\n"); return;
        }
    printf("File not found!\n");
}

void search_file() {
    char uname[NAME_LEN], fname[NAME_LEN];
    printf("Enter username: "); scanf("%s", uname);
    int u = find_user(uname);
    if (u == -1) { printf("User not found!\n"); return; }
    printf("Enter file name: "); scanf("%s", fname);
    for (int i = 0; i < users[u].file_count; i++)
        if (strcmp(users[u].files[i].name, fname) == 0) {
            printf("Found! %s/%s | Size: %d bytes\n", uname, fname, users[u].files[i].size);
            return;
        }
    printf("File not found!\n");
}

void display() {
    printf("\n===== TWO LEVEL DIRECTORY =====\n");
    if (user_count == 0) { printf("No users.\n"); return; }
    for (int i = 0; i < user_count; i++) {
        printf("\n/%s\n", users[i].username);
        printf("  %-20s %-10s\n", "File Name", "Size");
        printf("  ----------------------------\n");
        if (users[i].file_count == 0) { printf("  (empty)\n"); continue; }
        for (int j = 0; j < users[i].file_count; j++)
            printf("  %-20s %-10d\n", users[i].files[j].name, users[i].files[j].size);
    }
}

int main() {
    int ch;
    while (1) {
        printf("\n--- Two Level Directory ---\n");
        printf("1. Create User\n2. Create File\n3. Delete File\n4. Search File\n5. Display\n6. Exit\n");
        printf("Choice: "); scanf("%d", &ch);
        switch(ch) {
            case 1: create_user(); break;
            case 2: create_file(); break;
            case 3: delete_file(); break;
            case 4: search_file(); break;
            case 5: display();     break;
            case 6: return 0;
            default: printf("Invalid!\n");
        }
    }
}
