#include <stdio.h>
#define LEN 6

// Worker srtuct definition
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