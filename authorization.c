
#include "authorization.h"

void init_argument(Argument *arg) {
    argument = arg;
    verbose = arg->verbose;
}

bool authorize_with_request(Request *request) {
    if (!request->key || strcmp(argument->key, request->key)) {//NOLINT
        if (verbose) {
            printf("Authorize %s failed\n", request->addr);
        }
        return false;
    } else {
        printf("Authorized %s , +%dh\n", request->addr, request->time);
        if (verbose) {
            printf("Inserting iptables rule\n");
        }
        Task *task = malloc(sizeof(Task));
        task->next = NULL;
        task->addr = strdup(request->addr);
        task->start = time(NULL);
        task->end = hour_to_second(request->time) + task->start;
        if (verbose) {
            printf("Inserting task to main loop\n");
        }
        add_task_to_timer(task);
        return true;
    }
}