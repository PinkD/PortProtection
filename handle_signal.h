
#ifndef PORT_PROTECTION_HANDLE_SIGNAL_H
#define PORT_PROTECTION_HANDLE_SIGNAL_H

#include <signal.h>
#include <stdbool.h>
#include <stdio.h>

#include "iptables_wrapper.h"
#include "timer.h"


void _signal_handler(int signal);

void handle_signal();

#endif
