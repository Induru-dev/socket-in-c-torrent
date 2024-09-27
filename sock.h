#include <stdio.h> 
#include <time.h> 
#include <string.h> 
#include <errno.h> 
#include <netdb.h> 
#include <sys/uio.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <stdlib.h>
#include <signal.h> //for signal
#include <sys/wait.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>


#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

//int cli_count = 0;
