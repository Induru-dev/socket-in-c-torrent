#include "sock.h"

int main(int argc, char **argv){

        int     srvfd, a, selected_file_number;
        char    buffer[BUFFER_SIZE];
	char    send_buffer[BUFFER_SIZE];

        struct sockaddr_in      servsock;

        if ((srvfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ){
                printf("Socket creation failed\n");
                exit(1);
        }


        bzero(&servsock, sizeof(servsock));

        //here socket addres structure shold contain servers address and its port number
        servsock.sin_family = AF_INET;
        servsock.sin_port   = htons(5002);
        servsock.sin_addr.s_addr = inet_addr(argv[1]);
        //inet_pton(AF_INET, argv[1], &servsock.sin_addr;

        //here we set pointer to socket address structure and it must contain servers ip add,and port . in here a is for check if connect function implemented correctly
        a = connect(srvfd, (struct sockaddr*)&servsock,  sizeof(servsock));

        if(a == 0){
                printf("connection successfull\n");
        }
        else{
                printf("connect error");
                exit(1);
        }



        //for( ;; ){
	
	bzero(buffer,BUFFER_SIZE);

        read(srvfd, buffer, BUFFER_SIZE);
        printf("Available files:\n%s\n", buffer);


	printf("Enter the number of the file you want to download: ");
	scanf("%d", &selected_file_number);

	snprintf(send_buffer, sizeof(send_buffer), "%d", selected_file_number);
        write(srvfd, send_buffer, strlen(send_buffer));

	bzero(buffer,BUFFER_SIZE);
	read(srvfd, buffer, sizeof(buffer));

	recv_file(srvfd,buffer);
         
        //}


}

