#include <stdio.h>
#include "word_parser.h"

int main(int argc, char **argv)
{
	t_word_parser 	parser;
	char*			word;

	if (argc > 1 && argv[1] != NULL)
	{
		printf("[BEGIN] parser test\n");

		word_parser_init(&parser, argv[1]);

		while (word_parser_get_next_word(&parser, &word) > 0)
		{
			printf("%s\n", word);
		}

		word_parser_close(&parser);

		printf("[END] parser test\n");

		return (0);
	}

	return (-1);
}
