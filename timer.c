
#include "timer.h"

pthread_t *start_timer() {
    pthread_t *t = malloc(sizeof(pthread_t));
    mutex = malloc(sizeof(pthread_mutex_t));

    task_list = malloc(sizeof(Task));//init head
    task_list->addr = NULL;
    task_list->next = NULL;

    pthread_mutex_init(mutex, NULL);


    if (verbose) {
        printf("Creating main loop thread...\n");
    }

    pthread_create(t, NULL, (void *(*)(void *)) task_loop, NULL);
    return t;
}

void add_task_to_timer(Task *task) {//TODO: #enhancement# sorted list
    if (verbose) {
        printf("Adding %s to list...\n", task->addr);
    }
    pthread_mutex_lock(mutex);//lock list
    Task *t = task_list;
    while (t->next) {//seek to end
        if (!strcmp(t->next->addr, task->addr)) {//same addr, add time to exist task
            if (verbose) {
                printf("Adding %s to exist task...\n", task->addr);
            }
            t->next->end += (task->end - task->start);
            pthread_mutex_unlock(mutex);//unlock list
            return;
        }
        t = t->next;
    }
    t->next = task;//insert
    task->next = NULL;//in case forget to set to null
    insert_client(task->addr);//insert into iptables
    pthread_mutex_unlock(mutex);//unlock list
}

void cancel_task(Task *task) {
    if (verbose) {
        if (task->addr) {
            printf("Removing %s from list...\n", task->addr);
        }
    }
    //needn't to lock, because the outside function has locked it
//    pthread_mutex_lock(mutex);//lock list
    Task *t = task_list;
    while (t->next) {
        if (t->next == task) {
            remove_client(task->addr);//delete in iptables
            Task *tmp = t->next->next;
            t->next = tmp;
            break;
        }
        t = t->next;
    }
//    pthread_mutex_unlock(mutex);//unlock list
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

void task_loop() {
    if (verbose) {
        printf("Entering main loop...\n");
    }
    while (task_list) {
        pthread_mutex_lock(mutex);//lock list
        Task *t = task_list->next;//skip head
        if (t) {
            time_t now = time(NULL);
            while (t) {
                if (t->end < now) {//out of date
                    cancel_task(t);
                }
                t = t->next;
            }
        }
        pthread_mutex_unlock(mutex);//unlock list
        sleep(3);//check every 3 seconds
    }
    if (verbose) {
        printf("Leaving main loop...\n");
    }
    exit(exit_code);
}

#pragma clang diagnostic pop

time_t hour_to_second(int hour) {
    return hour * 60 * 60;
//    return hour * 5;//debug
}

void stop_timer(int code) {
    exit_code = code;
    Task *t = task_list;
    if (verbose) {
        printf("Cleaning up list...\n");
    }
    while (t) {
        Task *tmp = t;
        t = t->next;
        cancel_task(tmp);
        free_task(tmp);
    }
    task_list = NULL;
}

void free_task(Task *task) {
    if (task->addr) {
        free(task->addr);
    }
    free(task);
}
