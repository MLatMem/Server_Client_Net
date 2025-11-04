
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
static const int PORT[N_PORTS] = {4001, 4002, 4003};

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

    printf("Connected to server on ports 4001, 4002, 4003\n");

    /*// Main loop (each 100 ms)
    while (1) 
    {
        // ------- Wait for each port reading
        // (Wait up to 100ms for data)
        // ------- Dump it into a JSON
    }*/

    // Return 0
    return 0;
}
