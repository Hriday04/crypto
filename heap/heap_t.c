#include "heap_t.h"
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 4

static void swap_elements(heap_t *heap, size_t a, size_t b) {
    void *temp = malloc(heap->ele_size);
    void *pa = (char *)heap->eles + a * heap->ele_size;
    void *pb = (char *)heap->eles + b * heap->ele_size;
    memcpy(temp, pa, heap->ele_size);
    memcpy(pa, pb, heap->ele_size);
    memcpy(pb, temp, heap->ele_size);
    free(temp);
}

heap_t heap(size_t ele_size, bool (*gt)(void *, void *)) {
    heap_t h;
    h.ele_size = ele_size;
    h.num_eles = 0;
    h.capacity = INITIAL_CAPACITY;
    h.gt = gt;
    h.eles = malloc(INITIAL_CAPACITY * ele_size);
    return h;
}

void insert(heap_t *heap, void *ele_ptr) {
    size_t i, parent;
    void *dest;

    if (heap->num_eles == heap->capacity) {
        size_t new_capacity = heap->capacity * 2;
        void *new_eles = realloc(heap->eles, new_capacity * heap->ele_size);
        if (!new_eles) return;
        heap->eles = new_eles;
        heap->capacity = new_capacity;
    }

    i = heap->num_eles;
    dest = (char *)heap->eles + i * heap->ele_size;
    memcpy(dest, ele_ptr, heap->ele_size);
    heap->num_eles++;

    while (i > 0) {
        parent = (i - 1) / 2;
        void *curr = (char *)heap->eles + i * heap->ele_size;
        void *par = (char *)heap->eles + parent * heap->ele_size;
        if (!heap->gt(curr, par)) break;
        swap_elements(heap, i, parent);
        i = parent;
    }
}

void *maxpop(heap_t *heap) {
    void *result, *root, *last;
    size_t i, left, right, largest;

    if (heap->num_eles == 0) return NULL;

    result = malloc(heap->ele_size);
    root = heap->eles;
    last = (char *)heap->eles + (heap->num_eles - 1) * heap->ele_size;
    memcpy(result, root, heap->ele_size);
    memcpy(root, last, heap->ele_size);
    heap->num_eles--;

    i = 0;
    while (1) {
        left = 2 * i + 1;
        right = 2 * i + 2;
        largest = i;

        if (left < heap->num_eles) {
            void *l = (char *)heap->eles + left * heap->ele_size;
            void *c = (char *)heap->eles + largest * heap->ele_size;
            if (heap->gt(l, c)) largest = left;
        }

        if (right < heap->num_eles) {
            void *r = (char *)heap->eles + right * heap->ele_size;
            void *c = (char *)heap->eles + largest * heap->ele_size;
            if (heap->gt(r, c)) largest = right;
        }

        if (largest == i) break;

        swap_elements(heap, i, largest);
        i = largest;
    }

    return result;
}
