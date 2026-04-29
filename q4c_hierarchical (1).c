#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CHILDREN 10
#define NAME_LEN     30

typedef struct Node {
    char name[NAME_LEN];
    int  is_dir;
    int  size;
    struct Node *children[MAX_CHILDREN];
    int  child_count;
} Node;

Node *root = NULL;

Node *new_node(char *name, int is_dir, int size) {
    Node *n = (Node *)malloc(sizeof(Node));
    strcpy(n->name, name);
    n->is_dir = is_dir;
    n->size = size;
    n->child_count = 0;
    return n;
}

Node *find_node(Node *cur, char *name) {
    if (!cur) return NULL;
    if (strcmp(cur->name, name) == 0) return cur;
    for (int i = 0; i < cur->child_count; i++) {
        Node *f = find_node(cur->children[i], name);
        if (f) return f;
    }
    return NULL;
}

void add_entry() {
    char name[NAME_LEN]; int size = 0, type;
    if (!root) {
        printf("Enter root directory name: "); scanf("%s", name);
        root = new_node(name, 1, 0);
        printf("Root '%s' created.\n", name); return;
    }
    char parent[NAME_LEN];
    printf("Enter parent directory name: "); scanf("%s", parent);
    Node *p = find_node(root, parent);
    if (!p || !p->is_dir) { printf("Parent directory not found!\n"); return; }
    if (p->child_count >= MAX_CHILDREN) { printf("Directory full!\n"); return; }
    printf("Add (1)Directory or (2)File: "); scanf("%d", &type);
    printf("Enter name: "); scanf("%s", name);
    if (type == 2) { printf("Enter size: "); scanf("%d", &size); }
    p->children[p->child_count++] = new_node(name, type == 1, size);
    printf("%s '%s' added under '%s'.\n", type==1?"Directory":"File", name, parent);
}

void delete_node(Node *parent, char *name) {
    for (int i = 0; i < parent->child_count; i++) {
        if (strcmp(parent->children[i]->name, name) == 0) {
            free(parent->children[i]);
            for (int j = i; j < parent->child_count - 1; j++)
                parent->children[j] = parent->children[j+1];
            parent->child_count--;
            printf("Deleted '%s'.\n", name); return;
        }
        if (parent->children[i]->is_dir)
            delete_node(parent->children[i], name);
    }
}

void delete_entry() {
    if (!root) { printf("Empty!\n"); return; }
    char name[NAME_LEN];
    printf("Enter name to delete: "); scanf("%s", name);
    if (strcmp(root->name, name) == 0) { printf("Cannot delete root!\n"); return; }
    delete_node(root, name);
}

void search_entry() {
    if (!root) { printf("Empty!\n"); return; }
    char name[NAME_LEN];
    printf("Enter name to search: "); scanf("%s", name);
    Node *f = find_node(root, name);
    if (f)
        printf("Found! Name: %s | Type: %s | Size: %d bytes\n",
               f->name, f->is_dir ? "Directory" : "File", f->size);
    else
        printf("'%s' not found!\n", name);
}

void print_tree(Node *node, int level) {
    for (int i = 0; i < level; i++) printf(i == level-1 ? "|-- " : "|   ");
    if (node->is_dir)
        printf("[DIR]  %s/\n", node->name);
    else
        printf("[FILE] %s (%d bytes)\n", node->name, node->size);
    for (int i = 0; i < node->child_count; i++)
        print_tree(node->children[i], level + 1);
}

void display() {
    printf("\n===== HIERARCHICAL DIRECTORY =====\n");
    if (!root) { printf("No directory created.\n"); return; }
    print_tree(root, 0);
}

int main() {
    int ch;
    while (1) {
        printf("\n--- Hierarchical Directory ---\n");
        printf("1. Create Root / Add Entry\n2. Delete Entry\n3. Search Entry\n4. Display Tree\n5. Exit\n");
        printf("Choice: "); scanf("%d", &ch);
        switch(ch) {
            case 1: add_entry();    break;
            case 2: delete_entry(); break;
            case 3: search_entry(); break;
            case 4: display();      break;
            case 5: return 0;
            default: printf("Invalid!\n");
        }
    }
}
