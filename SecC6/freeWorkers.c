#define LEN 6

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	unsigned long id, salary;
	char* name;

	union { // unnamed union
		unsigned long n_year;
		char s_year[LEN + 1];
	};
} Worker;
typedef struct WorkerList {
	Worker* data;
	struct WorkerList* next;
} WorkerList;

void freeWorkers(WorkerList* head) {
	WorkerList* node = NULL;

	while (head) {	
		// suppose that an edge case of a NULL data pointer in a list element cannot occure
		free(head->data->name); // free worker name
		head->data->name = NULL;
							
		freeWorker(head->data);
		head->data = NULL; 
	
		node = head;
		head = head->next;
		
		free(node); // free list element
		node = NULL;
	}
}

void freeWorker(Worker* p_worker) {
	if (p_worker) {
		free(p_worker->name); // free worker name
		p_worker->name = NULL;
		
		free(p_worker); // free worker;
		p_worker == NULL;
	}
}
void alt_freeWorkers(WorkerList* head) {
	WorkerList* node = NULL;

	while (head) {
		freeWorker(head->data);
		head->data = NULL;

		node = head;
		head = head->next;

		free(node); // free list element
		node = NULL;
	}
}

