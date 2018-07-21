
#include "help.h"

void print_help(char *name) {
    printf("PortProtection: \n"
                   "\tA program to protect port with iptables by authorizing client on another port\n");
    printf("Usage: %s \n"
                   "\t-p, --port <listen port>\n"
                   "\t-pp, --protect <protect port>\n"
                   "\t-i, --interface <interface>\n"
                   "\t-k, --key <key>\n"
                   "\t-f, --file <key file>\n"
                   "\t-cf, --cert-file <ssl cert file>\n"
                   "\t-kf, --key-file <ssl key file>\n"
                   "\t-t, --tcp\n"
                   "\t-u, --udp\n"
                   "\t-v, --verbose\n", name
    );
    printf("Options explanation:\n"
                   "\t-p\tlisten port\n"
                   "\t-pp\tprotect port\n"
                   "\t-i\tbind interface\n"
                   "\t-k\tauthorization key\n"
                   "\t-f\tfile with authorization key(optional)\n"
                   "\t-cf\tssl cert file\n"
                   "\t-kf\tssl key file\n"
                   "\t-t\ttcp protocol(default)\n"
                   "\t-u\tudp protocol\n"
                   "\t-v\tshow verbose/debug messages\n"
    );
}

void print_run_as_root() {
    printf("Please run this command as root\n");
}

void print_error(ParseErrorCode error_code) {
    switch (error_code) {
        case NOT_ENOUGH_ARG:
            break;
        case BAD_CONFIG_FILE:
            printf("bad config file\n");
            break;
        case BAD_PORT_NUMBER:
            printf("bad port number\n");
            break;
        case UNKNOWN_PARAM:
            printf("unknown parameter detected\n");
            break;
        case UNKNOWN_ERROR:
        default:
            printf("unknown error\n");
            break;
    }
}

