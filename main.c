#include "commandline_parser.h"
#include "timer.h"
#include "permission.h"
#include "help.h"
#include "socket_client.h"
#include "handle_signal.h"
#include "debug.h"

//TODO: #enhancement# add UDP support
//TODO: #enhancement# protect multi port with the same port

int main(int argc, char *argv[]) {
    if (!check_root()) {
        print_run_as_root();
        return EXIT_FAILURE;
    }
    Argument *arg = parse_args(argc, argv);
    if (arg->error_code) {
        print_error(arg->error_code);
        print_help(argv[0]);
        free_arg(arg);
        return EXIT_FAILURE;
    }

    init_argument(arg);

    init_iptables(arg);

    handle_signal();//remove iptables rule on exit

    pthread_t *timer_t = start_timer();

    run_socket_client(arg->listen_port, arg->cert_file, arg->key_file);

    pthread_join(*timer_t, NULL);//main loop

    free_arg(arg);
    return EXIT_SUCCESS;
}