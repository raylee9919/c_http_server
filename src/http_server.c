#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>

#include "../include/http_server.h"
#include "../include/ansi_color.h"
#include "../include/error_handling.h"

void print_logo();

void init_server(struct http_server* server, unsigned short port)
{
    server->port_ = port;
    
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
        error_handling("bind() error during server initialization.\n");
    
    if (listen(server_socket, 5) == -1)
        error_handling("listen() error during server initialization.\n");

    server->socket_ = server_socket;

    print_logo();
    printf("HTTP Server Initialized.\n");
    printf("Port: " ANSI_COLOR_YELLOW "%d" ANSI_COLOR_RESET "\n\n", server->port_);
}

void print_logo()
{
    printf(ANSI_COLOR_MAGENTA);
    printf("   _____ ______ _______      ________ _____  \n");
    printf("  / ____|  ____|  __ \\ \\    / /  ____|  __ \\ \n");
    printf(" | (___ | |__  | |__) \\ \\  / /| |__  | |__) |\n");
    printf("  \\___ \\|  __| |  _  / \\ \\/ / |  __| |  _  / \n");
    printf("  ____) | |____| | \\ \\  \\  /  | |____| | \\ \\ \n");
    printf(" |_____/|______|_|  \\_\\  \\/   |______|_|  \\_\\\n");
    printf(ANSI_COLOR_RESET);
}
