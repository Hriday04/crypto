#include <stdio.h>
#include "list_t.h"

int main() {
    list_t lst = list_new();
    int i;
    for (i = 0; i < 10; i++) {
        list_add(&lst, (void *)(long)i);
    }

    size_t len = list_len(lst);
    size_t j;
    for (j = 0; j < len; j++) {
        printf("Element %lu: %ld\n", (unsigned long)j, (long)list_get(lst, j));
    }

    list_free(lst);
    return 0;
}
