/* Copyright 2021 Fotis Antonatos. See LICENSE */

#include <stdio.h>
#include <stdlib.h>

typedef enum direction { LEFT, RIGHT, CENTER } Direction;
typedef char (StateHandler)(char);

char etoa[CENTER + 1] = {'L', 'R', 'C'};
Direction gates[4]    = {LEFT};

StateHandler      *simulate_x1(char);
char               simulate_x2(char);
char               simulate_x3(char);
char               simulate_x4(char);
void               set_states(char *);
void               printgates();

void
printgates()
{
	char gateconfigs[5] = {etoa[gates[0]], etoa[gates[1]], etoa[gates[2]], etoa[gates[3]], '\0'};
	printf("%s->", gateconfigs);
}

StateHandler *
simulate_x1(char c)
{
	StateHandler *phdlr;

	switch (gates[0])
	{
	case LEFT:
		phdlr = &simulate_x2;
		break;
	case CENTER:
		phdlr = &simulate_x3;
		break;
	case RIGHT:
		phdlr = &simulate_x4;
		break;
	}

	gates[0] = (c == '0') ? (gates[0] + 1) % 3 : (gates[0] + 5) % 3;
	return phdlr;
}

char
simulate_x2(char c)
{
	char r;

	switch (gates[1])
	{
	case LEFT:
		r = 'B';
		break;
	case RIGHT:
		r = 'C';
		break;
	}

	gates[1] = (c == '0') ? (gates[1] + 1) % 2 : (gates[1] + 5) % 2;
	return r;
}

char
simulate_x3(char c)
{
	char r;

	switch (gates[2])
	{
	case LEFT:
		r = 'C';
		break;
	case RIGHT:
		r = 'D';
		break;
	}

	gates[2] = (c == '0') ? (gates[2] + 1) % 2 : (gates[2] + 5) % 2;
	return r;
}

char
simulate_x4(char c)
{
	char r;

	switch (gates[3])
	{
	case LEFT:
		r = 'D';
		break;
	case RIGHT:
		r = 'E';
		break;
	}

	gates[3] = (c == '0') ? (gates[3] + 1) % 2 : (gates[3] + 5) % 2;
	return r;
}

void
set_states(char *states)
{
	for (int i = 0; i < 4; i++) {
		switch (states[i])
		{
		case 'L':
			gates[i] = LEFT;
			break;
		case 'R':
			gates[i] = RIGHT;
			break;
		case 'C':
			gates[i] = CENTER;
			break;
		default: /* Should technically never happen */
			gates[i] = LEFT;
			break;
		}
	}
}

int
main (int argc, char **argv)
{
	StateHandler *st;
	char output;

	if (argc != 3)
		fprintf(stderr, "Usage: antonatos <paddle_states> <input>\n"), exit(1);

	set_states(argv[1]);

	printgates();
	for (char *iter = argv[2]; *iter != '\0'; iter++)
	{
		output = simulate_x1(*iter)(*iter);
		printgates();
	}

	printf("\b\b %c\n", output);
	return 0;
}