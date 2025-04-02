#include <iostream>
#include <cstdlib>      // For exit()
#include <cstring>      // For memset()
#include <unistd.h>     // For close()
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// A simple error handler that prints the error message and exits
void die(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main() {
    // Create a socket using IPv4 and TCP
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        die("socket()");
    }

    // Set the socket option to allow reuse of local addresses
    int val = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)) < 0) {
        die("setsockopt()");
    }

    // Configure the sockaddr_in structure for binding
    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234);          // Port number (converted to network byte order)
    addr.sin_addr.s_addr = htonl(0);        // Wildcard IP address (0.0.0.0)

    // Bind the socket to the specified IP and port
    int rv = bind(fd, reinterpret_cast<const struct sockaddr *>(&addr), sizeof(addr));
    if (rv < 0) {
        die("bind()");
    }

    std::cout << "Socket bound successfully on port 1234." << std::endl;

    // Normally you would continue with listen() and accept() here if needed

    // Close the socket
    close(fd);
    return 0;
}
