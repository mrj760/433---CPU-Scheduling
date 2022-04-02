#include <stdlib.h>
#include <stdio.h>

#include "task.h"
#include "list.h"

node* head = nullptr;
int numTasks = 0;

// add a new task to the list of tasks, sorting by priority as added
 void add(char *name, int priority, int burst) 
{
	// Allocate a task to add to the task list
	task* t = (struct task *) malloc(sizeof(struct task));
	t->name = name;
	t->priority = priority;
	t->burst = burst;
	t->tid = numTasks++;

	node* current = head;

	// insert the task at the front of the list if it has the most priority
	if (head == nullptr || t->priority < head->task->priority)
	{
		insert(&head, t);
	}
	// else insert it after all other tasks of the same priority but before the task with the next least priority
	// or insert it at the end if it has the least priority of all existing tasks
	else while (true)
	{
		if (current->next == nullptr || t->priority < current->next->task->priority)
		{
			struct node *newNode = (struct node *) malloc(sizeof(struct node));
			newNode->task = t;
			newNode->next = current->next;
			current->next = newNode;
			break;
		}
		current = current->next;
	}
}

/**
 *  * Run the Priority scheduler
 */
void schedule(int) 
{
	// perform each task until completion in the priority order made when adding them to the list
	traverse(head);
	int completeTime = 0;
	node* current = head;
	int totalWaitTime = 0;
	int totalTurnaroundTime = 0;
	while (current != nullptr)
	{
		completeTime += current->task->burst;
		// print job wait/turnaround info in order of completion
		int waitTime = (completeTime - current->task->burst);
		printf("TASK COMPLETED : [task=\"%s\"], [wait-time=\"%d\"], [turnaround-time=\"%d\"]\n", 
				current->task->name, waitTime, completeTime);
		totalWaitTime += waitTime;
		totalTurnaroundTime += completeTime;
		current = current->next;
	}

	// Print average wait/turnaround info
	printf("AVERAGES : [wait-time=\"%f\"], [turnaround-time=\"%f\"]", 
		1.0*totalWaitTime/numTasks, 1.0*totalTurnaroundTime/numTasks);
}
