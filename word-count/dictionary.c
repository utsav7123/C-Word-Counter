#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector_char.h>
#include <vector_string.h>

 bool is_word_char(char c) {
    // Check if the character is an uppercase or lowercase letter or a digit
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}


void vector_char_push_t(vector_char_t *vc, char c) {
    // If size reaches capacity, we need to resize the array
    if (vc->len >= vc->max) {
        vc->max = vc->max == 0 ? 1 : vc->max * 2;
        vc->data = realloc(vc->data, vc->max * sizeof(char));
    }
    // Add the new character and increase the size
    vc->data[vc->len++] = c;
}


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

  // TODO: Process source[] and count the number of words
  // Print the number of words in the end.
  vector_string *dictionary = vector_string_allocate();
    vector_char_t *token = vector_char_allocate();

    for (int i = 0; source[i] != '\0'; i++) {
      char c = source[i];
        if (is_word_char(c)) {
            vector_char_add(token, c);
        } else {
            if (token->len > 0) {
                vector_char_add(token, '\0'); // Null-terminate the token
                char *word = vector_char_get_array(token);
                if (!vector_string_find(dictionary, word)) {
                    vector_string_insert(dictionary, word);
                }
                token->len = 0; // Reset the token length for the next word
            }
        }
    }

    // Handle the last token (if any) after the loop
    if (token->len > 0) {
        vector_char_add(token, '\0'); // Null-terminate the last token
        char *word = vector_char_get_array(token);
        if (!vector_string_find(dictionary, word)) {
            vector_string_insert(dictionary, word);
        }
    }

    // Print the dictionary
    vector_string_print(dictionary);

    // Cleanup
    
    vector_string_deallocate(dictionary);
    vector_char_delete(token);
    free(source);

  return 0;
}