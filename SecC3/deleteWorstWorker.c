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

WorkerList* deleteWorstWorker(WorkerList* head) {
	if (!head) // check if list is empty
		return head;

	WorkerList* node = head;
	
	head = head->next;

	// suppose that an edge case of a NULL data pointer in a list element cannot occure
	free(node->data->name); // free worker name
	head->data->name = NULL;

	free(node->data); // free worker
	head->data = NULL;

	free(node); // free list head
	node = NULL;

	return head;
}