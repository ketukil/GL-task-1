/**
 * @file util.c
 * @author Damjan Belavic (damjan.belavic@vuka.hr)
 * @brief GlobalLogic Embedded Software Engineer in C / Task 1
 * @version 1.0
 * @date 2021-08-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "util.h"

void calc_timevalue(struct timeval *tv, time_t delay_ms)
{
    int sec, millis;

    sec = delay_ms / 1000;
    millis = delay_ms % 1000;

    tv->tv_sec = sec;
    tv->tv_usec = 1000 * millis;
}
