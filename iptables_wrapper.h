
#ifndef PORT_PROTECTION_IPTABLES_WRAPPER_H
#define PORT_PROTECTION_IPTABLES_WRAPPER_H

#include "commandline_parser.h"
#include "debug.h"

static Argument *argument;

const static int DEFAULT_FILL_LEN = 128;

const static char *INIT_IPTABLES_TEMPLE = "iptables -t filter -A INPUT -i %s -p tcp --dport %d -j REJECT";
const static char *CLEAN_IPTABLES_TEMPLE = "iptables -t filter -D INPUT -i %s -p tcp --dport %d -j REJECT";
const static char *INSERT_IPTABLES_TEMPLE = "iptables -t filter -I INPUT -i %s -p tcp --dport %d -s %s -j ACCEPT";
const static char *REMOVE_IPTABLES_TEMPLE = "iptables -t filter -D INPUT -i %s -p tcp --dport %d -s %s -j ACCEPT";

void init_iptables(Argument *arg);

void insert_client(char *addr);

void remove_client(char *addr);

void clean_iptables();

#endif
