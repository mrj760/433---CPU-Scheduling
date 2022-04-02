#include <stdlib.h>
#include <stdio.h>

#include "task.h"
#include "list.h"
#include "cpu.h"

node* head = nullptr;
int id = 0;

// add a new task to the list of tasks, sorting by priority as added
 void add(char *name, int priority, int burst) 
{
	// Allocate a task to add to the task list
	task* t = (struct task *) malloc(sizeof(struct task));
	t->name = name;
	t->priority = priority;
	t->burst = burst;
	t->tid = id++;

	node* temp = head;

	// insert the task at the front of the list if it has the most priority
	if (head == nullptr || t->priority < head->task->priority)
	{
		insert(&head, t);
	}
	// else insert it after all other tasks of the same priority but before the task with the next least priority
	// or insert it at the end if it has the least priority of all existing tasks
	else while (true)
	{
		if (temp->next == nullptr || t->priority < temp->next->task->priority)
		{
			struct node *newNode = (struct node *) malloc(sizeof(struct node));
			newNode->task = t;
			newNode->next = temp->next;
			temp->next = newNode;
			break;
		}
		temp = temp->next;
	}
}

/**
 *  * Run the Priority/Round-Robin scheduler
 */
void schedule(int rr_time) 
{
	traverse(head);
	int totalTime = 0;
	int completeCount = 0; // number of completed jobs. if ever >= total # jobs then stop rr schedule
	node* current = head;
	while (true)
	{
		// skip completed jobs
		if (current->task->burst == 0)
		{
			current = current->next;
			completeCount++;
			continue;
		}

		// reached end, go back to start and start tracking completed jobs from scratch
		if (current == nullptr)
		{
			if (completeCount >= id)
				break;
			current = head;
			completeCount = 0;
			continue;
		}

		// subtract either the rr_time or the rest of the burst time from the task, whichever is smaller
		int roundTime = current->task->burst < rr_time ? current->task->burst : rr_time;
		current->task->burst -= roundTime;

		// Track how much total time has been taken
		totalTime += roundTime;

		// Debug print
		printf("Current task: %s, Round Time: %d, Total Time: %d, Task Time Remaining: %d, Jobs Complete: %d\n", 
			current->task->name, roundTime, totalTime, current->task->burst, completeCount);

		// task just finished, print out its wait/turnaround info
		if (current->task->burst == 0)
		{
			// print job wait/turnaround info in order of completion
			printf("Task: %s, Wait-Time: %d, Turnaround-Time:%d\n", 
				current->task->name, totalTime - totalTime-current->task->burst, totalTime);
			completeCount++;
		}

		// move on
		current = current->next;
	}
}
