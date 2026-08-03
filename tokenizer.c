#include "tokenizer.h"
#include <stddef.h>
#include <string.h>

char *strmbtok(char *input, char *delimit, char *openblock, char *closeblock) {
  static char *token = NULL;
  char *lead = NULL;
  char *block = NULL;
  int iBlock = 0;
  int iBlockIndex = 0;

  if (input != NULL) {
    token = input;
    lead = input;
  } else {
    lead = token;
    if (*token == '\0') {
      return NULL;
    }
    lead = token;
  }

  while (*token != '\0') {
    if (iBlock) {
      if (closeblock[iBlockIndex] == *token) {
        iBlock = 0;
      }
      token++;
      continue;
    }
    if ((block = strchr(openblock, *token)) != NULL) {
      iBlock = 1;
      iBlockIndex = block - openblock;
      token++;
      continue;
    }
    if (strchr(delimit, *token) != NULL) {
      *token = '\0';
      token++;
      break;
    }
    token++;
  }
  return lead;
}
