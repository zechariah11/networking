#include <iostream>
#include <cstdlib>      // For exit()
#include <cstring>      // For memset()
#include <unistd.h>     // For close()
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdint>

struct sockaddr_in {
    uint16_t       sin_family; // AF_INET
    uint16_t       sin_port;   // port in big-endian
    struct in_addr sin_addr;   // IPv4
};
struct in_addr {
    uint32_t       s_addr;     // IPv4 in big-endian
};

int main() {
    printf("Hello, world!\n");
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    printf("file descriptor: %d\n", fd);
    int val = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    struct sockaddr_in addr = {};
    return 0;
}