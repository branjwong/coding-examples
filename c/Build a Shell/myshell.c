/*
Brandon J Wong
bjwong@sfu.ca
October 2nd, 2014

Assignment 1 - Build a Simple Shell
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <errno.h>

#define MAX_CMD 10
#define MAX_BUF 512
#define MAX_PATH 1024

void show_prompt();
void parse_cmd();
void print_tok();
void set_path();
void fork_child();
void check_exit();
void process_cmd();
void handle_errors();

pid_t childPID;
char buf[MAX_BUF];
char *cmd[MAX_CMD];
char path[MAX_PATH];
int cmdCount;
int shellStatus = 1;

// Print the prompt, with the time inside
void show_prompt()
{
    time_t curtime;
    struct tm *loctime;
    curtime = time(NULL);
	loctime = localtime(&curtime);				
	printf("<");
	if (loctime->tm_hour < 10)					// Add a 0 digit if necessary.
		printf("0%d:", loctime->tm_hour);
	else
		printf("%d:", loctime->tm_hour);
	if (loctime->tm_min < 10)					// Add a 0 digit if necessary.
		printf("0%d#> ", loctime->tm_min);
	else
		printf("%d#> ", loctime->tm_min);
}

// This part breaks the string, buf[], into tokens and stores a pointer to each token into "cmd[]"
void parse_cmd()
{
    int i;
    char *p;

    // reset cmd pointers to NULL, as the new set of commands hasn't been given yet
    for (i=0; i<cmdCount; i++)
    {
        cmd[i] = NULL;
    }

    fgets (buf, MAX_BUF, stdin);			// put user input in buffer

    i = 0;
    cmdCount = 0; 
    p = strtok (buf," \n");					// point to first token
    while (p != NULL)
    {
        cmd[i++] = p;						// set cmd[i] to token, i++
        p = strtok (NULL, " \n");			// point to next token
        cmdCount++;							// count number of commands
    }
}

/// This section iterates through "cmd[]" and displays each token on screen
void print_tok(char *cmd[], int cmdCount)
{
	int i;
    for (i=0;i<cmdCount; ++i)
    {
        printf("%s\n", cmd[i]);
    }
}

void set_path()
{		
	char *bin = "/bin/";
	strcpy(path, bin);						// start with /bin/ as path
	strcat(path, cmd[0]);					// add the next filename of the program to be executed to path
}

void handle_errors()
{
	if (errno == EACCES)
		printf("error: permission is denied for file\n");
    else if (errno == ENOEXEC)
        printf("error: file header is not recognised\n");
    else if (errno == ECHILD)
        printf("error: process specified by pid does not exist\n");
}

void fork_child()
{
	   
    childPID = fork();					// fork the process
    
    if (childPID == 0)					// if the process is the child
    {
    	// Child Process Work
    	execv(path, cmd);
    	handle_errors();
    	exit(EXIT_SUCCESS);
    }

    
    else if (childPID == -1)			// if the fork failed
    {
    	printf("error: fork failure\n");
    	exit(EXIT_FAILURE);
    }
   
    else								// if the process is the parent
    {
    	// Parent Process Work
    	waitpid(-1, 0, 0);             // first argument set to -1 -> wait for any child process
    }
}

void check_exit()
{
	if (strcasecmp(cmd[0], "exit") == 0)	// if exit is given as a command
		shellStatus = 0;					// allow loop to exit
}

void process_cmd()
{
	if (cmd[0] != NULL) 					// if there is input to process
	{
		set_path();
	    fork_child();
	    check_exit();
	}
}

int main ()
{

    while(shellStatus)
    {
    	show_prompt();
        parse_cmd();
        fflush(stdout);
        process_cmd();
    }
    return 0;
}

