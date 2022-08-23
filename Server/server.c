#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <ctype.h>
#define SIZE 1024

int file_counter = 0;

/**
 * @brief This method reads a txt file and counts the number of consonants that it contains
 * 
 * @return int consonants_count: this is the number of consonants that the file contains
 */
int counter(char file_name[]){

    FILE* ptr;
    char ch;
    int consonants_count = 0;

    // Stores the content of the file.
    ptr = fopen(file_name, "r");
 
    if (NULL == ptr) {
        printf("file can't be opened \n");
    }
  
    while (!feof(ptr)) {

        // Reads file content char by char
        ch = fgetc(ptr);

        // Converts character to lowercase
        ch = tolower(ch);

        // Checks if the character is a vowel (we need to check this first so the next)
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
        }

        // Checks if the char is a consonant
        else if ((ch >= 'a' && ch <= 'z')) {
            ++ consonants_count;
        }

    }

    printf("La cantidad de consonantes es: %d\n", consonants_count);
    
    fclose(ptr);
    return consonants_count;

}

void write_file(int sockfd)
{
    int n;
    FILE *fp;
    //char *filename = "recv.txt";
    char buffer[SIZE];

    //fp = fopen(filename, "w");
    while (1)
    {
        n = recv(sockfd, buffer, SIZE, 0);
        if (n <= 0)
        {
            break;
            return;
        }

        char numstr[10];
        //itoa(file_counter, numstr, 10);
        sprintf(numstr, "%d", file_counter);
        char filename[] = "f/file";
        strcat(filename, numstr);
        strcat(filename, ".txt");
        file_counter ++;
        fp = fopen(filename, "w");
        fprintf(fp, "%s", buffer);
        bzero(buffer, SIZE);
        fclose(fp);

        int consonants = counter(filename);
        char consonats_str[10];
        sprintf(consonats_str, "%d", consonants);
        
        //itoa(consonants, consonats_str, 10);

        char message[]= "\nAmount of consonants in file is: ";
        strcat(message, consonats_str);
        printf("prueba consonantes: %s\n", message);
        //strcat(message, "\0");
        if (send(sockfd, message, SIZE, 0) == -1) {
            perror("[-]Error in sending file.");
            exit(1);
        }
    
    }
    return;
}

int main()
{
    char *ip = "127.0.0.1";
    int port = 8080;
    int e;

    int sockfd, new_sock;
    struct sockaddr_in server_addr, new_addr;
    socklen_t addr_size;
    char buffer[SIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("[-]Error in socket");
        exit(1);
    }
    printf("[+]Server socket created successfully.\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    e = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (e < 0)
    {
        perror("[-]Error in bind");
        exit(1);
    }
    printf("[+]Binding successfull.\n");

    if (listen(sockfd, 10) == 0)
    {
        printf("[+]Listening....\n");
    }
    else
    {
        perror("[-]Error in listening");
        exit(1);
    }

    addr_size = sizeof(new_addr);
    new_sock = accept(sockfd, (struct sockaddr *)&new_addr, &addr_size);
    write_file(new_sock);
    printf("[+]Data written in the file successfully.\n");

    return 0;
}