#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector_char.h>
#include <vector_string.h>
int main(int argc, char **argv) {
  char *source = NULL;
  //long bufsize;

  if (argc != 2) {
    printf("./grade_tokenize.bin [FILE PATH]");
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

    vector_string *vs = vector_string_allocate();

    vector_char_t *current_word = vector_char_allocate();

    for (int i = 0; source[i] != '\0'; i++) {
        char c = source[i];

        if (isalnum(c)) {
            vector_char_add(current_word, c);
        } else if (current_word->len > 0) {
            vector_char_add(current_word, '\0');

            char *word = vector_char_get_array(current_word);

            if (!vector_string_find(vs, word)) {
                vector_string_insert(vs, word);
            }

            current_word->len = 0;
        }
    }

    if (current_word->len > 0) {
        vector_char_add(current_word, '\0');
        char *word = vector_char_get_array(current_word);
        if (!vector_string_find(vs, word)) {
            vector_string_insert(vs, word);
        }
    }

    vector_string_print(vs);

    vector_string_deallocate(vs);
    vector_char_delete(current_word);
    free(source);

    return 0;
}