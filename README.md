# Server_Client_Net
Here it is described the structure of the repository and the logic to develop everything

## Preliminar steps:
Understand the problem and think about the development environment and how to structure the solution.

* Understand the problem: Read the specifications carefully and discuss them with chatGPT.

* Development environment: 
    1. Working on windows, so a Docker image has been created to work in the required OS (debian).
    2. Creating a network so the two docker containers running can comunicate with each other

* Structure the solution:
    fsw-client/
    - src/
        - client_utils.h
        - client_utils.c
        - client1.c
        - Makefile
    - Dockerfile
    - README.md

* Develop client1.c, it should contain the following steps:
    - Declare global variables and set up
    - Connect to ports
    - Wait for each port reading each 100 ms
    - Dump it into a JSON

* Develop client_utils.h/c, it should contain all the functions

* Client 1:
    - Output 1 shows a sinoidal signal
    - Output 2 shows a triangular signal
    - Output 3 shows a square signal

![Output plot for client1](outputs_plot_client1.jpg)

* Develop client2.c, 
    - Part of client1 has been reused, adding new features required to implement task 2.


