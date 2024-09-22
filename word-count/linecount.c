#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <table_string.h>
#include <vector_char.h>
int main(int argc, char **argv) {
  char *source = NULL;

  if (argc != 2) {
    printf("./wordcount.bin [FILE PATH]");
    exit(1);
  }
  /**
   * @brief Read file into source.
   * source is a character array with file contents
   * It is null terminated
   */
  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL) { /* Error */
    printf("Error reading file");
    exit(1);
  }
  if (fp != NULL) {
    /* Go to the end of the file. */
    if (fseek(fp, 0L, SEEK_END) == 0) {
      /* Get the size of the file. */
      long bufsize = ftell(fp);
      if (bufsize == -1) { /* Error */
        printf("Error reading file");
      }
      /* Allocate our buffer to that size. */
      source = malloc(sizeof(char) * (bufsize + 1));
      /* Go back to the start of the file. */
      if (fseek(fp, 0L, SEEK_SET) != 0) { /* Error */
      }
      /* Read the entire file into memory. */
      size_t newLen = fread(source, sizeof(char), bufsize, fp);
      if (ferror(fp) != 0) {
        printf("Error reading file");
      } else {
        source[newLen++] = '\0'; /* Just to be safe. */
      }
    }
  }
  fclose(fp);

  /** Start processing file and separate into words */
  // TODO: Write linecount
  table_string *ts = table_string_allocate(8);

// Track line number
int line_number = 1;
char *token;
char *rest = source;

while (*rest != '\0') {
    // Process each line
    char *line = rest;

    // Find the next newline character
    char *newline = strchr(line, '\n');
    if (newline != NULL) {
        *newline = '\0';  // Temporarily terminate the string here
        rest = newline + 1;
    } else {
        rest += strlen(rest);  // End of the file
    }

    // Tokenize the line into words
    token = strtok(line, " ,.:;?!\n\t");  // Separate by space, punctuation
    while (token != NULL) {
        // Insert each word with its line number into the table string
        table_string_insert_or_add(ts, token, line_number);
        token = strtok(NULL, " ,.:;?!\n\t");
    }

    // Increment line number
    line_number++;
}

// After processing, print the results and deallocate memory
table_string_print(ts);
table_string_deallocate(ts);

// Free the source file content
free(source);
  return 0;
}