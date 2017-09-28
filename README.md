wordgrep:
wordgrep dictfile [inputfile ...]

wordgrep parses a dictionary file.
wordgrep filters (to the standard output) its input stream, the concatenation of all input files specified on the command line or standard contains one of the words from the dictfile.
Matching is performed on a full word basis.
Words are delimited by white space, tabulations and carriage return.

------------------------------------------

two examples/tests can be found in this folder.
test_dict: 

this program takes no arguments.
it simply adds hardcoded words into a dictionary then test if some hardcoded words are in this dictionary.

test_parser:
test_parser filetoparse

output the file word by word.

------------------------------------------

algorithm overview:

the data structure used to save the dictionary is a trie. (dictionary.h and dictionaty.c)
each nodes contains a token (a letter) and child nodes are the possible following tokens, leading in the end to a full word.
This algorithm allows to quickly add and search a word.

The word parser is a circular buffer, it uses two static buffers and switch when one of them is full.
The algorithm doesn't allow a word larger than the buffer size (here 512).

