#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "ls2.h"

/**
 * main.c
 * 
 * Main program to execute ls2 under 2 modes or none.
 *
 * Created on: Feb 8, 2024
 * Author: Tyler Higashihara
 * 
 */
int main(int argc, char* argv[]) {
    // Check number of command-line arguments
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: %s <path> [exact-match-pattern]\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Mode 1
    if (argc == 2) {
        listPath(argv[1], NULL, TRUE); 
    } 
    // Mode 2
    else {
        listPath(argv[1], argv[2], TRUE);
    }

    return EXIT_SUCCESS;
}
