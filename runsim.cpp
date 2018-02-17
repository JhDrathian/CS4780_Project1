//runsim program
//header

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

const int PROCESS_LIMIT = 20;

int main (int argc, char *argv[])
{
	int pr_limit = 0;
	int pr_count = 0;
	
	if (argc != 2)
	{
		cout << "Please specify a command line argument as single, positive integer " << endl;
	}
	else if (argc == 2 && atoi(argv[1]) > 0 && atoi(argv[1]) <= PROCESS_LIMIT)
	{
		pr_limit = atoi(argv[1]);
	}
	else
	{
		cout << "Please specify a single, positive integer greater than 0 and less than 20." << endl;
	}
	cout << "pr_limit is " << pr_limit << endl;
}

