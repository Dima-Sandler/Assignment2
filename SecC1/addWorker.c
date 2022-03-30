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

WorkerList* addWorker(WorkerList* head, Worker* w) {
	WorkerList* node = head, * nxt_node = NULL, * new_node = NULL;

	if (!w) { // edge case check
		puts("Failed to add a new worker.\n");
		return head;
	}

	new_node = (WorkerList*)malloc(sizeof(WorkerList)); // allocate memory for a new list element

	if (!new_node) { // malloc check
		puts("Memory alloction error.\n");
		return head;
	}

	// initialize the fields of the new element
	new_node->data = w;
	new_node->next = NULL;

	// check if the list is empty or the new element should be the first in the list
	if (head == NULL || w->salary <= head->data->salary) {
		new_node->next = head;
		return new_node;
	}

	nxt_node = head->next;

	// find after which element in the list the new element should be added
	while (nxt_node != NULL && w->salary > nxt_node->data->salary) {
		node = nxt_node;
		nxt_node = nxt_node->next;
	}

	// add the new element to the list
	node->next = new_node;
	new_node->next = nxt_node;

	return head;
}