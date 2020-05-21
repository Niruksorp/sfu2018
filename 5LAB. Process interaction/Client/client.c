#include "define.h"
#define IP "10.0.2.15"

int sock_client(char* datearr, char* argv[])
{
    struct sockaddr_in addr;
    int one = 1;
    int sock = socket(AF_INET, SOCK_STREAM, ZERO);
    if (sock < ZERO)
    {
        return ERRSOCK;	
    }
	
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[1]));
	if (!strcmp(argv[SECOND_ARGUMENT], "any")) addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    else addr.sin_addr.s_addr = inet_addr(argv[SECOND_ARGUMENT]);
	
    if(connect(sock, (struct sockaddr* )&addr, sizeof(addr)) < ZERO)
    {
	    return ERRCON;
    }
	
	if (send(sock, datearr, SIZE, ZERO) != -one)
    {
	printf("%s", datearr);
    	printf("Sending complete.\n");
    }
	
    else
    {
    	printf("Sending error.\n");
    }
	
    close(sock);

    return SUCCES;
}
