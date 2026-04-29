#include <stdio.h>
#include <math.h>

int main() {
    int page_size, logical_addr, num_pages, num_frames;
    int page_table[100];
    int i;

    printf("===== PAGING TECHNIQUE OF MEMORY MANAGEMENT =====\n");
    printf("Enter page size (in bytes): ");
    scanf("%d", &page_size);

    printf("Enter number of pages: ");
    scanf("%d", &num_pages);

    printf("Enter number of frames: ");
    scanf("%d", &num_frames);

    if (num_pages > num_frames) {
        printf("Warning: More pages than frames! Some pages won't be loaded.\n");
    }

    // Build Page Table
    printf("\nEnter frame number for each page (-1 if not in memory):\n");
    for (i = 0; i < num_pages; i++) {
        printf("Page %d -> Frame: ", i);
        scanf("%d", &page_table[i]);
    }

    // Display Page Table
    printf("\n---------- PAGE TABLE ----------\n");
    printf("Page No.\tFrame No.\tStatus\n");
    for (i = 0; i < num_pages; i++) {
        if (page_table[i] == -1)
            printf("%d\t\t-\t\tNot in Memory\n", i);
        else
            printf("%d\t\t%d\t\tIn Memory\n", i, page_table[i]);
    }

    // Address Translation
    printf("\n---------- ADDRESS TRANSLATION ----------\n");
    printf("Enter number of logical addresses to translate: ");
    int n;
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nEnter logical address %d: ", i + 1);
        scanf("%d", &logical_addr);

        int page_no  = logical_addr / page_size;
        int offset   = logical_addr % page_size;

        printf("Logical Address  : %d\n", logical_addr);
        printf("Page Number      : %d\n", page_no);
        printf("Offset           : %d\n", offset);

        if (page_no >= num_pages) {
            printf("Result           : ERROR - Page number out of range!\n");
        } else if (page_table[page_no] == -1) {
            printf("Result           : PAGE FAULT! Page not in memory.\n");
        } else {
            int physical_addr = page_table[page_no] * page_size + offset;
            printf("Frame Number     : %d\n", page_table[page_no]);
            printf("Physical Address : %d\n", physical_addr);
        }
        printf("----------------------------------------\n");
    }

    // Memory Layout
    printf("\n---------- MEMORY LAYOUT ----------\n");
    printf("Frame No.\tContents\n");
    for (i = 0; i < num_frames; i++) {
        int found = 0;
        for (int j = 0; j < num_pages; j++) {
            if (page_table[j] == i) {
                printf("%d\t\tPage %d\n", i, j);
                found = 1;
                break;
            }
        }
        if (!found) printf("%d\t\tFree\n", i);
    }

    return 0;
}
