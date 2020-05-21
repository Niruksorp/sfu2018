#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <unistd.h>
#include <stdbool.h>
#define WARR_ERROR 1
#define FIRST_ARGUMENT 1
#define SIZE_FOR_STR 2
#define DELIMM '.'
#define DELIMM_NEW '\n'
#define SIZE_FOR_START_MALLOC 5
#define FIRST_ARG 0
#define SECOND_ARG 1
#define THIRD_ARG 2
#define FOURTH_ARG 3
#define FIFTH_ARG 4
#define SECOND_ARGUMENT 2
#define MIN_YEAR 0
#define MAX_YEAR 100
#define MIN_MOUNTH 1
#define MAX_MOUNTH 12
#define MIN_DAY 1
#define FEB 2
#define LEEP_YEAR_MOUNTH 1
#define MIN_HOURS 0
#define MAX_HOURS 23
#define MIN_MINNUT 0
#define MAX_MINUTS 59
#define MALLOC_ERROR 1
#define DELIM "."
#define LEEP_YEAR 4
#define YEAR_IS_LEEP 0
#define UTC8_KJA 8
#define UTC0_GMT 0
#define UTC_MAX 14
#define UTC_MIN -12
#define SIZE_TEMP_ARRAY 3
#define SIZE_OF_DELIM_SIM 2
#define MAXPORT 65535
#define ZERO 0
#define SUCCES 0
#define SIZE 30
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
#define ENDOFPROGRAMM 0
#define ERRCON -2
#define ERRSOCK -1
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



