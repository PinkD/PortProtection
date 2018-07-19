cmake_minimum_required(VERSION 3.5)# cmake's  version in ubuntu 16.04 is 3.5.x
project(PortProtection C)

set(CMAKE_C_STANDARD 11)

link_libraries(ssl crypto pthread)

add_executable(PortProtection
        main.c
        commandline_parser.c
        help.c
        iptables_wrapper.c
        permission.c
        socket_client.c
        handle_signal.c
        request_handler.c
        request_parser.c
        authorization.c
        timer.c
        debug.c
        )


#add_executable(PortProtection test.c socket_client.c request_handler.c request_parser.c authorization.c)

