queue: priority_queue.h priority_queue.c queue_test.c
	clang -o queue_test queue_test.c -g

flow: priority_queue.h priority_queue.c flow.h flow.c
	clang priority_queue.c flow.c -c

library:
	gcc -c priority_queue.c flow.c 
	ar rcs libflow.a *.o

clean:
	rm priority_queue.o flow.o libflow.a
