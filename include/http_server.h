#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

struct http_server
{
    int socket_;
    int port_;
};

void init_server(struct http_server* server, unsigned short port);

#endif
