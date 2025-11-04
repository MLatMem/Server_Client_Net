#include "client_utils.h"

// Function to create a TCP connection to the given port
int connect_to_port(const char *host, int port) 
{
    // Socket file descriptor
    int sockfd;

    // Address and port of the server
    struct sockaddr_in serv_addr;

    // Converts a hostname into an IP address
    struct hostent *server = gethostbyname(host);

    // If the hostname couldn’t be resolved, print an error and return -1
    if (server == NULL) 
    {
        fprintf(stderr, "Error: no such host %s\n", host);
        return -1;
    }

    // Creates a new TCP socket, returns a socket descriptor
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // If the socket descriptor is negative, return an error
    if (sockfd < 0) 
    {
        perror("socket");
        return -1;
    }

    // Clears the entire serv_addr structure to zero. 
    // This ensures no garbage data remains in unused fields
    memset(&serv_addr, 0, sizeof(serv_addr));

    // Sets the address family to IPv4.
    serv_addr.sin_family = AF_INET;

    // Copies the IP address from the DNS result (server->h_addr) 
    // into your socket address structure
    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);

    // Converts the port number into network byte order
    serv_addr.sin_port = htons(port);

    // Tries to establish a TCP connection to the remote server
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    {
        perror("connect");
        close(sockfd);
        return -1;
    }

    // Make socket non-blocking
    fcntl(sockfd, F_SETFL, O_NONBLOCK);

    // Returns the open socket descriptor to the caller
    return sockfd;
}
