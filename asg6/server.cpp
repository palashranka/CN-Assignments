
#include <iostream>
#include <cstring>
#include <winsock2.h>
using namespace std;

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080

int main()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET serverSocket;
    char buffer[1024];

    sockaddr_in server{}, client{};
    int clientSize = sizeof(client);

    // Create UDP socket
    serverSocket = socket(AF_INET, SOCK_DGRAM, 0);

    // Set server address
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // Bind socket
    if (bind(serverSocket, (sockaddr *)&server,
             sizeof(server)) == SOCKET_ERROR)
    {
        cout << "Bind failed: " << WSAGetLastError() << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    cout << "UDP Server waiting..." << endl;

    while (true)
    {
        // Receive operation and string
        int bytes = recvfrom(serverSocket, buffer, 1023, 0,
                             (sockaddr *)&client, &clientSize);

        if (bytes == SOCKET_ERROR)
        {
            cout << "Receive failed: " << WSAGetLastError() << endl;
            break;
        }

        buffer[bytes] = '\0';

        char operation = buffer[0];
        string result = buffer + 1;

        if (operation == '1')
        {
            for (int i = 0; result[i] != '\0'; i++)
            {
                if (result[i] >= 'A' && result[i] <= 'Z')
                    result[i] = result[i] + 32;
            }
        }
        else if (operation == '2')
        {
            int left = 0;
            int right = (int)result.length() - 1;

            while (left < right)
            {
                char temp = result[left];
                result[left] = result[right];
                result[right] = temp;
                left++;
                right--;
            }
        }

        // Send result to the client that sent this request
        if (sendto(serverSocket, result.c_str(),
                   (int)result.length(), 0,
                   (sockaddr *)&client, clientSize) == SOCKET_ERROR)
        {
            cout << "Send failed: " << WSAGetLastError() << endl;
        }

        cout << "Result: " << result << endl;
    }

    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
