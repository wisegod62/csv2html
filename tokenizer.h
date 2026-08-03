#ifndef TOKENIZER_H
#define TOKENIZER_H

// Custom tokenization tool that safely parses chunks while respecting text
// blocks
char *strmbtok(char *input, char *delimit, char *openblock, char *closeblock);

#endif
