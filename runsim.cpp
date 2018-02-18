//runsim program
//header

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

using namespace std;

const int PROCESS_LIMIT = 20;
const int ARRAY_INPUT_CHAR_LIMIT = 100;

int makeargv(char *s, char *delimiters, char ***argvp);

int main (int argc, char *argv[])
{
	int pr_limit = 5; //default initilization, controls the maximum concurrent child processes
	int pr_count = 0; //tracks number of active children
	char input_array[ARRAY_INPUT_CHAR_LIMIT];
	char ** argv_array; // for makeargv
	pid_t childpid = 0; //for forking()
	int option = 0; 

   	if (argc < 2) //If number of arguments is 1 or less, give command line option
	{
		cerr << "Please enter -n followed by a positive integer to set the process limit. Process limit is set to 5 by default." << endl;
		return 1;
	}
                                  
	while ((option = getopt(argc, argv, "n:")) != -1) //process command line options with getopt()
	{
		switch (option)
		{
			case 'n' : pr_limit = atoi(optarg);
				break;
			default :
			{	 
				cerr << "Please use -n to specify a process limit. Default value is 5." << endl;
				exit (EXIT_FAILURE);
			}
		}
	}
	
	if (pr_limit < 1) //For the program to be even slightly useful, please give the computer a useful input
	{
		cerr << "Please specify a positive integer greater than 0." << endl;
		return 1;
	}

	cerr << "The Process Limit has been set to:  " << pr_limit << endl;

	while (fgets(input_array, ARRAY_INPUT_CHAR_LIMIT, stdin) != NULL) //read input from redirected stdin
	{
		if (pr_count == pr_limit) //if we hit the limit, we wait
		{
			wait(NULL);
			pr_count--;
			cerr << "pr_count update: " << pr_count << endl;
		}	
		makeargv(input_array, " ", &argv_array); //makeargv magic
		childpid = fork(); //dinner time
		if (childpid < 0) //check for a failed fork
		{
			perror("Failed to Fork");
		}
		if (childpid == 0) //spawn a child process
		{
			execvp(argv_array[0], &argv_array[0]);
			perror("Exec call was unsuccessful");
		}
		pr_count++; //increment for every spawn child
		cerr << "pr_count update: " << pr_count << endl;
		if (waitpid(-1, NULL, WNOHANG) != 0) //watching for children to terminate and decrement the count in order to spawn a new child
		{
			pr_count--;
			cerr << "pr_count update: " << pr_count << endl;
		}	
	}
	while (1) //finally, wait until ALL children terminate
	{
		childpid = wait(NULL);
		if (childpid == -1)
		{
			break;
		}
	}
	cerr << "Parent Process has completed." << endl;
}

int makeargv(char *s, char *delimiters, char ***argvp) //copypasta, the best kind of pasta
{
   char *t;
   char *snew;
   int numtokens;
   int i;
    /* snew is real start of string after skipping leading delimiters */
   snew = s + strspn(s, delimiters);
                              /* create space for a copy of snew in t */
   if ((t = calloc(strlen(snew) + 1, sizeof(char))) == NULL) {
      *argvp = NULL;
      numtokens = -1;
   } else {                     /* count the number of tokens in snew */
      strcpy(t, snew);
      if (strtok(t, delimiters) == NULL)
         numtokens = 0;
      else
         for (numtokens = 1; strtok(NULL, delimiters) != NULL;
              numtokens++)
              ;  
                /* create an argument array to contain ptrs to tokens */
      if ((*argvp = calloc(numtokens + 1, sizeof(char *))) == NULL) {
         free(t);
         numtokens = -1;
      } else {            /* insert pointers to tokens into the array */
         if (numtokens > 0) {
            strcpy(t, snew);
            **argvp = strtok(t, delimiters);
            for (i = 1; i < numtokens + 1; i++)
               *((*argvp) + i) = strtok(NULL, delimiters);
         } else {
           **argvp = NULL;
           free(t);
         }
      }
   }   
   return numtokens;
}
