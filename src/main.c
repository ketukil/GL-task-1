/**
 * @file main.c
 * @author Damjan Belavic (damjan.belavic@vuka.hr)
 * @brief GlobalLogic Embedded Software Engineer in C / Task 1
 * @version 1.0
 * @date 2021-08-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h> // srand(), rand()
#include <stdbool.h>
#include <stdint.h>
#include <string.h> // strlen()
#include <event2/event.h>
#include "detector.h"
#include "util.h"

#define GET_SIZE(p) sizeof(p) / sizeof(*p)

// ┌───────────────────────────────────────────────────────────────────────────┐
// │ CONSTANTS & TEST                                                          │
// └───────────────────────────────────────────────────────────────────────────┘

#define TEST_FROM_LIST 1 // 0 = random, 1 = from test list

const char *const TEST_INPUT_SEQUENCE[] = {
    "GabfdbLbsfbdRbasgOX",  // TRUE
    "AA4hfghdAAGLROX",      // TRUE
    "GLRObas832hXbasb",     // TRUE
    "GLROobiapjso83basb",   // FALSE (no X)
    "glroxbpoaijspoiasjdb", // FALSE (lower case)
    "GLpboiasjdbpoijOX"};   // FALSE (no R)
#define TEST_INPUT_SIZE GET_SIZE(TEST_INPUT_SEQUENCE)

const time_t TICKER_PERIOD = 10; // ms
const time_t TIMEOUT_PERIOD = 2000; // ms
const char *const SEARCH_SEQUENCE = "GLROX";

// ┌───────────────────────────────────────────────────────────────────────────┐
// │ Enums, Variables, Structures, Typedefs                                    │
// └───────────────────────────────────────────────────────────────────────────┘

// ┌───────────────────────────────────────────────────────────────────────────┐
// │ Prototypes                                                                │
// └───────────────────────────────────────────────────────────────────────────┘

void ticker(int, short, void *);
void ticker_init(struct event_base *, time_t);
char get_rand_ascii(void);
char get_char_from_list(const char *const *, int32_t);

// ┌───────────────────────────────────────────────────────────────────────────┐
// │ Main                                                                      │
// └───────────────────────────────────────────────────────────────────────────┘

int main(int argc, char *argv[])
{
    struct event_base *ev_base;

    srand(39); // Seed generated by fair d100 dice roll

    ev_base = event_base_new();

    ticker_init(ev_base, TICKER_PERIOD);
    detector_init(ev_base, TIMEOUT_PERIOD, SEARCH_SEQUENCE);

    printf("::: Detector is detecting... please stand by :::\n");

    event_base_dispatch(ev_base);

    (void)argc;
    (void)argv;

    return 0;
}

// ┌───────────────────────────────────────────────────────────────────────────┐
// │ Test related code                                                         │
// └───────────────────────────────────────────────────────────────────────────┘

/**
 * @brief Ticker is called periodically based on value passed
 * on initialization
 * 
 * @param fd 
 * @param event 
 * @param arg 
 */
void ticker(int fd, short event, void *arg)
{
    bool is_sequence_found;
    char input_character;

#if TEST_FROM_LIST
    input_character = get_char_from_list(TEST_INPUT_SEQUENCE, TEST_INPUT_SIZE);
#else
    input_character = get_rand_ascii();
#endif

    is_sequence_found = Process(input_character);
    if (is_sequence_found)
    {
        printf("::: FOUND :::");
    }

    (void)fd;
    (void)event;
    (void)arg;
}

/**
 * @brief Ticker initialization function
 * 
 * @param ev_base Event base structure
 * @param delay_ms number of milliseconds
 */
void ticker_init(struct event_base *ev_base, time_t delay_ms)
{
    struct event *ticker_event;
    struct timeval time_tv;

    ticker_event = event_new(ev_base, -1, EV_PERSIST, &ticker, NULL);
    calc_timevalue(&time_tv, delay_ms);
    event_add(ticker_event, &time_tv);
}

/**
 * @brief Generates ASCII character limited to Base64 range
 * 
 * @return char Base64 ASCII character
 */
char get_rand_ascii(void)
{
    char rand_char;
    for (;;)
    {
        rand_char = rand() % INT8_MAX;

        switch (rand_char)
        {
        case '+':
        case '/':
        case '0' ... '9':
        case 'A' ... 'Z':
        case 'a' ... 'z':
            return rand_char;
        default:
            break;
        }
    }
}

/**
 * @brief Get the char from list object in incremental order on every call.
 * Warps around when it reaches the end of the last char in last element
 * @param LIST List of string literals
 * @return char Single character form that list
 */
char get_char_from_list(const char *const LIST[], int32_t LIST_SIZE)
{
    static int32_t index = 0;
    static int32_t offset = 0;

    const char *string = LIST[index];
    int str_len_max = strlen(string);
    char character = string[offset++];

    if (offset >= str_len_max)
    {
        offset = 0;
        index++;
    }
    if (index >= LIST_SIZE)
    {
        index = 0;
        offset = 0;
    }

    return character;
}
