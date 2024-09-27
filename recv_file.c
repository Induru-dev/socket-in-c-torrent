#include "sock.h"

void recv_file(int sockfd, char *filename){

	int bytes_received;
	int last_printed_progress = 0;
	FILE *fp;
	char *direc = "/home/induru/Documents/recv_files";
	char full_path[BUFFER_SIZE];
	char buffer[BUFFER_SIZE];
	long file_size;
	long total_bytes_received = 0;
	float progress = 0;

	bzero(buffer, BUFFER_SIZE);
	bzero(full_path, BUFFER_SIZE);

	snprintf(full_path, sizeof(full_path), "%s/%s", direc, filename);

	fp = fopen(full_path, "wb");

	if (fp == NULL) {
    		perror("Failed to open file\n");
    		exit(1);
	}

	// Receive the file size from the server
    	if (recv(sockfd, &file_size, sizeof(file_size), 0) <= 0) {
        	perror("Failed to receive file size");
        	exit(1);
    	}

	printf("Downloading file of size: %ld bytes\n", file_size);

	//getting the file
	while ((bytes_received = recv(sockfd, buffer, BUFFER_SIZE, 0)) > 0) {
    		fwrite(buffer, sizeof(char), bytes_received, fp);
		total_bytes_received += bytes_received;

		// Calculate and display the download progress
        	progress = ((float)total_bytes_received / file_size) * 100;

		if ((int)progress >= last_printed_progress + 10 ) {
        		last_printed_progress = (int)progress;
        		printf("Download progress: %d%%\n", last_printed_progress); 	

        		//printf("Download progress: %.2f%%", progress); 
        		fflush(stdout); 
		}
    		bzero(buffer, BUFFER_SIZE);
	}
	
	if (bytes_received == -1) {
    		perror("Error receiving file\n");
    		exit(1);
	}else{
		printf("file recived successfully\n");
	}

	fclose(fp);

}
