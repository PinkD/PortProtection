#include "handle_signal.h"


void _signal_handler(int signal) {
    if (signal == SIGINT) {
        printf("SIGINT Received\n");
    } else if (signal == SIGTERM) {
        printf("SIGTERM Received\n");
    } else {
        printf("Signal %d Received\n", signal);
    }
    if (verbose) {
        printf("Cleaning iptables rules...\n");
    }
    clean_iptables();
    if (verbose) {
        printf("Stop main loop...\n");
    }
    printf("Doing some cleaning, please wait...\n");
    stop_timer();//stop main loop
}

void handle_signal() {
    struct sigaction action;
    action.sa_handler = _signal_handler;
    if (verbose) {
        printf("Handling SIGINT\n");
    }
    if (sigaction(SIGINT, &action, NULL)) {
        printf("Error handling SIGINT.\n");
    }
    if (verbose) {
        printf("Handling SIGTERM\n");
    }
    if (sigaction(SIGTERM, &action, NULL)) {
        printf("Error handling SIGTERM.\n");
    }
    if (verbose) {
        printf("Handling SIGKILL\n");
    }
    if (sigaction(SIGKILL, &action, NULL)) {
        printf("Error handling SIGKILL.\n");
    }
//    signal(SIGINT, _signal_handler);
}