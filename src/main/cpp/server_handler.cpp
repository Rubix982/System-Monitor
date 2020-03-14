//
// Created by saif on 3/14/20.
//

#include <server_handler.h>
#include <cstdlib>
#include <cstring>
#include "server_handler.h"

int server_handler::receive_data_from_server() {

    if ( recv(socket_desc, server_reply, server_reply.length(), 0) < 0) return 1;

    fprintf(stdin, "Data received.\n");
    puts(server_reply);

    return 0;
}

int server_handler::connect_to_ip_addr() {
    // Create a socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if ( socket_desc == - 1 ) printf("Could not create socket.\n");

    // Connect to a remote server
    if ( connect(socket_desc, ( struct sockaddr *) & server, sizeof(server)) < 0 ) return 1;
    else return 0;
}

int server_handler::send_data_to_server(const string &message) {
    if ( send(socket_desc, message.c_str(), message.length(), 0 ) < 0 ) return 1;
    return 0;
}

void server_handler::see_total_packets_detail() {

    fprintf(stdout, "PINGING: ")

}

server_handler::server_handler(const string &hostname) {
    char ip[100];

    if (( base_entry_data = gethostbyname( hostname.c_str() ) ) == nullptr )
    {
        // gethostbyname failed
        string err_tmp = "gethostbyname";
        herror(err_tmp.c_str());
        fprintf(stderr, "gethostbyname failed. Exiting process.\n");
        exit(1);
    }

    // Cast the h_addr_list to in_addr, since h_addr_list
    // also has the ip address in long format only

    addr_list = (struct in_addr **)  &base_entry_data->h_addr_list;

    for ( int i = 0; addr_list[i] != nullptr; ++i )
    {
        // return the first one
        strcpy(ip, inet_ntoa(*addr_list[i]));
    }

    fprintf(stdout, "%s resolved to: %s", hostname.c_str(), ip);

    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_family = AF_INET;
    server.sin_port = htons(80);
    class_ip_addr = ip;

    // Bind code together for socket description
}

int server_handler::bind_and_listen() {

    // Edit the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );

    // Bind to ip_addr
    if ( bind( socket_desc, (struct sockaddr *) & server, sizeof(server)) < 0 ) return 1;

    // Now that we are binded to a port, we can listen it through our socket
    listen(socket_desc, 3);

    // Accept incoming connection
    printf("Waiting for incoming connections.\n");
    int sizeof_struct = sizeof(struct sockaddr_in);
    int new_socket = accept(socket_desc, ( struct sockaddr *) & client, (socklen_t*)& sizeof_struct );

    if ( new_socket < 0 ) perror("accept");

    puts("connection accepted");

    return 0;
}
