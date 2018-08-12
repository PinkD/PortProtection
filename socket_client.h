
#ifndef PORT_PROTECTION_SOCKET_CLIENT_H
#define PORT_PROTECTION_SOCKET_CLIENT_H

#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include "request_handler.h"
#include "authorization.h"
#include "debug.h"


// OpenSSL Code Reference: TLS support in https://wiki.openssl.org/index.php/Simple_TLS_Server

const static int BUFFER_SIZE = 2048;

const static char *RESPONSE_HTTP_OK = "HTTP/1.0 200 OK\r\nContent-Length: %d\r\nConnection: close\r\n\r\n%s";
const static char *RESPONSE_RAW_OK = "OK\r\n%s\r\n";

const static char *RESPONSE_HTTP_BAD_REQUEST = "HTTP/1.0 400 Bad Request\r\nContent-Length: 7\r\nConnection: close\r\n\r\nERROR\r\n";
const static char *RESPONSE_RAW_BAD_REQUEST = "ERROR\r\n";

typedef union {
    int data;
    void *ptr;
} Converter;

static SSL_CTX *ctx;
int sock;

void _init_openssl();

void _cleanup_openssl();

SSL_CTX *_create_context();

void _configure_context(SSL_CTX *ctx, char *cert_path, char *key_path);

int create_socket_with_port(ushort port);

void socket_daemon(int socket);

void handle_accept(int client);

void run_socket_client(ushort port, char *cert, char *key);

char *addr_to_ip_str(struct in_addr addr);

#endif