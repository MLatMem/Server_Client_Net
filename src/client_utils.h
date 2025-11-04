#ifndef CLIENT_UTILS_H
#define CLIENT_UTILS_H

// C includes
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Network includes
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <fcntl.h>

/// Function to create a TCP connection to the given port
/// @param host             - Host name
/// @param port             - Port number
/// @return int             - Socket file descriptor
int connect_to_port(const char *host, int port);

#endif //CLIENT_UTILS_H