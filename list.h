#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <stdlib.h>

// #define DATASTRUCTURES_IMPLEMENTATION

#define list_create(type) _list_create(sizeof(type))

void list_destroy(void* list);

size_t list_len(void* list);

size_t list_cap(void* list);

void list_reserve(void* list, size_t newCap);

#define list_push(list, item) (list[_list_inc_len(list) - 1] = item)

#define list_pop(list) list[_list_dec_len(list)]

#define list_peek(list) list[list_len(list) - 1]

void* _list_create(size_t itemSize);
size_t _list_inc_len(void* list);
size_t _list_dec_len(void* list);

#endif // DATASTRUCTURES_H

#ifdef DATASTRUCTURES_IMPLEMENTATION

typedef struct {
    size_t itemSize;
    size_t len;
    size_t cap;
} _ListHeader;

#define _GET_LIST_HEADER(list) ((_ListHeader*)(list)-1)
#define _GET_LIST_DATA(header) ((_ListHeader*)(header) + 1)
#define _LIST_SIZE(header)                                                     \
    (sizeof(_ListHeader) + (header)->itemSize * (header)->cap)

void* _list_create(size_t itemSize) {
    _ListHeader* header = malloc(sizeof(_ListHeader) + itemSize);
    header->itemSize = itemSize;
    header->len = 0;
    header->cap = 1;
    return _GET_LIST_DATA(header);
}

void list_destroy(void* list) {
    free(_GET_LIST_HEADER(list));
}

size_t list_len(void* list) {
    return _GET_LIST_HEADER(list)->len;
}

size_t list_cap(void* list) {
    return _GET_LIST_HEADER(list)->cap;
}

void list_reserve(void* list, size_t newCap) {
    _ListHeader* header = _GET_LIST_HEADER(list);
    if (newCap > header->cap) {
        header->cap = newCap;
        header = realloc(header, _LIST_SIZE((header)));
    }
}

size_t _list_inc_len(void* list) {
    _ListHeader* header = _GET_LIST_HEADER(list);
    if (header->len == header->cap) list_reserve(list, header->cap * 2);
    return ++header->len;
}

size_t _list_dec_len(void* list) {
    _ListHeader* header = _GET_LIST_HEADER(list);
    return header->len > 0 ? --header->len : 0;
}

#endif // DATASTRUCTURES_IMPLEMENTATION