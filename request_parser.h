
#ifndef PORT_PROTECTION_REQUEST_PARSER_H
#define PORT_PROTECTION_REQUEST_PARSER_H


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>


typedef enum {
    HTTP_ERROR,
    RAW_ERROR,
    HTTP,
    RAW
} RequestType;

typedef struct {
    char *addr;
    RequestType type;
    char *key;
    int time;
} Request;

Request *parse_request(const char *data);

Request *_parse_http(const char *data);

Request *_parse_raw(const char *data);

void free_request(Request *request);

void str_strip(char *str);

#endif
