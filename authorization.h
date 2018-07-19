
#ifndef PORT_PROTECTION_AUTHORIZATION_H
#define PORT_PROTECTION_AUTHORIZATION_H

#include "request_handler.h"
#include "commandline_parser.h"
#include "iptables_wrapper.h"
#include "timer.h"
#include "debug.h"

static Argument *argument;

void init_argument(Argument *arg);

bool authorize_with_request(Request *request);

#endif