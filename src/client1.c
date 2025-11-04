
// File which contains common funcions
#include "client_utils.h"

// Number of ports
#define N_PORTS 3

//  Buffer size
#define BUFFER_SIZE 64

// Docker service name
// TODO: Provide the server name as input
const char SERVER[18] = "objective_swanson";

// Ports
const int PORT[N_PORTS] = {4001, 4002, 4003};

int main(void) 
{
    // -------- Declare global variables and set up
    // Socket file descriptor for ports
    int socket_descriptors[N_PORTS] = {0, 0, 0};

    // -------- Connect to ports
    for (int i = 0; i < N_PORTS; i++) 
    {
        // Connect to port i
        socket_descriptors[i] = connect_to_port(SERVER, PORT[i]);

        // Check conection failures
        if (socket_descriptors[i] < 0) 
        {
            fprintf(stderr, "Failed to connect to one or more ports\n");
            exit(EXIT_FAILURE);
        }
    }

    // Keeps track of a set of file descriptors
    fd_set readfds;

    int maxfd = -1;

    // Buffers to store data for ports
    char buffers[N_PORTS][BUFFER_SIZE] = {"--", "--", "--"};

    // Main loop (each 100 ms)
    while (1) 
    {
        // ------- Wait for each port reading
        // Clears the read set
        FD_ZERO(&readfds);

        for (int i = 0; i < N_PORTS; i++) 
        {
            // Adds each socket to the set
            add_socket_to_fd_set(socket_descriptors[i], &maxfd, &readfds);
        }

        // Define timeout interval
        struct timeval timeout;

        // Wait up to 100ms for data
        int activity = select(maxfd + 1, &readfds, NULL, NULL, &timeout);
        
        // Check activity failures
        if (activity < 0) 
        {
            fprintf(stderr, "Failure when checking activity \n");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < N_PORTS; i++) 
        {
            // Read latest values if available
            read_lastest_value(socket_descriptors[i], &readfds, buffers[i]);
        }

        // ------- Dump it into a JSON
        long long ts = current_time_ms();
        printf("{\"timestamp\": %lld, \"out1\": \"%s\", \"out2\": \"%s\", \"out3\": \"%s\"}\n",
               ts, buffers[0], buffers[1], buffers[2]);

        // Sleep for 100 ms
        struct timespec sleep_time = {0, 100000000L};
        nanosleep(&sleep_time, NULL);
    }
    
    // ------- Close connections
    for (int i = 0; i < N_PORTS; i++) 
    {
        close(socket_descriptors[i]);
    }

    // Return 0
    return 0;
}
