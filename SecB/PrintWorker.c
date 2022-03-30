#include <stdio.h>
#define LEN 6

typedef struct {
	unsigned long id, salary;
	char* name;

	union { // unnamed union
		unsigned long n_year;
		char s_year[LEN + 1];
	};
} Worker;

void PrintWorker(const Worker* p_worker, char year_type) {
	if (!p_worker) // edge case
		return;

	printf("ID Number: %lu\n", p_worker->ID);
	printf("Name: %s\n", p_worker->name);
	printf("Salary: %lu\n", p_worker->salary);
	printf("Start year: ");

	switch (year_type) {
	case 0:
		printf("%lu\n", p_worker->n_year);
		break;
	case 1:
		printf("%s\n", p_worker->s_year);
		break;
	default:
		printf("invalid year type\n");
	}
	printf("\n");
}