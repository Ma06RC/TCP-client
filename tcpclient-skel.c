// NWEN 243, Victoria University of Wellington. Author, Kris Bubendorfer.

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

#define bufsize 1024

int main(argc, argv) int argc; char *argv[];{
  int sock, rval;
  struct hostent *host;
  struct sockaddr_in server;  // not a pointer.
  char buf[bufsize];
  
  if(argc != 4){
    printf("usage:\ntcpclient hostname port string\n\n");
    return(-1);
  }
  
  // look up hostname (server) using DNS

  if ((host = gethostbyname(argv[1])) == 0) {
    fprintf(stderr, "%s: unknown host\n", argv[1]); 
    return(-1);  
  }

  // Set up fields for socket to point to host and port
  bcopy(host->h_addr, &server.sin_addr, host->h_length);
  server.sin_family = AF_INET;
  server.sin_port = htons(atoi(argv[2]));
 
  // Create socket 
  int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

  // connect (3-way handshake)
  socklen_t addr_size = sizeof server;
  int clientConnect = connect(clientSocket, (struct sockaddr_in *) &server , addr_size);

  // Copy the arg into buf so we can send it to the server
  
  strncpy(buf, argv[3], bufsize);
 
  // Send sentence to server
  int writeClient = write(clientSocket, buf, bufsize );

  // read response from server
  int readClient = read(clientSocket, buf, bufsize);

  // print result to window

  fprintf(stdout,"%s\n", buf);
  close(sock);
}
