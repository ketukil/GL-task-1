/**
 * @file detector.h
 * @author Damjan Belavic (damjan.belavic@vuka.hr)
 * @brief GlobalLogic Embedded Software Engineer in C / Task 1
 * @version 1.0
 * @date 2021-08-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef DETECTOR_H
#define DETECTOR_H

#include <stdbool.h>
#include <event2/event.h>

typedef struct event event_t;
typedef struct event_base event_base_t;
typedef struct timeval timeval_t;

void detector_init(event_base_t *, time_t, const char *);
void Process(char);

#endif /* DETECTOR_H */
