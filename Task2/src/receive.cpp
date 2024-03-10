#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <iot/socket.hpp>

int main() {
    const char* server_ip = "192.168.1.9"; // Server's IP address
    const int server_port = 8877; // Server's port
    char buffer[1024]; // Buffer to store incoming messages

    // Create a UDP socket
    uwe::socket sock(AF_INET, SOCK_DGRAM, 0);

    // Create server address structure
    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    inet_pton(AF_INET, server_ip, &server_addr.sin_addr); // Server's IP
    server_addr.sin_port = htons(server_port);

    // Bind the socket to the server address
    if (sock.bind((struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Bind failed" << std::endl;
        return 1;
    }

    std::cout << "Server is listening on IP " << server_ip << " port " << server_port << std::endl;

    while (true) {
        sockaddr_in client_addr;
        size_t client_addr_len = sizeof(client_addr);

        // Receive a message from a client
        ssize_t msg_len = sock.recvfrom(buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&client_addr, &client_addr_len);

        if (msg_len < 0) {
            std::cerr << "Error receiving message" << std::endl;
            continue;
        }

        // Null-terminate the received message
        buffer[msg_len] = '\0';

        // Print the received message and sender's address
        std::cout << "Received message: " << buffer << " from " << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port) << std::endl;

        // Echo back the received message to the client
        if (sock.sendto(buffer, msg_len, 0, (struct sockaddr*)&client_addr, client_addr_len) < 0) {
            std::cerr << "Error sending message" << std::endl;
        }
    }

    return 0;
}
