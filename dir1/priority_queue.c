#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

int default_capacity = 128;      // initialized min_heap will hold DEFAULT_CAPACITY elements

element_t* element_new(int index, void* data, int priority) {
    element_t* e = malloc(sizeof(element_t));
    e->index = index;
    e->data = data;
    e->priority = priority;
    return e;
}

/* assume that DATA void pointers are freed outside of this environment
      (this min heap only tracks DATA object priorities generically,
          => not responsible for managing their allocation)*/

min_heap_t* min_heap_new(int capacity) {
    if(capacity < 1) {
        capacity = default_capacity;
    }
    // first allocate array of NULL elements:
    element_t** es = malloc(sizeof(element_t*) * capacity);
    for(int i = 0; i < capacity; i++) {
        es[i] = NULL;
    }
    // build initialized empty heap struct
    min_heap_t* h = malloc(sizeof(min_heap_t));
    h->capacity = capacity;
    h->size = 0;
    h->elements = es;
    return h;
}

void min_heap_free(min_heap_t* h) {
    /* assume that DATA void pointers (in each element struct)
          are freed outside of this environment */
    for(int i = 0; i< h->capacity;i++) {
        if(h->elements[i]) {
            free(h->elements[i]);
        }
    }
    free(h->elements);
    free(h);
}

min_heap_t* min_heap_resize(min_heap_t* h) {
    /* Called when size > capacity. Double the heap capacity */
    int new_cap = h->capacity * 2;
    min_heap_t* h_new = min_heap_new(new_cap);
    
    // transfer data
    for(int i = 0; i < h->capacity;i++) {
        h_new->elements[i] = h->elements[i];
    }
    element_t** cp = h->elements;
    h->elements = h_new->elements;
    h->capacity = new_cap;
    free(cp);       // frees extra H and array but leaves elements allocated,
    free(h_new);    //  pointed to by H->ELEMENTS pointer array
                
    printf("resized array: capacity %d, occupied: %d\n",h->capacity,h->size);
    return h;
}

element_t* get_element(min_heap_t* h, int index) {
    if (index >= h->size) {
        return NULL;
    }
    return h->elements[index];
}

element_t* get_tail(min_heap_t* h) {
    // return right most leaf node, i.e. last element
    int last_index = h->size - 1;
    return h->elements[last_index];
}

element_t* left_child(min_heap_t* h, element_t* e) {
    /* return left child element (may be NULL)
         array index is zero-indexed; parent-child relation is 1-indexed */
    int left_index = 2 * (e->index + 1) - 1; 
    return get_element(h,left_index);
}

element_t* right_child(min_heap_t* h, element_t* e) {
    /* return right child element (may be NULL)
         array index is zero-indexed; parent-child relation is 1-indexed */
    int right_index = 2 * (e->index + 1); // + 1 - 1
    return get_element(h,right_index);
}

element_t* parent(min_heap_t* h, element_t* e) {
    /* return parent element or NULL if root
     preserve 0-index, but index rule (diagram) is in 1-index*/
    int i = e->index;
    if(!i) { // root has 0-index i = 0
        return NULL;
    } 
    int parent_index =  (i + 1) / 2; // signed int: floor division
    parent_index--;     // zero-indexed
    if (!parent_index) {
        return NULL;
    }
    return h->elements[parent_index];
}

void bubble_up(min_heap_t* h, int index) {
    /* check if element at INDEX has higher priority than its parents
     adjust tree structure accordingly */
    element_t* e = get_element(h,index);
    element_t* par = parent(h,e);
    if (par && (e->priority < par->priority)) {
        swap_elements(h, e->index,par->index);
        bubble_up(h,e->index); // <- E index field has been updated during BUBBLE UP
    }
}

void bubble_down(min_heap_t* h, int index) {
    /* check if element at INDEX has lower priority than its children
         adjust tree structure accordingly */
    element_t* e = get_element(h,index);
    element_t* left = left_child(h,e);
    element_t* right = right_child(h,e);
    int under_left = (left && (left->priority < e->priority));
    int under_right = (right && (right->priority < e->priority));
    int swap_left = 0;
    int swap_right = 0;
    if(under_left && under_right) {
        if (left->priority < right->priority) {
            swap_left = 1;
        } else {
            swap_right = 1;
        }
    } else if(under_left) {
        swap_left = 1; // left is higher priority than right
    } else if(under_right) {
        swap_right = 1; // right is higher priority than left
    } else {
        return ; // min heap property already observed
    }
    if(swap_left) {
        swap_elements(h,e->index,left->index);
    } else if(swap_right) {
        swap_elements(h,e->index,right->index);
    } else {
        return ;
    }
//    if(swap_left || swap_right) { // don't run bubble down if no swap made
    bubble_down(h,e->index); // E has updated index from SWAP_ELEMENTS        
}

void swap_elements(min_heap_t* h, int i, int j) {
    // swap elements at indices i and j
    int max_ind = h->size - 1;
    if ((i > max_ind) || (j > max_ind) ||
     (!h->elements[i]) || (!h->elements[j])) {
        printf("Index error: swap_elements %d %d but heap size only %d\n",i,j,h->size);
        exit(1);
    }
    element_t* tmp = h->elements[i];
    h->elements[i] = h->elements[j];
    h->elements[j] = tmp; 
    //set indices straight according to new placement
    h->elements[i]->index = i;
    h->elements[j]->index = j;
}

element_t* add_element(min_heap_t* h, void* data, int priority) {
    // create element struct, add to heap, then return it
    int index = h->size;
    h->size++;
    // allocate new element
    element_t* e_new = element_new(index,data,priority);
    // resize if need more room:
    if (h->size >= h->capacity) {
        printf("resizing array\n");
        h = min_heap_resize(h);
    }
    h->elements[index] = e_new;
    bubble_up(h,index);
    return e_new;
}

void remove_element(min_heap_t* h, int index) {
    /* swap target to bottom leaf TAIL, 
         remove target, then bubble down TAIL */
    element_t* target = get_element(h,index);
    element_t* tail = get_tail(h);
    swap_elements(h, target->index,tail->index);
    // remove target, now at bottom
    h->size--;
    int target_ind = target->index;
    free(target); // not responsible for freeing DATA field
    h->elements[target_ind] = NULL;
    // correct old tail for heap property
    if(h->size) {
        bubble_down(h,tail->index); // indices modified by SWAP_ELEMENTS
    }
}

void update_priority(min_heap_t* h, int index, int priority) {
    // if new priority is higher, bubble up. Else bubble down
    element_t* e = h->elements[index];
    int old_priority = e->priority;
    e->priority = priority;
    if(priority < old_priority) {
        bubble_up(h,e->index);
    } else if (priority > old_priority) {
        bubble_down(h,e->index);
    }
}

void* extract_min(min_heap_t* h) {
    // return the DATA of the top element, and remove it
    element_t* top = h->elements[0];
    void* payload = top->data;
    
    remove_element(h,top->index);
    return payload;
}