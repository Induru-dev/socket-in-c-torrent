#include "sock.h"

void send_list(int sockfd){

	struct dirent *de;
	DIR *dr = opendir("/home/induru/Documents/files");
	char file_list[BUFFER_SIZE];
	int file_number = 1;
	char file_entry[256];

	bzero(file_list,BUFFER_SIZE);

	if (dr == NULL) {
        	printf("Could not open directory");
        	exit(1);
    	}

    	while ((de = readdir(dr)) != NULL) {

        	// Ignore '.' and '..'
        	if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0) {

			bzero(file_entry,256);
			
			//1. file.mp4 widihata hadanawa file_entry eka athule 
            		snprintf(file_entry, sizeof(file_entry), "%d. %s\n", file_number, de->d_name);
            		strcat(file_list, file_entry);
            		file_number++;

            		//strcat(file_list, de->d_name);
            		//strcat(file_list, "\n");

        	}

    	}

    	closedir(dr);	

    	// Send the list of files to the client
    	if (send(sockfd, file_list, strlen(file_list), 0) == -1) {
        	printf("Failed to send file list");
        	exit(1);
    	}	
	
	
}
