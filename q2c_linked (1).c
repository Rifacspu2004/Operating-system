#include <stdio.h>

#define MAX_BLOCKS 50

int disk[MAX_BLOCKS];
int next[MAX_BLOCKS];

int main() {
    int start, n, i, current;

    for (i = 0; i < MAX_BLOCKS; i++) { disk[i] = 0; next[i] = -1; }

    printf("===== LINKED FILE ALLOCATION =====\n");
    printf("Enter starting block: ");
    scanf("%d", &start);
    printf("Enter total number of blocks: ");
    scanf("%d", &n);

    int blocks[n];
    blocks[0] = start;
    disk[start] = 1;

    printf("Enter remaining %d block numbers:\n", n - 1);
    for (i = 1; i < n; i++) {
        printf("Block[%d]: ", i);
        scanf("%d", &blocks[i]);
        disk[blocks[i]] = 1;
    }

    // Link all blocks
    for (i = 0; i < n - 1; i++) next[blocks[i]] = blocks[i + 1];
    next[blocks[n - 1]] = -1;

    printf("\nLinked File Structure:\n");
    printf("Block\tNext\n");
    printf("------------\n");
    current = start;
    while (current != -1) {
        if (next[current] == -1)
            printf("%d\tNULL\n", current);
        else
            printf("%d\t%d\n", current, next[current]);
        current = next[current];
    }

    printf("\nChain: ");
    current = start;
    while (current != -1) {
        printf("%d", current);
        if (next[current] != -1) printf(" -> ");
        current = next[current];
    }
    printf(" -> NULL\n");

    printf("\nDisk Status (F=Free, X=Occupied):\n");
    for (i = 0; i < MAX_BLOCKS; i++) {
        printf("[%2d:%s] ", i, disk[i] ? "X" : "F");
        if ((i + 1) % 10 == 0) printf("\n");
    }
    printf("\n");

    return 0;
}
