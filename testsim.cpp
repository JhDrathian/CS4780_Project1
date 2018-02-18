//header
//testsim
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[])
{
	cerr << "PID | " << (long)getpid() << " |"" Has been created!" << endl; //Let the user know a child has spawned
	int sleep_time = atoi(argv[1]); //set sleep time
	int repeat_factor = atoi(argv[2]); //set number of loops
	for ( int x = 0; x < repeat_factor; x++) //main loop
	{
		sleep(sleep_time); //sleepytime
		cerr << "PID | " << (long)getpid() << " | ""Has slept for " << sleep_time << " seconds" << endl; //primary job and output
	}
	cerr << "PID | " << (long)getpid() << " | ""Has terminated." << endl; //Let the user know a child has terminated
}

