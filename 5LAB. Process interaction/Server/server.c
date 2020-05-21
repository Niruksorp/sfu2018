#include "define.h"
#include "fun.h"

int main()
{
    int sock;
    int port = NUM_OF_PORT;
    char datearr[NUM_OF_ELEMENT];
    struct sockaddr_in addr;

    int listener = socket(AF_INET, SOCK_STREAM, DEFOULT);

    if (listener < DEFOULT)
    {
        perror("Socket error.\n");
        exit(ERROR_STATUS_LISTEN);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);


    if (bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < DEFOULT)
    {
        perror("Binding error.\n");
        exit(ERROR_STATUS_BIND);
    }

    listen(listener, ONE);

    sock = accept(listener, NULL, NULL);

    if (sock < DEFOULT)
    {
        perror("Accept error.\n");
        exit(SOCKET_ERROR);
    }

    recv(sock, datearr, NUM_OF_ELEMENT, DEFOULT);

    struct Date_Time result_date = make_new_date(parser(datearr));
    print_info(result_date);

    close(sock);
    return END_OF_PROGRAM;
}