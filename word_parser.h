#ifndef MY_WORD_PARSER_H_
# define MY_WORD_PARSER_H_

# define WORD_PARSER_BUFFER_SIZE 512

typedef struct s_word_parser
{
	const char* filename;
	int			fd;
	int			line_index;
	int			buffer_index;
	char		buffer[2][WORD_PARSER_BUFFER_SIZE];
} t_word_parser;

int		word_parser_init(t_word_parser* parser, const char* filename);
void	word_parser_close(t_word_parser* parser);

// return 0 if no more word available on the current file
// in parser
// out word
int word_parser_get_next_word(t_word_parser* parser, char** word);

#endif // MY_WORD_PARSER_H_
