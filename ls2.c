#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ls2.h"
#include <sys/stat.h>

/**
 * ls2.c
 * This ls2.c makes an attempt at creating a recursive ls function
 *
 *  Created on: Feb 8, 2024
 *      Author: Tyler Higashihara
 */

// Function definitions here for ls2

/**
 * Print the given path with indentation based on the depth.
 * 
 * @param *path The path to print.
 * @param depth The indentation depth.
 */
void printIndentedPath(const char *path, int depth) {
    for (int i = 0; i < depth; ++i) {
        printf(INDENT);
    }
    printf("%s", path);
}

/**
 * Recursive function to list files and directories in a given path.
 * 
 * @param *path The path to list.
 * @param *search The exact-match pattern
 * @param depth The current depth in the recursive call stack.
 */
void listPathRecursive(const char *path, const char *search, int depth) {
    DIR *dir;
    struct dirent *d;
    struct stat s;

    // Open directory
    if ((dir = opendir(path)) == NULL) {
        perror("opendir");
        return;
    }

    // Loop through entries in directory
    while ((d = readdir(dir)) != NULL) {

        // Concatenate path with entry 
        char *fullpath = malloc(strlen(path) + strlen(d->d_name) + 2); // +1 for '/' +1 for '\0'
        if (fullpath == NULL) {
            perror("malloc");
            closedir(dir);
            return;
        }
        snprintf(fullpath, strlen(path) + strlen(d->d_name) + 2, "%s/%s", path, d->d_name);

        // Print the indented path
        printIndentedPath(fullpath, depth);

        // Get information of file or directory
        if (lstat(fullpath, &s) == -1) {
            perror("lstat");
            free(fullpath);
            continue;
        }

        // Check if the entry is a directory
        if (S_ISDIR(s.st_mode)) {
            printf("/\n");
            // Check if the entry is not "." and ".."
            if (strcmp(d->d_name, ".") != 0 && strcmp(d->d_name, "..") != 0) {
                if (search != NULL && strcmp(d->d_name, search) == 0) {
                    // Recurse only if specified subdirectory is found
                    listPathRecursive(fullpath, NULL, depth + 1);
                } else if (search == NULL) {
                    // Recurse for all directories if no search pattern is specified
                    listPathRecursive(fullpath, NULL, depth + 1);
                }
            }
        } else if (search == NULL || strcmp(d->d_name, search) == 0) {
            // Print file size
            printf(" (%lu bytes)\n", (unsigned long)s.st_size);
        }

        // Free memory
        free(fullpath);
    }

    // close it
    closedir(dir);
}

/*
 * Function to list files and directories in a given path.
 * If isRecursive is true, it lists recursively.
 * 
 * @param path: The path to list.
 * @param search: The exact-match pattern to filter results (can be NULL for no filter).
 * @param isRecursive: Flag indicating whether to list recursively (1 for true, 0 for false).
 */
void listPath(const char *path, const char *search, int isRecursive) {
    if (isRecursive) {
        listPathRecursive(path, search, 0);  // Start with depth 0
    }
}