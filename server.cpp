#include <iostream>
#include <cstring>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <ctime>
#include <sstream>

#pragma comment(lib, "ws2_32.lib")

#define PORT 5000

std::string getCurrentTime() {
    std::time_t now = std::time(nullptr);
    char buf[100];

    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return std::string(buf);
}

int main() {
    WSADATA wsa;
    int wsa_result = WSAStartup(MAKEWORD(2,2), &wsa);
    if (wsa_result != 0) {
        std::cout << "WSAStartup failed: " << wsa_result << std::endl;
        return -1;
    }

    SOCKET server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == INVALID_SOCKET) {
        std::cout << "Socket failed: " << WSAGetLastError() << std::endl;
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) == SOCKET_ERROR) {
        std::cout << "Bind failed: " << WSAGetLastError() << std::endl;
        return -1;
    }

    // Listen
    if (listen(server_fd, 3) == SOCKET_ERROR) {
        std::cout << "Listen failed: " << WSAGetLastError() << std::endl;
        return -1;
    }

    std::cout << "Server listening...\n";

    // Accept
    new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
    if (new_socket == INVALID_SOCKET) {
        std::cout << "Accept failed: " << WSAGetLastError() << std::endl;
        return -1;
    }

    std::cout << "Client connected\n";

    // Step 1: Receive SYN
    recv(new_socket, buffer, 1024, 0);
    if (strcmp(buffer, "SYN") == 0) {
        std::cout << "Received SYN\n";

        // Step 2: Send SYN-ACK
        send(new_socket, "SYN-ACK", strlen("SYN-ACK"), 0);
        std::cout << "Sent SYN-ACK\n";

        memset(buffer, 0, sizeof(buffer));

        // Step 3: Receive ACK
        recv(new_socket, buffer, 1024, 0);
        if (strcmp(buffer, "ACK") == 0) {
            std::cout << "Handshake complete ✅\n";

            // Data exchange
            send(new_socket, "Hello from Server", 18, 0);

            memset(buffer, 0, sizeof(buffer));
            while (true) {
                 memset(buffer, 0, sizeof(buffer));

                int bytes = recv(new_socket, buffer, 1024, 0);
                if (bytes <= 0) {
                    std::cout << "Client disconnected\n";
                    break;
    }

    std::cout << "Received: " << buffer
              <<" | SERVER_TIME: " << getCurrentTime()
              << std::endl;
}
        }
    }

    closesocket(new_socket);
    closesocket(server_fd);
    WSACleanup();

    return 0;
}