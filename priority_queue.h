#include <stdio.h>
#include <stdlib.h>

/*
Provides access to a min heap data structure (priority queue)
Maintain: a Set S with associated numerical a(s) integers for each s in S
            a(s) can be consider the "priority" of element s
                                     index structure of min heap:
                                                       _____
Updates/Queries:                                       | i |
        remove(s)                                      |___|
        add(s)                                          / \
        change_value(s,a')                         ____/   \______
        extract_min()                             | 2i |   | 2i+1 | 
   the first 3 ops require bubble-up/down         |____|   |______|
                                    
Heap property:  The priority of a parent is "higher-priority" than those of its children:  a_p < min(a_c1,a_c2)
*/

typedef struct Element {
    int index;
    void* data; // generic pointer, cast to store pointer to any data type
    int priority;
    // not a linked list format, but rather an array format
} element_t;

typedef struct Min_heap {
    element_t** elements; // array of element pointers,
    int size;   // access nodes by index
    int capacity; // doubles on every reallocation
} min_heap_t;


element_t* element_new(int index, void* data, int priority);

min_heap_t* min_heap_new(int capacity);

void min_heap_free(min_heap_t* h);

void remove_element(min_heap_t* h, int index);

void swap_elements(min_heap_t* h, int i, int j);

element_t* add_element(min_heap_t* h, void* data, int priority);

void update_priority(min_heap_t* h, int index, int priority);

void* extract_min(min_heap_t* h);