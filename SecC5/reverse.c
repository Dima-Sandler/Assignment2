#define LEN 6
#include <stdio.h>

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

WorkerList* reverse(WorkerList* head) {
	WorkerList* prev_node = NULL, * next_node = NULL;

	while (head) {
		next_node = head->next;
		head->next = prev_node;
		prev_node = head;
		head = next_node;
	}
	
	return prev_node; // return new head
}

WorkerList* alt_reverse(WorkerList* head) {
	if (!head) // check if the list is not empty
		return head;

	WorkerList* prev_node = NULL, * next_node = head->next;

	while (next_node) {
		head->next = prev_node;
		prev_node = head;
		head = next_node;
		next_node = next_node->next;
	}

	return head;
}