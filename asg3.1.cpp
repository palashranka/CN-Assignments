#include <stdio.h>

int main() {
    int a, b, c, d;
    char extra;

    printf("Definition of Subnetting:\n");
    printf("Subnetting is the process of dividing a large network into\n");
    printf("smaller logical subnetworks to improve performance, security,\n");
    printf("and efficient utilization of IP addresses.\n\n");

    printf("Definition of Subnet Mask:\n");
    printf("A subnet mask is a 32-bit number used to separate the network\n");
    printf("portion and the host portion of an IP address.\n\n");

    printf("Loopback Address:\n");
    printf("127.0.0.1 is called the loopback address. It is a special\n");
    printf("network connection that allows a computer to send data to\n");
    printf("itself for testing and local communication.\n\n");

    printf("Purpose of Subnetting:\n");
    printf("1. Efficient utilization of IP addresses.\n");
    printf("2. Reduces network congestion.\n");
    printf("3. Improves network security.\n");
    printf("4. Simplifies network management.\n\n");

    printf("Enter an IP Address (e.g. 192.168.1.10): ");

    if (scanf("%d.%d.%d.%d%c", &a, &b, &c, &d, &extra) != 5 ||
        (extra != '\n' && extra != ' ' && extra != '\t') ||
        a < 0 || a > 255 ||
        b < 0 || b > 255 ||
        c < 0 || c > 255 ||
        d < 0 || d > 255) {

        printf("\nInvalid IP Address!\n");
        return 0;
    }

    printf("\nEntered IP Address : %d.%d.%d.%d\n\n", a, b, c, d);

    if (a == 0) {
        printf("0.0.0.0/8 is reserved for special purposes.\n");
        printf("It is not treated as a normal Class A network.\n");
        return 0;
    }

    if (a == 127) {
        printf("127.0.0.0 - 127.255.255.255 is the Loopback range.\n");
        printf("It is reserved for communication within the local computer.\n");
        return 0;
    }

    if (a == 255 && b == 255 && c == 255 && d == 255) {
        printf("255.255.255.255 is the Limited Broadcast Address.\n");
        printf("It is used to broadcast packets to all hosts on the local network.\n");
        return 0;
    }

    printf("----------------------------------------------------------------------------------------------------------------------------\n");
    printf("| Class | First Octet | Binary Prefix | IP Range                    | Subnet Mask   | Hosts/Network | Networks |\n");
    printf("----------------------------------------------------------------------------------------------------------------------------\n");

    if (a >= 1 && a <= 126) {

        long long totalHosts = 1LL << 24;
        long long hosts = totalHosts - 2;
        long long networks = 126;

        printf("|   A   |   1-126     |   0xxxxxxx    | 1.0.0.0 - 126.255.255.255 | 255.0.0.0     | %13lld | %8lld |\n",
               hosts, networks);

        printf("----------------------------------------------------------------------------------------------------------------------------\n");

        printf("\nExplanation:\n");
        printf("Host Bits          : 24\n");
        printf("Total Hosts        : 2^24 = %lld\n", totalHosts);
        printf("Usable Hosts       : %lld - 2 = %lld\n", totalHosts, hosts);
        printf("Reason for -2:\n");
        printf("1. First IP is reserved as the Network Address.\n");
        printf("2. Last IP is reserved as the Broadcast Address.\n");
        printf("Number of Networks : 126 usable Class A networks\n");
    }

    else if (a >= 128 && a <= 191) {

        long long totalHosts = 1LL << 16;
        long long hosts = totalHosts - 2;
        long long networks = 1LL << 14;

        printf("|   B   | 128-191     |   10xxxxxx    | 128.0.0.0 - 191.255.255.255 | 255.255.0.0   | %13lld | %8lld |\n",
               hosts, networks);

        printf("----------------------------------------------------------------------------------------------------------------------------\n");

        printf("\nExplanation:\n");
        printf("Host Bits          : 16\n");
        printf("Total Hosts        : 2^16 = %lld\n", totalHosts);
        printf("Usable Hosts       : %lld - 2 = %lld\n", totalHosts, hosts);
        printf("Reason for -2:\n");
        printf("1. First IP is reserved as the Network Address.\n");
        printf("2. Last IP is reserved as the Broadcast Address.\n");
        printf("Number of Networks : 2^14 = %lld\n", networks);
    }

    else if (a >= 192 && a <= 223) {

        long long totalHosts = 1LL << 8;
        long long hosts = totalHosts - 2;
        long long networks = 1LL << 21;

        printf("|   C   | 192-223     |   110xxxxx    | 192.0.0.0 - 223.255.255.255 | 255.255.255.0 | %13lld | %8lld |\n",
               hosts, networks);

        printf("----------------------------------------------------------------------------------------------------------------------------\n");

        printf("\nExplanation:\n");
        printf("Host Bits          : 8\n");
        printf("Total Hosts        : 2^8 = %lld\n", totalHosts);
        printf("Usable Hosts       : %lld - 2 = %lld\n", totalHosts, hosts);
        printf("Reason for -2:\n");
        printf("1. First IP is reserved as the Network Address.\n");
        printf("2. Last IP is reserved as the Broadcast Address.\n");
        printf("Number of Networks : 2^21 = %lld\n", networks);
    }

    else if (a >= 224 && a <= 239) {

        printf("|   D   | 224-239     |   1110xxxx    | 224.0.0.0 - 239.255.255.255 | N/A           | Multicast     | N/A      |\n");
        printf("----------------------------------------------------------------------------------------------------------------------------\n");

        printf("\nClass D is reserved for Multicast communication.\n");
        printf("No host or network calculation is applicable.\n");
    }

    else if (a >= 240 && a <= 254) {

        printf("|   E   | 240-254     |   1111xxxx    | 240.0.0.0 - 254.255.255.255 | N/A           | Experimental  | N/A      |\n");
        printf("----------------------------------------------------------------------------------------------------------------------------\n");

        printf("\nClass E is reserved for Experimental purposes.\n");
        printf("No host or network calculation is applicable.\n");
    }

    else {
        printf("Invalid IP Address!\n");
    }

    return 0;
}
