#include "tokenizer.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int headerRow = 1;

  char *input_file = NULL;
  char *output_file = NULL;
  int file_count = 0;

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--no-header") == 0 || strcmp(argv[i], "-n") == 0) {
      headerRow = 0;
    } else {
      if (file_count == 0) {
        input_file = argv[i];
      } else if (file_count == 1) {
        output_file = argv[i];
      }
      file_count++;
    }
  }

  if (file_count != 2) {
    fprintf(stderr, "Usage: %s [-n | --no-header] <input.csv> <output.html>\n",
            argv[0]);
    return 1;
  }

  FILE *fptr = fopen(input_file, "r");
  if (!fptr) {
    perror("Error opening input file");
    return 1;
  }

  if (freopen(output_file, "w+", stdout) == NULL) {
    perror("Error opening output file");
    fclose(fptr);
    return 1;
  }

  char buf[1024];

  char *tokPtr;

  int isFirstIter = headerRow;
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
