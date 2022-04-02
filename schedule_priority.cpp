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
 *  * Run the Priority scheduler
 */
void schedule(int) 
{
	// perform each task until completion in the priority order made when adding them to the list
	traverse(head);
	int completeTime = 0;
	node* current = head;
	while (current != nullptr)
	{
		completeTime += current->task->burst;
		// print job wait/turnaround info in order of completion
		printf("Task: %s, Wait-Time: %d, Turnaround-Time:%d\n", 
			current->task->name, completeTime-current->task->burst, completeTime);
		current = current->next;
	}
}
