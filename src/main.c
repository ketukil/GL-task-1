/**
 * @file main.c
 * @author  ()
 * @brief
 * @version 0.1
 * @date 2021-08-23
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <event.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>


char *test_input_sequence[] = {"INTIS", "IblaNTIS", "INblaTIS", "INTblaIS", "INTIblaS", "INTISbla"};

char *search_string = "INTIS";

// ┌───────────────────────────────────────────────────────────────────────────┐
// │ Prototypes                                                                │
// └───────────────────────────────────────────────────────────────────────────┘
int Process(); // Run every 100ms
int Found();   // Call when sequence is found
int Timeout(); // Timeout after 2000ms if no character is received

// ┌───────────────────────────────────────────────────────────────────────────┐
// │ Main                                                                      │
// └───────────────────────────────────────────────────────────────────────────┘

int main()
{
    printf("Hello World!\n");

    return 0;
}

// ┌───────────────────────────────────────────────────────────────────────────┐
// │  Coment box                                                               │
// └───────────────────────────────────────────────────────────────────────────┘

/**
 * @brief 
 * 
 * @return int 
 */
int Process()
{
    printf("Process.\n");
    return 0;
}

int Found()
{
    printf("Found.\n");
    return 0;
}

int Timeout()
{
    printf("Timeout.\n");
    return 0;
}
