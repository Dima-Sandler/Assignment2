// HA2, Q1

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
typedef struct WorkerList {
	Worker* data;
	struct WorkerList* next;
} WorkerList;

// functions declaration
void PrintWorker(const Worker*, char), update_worker(WorkerList*, float), freeWorkers(WorkerList*);
int index1(WorkerList*, long unsigned), index2(WorkerList*, long unsigned);
Worker* CreateWorker(char);
WorkerList* addWorker(WorkerList*, Worker*), * deleteWorstWorker(WorkerList*), * reverse(WorkerList*);

// functions definitions
void main() {
	char ops_menu[] = "Option menu:\n"
		"1 - add new workers\n"
		"2 - print list\n"
		"3 - search worker by ID number\n"
		"4 - delete worker with lowest salary\n"
		"5 - update all workers salary\n"
		"6 - reverse list order\n"
		"7 - change year type\n"
		"8 - exit\n",
		opt, year_type = 0;
	unsigned long n, id;
	float percent;
	Worker* p_worker = NULL;
	WorkerList* node = NULL, * list_head = NULL;

	while (1) {
		printf("%s\nChoose option: ", ops_menu);

		fseek(stdin, 0, SEEK_END); // set stdin file position to EOF
		scanf("%hhi", &opt);

		switch (opt) {
		case 1: // add new workers
			printf("\nEnter number of workers to add: ");
			scanf("%lu", &n);

			while (n--) { // create and add n new workers
				printf("\n");

				p_worker = CreateWorker(year_type);
				list_head = addWorker(list_head, p_worker);
			}
			break;
		case 2:	// print list	
			n = 1;
			// print all workers
			for (node = list_head; node; node = node->next) {
				printf("\n");
				printf("Worker #%lu\n", n++);
				PrintWorker(node->data, year_type);
			}
			break;
		case 3: // search worker by ID number
			printf("\nEnter ID number: ");
			scanf("%lu", &id);

			printf("\nSearch methoods:\n"
				"0 - iterative\n"
				"1 - recursive\n"
				"\nChoose option: ");
			scanf("%hhi", &opt);

			switch (opt) {
			case 0: // iterative methood
				printf("\nWorker #%d\n", index1(list_head, id));
				break;
			case 1: // recursive methood
				printf("\nWorker #%d\n", index2(list_head, id));
				break;
			default:
				printf("Invalid input\n");
			}
			break;
		case 4: // delete worker with lowest salary
			list_head = deleteWorstWorker(list_head);
			break;
		case 5: // update workers salary
			printf("Enter raise percentage: ");
			scanf("%f", &percent);

			update_worker(list_head, percent);
			break;
		case 6: // reverse workers list
			list_head = reverse(list_head);
			break;
		case 7: // change year type
			printf("\nEnter year type: ");
			scanf("%hhi", &year_type);
			break;
		case 8: // free workers list and exit
			freeWorkers(list_head);
			return;
		default:
			printf("Invalid input\n");
		}
		printf("\n");
	}
}
void PrintWorker(const Worker* p_worker, char year_type) {
	if (!p_worker) // edge case
		return;

	printf("ID Number: %lu\n", p_worker->id);
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
}
void update_worker(WorkerList* head, float percent) {
	for (; head; head = head->next)
		// suppose that an edge case of a NULL data pointer in a list element cannot occure
		(float)head->data->salary *= 1 + percent / 100; // arithmetic conversions from int to float
}
void freeWorkers(WorkerList* head) {
	WorkerList* node = NULL;

	while (head) {
		// suppose that an edge case of a NULL data pointer in a list element cannot occure
		free(head->data->name); // free worker name
		head->data->name = NULL;

		free(head->data); // free worker
		head->data = NULL;

		node = head;
		head = head->next;

		free(node); // free list element
		node = NULL;
	}
}
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
Worker* CreateWorker(char year_type) {
	Worker* p_worker = (Worker*)malloc(sizeof(Worker)); // allocate memory for a new worker

	if (!p_worker) { // malloc check
		printf("Memory alloction error.\n");
		return NULL;
	}

	p_worker->name = NULL;

	printf("Enter worker details:\n");
	printf("ID number: ");
	scanf("%lu", &p_worker->id); // ID input

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
		printf("\n");
	}

	return p_worker;
}
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
WorkerList* deleteWorstWorker(WorkerList* head) {
	if (!head) // check if list is empty
		return head;

	WorkerList* node = head;
	head = head->next;

	// suppose that an edge case of a NULL data pointer in a list element cannot occure
	free(node->data->name); // free worker name
	node->data->name = NULL;

	free(node->data); // free worker
	node->data = NULL;

	free(node); // free list head
	node = NULL;

	return head;
}
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