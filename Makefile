
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
LDFLAGS =

SRC 	= 	dictionary.c \
			word_parser.c

OBJ 	= $(SRC:.c=.o)

EXE 	= wordgrep

all: $(SRC) $(EXE) test_dict test_parser
	
$(EXE): $(OBJ) main.o
	$(CC) $(LDFLAGS) $(OBJ) main.o -o $@

test_dict: $(OBJ) test_dict.o
	$(CC) $(LDFLAGS) $(OBJ) test_dict.o -o $@

test_parser: $(OBJ) test_parser.o
	$(CC) $(LDFLAGS) $(OBJ) test_parser.o -o $@

clean:
	rm -rf *.o

fclean:
	rm -rf $(EXE) test_dict test_parser

re: fclean all