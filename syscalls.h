/*
 * hashTab Supporting Functions
 * Program 2 assignment
 * CSE109 Fall 2021
 * student ID (e.g., idk321): jwk324
 * student Last name: Keane
 * student First name: Jack
 * gitHub ID: @jackwkeane
 */

#ifndef SYSCALLS
#define SYSCALLS

#include <stdio.h>          /* for fprintf */
#include <stdlib.h>         /* for exit */
#include <errno.h>          /* for errno */
#include <string.h>         /* for strerror */
#include <unistd.h>         /* for fork, pipe */
#include <sys/socket.h>     /* for socketpair */
#include<sys/wait.h>        /* for wait */

void *Malloc(size_t);                                                        /* in: bytes to allocate; return: ptr of type void to allocated memory */
FILE *Fopen(const char*, const char*);                                       /* in: path/file, mode; return: file ptr */
size_t Fread(void *, size_t, size_t, FILE *);                                /* in: buffer ptr, buffer size, num buffers, input file ptr; return: bytes read */
void Fclose(FILE*);                                                          /* in: file ptr */
int Pipe(int []);                                                            /* in: int array, index 0 will be read end, index 1 will be write end out: returns 0 on success, returns -1 on error.*/
pid_t Fork();                                                                /* in: void out: returns a new process */
size_t Fwrite(const void *, size_t, size_t, FILE *);                         /* in: buffer ptr, buffer size, num buffers, output file ptr; return: bytes written */
ssize_t Read(int, void *, size_t);                                           /* in: file descriptor, buffer to read data from, length of buffer out: number of bytes read on success */
ssize_t Write(int, const void *, size_t);                                    /* in: file descriptor, buffer to read data from, length of buffer out: number of bytes written on success */
int Close(int);                                                              /* in: file descriptor out: 0 on success, -1 on error */
int Socketpair(int, int, int, int[]);                                        /* in: specificed domain, specifiec type, optional protocol, sv[0] and sv[1] socket pair out: returns 0 on success, -1 on error */
pid_t Wait(int*);                                                            /* in: argument out: process ID of dead child processes */
int Unlink(const char *);                                                    /* in: file descriptor out: deleted file and link return: 0 for success, -1 on failure */







#endif