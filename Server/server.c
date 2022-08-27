#include <arpa/inet.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logger.h"

#define SIZE 1024

int file_counter = 0;
int port;
char *filefolder;
char *filefolder_aux;

/**
 * This method reads a txt file and counts the number of consonants that it contains
 *
 * returns int consonants_count: this is the number of consonants that the file contains
 */
int counter(char file_name[])
{
    FILE *ptr;
    char ch;
    int consonants_count = 0;

    // Stores the content of the file.
    ptr = fopen(file_name, "r");

    if (NULL == ptr)
    {
        docs_log("File '%s' can't be opened\n", file_name);
    }

    while (!feof(ptr))
    {

        // Reads file content char by char
        ch = fgetc(ptr);

        // Converts character to lowercase
        ch = tolower(ch);

        // Checks if the character is a vowel (we need to check this first so the next)
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
        {
        }

        // Checks if the char is a consonant
        else if ((ch >= 'a' && ch <= 'z'))
        {
            ++consonants_count;
        }
    }

    fclose(ptr);
    return consonants_count;
}

/**
 * This method updates the valus of port and folder where
 * the received files will be saved
 *
 * The information will be located in server-config.txt
 */
void update_config()
{
    FILE *config_file;
    config_file = fopen("/usr/bin/doc-server/server-config.txt", "r");

    if (config_file == NULL)
    {
        docs_log("Error opening the configuration file (/usr/bin/doc-server/server-config.txt)\n");
        exit(1);
    }

    // read the important lines from the files and save the information
    char *line;
    size_t len = 0;
    getline(&line, &len, config_file);
    getline(&line, &len, config_file);
    port = atoi(line);

    getline(&line, &len, config_file);
    getline(&line, &len, config_file);
    filefolder = line;
}

/**
 * This method saves the received file in the respective
 * direction
 */
void write_file(int sockfd)
{
    int n;
    FILE *fp;
    char buffer[SIZE];

    // This cycle keeps receiving files
    while (1)
    {
        // the cycle ends when when there is an error with the socket
        n = recv(sockfd, buffer, SIZE, 0);

        if (n <= 0)
        {
            break;
            return;
        }

        // create file path
        char numstr[10];
        sprintf(numstr, "%d", file_counter);
        char filename[] = "file";
        strcat(filefolder, filename);
        strcat(filefolder, numstr);
        strcat(filefolder, ".txt");
        file_counter++;

        // open file and save it
        fp = fopen(filefolder, "w");
        fprintf(fp, "%s", buffer);
        bzero(buffer, SIZE);
        fclose(fp);

        // calculate the amount of consonants
        int consonants = counter(filefolder);
        char consonats_str[10];
        sprintf(consonats_str, "%d", consonants);

        // send the amount of consonants as a message to the client
        char message[] = "\nAmount of consonants in file is: ";
        strcat(message, consonats_str);

        if (send(sockfd, message, SIZE, 0) == -1)
        {
            docs_log("[-]Error in sending file.\n");
            exit(1);
        }

        // update with config file info
        update_config();
    }
    return;
}

int main()
{
    char *ip = "127.0.0.1";
    int e;

    // update configuration file
    update_config();

    // start the server
    int sockfd, new_sock;
    struct sockaddr_in server_addr, new_addr;
    socklen_t addr_size;
    char buffer[SIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        docs_log("[-]Error in socket\n");
        exit(1);
    }

    docs_log("[+]Server socket created successfully.\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    // connect to client
    e = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (e < 0)
    {
        docs_log("[-]Error in bind\n");
        exit(1);
    }

    docs_log("[+]Binding successfull.\n");

    if (listen(sockfd, 10) == 0)
    {
        docs_log("[+]Listening....\n");
    }
    else
    {
        docs_log("[-]Error in listening\n");
        exit(1);
    }

    // begin communication with client
    addr_size = sizeof(new_addr);
    new_sock = accept(sockfd, (struct sockaddr *)&new_addr, &addr_size);
    docs_log("[+]Connection accepted\n");
    system("sudo strace -c -p $(pidod server) -o ~/Documents/docserver");
    write_file(new_sock);
    docs_log("[+]Data written in the file successfully.\n");

    return 0;
}
