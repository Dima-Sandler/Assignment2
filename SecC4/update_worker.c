#define _CRT_SECURE_NO_WARNINGS // disable scanf errors
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

void update_worker(WorkerList* head, float percent) {
	for (; head; head = head->next)
		// suppose that an edge case of a NULL data pointer in a list element cannot occure
		(float)head->data->salary *= 1 + percent / 100; // arithmetic conversions from int to float
}
