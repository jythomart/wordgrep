#include <stdio.h>
#include "dictionary.h"
#include "word_parser.h"

int main(int argc, char **argv)
{
	t_tree_node* 	dict;
	t_word_parser 	parser;
	char*			word;
	int 			i;

	if (argc > 2)
	{
		dict = dictionary_create();

		if (dict != NULL)
		{
			word_parser_init(&parser, argv[1]);
			while (word_parser_get_next_word(&parser, &word) > 0)
			{
				dictionary_add_entry(dict, word);
			}
			word_parser_close(&parser);

			i = 2;
			while (i < argc)
			{
				word_parser_init(&parser, argv[i]);
				while (word_parser_get_next_word(&parser, &word) > 0)
				{
					if (dictionary_contains_word(dict, word) != 0)
					{
						printf("%s\n", argv[i]);
						break;
					}
				}
				word_parser_close(&parser);
				++i;
			}

			dictionary_destroy(dict);
			return (0);
		}
	}

	return (-1);
}
