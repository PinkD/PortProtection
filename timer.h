
#ifndef PORT_PROTECTION_TIMER_H
#define PORT_PROTECTION_TIMER_H

#include <pthread.h>
#include <malloc.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct ST_TASK_TMP {
    char *addr;//don't free, it's not a copy
    time_t start;
    time_t end;
    struct ST_TASK_TMP *next;
} Task;

#include "iptables_wrapper.h"
#include "debug.h"

Task *task_list;
pthread_mutex_t *mutex;

pthread_t *start_timer();

void add_task_to_timer(Task *task);

void cancel_task(Task *task);

void task_loop();

void stop_timer();

time_t hour_to_second(int hour);

void free_task(Task *task);

#endif
