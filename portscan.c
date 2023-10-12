#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

struct addrinfo hints;
struct addrinfo *res;

int main(int argc, char *argv[]){
  int status;
  int sockfd;
  int val; 

  if (argc != 2){
    fprintf(stderr, "Need target host as second argument\n");
    return (1);
  }

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  for(int i = 0; i <= 100; i++){
    char port[6];
    sprintf(port, "%d", i);
    status = getaddrinfo(argv[1], port, &hints, &res);
    if (status != 0){
      fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
    }
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfd == -1){
      perror("socket");
      freeaddrinfo(res);
      return(2);
    }
    val = connect(sockfd, res->ai_addr, res->ai_addrlen);
    if (val == 0){
      printf("Port %d is open\n", i);
    }
    close(sockfd);
    freeaddrinfo(res);

  }

  return(0);
}
