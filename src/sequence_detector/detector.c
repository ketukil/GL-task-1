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
#include <event2/event.h>
#include "detector.h"

// ┌───────────────────────────────────────────────────────────────────────────┐
// │ Enums, Variables, Structures, Typedefs                                    │
// └───────────────────────────────────────────────────────────────────────────┘

struct DETECTOR
{
    int curr_state;
    int max_states;
    const char *sequence;
    event_t *event;
    timeval_t *time;
} detector;

// ┌───────────────────────────────────────────────────────────────────────────┐
// │ Prototypes                                                                │
// └───────────────────────────────────────────────────────────────────────────┘

static void Timeout(evutil_socket_t, short, void *); // Timeout after 2000ms
static void Found();                                 //

// ┌───────────────────────────────────────────────────────────────────────────┐
// │ Business functions                                                        │
// └───────────────────────────────────────────────────────────────────────────┘

void detector_init(const char *sq, event_t *ev, timeval_t *time)
{
    detector.sequence = sq;
    detector.curr_state = 0;
    detector.max_states = strlen(sq);
    detector.event = ev;
    detector.time = time;
}

/**
 * @brief Entry point function callled every 100ms
 * 
 */
void Process(char symbol)
{
    static int index = 0;
    printf("%c\n", symbol);
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

    printf("::: Timeout :::\n");
}

/**
 * @brief Handles output when desired sequence is found
 * 
 */
static void Found()
{
    printf("Found.\n");
}