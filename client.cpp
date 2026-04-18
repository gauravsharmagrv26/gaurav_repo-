#include <iostream>
#include <cstring>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
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

    SOCKET sock;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        std::cout << "Socket creation error: " << WSAGetLastError() << std::endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IP
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cout << "Invalid address\n";
        return -1;
    }

    // Connect
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR) {
        std::cout << "Connection Failed: " << WSAGetLastError() << std::endl;
        return -1;
    }

    // Step 1: Send SYN
    send(sock, "SYN", strlen("SYN"), 0);
    std::cout << "Sent SYN\n";

    // Step 2: Receive SYN-ACK
    recv(sock, buffer, 1024, 0);
    if (strcmp(buffer, "SYN-ACK") == 0) {
        std::cout << "Received SYN-ACK\n";

        // Step 3: Send ACK
        send(sock, "ACK", strlen("ACK"), 0);
        std::cout << "Handshake complete ✅\n";

        /* Data exchange
        memset(buffer, 0, sizeof(buffer));
        recv(sock, buffer, 1024, 0);
        std::cout << "Server says: " << buffer << std::endl;

        send(sock, "Hello from Client", 18, 0);*/

        // Continuous Data Sending
        while (true) {
            int value = rand() % 100;

            std::string msg = "DATA:" + std::to_string(value) +
                              " | TIME:" + getCurrentTime();

            send(sock, msg.c_str(), msg.size(), 0);
            std::cout << "Sent: " << msg << std::endl;

            Sleep(1000);
        }

    }

    closesocket(sock);
    WSACleanup();

    return 0;
}