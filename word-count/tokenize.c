#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector_char.h>

int is_valid_char(char ch) {
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9');
}

int main(int argc, char **argv) {
  char *source = NULL;

  /**
   * @brief Read file into source.
   * source is a character array with file contents
   * It is null terminated
   */
  if (argc != 2) {
    printf("./grade_tokenize.bin [FILE PATH] \n");
    exit(1);
  }

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

  // TODO: Tokenize processing
  // TODO:source contains the string to be processed.
  /** Start processing file and separate into words */
  /** Pseudocode */
  // 1. Iterate over characters
  // 2. if current-character starts word start accumulating into vector_char
  // 3. if current character terminates word. print and restart word start
  // check. Free all data.
  // Hint: Use vector_char
  vector_char_t *current_word = vector_char_allocate(); // Allocate a vector for the current word

  // Iterate through the source string
  for (size_t i = 0; source[i] != '\0'; i++) {
    char c = source[i];

    if (isalnum(c)) {
      // If it's an alphanumeric character, accumulate it in the vector
      vector_char_add(current_word, c);
    } else {
      // If it's not an alphanumeric character, process the current word
      if (current_word->len > 0) {
        // Null-terminate the current word (so it can be printed)
        vector_char_add(current_word, '\0');
        
        // Print the current word
        printf("%s\n", vector_char_get_array(current_word));

        // Reset the vector for the next word
        current_word->len = 0;
      }
    }
  }

  // If the file ends and we still have an accumulated word, print it
  if (current_word->len > 0) {
    vector_char_add(current_word, '\0');
    printf("%s\n", vector_char_get_array(current_word));
  }

  // Free the allocated memory
  vector_char_delete(current_word);
  free(source);

  vector_char_t *word = vector_char_allocate();

    for (int i = 0; source[i] != '\0'; i++) {
        if (is_valid_char(source[i])) {
            // Add valid characters to the vector_char
            vector_char_add(word, source[i]);
        } else if (word->len > 0) {
            // If a word is accumulated, terminate it and print it
            vector_char_add(word, '\0'); // Null terminate the string
            printf("%s\n", vector_char_get_array(word));
            word->len = 0; // Reset the vector for the next word
        }
    }

    // Handle any leftover word at the end of the source
    if (word->len > 0) {
        vector_char_add(word, '\0');
        printf("%s\n", vector_char_get_array(word));
    }

    vector_char_delete(word); // Clean up memory

    free(source); // Clean up allocated memory for source
    return 0;
}