#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "word_parser.h"

int word_parser_init(t_word_parser* parser, const char* filename)
{
	if (parser != NULL && filename != NULL)
	{
		parser->filename = filename;
		parser->fd = open(filename, O_RDONLY);
		parser->line_index = 0;
		parser->buffer_index = 0;
		parser->buffer[0][0] = '\0';

		return parser->fd;
	}

	return -1;
}

void word_parser_close(t_word_parser* parser)
{
	if (parser != NULL && parser->fd != -1)
	{
		close(parser->fd);
		parser->fd = -1;
	}
}

static int is_a_separator_token(char c)
{
	return (c == ' ' || c == '\r' || c == '\t' || c == '\n');
}

int word_parser_get_next_word(t_word_parser* parser, char** word)
{
	if (parser != NULL && parser->fd != -1)
	{
		char* buff = parser->buffer[parser->buffer_index];
		int begin = parser->line_index;
		int end;

		if (buff[begin] == '\0')
		{
			parser->line_index = 0;
			parser->buffer_index = (parser->buffer_index + 1) % 2;
			end = read(parser->fd, parser->buffer[parser->buffer_index], WORD_PARSER_BUFFER_SIZE - 1);
			if (end <= 0) // error or EOF
				return end;
			parser->buffer[parser->buffer_index][end] = '\0';

			buff = parser->buffer[parser->buffer_index];
			begin = parser->line_index;
		}

		while (buff[begin] != '\0' && is_a_separator_token(buff[begin]))
			++begin;	// skip spaces

		end = begin;

		while (buff[end] != '\0' && !is_a_separator_token(buff[end]))
			++end;

		while (buff[end] == '\0')
		{
			//handle the case of a cut word
			int word_length = end - begin;
			parser->buffer_index = (parser->buffer_index + 1) % 2;
			buff = strcpy(parser->buffer[parser->buffer_index], &buff[begin]);
			end = read(parser->fd, buff + word_length, WORD_PARSER_BUFFER_SIZE - 1 - word_length);
			if (end <= 0) // error or EOF
				return end;
			parser->buffer[parser->buffer_index][end + word_length] = '\0';

			begin = 0;
			end = begin;

			while (buff[end] != '\0' && !is_a_separator_token(buff[end]))
				++end;
		}

		buff[end] = '\0';
		parser->line_index = end + 1;

		*word = &(buff[begin]);
		return end - begin;
	}

	return -1;
}
