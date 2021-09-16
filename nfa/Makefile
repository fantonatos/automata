EXE = antonatos
CC = gcc
CFLAGS1 = -Ofast -Wall -Wextra
CFLAGS2 = -Ofast -Wall -Wextra -Werror

antonatos: antonatos.c
	$(CC) $(CFLAGS1) antonatos.c -o $(EXE)

release: antonatos.c
	$(CC) $(CFLAGS2) antonatos.c -o $(EXE)
	strip $(EXE)

clean:
	rm -f $(EXE)