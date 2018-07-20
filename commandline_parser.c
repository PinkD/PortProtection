#include "commandline_parser.h"

bool check_interface(char *interface) {
    char *cmd = "ls /sys/class/net";
    FILE *f = popen(cmd, "r");
    char *tmp = malloc(MAX_STR_LEN + 1);
    if (verbose) {
        printf("Checking interface...");
    }
    if (f) {
        while (~fscanf(f, "%s", tmp)) {
            if (!strcmp(tmp, interface)) {
                free(tmp);
                if (verbose) {
                    printf("OK\n");
                }
                fclose(f);
                return true;
            }
        }
        fclose(f);
    }
    if (verbose) {
        printf("Failed\n");
    }
    free(tmp);
    return false;
}

char *read_key(char *path) {
    char *key = malloc(MAX_STR_LEN + 1);
    FILE *f = fopen(path, "r");
    int ret = fscanf(f, "%s", key);
    fclose(f);
    if (ret < 0 || ret > MAX_STR_LEN) {
        free(key);
        return 0;
    } else {
        return key;
    }
}

Argument *parse_args(int argc, char *argv[]) {
    Argument *arg = malloc(sizeof(Argument));
    arg->error_code = OK;
    if (argc < 13 && argc != 3) {//not enough arg, the second condition is for `-c`
        arg->error_code = NOT_ENOUGH_ARG;
        return arg;
    }
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-c") || !strcmp(argv[i], "--config")) {
            arg = parse_config(argv[0], argv[++i]);
            break;
        } else if (!strcmp(argv[i], "-v") || !strcmp(argv[i], "--verbose")) {
            arg->verbose = true;
        } else if (!strcmp(argv[i], "-p") || !strcmp(argv[i], "--port")) {
            ushort port = (ushort) atoi(argv[++i]);
            if (port) {
                arg->listen_port = port;
            } else {
                arg->error_code = BAD_PORT_NUMBER;
                return arg;
            }
        } else if (!strcmp(argv[i], "-pp") || !strcmp(argv[i], "--protect-port")) {
            ushort port = (ushort) atoi(argv[++i]);
            if (port) {
                arg->protect_port = port;
            } else {
                arg->error_code = BAD_PORT_NUMBER;
                return arg;
            }
        } else if (!strcmp(argv[i], "-i") || !strcmp(argv[i], "--interface")) {
            char *tmp = argv[++i];
            char *interface = malloc(strlen(tmp) + 1);
            strcpy(interface, tmp);
            if (check_interface(interface)) {
                arg->interface_name = interface;
            } else {
                arg->error_code = BAD_INTERFACE;
                free(interface);
                return arg;
            }
        } else if (!strcmp(argv[i], "-k") || !strcmp(argv[i], "--key")) {
            char *tmp = argv[++i];
            size_t len = strlen(tmp);
            if (len > MAX_STR_LEN) {
                arg->error_code = BAD_KEY_TOO_LONG;
                return arg;
            }
            char *key = malloc(len + 1);
            strcpy(key, tmp);
            arg->key = key;
        } else if (!strcmp(argv[i], "-f") || !strcmp(argv[i], "--file")) {
            char *key = read_key(argv[++i]);
            if (key) {
                arg->key = key;
            } else {
                arg->error_code = BAD_KEY_FILE;
                return arg;
            }
        } else if (!strcmp(argv[i], "-cf") || !strcmp(argv[i], "--cert-file")) {
            char *tmp = argv[++i];
            char *cert_file = malloc(strlen(tmp) + 1);
            strcpy(cert_file, tmp);
            arg->cert_file = cert_file;
        } else if (!strcmp(argv[i], "-kf") || !strcmp(argv[i], "--key-file")) {
            char *tmp = argv[++i];
            char *key_file = malloc(strlen(tmp) + 1);
            strcpy(key_file, tmp);
            arg->key_file = key_file;
        } else {
            arg->error_code = UNKNOWN_PARAM;
            return arg;
        }
    }
    return arg;
}

void free_arg(Argument *arg) {
    free(arg->key);
    free(arg->interface_name);
    free(arg->cert_file);
    free(arg->key_file);
    free(arg);
}

void print_arg(Argument *arg) {
    printf("protect port `%d` with port `%d` on interface `%s` with key `%s`, cert file %s, private key file %s",
           arg->protect_port,
           arg->listen_port,
           arg->interface_name,
           arg->key,
           arg->cert_file,
           arg->key_file
    );
    if (arg->verbose) {
        printf(", verbose\n");
    } else {
        printf("\n");
    }
}
