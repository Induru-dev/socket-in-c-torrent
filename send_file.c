#include "sock.h"

void send_file(FILE *fp, int sockfd){

	char data[BUFFER_SIZE];
	long file_size;
	bzero(data,BUFFER_SIZE);

	// Get the file size
    	fseek(fp, 0L, SEEK_END);
    	file_size = ftell(fp);  
    	rewind(fp);

    	// Send the file size to the client
    	if (send(sockfd, &file_size, sizeof(file_size), 0) == -1) {
        	perror("Failed to send file size");
        	exit(1);
    	}

	while (fread(data, sizeof(char), BUFFER_SIZE, fp) > 0) {
        
		if (send(sockfd, data, BUFFER_SIZE, 0) == -1) {
            		perror("Failed to send file");
            		exit(1);
        	}

        	bzero(data, BUFFER_SIZE);
    	}

	printf("File sent successfully\n");

	shutdown(sockfd, SHUT_WR);  // Close write-side of socket to signal end of transfer


}
