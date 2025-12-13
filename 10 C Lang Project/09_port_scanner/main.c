#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#define SOCKET int
#define INVALID_SOCKET -1
#define closesocket close
#endif

#define MAX_PORTS 1000
#define TIMEOUT 3

// Function prototypes
void init_winsock();
void cleanup_winsock();
void scan_port(char* target, int port);
void scan_range(char* target, int start_port, int end_port);
void scan_common_ports(char* target);
void print_menu();

#ifdef _WIN32
void init_winsock() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        printf("WSAStartup failed\n");
        exit(1);
    }
}

void cleanup_winsock() {
    WSACleanup();
}
#endif

int main() {
    int choice;
    char target[256];
    int port, start_port, end_port;
    char continueOperation;

    #ifdef _WIN32
    init_winsock();
    #endif
    
    printf("Welcome to the Network Port Scanner!\n");
    printf("Note: This tool is for educational purposes only.\n");
    printf("Only scan systems you own or have explicit permission to scan.\n");

    do {
        print_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Scan single port
                printf("Enter target IP or hostname: ");
                scanf("%s", target);
                printf("Enter port number: ");
                scanf("%d", &port);
                scan_port(target, port);
                break;

            case 2: // Scan port range
                printf("Enter target IP or hostname: ");
                scanf("%s", target);
                printf("Enter start port: ");
                scanf("%d", &start_port);
                printf("Enter end port: ");
                scanf("%d", &end_port);
                scan_range(target, start_port, end_port);
                break;

            case 3: // Scan common ports
                printf("Enter target IP or hostname: ");
                scanf("%s", target);
                scan_common_ports(target);
                break;

            case 4: // Exit
                printf("Thank you for using the Network Port Scanner!\n");
                #ifdef _WIN32
                cleanup_winsock();
                #endif
                exit(0);

            default:
                printf("Invalid choice! Please select a valid option.\n");
        }

        printf("\nDo you want to perform another scan? (y/n): ");
        scanf(" %c", &continueOperation);
        printf("\n");

    } while (continueOperation == 'y' || continueOperation == 'Y');

    return 0;
}

// Function to scan a single port
void scan_port(char* target, int port) {
    struct sockaddr_in addr;
    SOCKET sock;
    
    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        #ifdef _WIN32
        printf("Socket creation failed: %d\n", WSAGetLastError());
        #else
        printf("Socket creation failed: %s\n", strerror(errno));
        #endif
        return;
    }
    
    // Set up address structure
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    
    // Resolve hostname to IP address
    struct hostent *host_entry;
    host_entry = gethostbyname(target);
    if (host_entry == NULL) {
        // Try to convert target directly as IP address
        if (inet_aton(target, &addr.sin_addr) == 0) {
            printf("Invalid hostname or IP address: %s\n", target);
            #ifdef _WIN32
            closesocket(sock);
            #else
            close(sock);
            #endif
            return;
        }
    } else {
        // Copy IP address from host entry
        memcpy(&addr.sin_addr, host_entry->h_addr_list[0], host_entry->h_length);
    }
    
    // Connect to the port
    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        printf("Port %d: CLOSED\n", port);
    } else {
        printf("Port %d: OPEN\n", port);
    }
    
    #ifdef _WIN32
    closesocket(sock);
    #else
    close(sock);
    #endif
}

// Function to scan a range of ports
void scan_range(char* target, int start_port, int end_port) {
    if (start_port < 1 || end_port > 65535 || start_port > end_port) {
        printf("Invalid port range! Ports must be between 1-65535.\n");
        return;
    }
    
    printf("Scanning ports %d to %d on %s...\n", start_port, end_port, target);
    printf("Port\tStatus\n");
    printf("------------\n");
    
    for (int port = start_port; port <= end_port; port++) {
        struct sockaddr_in addr;
        SOCKET sock;
        
        // Create socket
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == INVALID_SOCKET) {
            continue;  // Skip this port if socket creation fails
        }
        
        // Set up address structure
        memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        
        // Resolve hostname to IP address
        struct hostent *host_entry;
        host_entry = gethostbyname(target);
        if (host_entry == NULL) {
            // Try to convert target directly as IP address
            if (inet_aton(target, &addr.sin_addr) == 0) {
                #ifdef _WIN32
                closesocket(sock);
                #else
                close(sock);
                #endif
                continue;  // Skip this port if invalid target
            }
        } else {
            // Copy IP address from host entry
            memcpy(&addr.sin_addr, host_entry->h_addr_list[0], host_entry->h_length);
        }
        
        // Connect to the port
        if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
            // Port is closed
        } else {
            printf("%d\tOPEN\n", port);
        }
        
        #ifdef _WIN32
        closesocket(sock);
        #else
        close(sock);
        #endif
    }
    
    printf("Scan complete.\n");
}

// Function to scan common ports
void scan_common_ports(char* target) {
    int common_ports[] = {
        21, 22, 23, 25, 53, 80, 110, 111, 135, 139, 
        143, 443, 445, 993, 995, 1723, 3306, 3389, 5900, 8080
    };
    int num_ports = sizeof(common_ports) / sizeof(common_ports[0]);
    
    printf("Scanning common ports on %s...\n", target);
    printf("Port\tService\t\tStatus\n");
    printf("---------------------------\n");
    
    char* services[] = {
        "FTP", "SSH", "Telnet", "SMTP", "DNS", "HTTP", "POP3", "RPCbind", "MS RPC", "NetBIOS",
        "IMAP", "HTTPS", "SMB", "IMAPS", "POP3S", "PPTP", "MySQL", "RDP", "VNC", "HTTP Proxy"
    };
    
    for (int i = 0; i < num_ports; i++) {
        int port = common_ports[i];
        struct sockaddr_in addr;
        SOCKET sock;
        
        // Create socket
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == INVALID_SOCKET) {
            continue;  // Skip this port if socket creation fails
        }
        
        // Set up address structure
        memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        
        // Resolve hostname to IP address
        struct hostent *host_entry;
        host_entry = gethostbyname(target);
        if (host_entry == NULL) {
            // Try to convert target directly as IP address
            if (inet_aton(target, &addr.sin_addr) == 0) {
                #ifdef _WIN32
                closesocket(sock);
                #else
                close(sock);
                #endif
                continue;  // Skip this port if invalid target
            }
        } else {
            // Copy IP address from host entry
            memcpy(&addr.sin_addr, host_entry->h_addr_list[0], host_entry->h_length);
        }
        
        // Connect to the port
        if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
            printf("%d\t%-12s\tCLOSED\n", port, services[i]);
        } else {
            printf("%d\t%-12s\tOPEN\n", port, services[i]);
        }
        
        #ifdef _WIN32
        closesocket(sock);
        #else
        close(sock);
        #endif
    }
    
    printf("Scan complete.\n");
}

// Function to print the menu
void print_menu() {
    printf("\n===== Network Port Scanner =====\n");
    printf("1. Scan single port\n");
    printf("2. Scan port range\n");
    printf("3. Scan common ports\n");
    printf("4. Exit\n");
    printf("==============================\n");
}