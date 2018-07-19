
#ifndef PORT_PROTECTION_REQUEST_HANDLER_H
#define PORT_PROTECTION_REQUEST_HANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>


#include "request_parser.h"

Request *handle_request(const char *data);

#endif
