#include "sock.h"

void log_info(FILE *log_file, struct sockaddr_in *clisock, const char *file_name, int trans_status){

	time_t now;
    	struct tm *local_time; //tm is a sructure that hold time data
    	char time_str[100];

    	// Get the current time in to now variable
    	time(&now);

	//converts into more human readable way
    	local_time = localtime(&now);

    	// Format the time as a string
    	strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", local_time);

    	// Log the information to the log file
    	fprintf(log_file, "Client IP: %s\n", inet_ntoa(clisock->sin_addr));
    	fprintf(log_file, "Client Port: %d\n", ntohs(clisock->sin_port));
    	fprintf(log_file, "Connected Time: %s\n", time_str);
    	fprintf(log_file, "Requested File: %s\n", file_name);
    	fprintf(log_file, "Transfer Status: %s\n", trans_status ? "Failed" : "Successful");
    	fprintf(log_file, "--------------------------\n");
    
    	// Ensure data is written to the log file immediately
    	fflush(log_file);

}
