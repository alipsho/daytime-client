//CLIENT
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define MY_PORT_NUMBER 4444

//make connection from client
int main(int argc, char **argv) {

		int socketfd;
	
	if( (socketfd = socket( AF_INET, SOCK_STREAM, 0)) < 0) {  //Make socket using TCP protocol
		perror("socket");
		exit(1);
	}


// set up address of the server
	struct sockaddr_in servAddr;
	struct hostent *hostEntry;
	struct in_addr **pptr;

	memset(&servAddr, 0,sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(MY_PORT_NUMBER);
	servAddr.sin_addr.s_addr = inet_addr("192.168.56.102");
// connect and read from server
	if( (connect(socketfd, (struct sockaddr *) &servAddr,sizeof(servAddr))) < 0 ) {
		perror("connect");
		exit(1);
	}
	
	//Read date/time from server
	char buffer[100];
	int byteRead = read(socketfd, buffer, 100);
	if(byteRead <= 0) {
		perror("read");
		exit(1);
	}
	buffer[byteRead] = '\0';
	printf("Current date/time from server: %s\n", buffer);
	close(socketfd);
	exit(0);
}

