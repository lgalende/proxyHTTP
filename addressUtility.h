#ifndef ADDRESSUTILITY_H_
#define ADDRESSUTILITY_H_

#include <stdbool.h>
#include <stdio.h>
#include <sys/socket.h>

// fills addrBuffer with socket address in readable format
int printSocketAddress(const struct sockaddr *address, char * addrBuffer);

// Test socket address equality
bool sockAddrsEqual(const struct sockaddr *addr1, const struct sockaddr *addr2);


#endif 
