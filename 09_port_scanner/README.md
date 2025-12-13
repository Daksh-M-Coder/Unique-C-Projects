# Network Port Scanner

## Description
A network port scanning tool that checks the status of ports on remote hosts. This tool can scan single ports, ranges of ports, or common service ports to determine if they are open or closed. The scanner is designed for educational purposes to understand network connectivity and security concepts.

## Features
- Single port scanning
- Port range scanning
- Common ports scanning (20 popular service ports)
- Cross-platform compatibility (Windows and Unix-like systems)
- Proper error handling and validation
- Service name identification for common ports

## Networking Concepts Demonstrated
1. **TCP Socket Programming**: Creating and using TCP sockets for network connections
2. **Network Address Resolution**: Converting hostnames to IP addresses
3. **Port Scanning Techniques**: Connecting to ports to determine their status
4. **Cross-Platform Networking**: Handling differences between Windows and Unix networking APIs
5. **Error Handling**: Managing network errors and exceptions

## Standard Library Functions Used
- `stdio.h` - For input/output operations (`printf`, `scanf`)
- `stdlib.h` - For standard library functions (`exit`)
- `string.h` - For string operations (`memset`, `memcpy`)
- Platform-specific networking libraries:
  - Windows: `winsock2.h`, `ws2tcpip.h`
  - Unix: `sys/socket.h`, `netinet/in.h`, `arpa/inet.h`, `netdb.h`

## How to Compile and Run

### Compilation on Windows
```bash
gcc -o port_scanner main.c -lws2_32
```

### Compilation on Unix/Linux/macOS
```bash
gcc -o port_scanner main.c
```

### Execution
```bash
./port_scanner
```

On Windows:
```bash
port_scanner.exe
```

## How to Use
1. Run the program
2. Select an operation from the menu:
   - Scan single port: Check the status of one specific port
   - Scan port range: Check the status of a range of ports
   - Scan common ports: Check popular service ports (FTP, SSH, HTTP, etc.)
   - Exit: Quit the program
3. Enter the target IP address or hostname when prompted
4. Enter port numbers as required for the selected operation
5. Choose to continue or exit after each scan

## Sample Output
```
Welcome to the Network Port Scanner!
Note: This tool is for educational purposes only.
Only scan systems you own or have explicit permission to scan.

===== Network Port Scanner =====
1. Scan single port
2. Scan port range
3. Scan common ports
4. Exit
==============================
Enter your choice: 3
Enter target IP or hostname: 127.0.0.1
Scanning common ports on 127.0.0.1...
Port    Service         Status
---------------------------
22      SSH             OPEN
80      HTTP            OPEN
443     HTTPS           CLOSED
3306    MySQL           OPEN
```

## Technical Details

### Port Scanning Method
The scanner uses TCP connect scanning, which attempts to establish a full TCP connection to each port:
1. Create a TCP socket
2. Attempt to connect to the target port
3. If connection succeeds, port is open
4. If connection fails, port is closed
5. Close the socket

### Supported Platforms
- Windows (using Winsock API)
- Linux/Unix/macOS (using BSD sockets)

### Port Range
Valid port numbers are between 1-65535.

## Legal and Ethical Notice
This tool is for educational purposes only. Only scan systems you own or have explicit written permission to scan. Unauthorized port scanning may violate laws and regulations in your jurisdiction.

## Educational Value
This implementation demonstrates:
1. Network programming concepts
2. Cross-platform development techniques
3. Socket programming fundamentals
4. Network security basics
5. Error handling in network applications