#include <stdlib.h>
#include <stdio.h>
#include "dictionary.h"

t_list_node*	list_create()
{
	t_list_node* node = NULL;

	node = malloc(sizeof(*node));

	if (node != NULL)
	{
		node->data = NULL;
		node->next = NULL;
	}

	return node;
}

t_tree_node*	dictionary_create()
{
	t_tree_node* root = NULL;

	root = malloc(sizeof(*root));

	if (root != NULL)
	{
		root->c = '\0';
		root->children = NULL;
	}

	return root;
}

void	dictionary_destroy(t_tree_node* dict)
{
	if (dict != NULL)
	{
		t_list_node* prev_child;
		t_list_node* children;

		prev_child = NULL;
		children = dict->children;

		while (children != NULL)
		{
			t_tree_node* child;

			child = (t_tree_node*)children->data;

			dictionary_destroy(child);

			prev_child = children;
			children = children->next;

			free(prev_child);
		}

		free(dict);
	}
}

void	dictionary_add_entry(t_tree_node* dict, const char* entry)
{
	if (dict != NULL && entry != NULL)
	{
		t_list_node* prev_children;
		t_list_node* children;

		prev_children = NULL;
		children = dict->children;

		while (children != NULL) // test if current letter already in node
		{
			t_tree_node* child = (t_tree_node*)children->data;
			if (child->c == *entry)
			{
				if (*entry != '\0')
					dictionary_add_entry(child, entry + 1);	// word is not over continue adding the entry
				return;
			}
			prev_children = children;
			children = children->next;
		}

		// add a new child
		{
			t_list_node* new_child;
			t_tree_node* new_dict;

			new_child = list_create();
			if (new_child == NULL)
				return;

			new_dict = dictionary_create();
			if (new_dict == NULL)
			{
				free(new_child);
				return;
			}

			new_child->data = new_dict;
			new_child->next = NULL;

			new_dict->c = *entry;
			new_dict->children = NULL;

			if (prev_children == NULL) // node has no child
				dict->children = new_child;
			else
				prev_children->next = new_child;

			if (*entry != '\0')
				dictionary_add_entry(new_dict, entry + 1);	// word is not over continue adding the entry
		}
	}
}

int	dictionary_contains_word(t_tree_node* dict, const char* word)
{
	if (dict != NULL && word != NULL)
	{
		t_list_node* children = dict->children;

		while (children != NULL)
		{
			t_tree_node* child = (t_tree_node*)children->data;

			if (child->c == *word)
			{
				if (*word == '\0')
					return 1;
				else
					return dictionary_contains_word(child, word + 1);
			}
			children = children->next;
		}
	}
	return 0;
}
