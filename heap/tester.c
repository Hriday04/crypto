#include <stdio.h>
#include <stdlib.h>
#include "heap_t.h"

bool gt_int(void *a, void *b) {
    return *(int *)a > *(int *)b;
}

int main() {
    heap_t h = heap(sizeof(int), gt_int);
    int i, vals[] = {100, 200, 50, 400, 300};

    for (i = 0; i < 5; i++) {
        insert(&h, &vals[i]);
    }

    for (i = 0; i < 5; i++) {
        int *max = (int *)maxpop(&h);
        if (max) {
            printf("Max: %d\n", *max);
            free(max);
        }
    }

    free(h.eles);
    return 0;
}
