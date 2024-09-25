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
  void table_string_print(table_string *ts) {
    int total_entries = 0;
    
    // First, count how many entries we have across all buckets
    for (int i = 0; i < ts->buckets; i++) {
        vs_entry_t *current = ts->heads[i];
        while (current != NULL) {
            total_entries++;
            current = current->next;
        }
    }

    // Allocate an array to hold pointers to all vs_entry_t elements
    vs_entry_t **entries = malloc(total_entries * sizeof(vs_entry_t *));
    if (!entries) {
        perror("Unable to allocate memory for sorting entries");
        exit(EXIT_FAILURE);
    }

    // Collect all entries from the hash table into the array
    int index = 0;
    for (int i = 0; i < ts->buckets; i++) {
        vs_entry_t *current = ts->heads[i];
        while (current != NULL) {
            entries[index++] = current;
            current = current->next;
        }
    }

    // Sort the array alphabetically by word (value)
    //qsort(entries, total_entries, sizeof(vs_entry_t *), compare_entries);

    // Print the sorted entries
    for (int i = 0; i < total_entries; i++) {
        vs_entry_t *current = entries[i];
        printf("%s: ", current->value);
        for (int j = 0; j < current->size_of_lines; j++) {
            printf("%d ", current->lines[j]);
            
        }
        printf("\n");
    }

    // Free the array of entries
    free(entries);
}
  int buckets = 4; // Number of buckets (power of 2 for efficient hashing)
    table_string *ts = table_string_allocate(buckets);
    char *word = malloc(128 * sizeof(char)); // Allocate a buffer for the current word (adjust size as needed)
    if (!word) {
        printf("Memory allocation error");
        exit(1);
    }

    int line = 1;  // Start at line 1
    int word_pos = 0;
    char c;

    for (int i = 0; source[i] != '\0'; i++) {
        c = source[i];

        if (isspace(c) || ispunct(c)) {
            // If the current character is a whitespace or punctuation, the word ends here
            if (word_pos > 0) {  // If we have a word to process
                word[word_pos] = '\0';  // Null-terminate the word
                table_string_insert_or_add(ts, word, line);  // Insert word and line into the table
                word_pos = 0;  // Reset word position for the next word
            }
            if (c == '\n') {
                line++;  // Increment line number when encountering a newline
            }
        } else {
            // Collect characters for the word
            word[word_pos++] = c;
        }
    }

    // Insert the last word if there is one
    if (word_pos > 0) {
        word[word_pos] = '\0';
        table_string_insert_or_add(ts, word, line);
    }

    // Print the table of words and their occurrences
    table_string_print(ts);

    // Deallocate memory
    free(word);
    table_string_deallocate(ts);
    free(source);

  return 0;
}