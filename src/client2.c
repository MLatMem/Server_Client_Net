
// File which contains common funcions
#include "client_utils.h"

int main(void) 
{
    // -------- Declare global variables and set up
    // Socket file descriptor for ports
    int socket_descriptors[N_PORTS] = {0, 0, 0};

    // -------- Connect to ports
    for (int i = 0; i < N_PORTS; i++) 
    {
        // Connect to port i TCP
        socket_descriptors[i] = connect_to_port(SERVER, PORT[i], SOCK_STREAM);

        // Check conection failures
        if (socket_descriptors[i] < 0) 
        {
            fprintf(stderr, "Failed to connect to one or more ports\n");
            exit(EXIT_FAILURE);
        }
    }

    // Connect to port UDP
    int udp_sock = connect_to_port(SERVER, UDP_PORT, SOCK_DGRAM);

    // Keeps track of a set of file descriptors
    fd_set readfds;

    int maxfd = -1;

    // Buffers to store data for ports
    char buffers[N_PORTS][BUFFER_SIZE] = {"--", "--", "--"};
    
    // Last out3 value
    double last_out3 = 0.0;

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
        // 0 seconds
        timeout.tv_sec = 0;
        // 100 ms
        timeout.tv_usec = 10; 

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

        double out3_val = strtod(buffers[2], NULL);

        if (out3_val >= 3.0 && last_out3 < 3.0) 
        {
            // Rising threshold → set 1 Hz, 8000
            send_control_message(udp_sock, 2, 1, 1, 1);     // write op=2, object=1, property=1(freq)=1Hz
            send_control_message(udp_sock, 2, 1, 2, 8000);  // amplitude=8000
        } 
        else if (out3_val < 3.0 && last_out3 >= 3.0) 
        {
            // Falling threshold → set 2 Hz, 4000
            send_control_message(udp_sock, 2, 1, 1, 2);
            send_control_message(udp_sock, 2, 1, 2, 4000);
        }

        last_out3 = out3_val;

        // Sleep for 20 ms
        struct timespec sleep_time = {0, 20000000L};
        nanosleep(&sleep_time, NULL);
    }
    
    // ------- Close connections
    close(udp_sock);
    for (int i = 0; i < N_PORTS; i++) 
    {
        close(socket_descriptors[i]);
    }

    // Return 0
    return 0;
}
