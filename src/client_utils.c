#include "client_utils.h"

// Function to create a TCP connection to the given port
int connect_to_port(const char *host, int port, int type) 
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
    sockfd = socket(AF_INET, type, 0);

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

// Add socket to the set
void add_socket_to_fd_set(const int socket_descriptor, 
    int *maxfd, 
    fd_set *readfds)
{
    // Adds each socket to the set
    FD_SET(socket_descriptor, readfds);

    // Check if max socket descriptor should be
    // updated
    if (socket_descriptor > *maxfd)
    {
        // Update max socket descriptor value
        *maxfd = socket_descriptor;
    }
}

// Read latest values if available
void read_lastest_value(const int socket_descriptor, 
    const fd_set *readfds,
    char *buffer)
{
    // Read latest values if available
    if (FD_ISSET(socket_descriptor, readfds)) 
    {
        // Temporal
        char tmp[128];

        int n = read(socket_descriptor, tmp, sizeof(tmp) - 1);

        if (n > 0) 
        {
            // terminator
            tmp[n] = '\0';
            
            // store latest
            strcpy(buffer, strtok(tmp, "\n")); 
        }
    }
}
// Get current timestamp in milliseconds since Unix epoch
long long current_time_ms() 
{
    // Store absolute system time
    struct timeval tv;

    // Get the current system time
    gettimeofday(&tv, NULL);

    // Return milliseconds since the Unix epoch.
    return (long long)(tv.tv_sec) * SEC_TO_MILISEC + (tv.tv_usec / SEC_TO_MILISEC);
}

// Send UDP binary control message
void send_control_message(int sockfd, 
    uint16_t operation,
    uint16_t object, 
    uint16_t property, 
    uint16_t value) 
{
    // Message content
    uint16_t msg[4];

    // Select operation
    int fields = (operation == 1) ? 3 : 4;

    // Read fields
    msg[0] = htons(operation);
    msg[1] = htons(object);
    msg[2] = htons(property);

    // Select value
    if (operation == 2)
    {
        msg[3] = htons(value);
    } 
    
    // Send message
    ssize_t len = send(sockfd, msg, fields * sizeof(uint16_t), 0);

    // Check if error
    if (len < 0) 
    {
        perror("send");
    }
}
