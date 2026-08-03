#include <stdio.h>
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

int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "Usage: %s <input.csv> <output.html>\n", argv[0]);
    return 1;
  }

  FILE *fptr = fopen(argv[1], "r");
  if (!fptr) {
    perror("Error opening input file");
    return 1;
  }

  if (freopen(argv[2], "w+", stdout) == NULL) {
    perror("Error opening output file");
    fclose(fptr);
    return 1;
  }

  char buf[1024];

  char *tokPtr;

  int isFirstIter = 1;
  printf("<table>");
  while (fgets(buf, sizeof(buf), fptr) != NULL) {
    buf[strcspn(buf, "\r\n")] = '\0';

    tokPtr = strmbtok(buf, ",", "\"", "\"");

    printf("<tr>");
    while (tokPtr != NULL) {
      printf("<t%s>%s</t%s>", isFirstIter ? "h" : "d", tokPtr,
             isFirstIter ? "h" : "d");
      tokPtr = strmbtok(NULL, ",", "\"", "\"");
    }
    printf("</tr>");

    if (isFirstIter) {
      isFirstIter = 0;
    }
  }
  printf("</table>");
  return 0;
}
