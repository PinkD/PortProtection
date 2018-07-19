
#include "iptables_wrapper.h"

void init_iptables(Argument *arg) {
    argument = arg;
    char *rule = malloc(strlen(INIT_IPTABLES_TEMPLE) + DEFAULT_FILL_LEN);
    sprintf(rule, INIT_IPTABLES_TEMPLE, argument->interface_name, argument->protect_port);
    if (verbose) {
        printf("Initializing iptables rule...\n");
        printf(rule);
        printf("\n");
    }
    if (system(rule)) {
        printf("Error initializing iptables rule\n");
    }
    free(rule);
}

void clean_iptables() {
    char *rule = malloc(strlen(CLEAN_IPTABLES_TEMPLE) + DEFAULT_FILL_LEN);
    sprintf(rule, CLEAN_IPTABLES_TEMPLE, argument->interface_name, argument->protect_port);
    if (verbose) {
        printf("Cleaning iptables rule...\n");
        printf(rule);
        printf("\n");
    }
    if (system(rule)) {
        printf("Error cleaning iptables rule!\n");
    }
    free(rule);
}

void insert_client(char *addr) {
    char *rule = malloc(strlen(INSERT_IPTABLES_TEMPLE) + DEFAULT_FILL_LEN);
    sprintf(rule, INSERT_IPTABLES_TEMPLE, argument->interface_name, argument->protect_port, addr);
    if (verbose) {
        printf("Inserting iptables rule...\n");
        printf(rule);
        printf("\n");
    }
    if (system(rule)) {
        printf("Error adding iptables rule for %s\n", addr);
    }
    free(rule);
}

void remove_client(char *addr) {
    char *rule = malloc(strlen(REMOVE_IPTABLES_TEMPLE) + DEFAULT_FILL_LEN);
    sprintf(rule, REMOVE_IPTABLES_TEMPLE, argument->interface_name, argument->protect_port, addr);
    if (verbose) {
        printf("Removing iptables rule...\n");
        printf(rule);
        printf("\n");
    }
    if (system(rule)) {
        printf("Error removing iptables rule for %s\n", addr);
    }
    free(rule);
}
