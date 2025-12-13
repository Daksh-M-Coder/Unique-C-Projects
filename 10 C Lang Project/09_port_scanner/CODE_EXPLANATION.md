# Network Port Scanner - Code Explanation

## Program Structure
The network port scanner demonstrates TCP socket programming to check the status of ports on remote hosts. It implements cross-platform networking by using conditional compilation to handle differences between Windows (Winsock) and Unix-like systems (BSD sockets).

## Key Components

### Header Files
```c
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
```
- Conditional compilation handles platform-specific networking APIs
- Windows uses Winsock2 library with specific initialization/cleanup
- Unix systems use standard BSD socket API
- Compatibility macros ensure consistent code across platforms

### Constants
```c
#define MAX_PORTS 1000
#define TIMEOUT 3
```
- `MAX_PORTS`: Maximum number of ports that can be scanned
- `TIMEOUT`: Connection timeout in seconds (not currently implemented)

### Type Definitions
```c
#define SOCKET int
#define INVALID_SOCKET -1
```
- Ensures consistent socket type handling across platforms
- Defines error condition for socket creation

### Function Prototypes
```c
void init_winsock();
void cleanup_winsock();
void scan_port(char* target, int port);
void scan_range(char* target, int start_port, int end_port);
void scan_common_ports(char* target);
void print_menu();
```
- Platform-specific initialization/cleanup functions
- Core scanning functions for different use cases
- User interface functions

## Detailed Code Walkthrough

### Platform Initialization
```c
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
```
- Windows requires explicit initialization of Winsock library
- `WSAStartup` initializes Winsock DLL
- `WSACleanup` releases resources when done
- Not needed on Unix systems

### Main Function
```c
int main() {
    #ifdef _WIN32
    init_winsock();
    #endif
    
    // ... main program loop ...
    
    #ifdef _WIN32
    cleanup_winsock();
    #endif
    exit(0);
}
```
- Initializes networking subsystem on Windows
- Runs main menu-driven loop
- Cleans up networking resources before exit

### Single Port Scanning
```c
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
```

Key aspects:
1. **Socket Creation**: Creates TCP socket for connection
2. **Error Handling**: Platform-specific error reporting
3. **Address Resolution**: Converts hostname to IP address using DNS
4. **Fallback Parsing**: Direct IP address parsing if DNS fails
5. **Connection Attempt**: Uses connect() to test port status
6. **Resource Cleanup**: Properly closes socket on all paths

### Hostname Resolution
```c
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
```
- Uses `gethostbyname()` for DNS resolution
- Falls back to `inet_aton()` for direct IP parsing
- Copies resolved address to socket structure

### Port Range Scanning
```c
void scan_range(char* target, int start_port, int end_port) {
    if (start_port < 1 || end_port > 65535 || start_port > end_port) {
        printf("Invalid port range! Ports must be between 1-65535.\n");
        return;
    }
    
    printf("Scanning ports %d to %d on %s...\n", start_port, end_port, target);
    printf("Port\tStatus\n");
    printf("------------\n");
    
    for (int port = start_port; port <= end_port; port++) {
        // ... similar socket creation and connection logic ...
        
        // Connect to the port
        if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
            // Port is closed (silent for closed ports in range scan)
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
```
- Validates port range parameters
- Iterates through specified port range
- Reports only open ports to reduce output noise
- Follows same connection pattern as single port scan

### Common Ports Scanning
```c
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
        // ... socket creation and connection logic ...
        
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
```
- Predefined array of commonly used service ports
- Corresponding service names for better user experience
- Reports status of all scanned ports
- Useful for quick security assessments

## Cross-Platform Considerations
```c
#ifdef _WIN32
    // Windows-specific code
    closesocket(sock);
#else
    // Unix-specific code
    close(sock);
#endif
```
- Uses conditional compilation for platform-specific APIs
- Consistent interface through macro definitions
- Proper resource cleanup on both platforms

## Error Handling
- Socket creation failures
- Invalid hostname/IP address handling
- Port range validation
- Platform-specific error reporting
- Graceful degradation when possible

## Program Flow
1. Initialize networking subsystem (Windows only)
2. Present menu to user
3. Process user selections:
   - Collect target and port information
   - Perform appropriate scan
   - Display results
4. Clean up networking resources before exit

## Learning Points
1. **Network Programming**: Socket creation and connection
2. **Cross-Platform Development**: Handling platform differences
3. **DNS Resolution**: Hostname to IP address conversion
4. **Error Handling**: Robust error checking and reporting
5. **Resource Management**: Proper socket cleanup
6. **Conditional Compilation**: Platform-specific code compilation

## Limitations and Possible Improvements
1. **No Timeout**: Connections may hang on filtered ports
2. **Sequential Scanning**: Slow for large port ranges
3. **No Stealth Options**: Easily detected by intrusion detection systems
4. **Limited Error Detail**: Basic error reporting only
5. **No Output Formatting Options**: Fixed output format
6. **No Configuration File**: Hard-coded port lists
7. **No Parallel Processing**: Could scan multiple ports simultaneously