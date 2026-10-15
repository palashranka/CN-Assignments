
#include <iostream>
#include <cstring>
#include <winsock2.h>
#include <ws2tcpip.h>

using namespace std;

#pragma comment(lib, "ws2_32.lib")

#define PORT 8081

int main()
{
    WSADATA wsa;
    SOCKET serverSocket, clientSocket;
    char buffer[1024];

    sockaddr_in server{}, client{};
    int clientSize = sizeof(client);

    // 1. Initialize Winsock
    WSAStartup(MAKEWORD(2, 2), &wsa);

    // 2. Create TCP socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // 3. Set server address
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // 4. Bind socket
    bind(serverSocket, (sockaddr *)&server, sizeof(server));

    // 5. Listen for client
    listen(serverSocket, 5);

    cout << "Server waiting for client..." << endl;

    // 6. Accept connection
    clientSocket = accept(serverSocket,
                          (sockaddr *)&client, &clientSize);

    cout << "Client connected!" << endl;

    // 7. Receive and send messages
    while (true)
    {
        memset(buffer, 0, sizeof(buffer));

        int bytes = recv(clientSocket, buffer,
                         sizeof(buffer) - 1, 0);

        if (bytes <= 0)
        {
            cout << "Client disconnected!" << endl;
            break;
        }

        buffer[bytes] = '\0';
        cout << "Client: " << buffer << endl;

        if (strcmp(buffer, "exit") == 0)
            break;

        cout << "Enter reply: ";
        cin.getline(buffer, sizeof(buffer));

        send(clientSocket, buffer,
             (int)strlen(buffer), 0);

        if (strcmp(buffer, "exit") == 0)
            break;
    }

    // 8. Close sockets
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
