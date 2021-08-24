/**
 * @file seq_detect.c
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
#include "seq_detect.h"

// ┌───────────────────────────────────────────────────────────────────────────┐
// │ Enums, Variables, Structures, Typedefs                                    │
// └───────────────────────────────────────────────────────────────────────────┘

struct event_base *event_base;
struct event *heartbeat_event, *timeout_event;
struct timeval time_100ms = {0, 100000};
struct timeval time_2000ms = {2, 0};

extern uint8_t UART_RX_REG;
// ┌───────────────────────────────────────────────────────────────────────────┐
// │ Prototypes                                                                │
// └───────────────────────────────────────────────────────────────────────────┘

static void Process(evutil_socket_t, short, void *); // Runs every 100ms
static void Timeout(evutil_socket_t, short, void *); // Timeout after 2000ms
static void Found();                                 //

// ┌───────────────────────────────────────────────────────────────────────────┐
// │ Initialization                                                            │
// └───────────────────────────────────────────────────────────────────────────┘

/**
 * @brief Initialize sequence detector
 * 
 * @param sequence of characters to be detected
 */
void sequence_detector_init(const char *sequence)
{

    event_base = event_base_new();

    heartbeat_event = event_new(event_base, -1, EV_PERSIST, &Process, (void *)sequence);
    timeout_event = event_new(event_base, -1, 0, &Timeout, NULL);
    event_add(heartbeat_event, &time_100ms);

    event_base_dispatch(event_base);
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
    const char *sequence = arg;
    static int index = 0;

    printf("Process (%d, %d, %s): %d\n", fd, event, sequence, index++);
    if (index == 50)
        event_add(timeout_event, &time_2000ms);

    if(index == 100)
        event_add(timeout_event, &time_2000ms); // Rearm oneshot timer

    if (strcmp(sequence, "GLROX") == 0)
        Found();
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
    printf("Found. %c\n", UART_RX_REG);
}