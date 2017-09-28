#include <stdio.h>
#include "dictionary.h"

static void unit_test_word(t_tree_node* dict, const char* word, int expected)
{
	if ( dictionary_contains_word(dict, word) != expected)
	{
		printf("FAIL ! %s is %s in the dictionary\n", word, expected ? "NOT" : "");
	}
}

int main(int argc, char **argv)
{
	t_tree_node* 	dict;

	(void) argc; // not used
	(void) argv; // not used
	
	dict = dictionary_create();

	if (dict != NULL)
	{
		printf("[BEGIN] dictionary test\n");

		dictionary_add_entry(dict, "a");
		dictionary_add_entry(dict, "bar");
		dictionary_add_entry(dict, "car");
		dictionary_add_entry(dict, "carat");
		dictionary_add_entry(dict, "carrot");

		unit_test_word(dict, "car", 1);
		unit_test_word(dict, "c", 0);
		unit_test_word(dict, "carrrrrrrrrrrrrrrrr", 0);
		unit_test_word(dict, "carrrrrrrrrrrrrrrrrot", 0);
		unit_test_word(dict, "", 0);
		unit_test_word(dict, "a", 1);

		printf("[END] dictionary test\n");

		dictionary_destroy(dict);
		return (0);
	}

	return (-1);
}
