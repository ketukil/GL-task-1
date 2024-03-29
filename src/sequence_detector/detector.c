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

#include "detector.h"
#include "util.h"
#include <event2/event.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h> // malloc()
#include <string.h> // strlen()

// ┌───────────────────────────────────────────────────────────────────────────┐
// │ Enums, Variables, Structures, Typedefs                                    │
// └───────────────────────────────────────────────────────────────────────────┘

const char *pattern;
int32_t pattern_len;
int32_t state;
int32_t count = 0;

struct event_base *ev_base;
struct event *timeout_event;
struct timeval timeout_tv;

// ┌───────────────────────────────────────────────────────────────────────────┐
// │ Prototypes                                                                │
// └───────────────────────────────────────────────────────────────────────────┘

static void Timeout(int, short, void *);
static void Found();

// ┌───────────────────────────────────────────────────────────────────────────┐
// │ Business functions                                                        │
// └───────────────────────────────────────────────────────────────────────────┘

void detector_init(event_base_t *ev_base, time_t delay_ms, const char *search_pattern)
{
    // Initialize Timeout as one shot timer
    timeout_event = event_new(ev_base, -1, 0, &Timeout, NULL);
    calc_timevalue(&timeout_tv, delay_ms);

    // Detector initial conditions
    pattern = search_pattern;
    pattern_len = strlen(search_pattern);
    state = 0;
}

/**
 * @brief Tries to detect externally defined pattern in the
 * incoming symbols. Timesout if no character is received 
 * for time defined on initialization.
 * @param symbol Single input character
 */
bool Process(char symbol)
{
    bool is_found = false;

    count++;

    char pattern_symbol = pattern[state];
    if (pattern_symbol == symbol)
    {
        state++;

        if (state >= pattern_len)
        {
            Found(count);
            is_found = true;
        }
    }

    // Rearm timeout counter
    event_add(timeout_event, &timeout_tv);
    return is_found;
}

/**
 * @brief 
 * 
 */
static void Timeout(int fd, short event, void *arg)
{
    printf("::: Timeout :::\n");
    state = 0; // Reset Process state
    count = 0;

    (void)fd;
    (void)event;
    (void)arg;
}

/** 
 * @brief Handles output when desired sequence is found
 * 
 */
static void Found(int32_t counts)
{
    printf("::: %s ::: Found after %d counts:::\n", pattern, counts);
    state = 0; // Reset Process state
    count = 0;
}
