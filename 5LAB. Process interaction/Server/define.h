#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define UTC8_KJA 8
#define UTC0_GMT 0
#define UTC_MAX 14
#define UTC_MIN -12
#define DELIMETR "."
#define MALLOC_ERROR 1
#define ERROR_STATUS_LISTEN 1
#define ERROR_STATUS_BIND 2
#define SOCKET_ERROR 3
#define END_OF_PROGRAM 0
#define DEFOULT 0
#define NUM_OF_ELEMENT 22
#define ONE 1
#define NUM_OF_PORT 1444
#define TEMP_ELEMENT 0
#define JANUARY 31
#define FEBRUARY 28
#define MARCH 31
#define APRIL 30
#define MAY 31
#define JUNE 30
#define JULY 31
#define AUGUST 31
#define SEPTEMBER 30
#define OCTOBER 31
#define NOVEMBER 30
#define DECEMBER 31
#define FIRST_MO 1
#define CHECK_LEEP_YEAR 4
#define HELP_FOR_PRINT 10
#define MIN_HOURS 0
#define NEW_DAY 24
#define PREV 1
#define NEXT 1
#define GO_TO_NEXT 0
#define MAX_YEAR 100
#define PREV_MAX_YEAR 99
#define MAX_HOURS 23
///Структура, хранящая представление даты и времени
struct Date_Time
{
    int day;
    int month;
    int year;
    int hours;
    int minutes;
    int timezone;
};

