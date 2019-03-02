# Priority Queue
A priority_queue (min heap) data structure library implemented in C.

I built this simple data structure implementation to use in later projects as part of C static libraries.
Provides access to a min heap data structure (priority queue)

## Maintains: 
  a Set S with associated numerical a(s) integers for each s in S
            a(s) can be consider the "priority" of element s
                                    
                                          
## Updates/Queries:                                     
    -    remove(s)                                    
    -    add(s)                                          
    -    change_value(s,a')                       
    -    extract_min()                           
   the first 3 ops require bubble-up/down  
                                    
## Heap property:  
  The priority of a parent is "higher-priority" than those of its children:  a_p < min(a_c1,a_c2)
