#include <stdlib.h>
#include <stdio.h>

#include "task.h"
#include "list.h"
#include "cpu.h"

node* head = nullptr;
int numTasks = 0;

// add a new task to the list of tasks
void add(char *name, int priority, int burst) 
{
	// Allocate a task to add to the task list
	task* t = (struct task *) malloc(sizeof(struct task));
	t->name = name;
	t->burst = burst;
	t->priority = priority;
	t->tid = numTasks++;

	if (head == nullptr){
		struct node *newNode = (struct node *) malloc(sizeof(struct node));
		newNode->task = t;
		newNode->next = nullptr;
		head = newNode;
		return;
	}

	node* current = head;
	while (true)
	{
		if (current->next == nullptr)
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
 *  * Run the FCFS scheduler
 *   */
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
