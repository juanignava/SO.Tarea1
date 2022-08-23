#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#define SIZE 1024
 
void send_file(FILE *fp, int sockfd){
  int n;
  char data[SIZE] = {0};
  char message[SIZE];
  char buffer[SIZE];
 
  while(fgets(data, SIZE, fp) != NULL) {
    strcat(message, data);
  }
  if (send(sockfd, message, sizeof(message), 0) == -1) {
      perror("[-]Error in sending file.");
      exit(1);
    }
    bzero(message, SIZE);
    recv(sockfd, buffer, SIZE, 0);
    printf("%s", buffer);
}

 
int main(){
  char ip[50] = "127.0.0.1";
  int port = 8080;
  int e;
 
  int sockfd;
  struct sockaddr_in server_addr;
  FILE *fp;

  char specify[20];
  printf("\n[ip = 127.0.0.1 and port= 880]");
  printf("\nSpecify a different ip and port? (yes/no): ");
  scanf(" %s", specify);

  if (!strcmp("yes", specify))
  {
      printf("\nNew IP address: ");
      scanf(" %s", ip);
      char portstr[10];
      printf("\nNew port: ");
      scanf(" %s", portstr);
      port = atoi(portstr);
  }

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    perror("\n[-]Error in socket");
    exit(1);
  }
  printf("\n[+]Server socket created successfully.\n");
 
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);
 
  e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(e == -1) {
    perror("[-]Error in socket");
    exit(1);
  }
  printf("[+]Connected to Server.\n");
  
  char filename[100];
  while (1)
  {
      printf("\nType the file path or end to finish program: ");
      scanf(" %s", filename);
      
      printf("filename es: %s", filename);
      int comparacion = strcmp("end", filename);
    
      if (!strcmp("end", filename))
      {
        printf("\nProcess ended by user.");
        break;
      }
      
      fp = fopen(filename, "r");
      if (fp == NULL) {
        perror("\n[-]Error in reading file.");
        continue;;
      }
    
      send_file(fp, sockfd);
      printf("\n[+]File data sent successfully.\n");
  }
  
  
 
  printf("\n[+]Closing the connection.\n");
  close(sockfd);
 
  return 0;
}