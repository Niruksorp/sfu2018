#include "define.h"
#include "fun.h"
#include "client.h"
#define MY_IP "192.168.0.101"
/*! \brief главная функция программы
 *
 *  \return 0 при успешном завершении
 */

int main(int argc, char* argv[])
{
	int argc_num = 3;
	char datearr[11];
	if (argc != argc_num)
	{
		printf("Error. Invalid number of arguments. Try again: ./client [PORT] [IP]\n");
		return ENDOFPROGRAMM;
	}
	if (atoi(argv[FIRST_ARGUMENT]) <= ZERO || atoi(argv[FIRST_ARGUMENT]) > MAXPORT)
	{
		printf("Error. Invalid first argument. PORT = [1, 65535]. Try again: ./client [PORT] [IP]\n");
		return ENDOFPROGRAMM;
	}
	
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 0), &wsaData))
	{
		printf("ERROR: WSAStartup failed %d", WSAGetLastError());
		return WARR_ERROR;
	}

	struct Date_Time temp = input_current_date_time();
	//temp = input_current_date_time();
	temp.timezone = input_timezone();

	char rez[22] = "";
	convert_into_the_string(temp, rez);

	int status = sock_client(rez, argv);

	if (status == ERRSOCK)
	{
		perror("Socket error.");
	}
	else if (status == ERRCON)
	{
		perror("Connection error. Check PORT and IP for correct");
	}

	return ENDOFPROGRAMM;
}
