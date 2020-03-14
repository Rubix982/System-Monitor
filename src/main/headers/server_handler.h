//
// Created by saif on 3/14/20.
//

#ifndef SYSTEMMONITOR_SERVER_HANDLER_H
#define SYSTEMMONITOR_SERVER_HANDLER_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string>
#include <stdio.h>

class server_handler {

private:

    // Socket server data
    struct sockaddr_in server{}, client{};

    // hostname resolution
    struct hostent *base_entry_data{};
    struct in_addr **addr_list{};

    // Misc Data
    int socket_desc{};                  // Store socket value
    string class_ip_addr{};             // Get back ip address
    string server_reply{};              // See what the server reply is

public:
    int send_data_to_server(const string& message);
    explicit server_handler(const string&);
    int connect_to_ip_addr();
    int bind_and_listen();
    int receive_data_from_server();
    void see_total_packets_detail();
};

#endif //SYSTEMMONITOR_SERVER_HANDLER_H
