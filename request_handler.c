#include "request_handler.h"

Request *handle_request(const char *data) {
    Request *request;
    if (!data) {
        request = malloc(sizeof(Request));
        request->type = RAW_ERROR;
        return request;
    }
    return parse_request(data);
}
