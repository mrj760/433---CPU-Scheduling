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
	// Add to list in FCFS schedule
	
}

/**
 *  * Run the RR scheduler
 *   */
void schedule(int rr_time) 
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
		printf("TASK COMPLETED : [Task=\"%s\"], [Wait-Time=\"%d\"], [Turnaround-Time=\"%d\"]\n", 
				current->task->name, waitTime, completeTime);
		totalWaitTime += waitTime;
		totalTurnaroundTime += completeTime;
		current = current->next;
	}

	// Print average wait/turnaround info
	printf("AVERAGES : [Wait Time=\"%f\", [Turnaround Time=\"%f\"]", 
		1.0*totalWaitTime/numTasks, 1.0*totalTurnaroundTime/numTasks);
}
