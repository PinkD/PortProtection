#include "request_parser.h"

/**
 *
 * @param data to parse
 * @return Request (NotNull)
 */
Request *parse_request(const char *data) {
    if (strstr(data, "HTTP")) {
        return _parse_http(data);
    } else {
        return _parse_raw(data);
    }
}

Request *_parse_http(const char *data) {
    char *start = strstr(data, "\r\n\r\n");
    Request *request;
    if (start) {
        start += 4;
        request = _parse_raw(start);
        request->type = HTTP;
        return request;
    }
    request = malloc(sizeof(Request));
    request->type = HTTP_ERROR;
    return request;
}

Request *_parse_raw(const char *data) {
    char *tmp = strdup(data);
    char *start = tmp;
    int count = 0;
    str_strip(start);//right strip `\n` and ` `
    while (strsep(&start, "&")) {
        count++;
    }
    start = tmp;
    char *key;
    char *value;
    Request *request = malloc(sizeof(Request));
    request->time = 0;
    while (count--) {
        key = value = start;
        start += strlen(start) + 1;
        strsep(&value, "=");
        if (!strcmp(key, "key")) {
            if (value) {
                request->key = strdup(value);
            }
        } else if (!strcmp(key, "time")) {
            int time = atoi(value);
            request->time = time;
        }
    }
    request->type = RAW;
    if (!request->time) {
        request->time = 1;
    }
    free(tmp);
    return request;
}

void free_request(Request *request) {
    if (request->addr) {
        free(request->addr);
    }
    if (request->key) {
        free(request->key);
    }
    free(request);
}

void str_strip(char *str) {
    size_t len = strlen(str);
    char *end = str + len - 1;
    if (*end == '\n' || *end == ' ') {
        *end = 0;
        str_strip(str);
    }
}

