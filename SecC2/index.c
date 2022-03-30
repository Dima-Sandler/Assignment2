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

int index1(WorkerList* head, long unsigned id) {
	for (int i = 1; head; head = head->next, i++)
		if (head->data->id == id)
			return i;
	
	return -1; // worker with matching ID not found
}
int index2(WorkerList* head, long unsigned id) {
	if (!head) // stop condition 1: worker with matching ID not found or empty list
		return -1;

	if (head->data->id == id) // stop condition 2: worker with matching ID found
		return 1;
	
	int res = index2(head->next, id);
	
	return res == -1 ? res : res + 1;
}

