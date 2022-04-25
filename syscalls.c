/*
 * hashTab Supporting Functions
 * Program 2 assignment
 * CSE109 Fall 2021
 * student ID (e.g., idk321): jwk324
 * student Last name: Keane
 * student First name: Jack
 * gitHub ID: @jackwkeane
 */

#include "syscalls.h"

/* Defining the debug macro from the make file */
#ifdef DEBUG
#define DEBUG 1
#else
#define DEBUG 0
#endif

/* in: bytes to allocate; return: ptr of type void to allocated memory */
void *Malloc(size_t numBytes) {                                             
    void *ptr = NULL;                                                 
    if ((ptr = malloc(numBytes)) == NULL) {                                
        fprintf(stderr, "Could not allocate space - %s", strerror(errno));   
        exit(errno);                                                            
    }
    return ptr; /* Functions of type void * call for a pointer to be returned */
}

/* in: path/file, mode; return: file ptr */
FILE *Fopen(const char *path, const char *mode) {
    FILE *fp = NULL;
    if((fp = fopen(path, mode)) == NULL){
        fprintf(stderr, "fopen error (%d): %s\n", errno, strerror(errno)); /* Formatted print taken from program directions */
        exit(errno); 
    }
    return fp;
}

/* in: buffer ptr, buffer size, num buffers, input file ptr; return: bytes read */
size_t Fread(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t num_items = 0;
    if((num_items = fread(ptr, size, nmemb, stream)) != nmemb)  { /* If statement to check to see if the return value differs from the nmemb parameter, therefore causing an error or meaning the function has reached the end of file. */
        if(!feof(stream) && ferror(stream)) { /* If statement that if true means that fread returned an error */
            fprintf(stderr, "fread error (%d): %s\n", errno, strerror(errno)); /* Formatted print taken from program directions */
            exit(errno);
        }
    }
    return num_items; /* Returns the totla number of elements successfully read */
}        

/* in: file ptr */
void Fclose(FILE *stream) {
    if(fclose(stream)) { /* Checks to see if the stream returns EOF */ 
        fprintf(stderr, "fclose error (%d): %s\n", errno, strerror(errno)); /* Formatted print taken from program directions */
        exit(errno);
    }
}   

/* in: buffer ptr, buffer size, num buffers, output file ptr; return: bytes written */
size_t Fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t num_items;
    if((num_items = fwrite(ptr, size, nmemb, stream)) != nmemb)  { /* If statement to check to see if the return value differs from the nmemb parameter, therefore causing an error */
        fprintf(stderr, "fwrite error (%d): %s\n", errno, strerror(errno)); /* Formatted print taken from program directions */
        exit(errno);
    }
    return num_items; /* Returns the totla number of elements successfully returned as size_t object */
}  

/* in: int array, index 0 will be read end, index 1 will be write end out: returns 0 on success, returns -1 on error.*/
int Pipe(int filedes[]) {
    if (pipe(filedes) == -1) {       
        fprintf(stderr, "pipe error (%d): %s\n", errno, strerror(errno));
        exit(errno);
    } else {
        return pipe(filedes);
    }
}   

/* in: void out: returns a new process */
pid_t Fork() {
    pid_t pid;
    if ((pid = fork()) == -1) {  /* create process */
        fprintf(stderr, "fork error (%d): %s\n", errno, strerror(errno));
        exit(errno);
    } else {
        return pid;
    }
} 

/* in: file descriptor, buffer to read data from, length of buffer out: number of bytes read on success */
ssize_t Read(int fildes, void *buf, size_t nbyte) {
    ssize_t numBytes;
    if ((numBytes = read(fildes, buf, nbyte)) == 0) { /* read in a string from the pipe */
      fprintf(stderr, "PARENT: read error (%d): %s\n", errno, strerror(errno));
      exit(errno);
    } else {
        return numBytes; /* If no error, normal return. */
    }
}

/* in: file descriptor, buffer to read data from, length of buffer out: number of bytes written on success */
ssize_t Write(int fildes, const void *buf, size_t nbyte) {
    ssize_t numBytes; 
    if ((numBytes = write(fildes, buf, nbyte)) == -1) { /* send "string" down the pipe */
        fprintf(stderr, "CHILD: write error (%d): %s\n", errno, strerror(errno));
        exit(errno);
    } else {
        return numBytes; /* If no error, normal return. */
    }
}

/* in: file descriptor out: 0 on success, -1 on error */
int Close(int fildes) {
    if (close(fildes) == -1) {  /* close unneeded "write" end of pipe */
      fprintf(stderr, "PARENT: close error (%d): %s\n", errno, strerror(errno));
      exit(errno);
    } else {
        return close(fildes); /* If no error, normal return. */
    }
}

/* in: specificed domain, specifiec type, optional protocol, sv[0] and sv[1] socket pair out: returns 0 on success, -1 on error */
int Socketpair(int domain, int type, int protocol, int sv[2]) {
    if (socketpair(domain, type, protocol, sv) < 0) {
      fprintf(stderr, "socketpair error (%d): %s\n", errno, strerror(errno));
      exit(errno);
    } else {
        return socketpair(domain, type, protocol, sv);
    }
} 

/* in: argument status out: process ID of dead children */
pid_t Wait(int *stat_loc) {
    pid_t pid;
    if ((pid = wait(stat_loc)) == -1){
        fprintf(stderr, "wait error (%d): %s\n", errno, strerror(errno));
        exit(errno);
    }
    return pid;
}

/* in: file descriptor out: deleted file and link return: 0 for success, -1 on failure */
int Unlink(const char *path) {
    if (unlink(path) == -1) {
        fprintf(stderr, "unlink error (%d): %s\n", errno, strerror(errno));
        exit(errno);
    }
    return unlink(path); 
}