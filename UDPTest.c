#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include "logger.h"

#define MAXSTRINGLENGTH 1024

int main(int argc, char *argv[]) {
    
    if (argc < 3 || argc > 4) {
        log(FATAL, "Parameter(s) <Server Address/Name> <FQDN> [<Server Port>]");
        exit(EXIT_FAILURE);
    }
    
    char *server = argv[1];     // First arg: server address/name
    char *echoString = argv[2]; // Second arg: FQDN
    
    size_t echoStringLen = strlen(echoString);
    
    // Third arg  server port
    char * servPort = argv[3];
    
    struct addrinfo addrCriteria;                   // Criteria for address match
    memset(&addrCriteria, 0, sizeof(addrCriteria)); // Zero out structure
    addrCriteria.ai_family = AF_UNSPEC;             // Any address family
    addrCriteria.ai_socktype = SOCK_DGRAM;          // Only datagram sockets
    addrCriteria.ai_protocol = IPPROTO_UDP;         // Only UDP protocol
    
    // Get address(es)
    // TODO: recorrer todas las IPs devueltas por getaddrinfo, hasta que una responda
    struct addrinfo *servAddr; // List of server addresses
    int rtnVal = getaddrinfo(server, servPort, &addrCriteria, &servAddr);
    if (rtnVal != 0) {
        log(FATAL, "getaddrinfo() failed: %s", gai_strerror(rtnVal));
        exit(EXIT_FAILURE);
        
    }
    // Create a datagram/UDP socket
    int sock = socket(servAddr->ai_family, servAddr->ai_socktype,
                      servAddr->ai_protocol); // Socket descriptor for client
    if (sock < 0) {
        log(FATAL, "socket failed");
        exit(EXIT_FAILURE);
               
    }
    // Send the string to the server
    ssize_t numBytes = sendto(sock, echoString, echoStringLen, 0,
                              servAddr->ai_addr, servAddr->ai_addrlen);
    if (numBytes < 0) {
        log(FATAL, "sendto failed");
        exit(EXIT_FAILURE);
               
    }
    
    // Receive a response
    
    struct sockaddr_storage fromAddr; // Source address of server
    // Set length of from address structure (in-out parameter)
    socklen_t fromAddrLen = sizeof(fromAddr);
    char buffer[MAXSTRINGLENGTH + 1]; // I/O buffer
    numBytes = recvfrom(sock, buffer, MAXSTRINGLENGTH, 0,
                        (struct sockaddr *) &fromAddr, &fromAddrLen);
    if (numBytes < 0) {
        log(FATAL, "recvfrom() failed");
        exit(EXIT_FAILURE);
    }
    
    buffer[numBytes] = '\0';     // Null-terminate received data
    printf("Received: %s\n", buffer);
    
    close(sock);
    exit(0);
}
