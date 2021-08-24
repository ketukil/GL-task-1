/**
 * @file detector.c
 * @author Damjan Belavic (damjan.belavic@vuka.hr)
 * @brief GlobalLogic Embedded Software Engineer in C / Task 1
 * @version 1.0
 * @date 2021-08-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <event2/event.h>
#include "detector.h"
#include "util.h"

// ┌───────────────────────────────────────────────────────────────────────────┐
// │ Enums, Variables, Structures, Typedefs                                    │
// └───────────────────────────────────────────────────────────────────────────┘

int curr_state;
int max_states;
const char *sequence;

struct event_base *ev_base;
struct event *timeout_event;
struct timeval tv_time;

// ┌───────────────────────────────────────────────────────────────────────────┐
// │ Prototypes                                                                │
// └───────────────────────────────────────────────────────────────────────────┘

static void Timeout(int, short, void *); // Timeout after 2000ms
static void Found();                     //

// ┌───────────────────────────────────────────────────────────────────────────┐
// │ Business functions                                                        │
// └───────────────────────────────────────────────────────────────────────────┘

void detector_init(event_base_t *ev_base, time_t delay_ms, const char *sq)
{

    // Initialize Timeout as one shot timer
    calc_timevalue(&tv_time, delay_ms);
    timeout_event = event_new(ev_base, -1, 0, &Timeout, NULL);
    // event_add(timeout_event, time);

    // Detector initial conditions
    sequence = sq;
    curr_state = 0;
    max_states = strlen(sq);
}

/**
 * @brief Entry point function callled every 100ms
 * 
 */
void Process(char symbol)
{
    static int index = 1;

    index = ++curr_state;
    if (index % 50 == 0)
        event_add(timeout_event, &tv_time);

    printf("%d: %c\n", index, symbol);
}

/**
 * @brief Reset input sequence buffer
 * 
 */
static void Timeout(int fd, short event, void *arg)
{
    (void)fd;
    (void)event;
    (void)arg;

    curr_state = 0;

    printf("::: Timeout :::\n");
}

/**
 * @brief Handles output when desired sequence is found
 * 
 */
static void Found()
{
    curr_state = 0;
    printf("Found.\n");
}
