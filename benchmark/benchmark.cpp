/* Copyright 2021 Fotis Antonatos. See LICENSE */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include <string>

int
main(int argc, char **argv)
{
	std::string command;
	struct timeval start, end;
	
	for (int i = 1; i < argc; i++)
		command = std::string(command + " " + argv[i]);

	gettimeofday(&start, NULL);
	system(command.c_str());
	gettimeofday(&end, NULL);

	long delta = ((end.tv_sec - start.tv_sec)*1000000L+end.tv_usec) - start.tv_usec;

	printf("\nExecution Time: %ld μs\n", delta);

	return 0;
}
