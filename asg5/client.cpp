#include <iostream>
#include <cstring>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

#define PORT 8081

int main()
{
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        cerr << "Winsock initialization failed!" << endl;
        return 1;
    }

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET)
    {
        cerr << "Socket creation failed! Error: " << WSAGetLastError() << endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    server.sin_port = htons(PORT);

    if (connect(clientSocket, (sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
    {
        cerr << "Connection failed! Error: " << WSAGetLastError()
             << ". Make sure server.exe is running on port " << PORT << "." << endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    cout << "Connected to server. Type exit to quit." << endl;
    char buffer[1024];

    while (true)
    {
        cout << "You: ";
        if (!cin.getline(buffer, sizeof(buffer)))
            break;

        int messageLength = static_cast<int>(strlen(buffer));
        if (send(clientSocket, buffer, messageLength, 0) == SOCKET_ERROR)
        {
            cerr << "Send failed! Error: " << WSAGetLastError() << endl;
            break;
        }

        if (strcmp(buffer, "exit") == 0)
            break;

        int bytes = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytes <= 0)
        {
            if (bytes == SOCKET_ERROR)
                cerr << "Receive failed! Error: " << WSAGetLastError() << endl;
            else
                cout << "Server disconnected." << endl;
            break;
        }

        buffer[bytes] = '\0';
        cout << "Server: " << buffer << endl;

        if (strcmp(buffer, "exit") == 0)
            break;
    }

    closesocket(clientSocket);
    WSACleanup();
    return 0;
}
