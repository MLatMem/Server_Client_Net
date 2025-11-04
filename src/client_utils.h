#ifndef CLIENT_UTILS_H
#define CLIENT_UTILS_H

// C includes
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

// Network includes
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <fcntl.h>

// Time includes
#include <sys/time.h>
#include <time.h>

/// Const to pass from seconds to nanoseconds
static const int SEC_TO_MILISEC = 1000;

/// Get current timestamp in milliseconds since Unix epoch
/// @return long long               - Time in miliseconds
long long current_time_ms();

/// Add socket to the set
/// @param socket_descriptor        - Socket file descriptor
/// @param maxfd                    - Maximum file descriptor
/// @param readfds                  - Set of file descriptors
void add_socket_to_fd_set(const int socket_descriptor, 
    int *maxfd, 
    fd_set *readfds);

// Read latest values if available
/// @param socket_descriptor        - Socket file descriptor
/// @param readfds                  - Set of file descriptors
/// @param buffer                   - Buffer with lastest value
void read_lastest_value(const int socket_descriptor, 
    const fd_set *readfds,
    char *buffer);

/// Function to create a TCP connection to the given port
/// @param host                     - Host name
/// @param port                     - Port number
/// @return int                     - Socket file descriptor
int connect_to_port(const char *host, int port);

#endif //CLIENT_UTILS_H