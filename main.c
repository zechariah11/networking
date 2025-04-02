#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void die(const char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    printf("Hello, world!\n");

    // Initialize a socket and bind to fd handle
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) { die("socket()"); }
    printf("file descriptor: %d\n", fd);
    
    int val = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)) < 0) {
        die("setsockopt()");
    }

    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234);
    addr.sin_addr.s_addr = htonl(0);

    int rv = bind(fd, (const struct sockaddr *) &addr, sizeof(addr));
    if (rv) { die("bind()"); }

    printf("Successfully bound to port 1234\n");
    return 0;
}