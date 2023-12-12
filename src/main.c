#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../include/route.h"
#include "../include/http_server.h"
#include "../include/error_handling.h"
#include "../include/response.h"
#include "../include/ansi_color.h"

void clear_terminal();

int main()
{
    clear_terminal();

    struct http_server server;
    init_server(&server, 6969);

    struct route* tree_root = insert(NULL, "/", "index.html");

    int client_socket;
    char buf[8192];

    while (1)
    {
        if ((client_socket = accept(server.socket_, NULL, NULL)) == -1)
            error_handling("accept() error.\n");

        if (read(client_socket, buf, sizeof(buf)) == -1)
            error_handling("read() error.\n");

        printf("%s\n", buf);

        char* http_header = strtok(buf, "\n");

        char* token = strtok(http_header, " ");

        char* method;
        char* url_key;

        method = token;
        token = strtok(NULL, " ");
        url_key = token;

        printf(ANSI_COLOR_MAGENTA "Method: " ANSI_COLOR_YELLOW "%s" ANSI_COLOR_RESET "\n", method);
        printf(ANSI_COLOR_MAGENTA "Route: " ANSI_COLOR_YELLOW "%s" ANSI_COLOR_RESET "\n\n\n", url_key);

        char* response_data;
        char file_name[1024] = "../static/";
        if (method == NULL || url_key == NULL)
            response_data = render_static_file("../static/404.html");
        else
        {
            struct route* found_route = find(tree_root, url_key);
            if (found_route == NULL)
                response_data = render_static_file("../static/404.html");
            else
            {
                strcat(file_name, found_route->value_);
                response_data = render_static_file(file_name);
            }
        }

        char response_header[8192] = "HTTP/1.1 200 OK\r\n\r\n";
        strcat(response_header, response_data);
        strcat(response_header, "\r\n\r\n");

        write(client_socket, response_header, strlen(response_header));
        close(client_socket);
        free(response_data);
    }

    close(server.socket_);
    return 0;
}

void clear_terminal()
{
    int pid = fork();
    if (pid == 0) {
        char* opt;
        execv("/usr/bin/clear", &opt);
        exit(0);
    } else {
        waitpid(pid, NULL, 0);
    }
}
