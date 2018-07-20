
#ifndef PORT_PROTECTION_CONFIG_PARSER_H
#define PORT_PROTECTION_CONFIG_PARSER_H

#include "commandline_parser.h"

const static int LINE_LEN = 512;

Argument *parse_config(char *argv0, char *file);

char *read_line(FILE *f);

#endif