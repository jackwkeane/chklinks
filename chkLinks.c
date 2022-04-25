/*
 * chkLink Program
 * Program 3 assignment
 * CSE109 Fall 2021
 * student ID (e.g., idk321): jwk324
 * student Last name: Keane
 * student First name: Jack
 * gitHub ID: @jackwkeane
 */

#include <stdio.h>       /* for fprintf, sprintf */
#include <stdlib.h>      /* for exit */
#include <errno.h>       /* error handling */
#include <string.h>      /* for ? */
#include "chkLinks_funcs.h"  /* for supporting functions */
#include "syscalls.h"       /* for wrapped system call functions */

int main (int argc, char* argv[]) {
    parseArgs(argc, argv);
    return 0;   
}