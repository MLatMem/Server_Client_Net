
// File which contains common funcions
#include "client_utils.h"

// Number of ports
#define N_PORTS 3

//  Buffer size
#define BUFFER_SIZE 64

// Docker service name
const char SERVER[10] = "fsw-server";  

// Ports
static const int PORT[N_PORTS] = {4001, 4002, 4003};

int main(void) 
{
    // -------- Declare global variables and set up

    // -------- Connect to ports
    for (int i = 0; i < N_PORTS; i++) 
    {
        // Connect to port i
        // Check conection failures
    }

    // Main loop (each 100 ms)
    while (1) 
    {
        // ------- Wait for each port reading
        // (Wait up to 100ms for data)
        // ------- Dump it into a JSON
    }

    // Return 0
    return 0;
}
