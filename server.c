#include        "sock.h"


int main(int argc, char **argv){

        int listenfd;
	int connfd[MAX_CLIENTS];
	int i=0;
	pid_t	childpid;
	socklen_t clilen;
	const char *ptr;
	void sig_chld(int);
	char buffer[BUFFER_SIZE];
	char file_name[BUFFER_SIZE];
	FILE *fp;
	char *direc = "/home/induru/Documents/files";
	
	

	//creating socket addrr stucture
        struct sockaddr_in servsock, clisock;
	
	//creating socket
        if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ){
                perror("Socket creation failed\n");
                exit(1);
        }

	//make all 0
        bzero(&servsock,sizeof(servsock));
	

	//assigneing port and ip addr
        servsock.sin_family = AF_INET;
        servsock.sin_port = htons(5002);
        servsock.sin_addr.s_addr = inet_addr(argv[1]);
        //inet_aton(argv[1], &servsock.sin_addr);

	//bind
        if ((bind(listenfd, (struct sockaddr*)&servsock, sizeof(servsock))) < 0){
                perror("bind failed\n");
                exit(1);
        }

	printf("waiting for client connections.....");
	
	//listen
        if(listen(listenfd,20) < 0){
                perror("listen failed\n");
                exit(1);
        }

	//hadle zombie process
	signal(SIGCHLD,sig_chld);
	

        

        for(i=0; i < MAX_CLIENTS; i++){

				
		bzero(&clisock,sizeof(clisock));
		clilen = sizeof(clisock);

		//accept 
	        if( (connfd[i] = accept(listenfd, (struct sockaddr*)&clisock , &clilen)) < 0 ){
			if(errno == EINTR){
				continue;
			}
			else{
				perror("accept error\n");
				exit(1);
			}
		}


		//getting clients details
		if( (ptr = inet_ntop(AF_INET, &clisock.sin_addr, buffer, sizeof(buffer))) == 0 ) {
			perror("inet_ntop error \n");
			exit (1);
		}
		printf("connection from %s, port %d\n", ptr, ntohs(clisock.sin_port));
		ptr = NULL;


		//creating child server
		if((childpid =  fork())==0)
		{
			close(listenfd);
			
			send_list(connfd[i]);
			
			//initialization of some functions
			int file_number, file_count = 1;
			struct dirent *de; //creating srtucrture object
			DIR *dr = opendir(direc); //opening foldedr path

			if (dr == NULL) {
    				perror("Could not open directory");
    				exit(1);
			}

			bzero(buffer,BUFFER_SIZE);
			
			//get number from client
			read(connfd[i], buffer, sizeof(buffer));
			file_number = atoi(buffer);

			//read each enty of directory
			while ((de = readdir(dr)) != NULL) {
				if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0) { //ignore . and  ..
					if (file_count == file_number){ 
						
						char full_path[BUFFER_SIZE];
            					snprintf(full_path, sizeof(full_path), "%s/%s", direc, de->d_name); //get file name from de and append it with folder path

						//open file
            					fp = fopen(full_path, "rb");

						if (fp == NULL) {
							perror("Error opening file");
							exit(1);
	    					}

						printf("File opened successfully.\n");
						
						//send file name to client
						strcpy(file_name,de->d_name);
						send(connfd[i], file_name, sizeof(file_name), 0);
						
					}

					file_count++;

				}
			}

			//sending file
			send_file(fp,connfd[i]);

			fclose(fp);
			close(connfd[i]);						
	
		}
		
		close(connfd[i]);

        }

      

        return 0;

}












