/*
 * chkLink Supporting Functions
 * Program 3 assignment
 * CSE109 Fall 2021
 * student ID (e.g., idk321): jwk324
 * student Last name: Keane
 * student First name: Jack
 * gitHub ID: @jackwkeane
 */

#include "chkLinks_funcs.h"

/* in: Nothing out: prints out help message. */
void help() {
    fprintf(stdout, "\nUsage: chkLinks <userid> <password> <server> <fully-qualified filename>\n\n");
}

/* in: userid, password, server, pathname out: CURL return code */
int ftpDownload(char *userid, char *password, char *server, char *pathname, ftpFile_t file) {
  char str[128];                                               /* character string for setting curl settings, call values, or bail messages */
  CURLcode crc;                                                /* variable to hold CURL function recturn codes */
  CURL *cp = NULL;                                             /* pointer/handle to curl session/transfer */
  ftpFile_t FTPfile = {file.filename, NULL };              /* declare and define an ftpFile_t object, you can change filename or make it a variable */

  curl_global_init(CURL_GLOBAL_ALL);                                           /* 1 - initialize curl global state; setup and initialize underlying libraries */

  cp = curl_easy_init();                                       /* 2 - initialize pointer/handle for curl session/transfer */

  if (cp) {                                                    /* check if curl handle creation was successful, and if so, proceed */
    sprintf(str, "%s:%s", userid, password);                   /* set string str to "<userid>:<password>" */

    curl_easy_setopt(cp, CURLOPT_USERPWD, str);                                                           /* 3 - set username and password */

    sprintf(str, "sftp://%s/%s", server, pathname);            /* change string str to "sftp://<server>/<pathname>" */

    curl_easy_setopt(cp, CURLOPT_URL, str);                                                           /* 4 - set protocol, server, directory, and file */

    curl_easy_setopt(cp, CURLOPT_WRITEFUNCTION, ftpWrite);                                                             /* 5 - declare our callback to be called when there's data to be written */

    curl_easy_setopt(cp, CURLOPT_WRITEDATA, &FTPfile);                                                             /* 6 - set a pointer to our struct to pass to the callback */

    crc = curl_easy_perform(cp);                                                     /* 7 - perform the curl call and capture the return value */

    curl_easy_cleanup(cp);                                                           /* 8 - cleanup local session/transfer */
  
    if (FTPfile.stream) {
      Fclose(FTPfile.stream);
    }                                                           /* 9 - close the local file */

    curl_global_cleanup();                                                           /* 10 - free and clean up associated global resources init call allocated */

  } else {                                                     /* bail in the unlikely event curl handle creation failed */
    fprintf(stderr, "Initialization of curl session/transfer handle was unsuccessful\n");
    exit(202);
  }

  //file->stream = *FTPfile.stream;
  return (int)crc;     
}                                        


/* in: buffer ptr, buffer size, num buffers, output file ptr; return: bytes written */
size_t ftpWrite(char *buffer, size_t size, size_t nmemb, void *stream) { 
    ftpFile_t *oFile = (ftpFile_t *)stream;
    if(!oFile->stream) {
       oFile->stream = Fopen(oFile->filename, "w");  /* open file for writing */
    }
    return Fwrite(buffer, size, nmemb, oFile->stream);
}

/* in: argc, argv */
void parseArgs(int argc, char *argv[]) {
  if (argc == 2 && (strcmp(argv[1], "-h") || strcmp(argv[1], "--help"))) {
    help();
    exit(0);
  } else if (argc == 5) {
    // Setting file name
    char *filename = NULL;
    size_t fileCount = 0; 
    // Incrementing file count and also getting name of file. 
    fileCount = newfilename(&filename, fileCount); 
    // Recursive link checking function.
    searchhrefs(argv[1], argv[2], argv[3], argv[4], filename, fileCount);

  } else {
    fprintf(stderr, "Expecting 4 arguments to be passed\n");
    help();
  }
}     

/* in: filename, count -> mutates filename to include count and returns count */
size_t newfilename(char **filename, size_t count) {
    *filename = Malloc(256 * sizeof(char));
    strcpy(*filename, "/tmp/file_");
    char pid[10]; 
    sprintf(pid, "%d", (int)getpid());
    strcat(*filename, strcat(pid, "_"));
    char countChar[12];
    sprintf(countChar, "%zu", count);
    strcat(*filename, countChar);  
    return ++count;
}     

/* in: username, password, host, loc, filename, filenum return: success with 0, failure with -1 */   
void searchhrefs(char *user, char *password, char *host, char *loc, char *filename, size_t fileNum) {
    // Creating null file pointer and null ftpFile_t
    FILE *dwnld = NULL;
    ftpFile_t file = {"dwnld", NULL};
    file.filename = filename;
    
    // Downloading file
    //fprintf(stdout, "Being passed in host: %s\t\tBeing passed in location: %s\n", host, loc);
    int crc = ftpDownload(user, password, host, loc, file);

    // Error checking the CURL Return code.
    if (crc) {
      fprintf(stderr, "%s (%d) - %s from %s\n", curl_easy_strerror(crc), crc, loc, host);
      //exit(crc);
    } else {
      dwnld = Fopen(filename, "r");
      // Will store - line + link - reduced down to just link.
      char link[256]; 

      // Iterating over file
      char i;
      while ((i = fgetc(dwnld)) != EOF) {
        if(i == '<') {
          char j = fgetc(dwnld);
          if (j == 'a') {
            fscanf(dwnld, "%[^>]", link);
            char *pre = strstr(link, "http");
            if (pre) {
              char *mid = strstr(link, "://");
              if (mid) {
                char nHost[256];
                char nLoc[256];
                
                char *strt = mid + 3; // Moves forward 3 indeces skipping past "://"
                char *end = strchr(strt, '/');
                *end = '\0';
                end++; 
                end[strlen(end) - 1] = '\0';
                strcpy(nHost, strt);
                strcpy(nLoc, end);
                char *newfn;
                fileNum = newfilename(&newfn, fileNum);
                strcpy(filename, newfn);
                searchhrefs(user, password, nHost, nLoc, filename, fileNum);
              } else {
                fprintf(stderr, "No \"://\" found in URL (203) - %s\n", link);
              }
            } else {
              fprintf(stderr, "No \"http[s]\" found in URL (202) - %s\n", link);
            }
          } else if (j == '!') {
            char junk[256];
            fscanf(dwnld, "%[^>]", junk);
          }
        } 
      }
      //fprintf(stdout, "File name: %s\n", filename);
      Fclose(dwnld);
      //Unlink(filename);
    } 
    
    
}  





