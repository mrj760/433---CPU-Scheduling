/**
 * Driver.c
 *
 * Schedule is in the format
 *
 *  [name] [priority] [CPU burst]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "task.h"
#include "list.h"
#include "schedulers.h"

#define SIZE 100

char *strsep(char **stringp, const char *delim)
{
  char *start = *stringp;
  char *p;

  p = (start != NULL) ? strpbrk(start, delim) : NULL;

  if (p == NULL)
  {
    *stringp = NULL;
  }
  else
  {
    *p = '\0';
    *stringp = p + 1;
  }

  return start;
}

int main(int argc, char *argv[])
{
  std::cout << "=================================" << std::endl;
  std::cout << "CS 433 Programming assignment 3" << std::endl;
  std::cout << "Author: Christian Contreras, Micah Johnson, and Eric Tyler" << std::endl;
  std::cout << "Date: 03/31/2022" << std::endl;
  std::cout << "Course: CS433 (Operating Systems)" << std::endl;
  std::cout << "Description : Finds the turnaround/waiting times of differing scheduling algorithms" << std::endl;
  std::cout << "=================================" << std::endl;

  FILE *in;
  char *temp;
  char task[SIZE];

  char *name;
  int priority;
  int burst;

  in = fopen(argv[1], "r");

  while (fgets(task, SIZE, in) != NULL)
  {
    temp = strdup(task);
    name = strsep(&temp, ",");
    priority = atoi(strsep(&temp, ","));
    burst = atoi(strsep(&temp, ","));

    // add the task to the scheduler's list of tasks
    add(name, priority, burst);

    free(temp);
  }

  fclose(in);

  // invoke the scheduler
  if (argv[2] != nullptr)
    schedule(atoi(argv[2]));
  else
    schedule();

  return 0;
}
