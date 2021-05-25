#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "logger.h"
#include "tcpClientUtil.h"


// Modificamos el cliente original para que envie infinitamente pero nunca lea
int main(int argc, char *argv[]) {

	if (argc < 2 || argc > 3) {
		printf("Parameter(s): <Server Name/Address> [<Server Port/Name>]\n");
		exit(1);
	}

	char *server = argv[1];     // First arg: server name IP address 
	char *echoString ="Un texto enviado infinitas veces"; 

	// Third arg (optional): server port .  7 is well-known echo port
	char * port = (argc == 4) ? argv[3] : "echo";

	// Create a reliable, stream socket using TCP
	int sock = tcpClientSocket(server, port);
	if (sock < 0) {
		log(FATAL, "socket() failed")
			exit(1);
	}

	size_t echoStringLen = strlen(echoString); // Determine input length

	// Send the string to the server
	ssize_t numBytes = send(sock, echoString, echoStringLen, 0);
	if (numBytes < 0 || numBytes != echoStringLen)
		log(FATAL, "send() failed expected %zu sent %zu", echoStringLen, numBytes)

			// Receive the same string back from the server
			// Send the string to the server
			while (1) {
				numBytes = send(sock, echoString, echoStringLen, 0);
				if (numBytes < 0)
					log(FATAL, "send() failed")
				else if (numBytes != echoStringLen)
					log(ERROR, "send() sent unexpected number of bytes")
			}

	close(sock);
	return 0;
}
