
#include "config_parser.h"


Argument *parse_config(char *argv0, char *file) {
    Argument *arg = malloc(sizeof(Argument));
    FILE *f = fopen(file, "r");
    if (!f) {
        arg->error_code = BAD_CONFIG_FILE;
        return arg;
    }
    int argc = 1;
    char **argv = malloc(sizeof(char *) * (MAX_PARAM_LEN + 1));
    char *line = read_line(f);
    argv[0] = argv0;
    while (line) {
        if (*line != '#') {
            char *value = line;
            char *key = strsep(&value, " ");
            if (key) {
                *(argv + argc) = malloc(strlen(key) + 3);
                strcpy(*(argv + argc), "--");
                strcpy(*(argv + argc) + 2, key);
                argc++;
                if (value) {
                    *(argv + argc) = malloc(strlen(value) + 1);
                    strcpy(*(argv + argc), value);
                    argc++;
                }
            }
        }
        free(line);
        line = read_line(f);
    }
    arg = parse_args(argc, argv);
    for (int i = 1; i < MAX_PARAM_LEN + 1; i++) {
        free(*(argv + i));
    }
    free(argv);
    return arg;
}

char *read_line(FILE *f) {
    char *line = malloc(sizeof(char) * LINE_LEN);
    int len = 0;
    char ch = 0;
    while (len < LINE_LEN && (ch = (char) fgetc(f)) != '\n' && ch != EOF) {
        *(line + len) = ch;
        len++;
    }
    *(line + len) = 0;
    if (len) {
        return line;
    } else {
        free(line);
        return NULL;
    }
}
