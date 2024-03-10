#include <util.hpp>
#include <iot/socket.hpp>

#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
    // set client IP address
    uwe::set_ipaddr("192.168.1.7");

	const int server_port = 8877;
    const char* server_name = "192.168.1.9";

    sockaddr_in server_address; // data structure for storing IPv4 or IPv6 addresses
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET; // IPv4 address

	// creates binary representation of server name and stores it as sin_addr
	inet_pton(AF_INET, server_name, &server_address.sin_addr);

    // htons: port in network order format
	server_address.sin_port = htons(server_port);

	uwe::socket sock{AF_INET, SOCK_DGRAM, 0};

	// port for client
	const int client_port = 1001;

    // socket address used for the client
	struct sockaddr_in client_address;
	memset(&client_address, 0, sizeof(client_address));
	client_address.sin_family = AF_INET;
	client_address.sin_port = htons(client_port);
	inet_pton(AF_INET, uwe::get_ipaddr().c_str(), &client_address.sin_addr);

	sock.bind((struct sockaddr *)&client_address, sizeof(client_address));

		// data that will be sent to the server
	std::string message = "This is an IOT packet";

    // send data
	int len = sock.sendto(
    message.c_str(), message.length(), 0,
	(sockaddr*)&server_address, sizeof(server_address));

	char buffer[1024];

	while (true) {
        sockaddr_in server_address;
        size_t server_address_len = sizeof(server_address);

        // Receive a message from a client
        ssize_t msg_len = sock.recvfrom(buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&server_address, &server_address_len);

        if (msg_len < 0) {
            std::cerr << "Error receiving message" << std::endl;
            continue;
        }

        // Null-terminate the received message
        buffer[msg_len] = '\0';

        // Print the received message and sender's address
        std::cout << "Echoed back " << buffer << " from " << inet_ntoa(server_address.sin_addr) << ":" << ntohs(server_address.sin_port) << std::endl;

        // Echo back the received message to the client
        if (sock.sendto(buffer, msg_len, 0, (struct sockaddr*)&server_address, server_address_len) < 0) {
            std::cerr << "Error sending message" << std::endl;
        }

    return 0;
}
}