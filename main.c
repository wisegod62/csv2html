#include "tokenizer.h"
#include <stdio.h>
#include <string.h>

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
  printf("<table>\n");
  while (fgets(buf, sizeof(buf), fptr) != NULL) {
    buf[strcspn(buf, "\r\n")] = '\0';

    tokPtr = strmbtok(buf, ",", "\"", "\"");

    printf("  <tr>");
    while (tokPtr != NULL) {
      char tag = isFirstIter ? 'h' : 'd';
      char *clean_text = trim_quotes(tokPtr);

      printf("<t%c>%s</t%c>", tag, clean_text, tag);
      tokPtr = strmbtok(NULL, ",", "\"", "\"");
    }
    printf("</tr>\n");

    if (isFirstIter) {
      isFirstIter = 0;
    }
  }
  printf("</table>\n");

  fclose(fptr);
  return 0;
}
