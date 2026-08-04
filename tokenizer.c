#include "tokenizer.h"
#include <stddef.h>
#include <string.h>

char *trim_quotes(char *str) {
  if (str == NULL)
    return NULL;

  size_t len = strlen(str);

  if (len >= 2 && str[0] == '"' && str[len - 1] == '"') {
    str[len - 1] = '\0';
    str = str + 1;
  }

  size_t i = 0;
  size_t j = 0;

  while (str[i] != '\0') {
    if (str[i] == '"' && str[i + 1] == '"') {
      str[j++] = '"';
      i += 2;
    } else {
      str[j++] = str[i++];
    }
  }
  str[j] = '\0';

  return str;
}

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
