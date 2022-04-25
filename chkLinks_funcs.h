/*
 * chkLink Supporting Functions
 * Program 3 assignment
 * CSE109 Fall 2021
 * student ID (e.g., idk321): jwk324
 * student Last name: Keane
 * student First name: Jack
 * gitHub ID: @jackwkeane
 */

#ifndef CHKLINKS_FUNCS
#define CHKLINKS_FUNCS

#include <stdio.h>          /* for fprintf, etc. */
#include <stdlib.h>         /* for exit */
#include <string.h>         /* for strerror */
#include <errno.h>          /* for errno */
#include <curl/curl.h>      /* for curl, baby! */
#include <sys/socket.h>     /*  for socketpair */
#include <sys/wait.h>       /* for wait */
#include "syscalls.h"       /* for wrapped system calls */

/* Struct */
struct ftpfile {
  const char *filename;   /* name to store the file as */
  FILE *stream;           /* file pointer/handle */
};
typedef struct ftpfile ftpFile_t;

/* Define Function Headers Here */
void help();                                                              /* in: Nothing out: prints out help message. */
int ftpDownload(char *, char *, char *, char *, ftpFile_t);             /* in: userid, password, server, ftpFile,e return: CURL return code */
size_t ftpWrite(char *, size_t, size_t, void *);                          /* in: buffer ptr, buffer size, num buffers, output file ptr; return: bytes written */
void parseArgs(int, char *[]);                                            /* in: argc, argv */
void searchhrefs(char *, char *, char*, char*, char*, size_t);             /* in: username, password, file, filename, filenum return: success with 0, failure with -1 */     
size_t newfilename(char**, size_t);                                       /* in: filename, count -> mutates filename to include count returns: count incremented */

#endif