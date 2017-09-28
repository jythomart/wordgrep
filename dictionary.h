#ifndef MY_DICTIONARY_H_
# define MY_DICTIONARY_H_

typedef struct s_list_node
{
	void*				data;
	struct s_list_node*	next;
} t_list_node;

typedef struct s_tree_node
{
	char				c;
	t_list_node*		children;
} t_tree_node;

t_list_node*	list_create();

t_tree_node*	dictionary_create();
void			dictionary_destroy(t_tree_node* dictionary);

void			dictionary_add_entry(t_tree_node* dictonary, const char* entry);

int				dictionary_contains_word(t_tree_node* dictionary, const char* word);

#endif // MY_DICTIONARY_H_
