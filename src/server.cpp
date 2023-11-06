#include <iostream>
#include "webserver.h"
#include <string>
#include <fstream>
#include <sstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

const int PORT = 8081;

std::string getMimeType(const std::string& fileExt) {
    if (fileExt == "html") {
        return "text/html";
    } else if (fileExt == "css") {
        return "text/css";
    }
    return "text/plain";
}

void handleClient(int clientSocket) {
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    
    // Receive the HTTP request from the client
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytesRead < 0) {
        std::cerr << "Error receiving data from the client" << std::endl;
        return;
    }

    // Parse the HTTP request
    std::istringstream request(buffer);
    std::string method, path, version;
    request >> method >> path >> version;

    if (method != "GET") {
        // We only support GET requests
        std::string response = "HTTP/1.1 405 Method Not Allowed\r\n\r\n";
        send(clientSocket, response.c_str(), response.size(), 0);
        close(clientSocket);
        return;
    }

    // Remove the leading '/' from the path
    path = path.substr(1);

    // Serve index.html by default if no path is specified
    if (path.empty()) {
        path = "index.html";
    }

    // Try to open and send the requested file
    std::ifstream file(path, std::ios::in | std::ios::binary);
    if (!file) {
        std::string response = "HTTP/1.1 404 Not Found\r\n\r\n";
        send(clientSocket, response.c_str(), response.size(), 0);
    } else {
        std::string response = "HTTP/1.1 200 OK\r\n";
        std::string fileExt = path.substr(path.find_last_of('.') + 1);
        response += "Content-Type: " + getMimeType(fileExt) + "\r\n";
        std::stringstream content;
        content << file.rdbuf();
        response += "Content-Length: " + std::to_string(content.str().size()) + "\r\n\r\n" + content.str();
        send(clientSocket, response.c_str(), response.size(), 0);
    }

    close(clientSocket);
}

int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Error binding socket" << std::endl;
        return 1;
    }

    if (listen(serverSocket, 5) < 0) {
        std::cerr << "Error listening on socket" << std::endl;
        return 1;
    }

    std::cout << "Server is listening on port " << PORT << std::endl;

    while (true) {
        struct sockaddr_in clientAddress;
        socklen_t clientAddressLength = sizeof(clientAddress);
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);
        if (clientSocket < 0) {
            std::cerr << "Error accepting client connection" << std::endl;
            continue;
        }
        
        handleClient(clientSocket);
    }

    close(serverSocket);
    return 0;
}
