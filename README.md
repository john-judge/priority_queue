# Priority Queue
A simple priority_queue (min heap) data structure library implemented in C.

I built this simple data structure implementation to use in later projects as part of C static libraries.
Provides access to a min heap data structure (priority queue)

## Maintains: 
  a Set S with associated numerical a(s) integers for each s in S
            a(s) can be consider the "priority" of element s
                                    
                                          
## Updates/Queries:                                     
    -    remove(s)              // O(log n)           
    -    add(s)                 // O(log n)                
    -    change_value(s,a')     // O(log n)           
    -    extract_min()          // O(1)                     
   (the first 3 operations require bubble-up/down)
                                    
## Heap property:  
  The priority of a parent is "higher-priority" than those of its children:  
  
 <a href="https://www.codecogs.com/eqnedit.php?latex=a_{parent}&space;\leq&space;min(a_{left},a_{right})" target="_blank"><img src="https://latex.codecogs.com/gif.latex?a_{parent}&space;\leq&space;min(a_{left},a_{right})" title="a_{parent} \leq min(a_{left},a_{right})" /></a>
