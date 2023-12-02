#include <stdio.h>

#define DATASTRUCTURES_IMPLEMENTATION
#include "list.h"

int main(void) {
    float* list = list_create(int);

    list_push(list, 2.1);
    list_push(list, 4.2);
    list_push(list, 6.3);
    list_push(list, 8.4);

    list[3] = 10.5;

    printf("len: %ld\n", list_len(list));

    while (list_len(list) > 0) {
        printf("%f\n", list_pop(list));
    }

    printf("len: %ld\n", list_len(list));

    list_destroy(list);
}