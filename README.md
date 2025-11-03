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


