#ifndef webserver_h 
#define webserver_h

#include <string>

void handleClient(int clientSocket);
std::string getMimeType(const std::string& fileExt);

// Additional function declarations
void setupServer(int& serverSocket, int port);
void bindServer(int serverSocket, int port);
void listenServer(int serverSocket, int backlog);
void closeServer(int serverSocket);

#endif
