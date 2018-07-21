
#ifndef PORT_PROTECTION_COMMANDLINEPARSER_H
#define PORT_PROTECTION_COMMANDLINEPARSER_H

#include <stdbool.h>
#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


static const int MAX_STR_LEN = 254;
static const int MAX_PARAM_LEN = 15;

typedef unsigned short ushort;
typedef enum {
    OK = 0,
    NOT_ENOUGH_ARG,
    BAD_PORT_NUMBER,
    BAD_INTERFACE,
    BAD_KEY_TOO_LONG,
    BAD_KEY_FILE,
    UNKNOWN_ERROR,
    UNKNOWN_PARAM,
    BAD_CONFIG_FILE

} ParseErrorCode;

typedef enum {
    TCP,
    UDP
} Protocol;

typedef struct {
    bool verbose;
    ushort listen_port;
    ushort protect_port;
    char *interface_name;
    char *key;
    char *cert_file;
    char *key_file;
    ParseErrorCode error_code;
    Protocol protocol;
} Argument;


#include "debug.h"
#include "config_parser.h"


/**
 * check if interface exists
 * @param interface
 * @return
 */
bool check_interface(char *interface);

/**
 * read key from file
 * @param file
 * @return key
 */
char *read_key(char *file);

/**
 * parse arguments
 * @param argc from main
 * @param argv from main
 * @return parsed args, error code in Argument.errorCode
 */
Argument *parse_args(int argc, char *argv[]);

/**
 * free argument
 * @param arg to free
 */
void free_arg(Argument *arg);


void print_arg(Argument *arg);

#endif
