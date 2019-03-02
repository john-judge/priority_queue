#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.c"

/* Tests for priority queue implementation */


int main() {
    printf("Allocating default size heap...\n");
    min_heap_t* h = min_heap_new(0);

    int n = 1500;
    int data[1500]; // data
    int priority[1500]; // priorities of data
    int priority2[1500]; // priorities change.
    element_t* elements[1500];
    for(int i = 0; i< n; i++) {
        data[i] = 100 * i;
        priority[i] = ((2 * i +3) % n) + 15;
        priority2[i] = i;
    }

    printf("Adding elements\n");
    for (int i = 0; i<n;i++) {
        printf("adding data %d at priority %d\n",data[i],priority[i]);
        elements[i] = add_element(h,(void*)data[i],priority[i]);
    }

    printf("\n Get those priorities straight.\n");
    for(int i= 0; i<n;i++) {
        element_t* e = elements[i];
        printf("Changing data %d priority: %d -> %d\n",(int)e->data,e->priority,priority2[i]);
        update_priority(h,e->index,priority2[i]);
        
        //void* data = extract_min(h);
        //printf("extracted data %d at priority %d\n",(int)data,i);        
    }

    printf("\nExtracting elements in order of priority\n");
    for (int i = 0; i<n;i++) {
        
        void* data = extract_min(h);
        printf("extracted data %d at priority %d\n",(int)data,i);
    }
    min_heap_free(h);
}