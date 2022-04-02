#include <stdlib.h>
#include <stdio.h>

#include "task.h"
#include "list.h"
#include "cpu.h"

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
	int totalTimeElapsed = 0;
	int completeCount = 0; // number of completed jobs. if ever >= total # jobs then stop rr schedule
	node* current = head;

	int totalWaitTime = 0;
	int totalTurnaroundTime = 0;

	while (true)
	{


		if (current->task->burst == 0)
		{ 	// skip completed jobs
			current = current->next;
			// printf("\n"); // debug
			continue;
		}


		// time to elapse this round will either be the rr_time or the rest of the current task's burst time, whichever is smaller
		// deduct from current task's burst time and track total elapsed time
		int roundTimeElapsed;
		if (rr_time == 0)
			roundTimeElapsed = current->task->burst;
		else
			roundTimeElapsed = current->task->burst < rr_time ? current->task->burst : rr_time;
		current->task->burst -= roundTimeElapsed;
		totalTimeElapsed += roundTimeElapsed;

		

		if (current->task->burst == 0)
		{ 	// Task just finished
			// Print task-specific wait/turnaround info in order of completion
			int waitTime = (totalTimeElapsed - roundTimeElapsed - current->task->burst);
			printf("TASK COMPLETED : [task=\"%s\"], [wait-time=\"%d\"], [turnaround-time=\"%d\"]\n",  
				current->task->name, waitTime, totalTimeElapsed);
			totalWaitTime += waitTime;
			totalTurnaroundTime += totalTimeElapsed;
			if (++completeCount >= numTasks)
				break;
		}

		
		if (current->next == nullptr)
		{ 	// Reached end. Start over and reset job completion count
			current = head;
			continue;
		}
		else 
		{ 	// Move on
			current = current->next;
		}
	}
	
	// Print average wait/turnaround info
	printf("AVERAGES : [wait-time=\"%f\"], [turnaround-time=\"%f\"]",
		1.0*totalWaitTime/numTasks, 1.0*totalTurnaroundTime/numTasks);
}
