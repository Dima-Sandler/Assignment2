#define _CRT_SECURE_NO_WARNINGS // disable scanf errors
#define LEN 6
#define SIZE 15

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	unsigned long id, salary;
	char* name;

	union { // unnamed union
		unsigned long n_year;
		char s_year[LEN + 1];
	};
} Worker;

Worker* CreateWorker(char year_type) {
	Worker* p_worker = (Worker*)malloc(sizeof(Worker)); // allocate memory for a new worker

	if (!p_worker) { // malloc check
		printf("Memory alloction error.\n");
		return NULL;
	}

	p_worker->name = NULL;

	printf("Enter worker details:\n");
	printf("ID: ");
	scanf("%lu", &p_worker->ID); // ID input

	printf("Name: ");

	char buff[SIZE]; // temporary array to check the name length

	fseek(stdin, 0, SEEK_END); // set stdin file position to EOF
	gets_s(buff, SIZE); // name input

	// allocate memory for the name
	p_worker->name = (char*)malloc(strlen(buff) + 1);

	if (p_worker->name) // malloc check
		strcpy(p_worker->name, buff);

	printf("Salary: ");
	scanf("%lu", &p_worker->salary); // salary input

	printf("Start year: ");
	fseek(stdin, 0, SEEK_END);

	switch (year_type) {
	case 0:
		scanf("%lu", &p_worker->n_year); // number year input	
		break;
	case 1:
		gets_s(p_worker->s_year, LEN); // string year input
		break;
	default:
		printf("\n"); // newline
	}
	printf("\n");

	return p_worker;
}


