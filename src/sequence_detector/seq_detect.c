/**
 * @file seq_detect.c
 * @author ketukil (cat2kill@gmial.com)
 * @brief 
 * @version 1.0
 * @date 2021-08-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <event2/event.h>
#include "seq_detect.h"

// ┌───────────────────────────────────────────────────────────────────────────┐
// │ Prototypes                                                                │
// └───────────────────────────────────────────────────────────────────────────┘

static void Process(evutil_socket_t, short, void *); // Runs every 100ms
static void Found();                     // 
static void Timeout(evutil_socket_t, short, void *); // Timeout after 2000ms

// ┌───────────────────────────────────────────────────────────────────────────┐
// │ Initialization                                                            │
// └───────────────────────────────────────────────────────────────────────────┘


/**
 * @brief Initialize sequence detector
 * 
 * @param sequence of characters to be detected
 */
void sequence_detector_init(const char * sequence)
{
    struct event_base *base;
    struct event *heartbeat_event, *timeout_event;
    struct timeval time_100ms = { 0, 100000 };
    struct timeval time_2000ms = { 2, 0 };

    base = event_base_new();

    heartbeat_event = event_new(base, -1, EV_PERSIST, &Process, sequence);
    timeout_event = event_new(base, -1, EV_PERSIST, &Timeout, NULL);

    event_add(heartbeat_event, &time_100ms);
    event_add(timeout_event, &time_2000ms);

    event_base_dispatch(base);
}

// ┌───────────────────────────────────────────────────────────────────────────┐
// │ Business functions                                                        │
// └───────────────────────────────────────────────────────────────────────────┘

/**
 * @brief Entry point function callled every 100ms
 * 
 */
static void Process(int fd, short event, void *arg)
{
    const char *seq = arg;
    static int index = 0;

    printf("Process (%d, %d, %s): %d\n", fd, event, seq, index++);
}

/**
 * @brief Reset input sequence buffer
 * 
 */
static void Timeout(int fd, short event, void *arg)
{
    printf("Timeout (%d, %d, %p)\n", fd, event, arg);
}

/**
 * @brief Handles output when desired sequence is found
 * 
 */
static void Found()
{
    printf("Found.\n");
}