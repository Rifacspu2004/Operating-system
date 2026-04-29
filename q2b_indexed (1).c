#include <stdio.h>

#define MAX_BLOCKS 50

int disk[MAX_BLOCKS];

int main() {
    int index_block, n, blocks[MAX_BLOCKS], i;

    for (i = 0; i < MAX_BLOCKS; i++) disk[i] = 0;

    printf("===== INDEXED FILE ALLOCATION =====\n");
    printf("Enter index block number: ");
    scanf("%d", &index_block);
    disk[index_block] = 1;

    printf("Enter number of data blocks: ");
    scanf("%d", &n);

    printf("Enter %d data block numbers:\n", n);
    for (i = 0; i < n; i++) {
        printf("Block[%d]: ", i);
        scanf("%d", &blocks[i]);
        disk[blocks[i]] = 1;
    }

    printf("\nIndex Block: %d\n", index_block);
    printf("\nIndex Table:\n");
    printf("Index\tData Block\n");
    printf("------------------\n");
    for (i = 0; i < n; i++)
        printf("%d\t%d\n", i, blocks[i]);

    printf("\nDisk Status (F=Free, X=Occupied):\n");
    for (i = 0; i < MAX_BLOCKS; i++) {
        printf("[%2d:%s] ", i, disk[i] ? "X" : "F");
        if ((i + 1) % 10 == 0) printf("\n");
    }
    printf("\n");

    return 0;
}
