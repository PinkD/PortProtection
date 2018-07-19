
#ifndef PORT_PROTECTION_HELP_H
#define PORT_PROTECTION_HELP_H

#include "commandline_parser.h"

void print_help(char *name);

void print_run_as_root();

void print_error(ParseErrorCode error_code);

#endif
