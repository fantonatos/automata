/*
 * © 2021 Fotis Antonatos
 *
 * Copying and distribution of this software, in binary or source format,
 * and any accompanying files or documentation, with or without modification,
 * are permitted in any medium without royalty provided the copyright
 * notice and this notice are preserved.  This file is offered as-is,
 * without any warranty.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

struct transition {
	char input;
	short dest;
	struct transition *next;
};

enum outcome { UNKNOWN = 0, ACCEPTED = 1, REJECTED = -1};

static enum outcome         results[1000]       = { UNKNOWN };
static struct transition   *transitions[1000]   = { NULL };
static bool                 accept_states[1000] = { false };
static signed short         start = -1;

void
ldfile_transition_add(char input, short dest_state, short origin_state)
{
	struct transition *tr = (struct transition *) calloc(1, sizeof(struct transition));
	*tr = (struct transition) { input, dest_state, NULL };

	if (transitions[origin_state] == NULL)
		transitions[origin_state] = tr;
	else {
		struct transition *iter = transitions[origin_state];
		while(iter->next != NULL) {
			iter = iter->next;
		}
		iter->next = tr;
	}
}

char
ldfile_transition_getinput(char *cmd)
{
	char b, *ftab = strchr(cmd, '\t'), *ntab = strchr(ftab + 1, '\t');
	(void) strncpy(&b, ntab + 1, 1);
	return b;
}

short
ldfile_transition_getdest(char *cmd)
{
	char b[5] = {0}, *tab, *lf, **tmp = NULL;
	tab = strchr(cmd, '\t');
	tab = strchr(tab + 1, '\t');
	tab = strchr(tab + 1, '\t');
	lf = strchr(cmd, '\0');

	(void) strncpy(b, tab, lf - tab);
	return (short) strtol(b, tmp, 10);
}

short
ldfile_getstate(char *cmd)
{
	char b[5] = {0}, *ftab = strchr(cmd, '\t'), 
	                 *ntab = strchr(ftab + 1, '\t'),
	                **tmp = NULL;
	(void) strncpy(b, ftab, ntab - ftab);
	return (short) strtol(b, tmp, 10);
}

void
ldfile(char *filename)
{
	FILE *fp;
	char c, b[25] = {0};
	int bx = 0;

	if (!(fp = fopen(filename, "r")))
		printf("Failed to open %s\n", filename), exit(1);

	while ((c = fgetc(fp))) {
		if (c == '\n' || c == EOF) {
			if (b[0] == 's') {
				if (strstr(b, "start"))
					start = ldfile_getstate(b);
				if (strstr(b, "accept"))
					accept_states[ldfile_getstate(b)] = true;
			} else if (b[0] == 't')
				ldfile_transition_add(
					ldfile_transition_getinput(b),
					ldfile_transition_getdest(b),
					ldfile_getstate(b)
				);
			memset(b, 0, sizeof(b));
			bx = 0;
		} else
			b[bx++] = c;

		if (c == EOF)
			break;
	}
	fclose(fp);
}

void
simulate(short state, char *input)
{
	char inch = input[0], *remaining = calloc(1, strlen(input) + 1);
	bool recognized = false;
	(void) strcpy(remaining, input + 1);

	for (struct transition *iterator = transitions[state]; iterator != NULL; iterator = iterator->next)
		if ((inch == iterator->input) && (recognized = true))
			simulate(iterator->dest, remaining);
	
	free(remaining);
	if (input[0] == '\0') results[state] = (accept_states[state]) ? ACCEPTED : REJECTED;
}

int
main(int argc, char **argv)
{
	char *filename, *input;
	bool accepted = false;
	short i;

	if (argc != 3)
		fprintf(stderr, "Usage: antonatos sample.txt 'input'\n"), exit(1);

	/* Read the file and construct the automaton. */
	filename = argv[1];
	input = argv[2];
	ldfile(filename);

	simulate(start, input);

	for (i = 0; i < 1000; i++)
		if (results[i] == ACCEPTED) accepted = true;

	printf("%s", accepted ? "accept" : "reject");

	for (i = 0; i < 1000; i++)
		if ((results[i] == ACCEPTED && accepted == true) || (results[i] == REJECTED && accepted == false))
			printf(" %d", i);

	printf("\n");
	return 0;
}
