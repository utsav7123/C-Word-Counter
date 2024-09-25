#include "table_string.h"
#include "str_cmp.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUCKETS
// DO NOT ADD ANY NEW FUNCTIONS BEFORE djb2
// Hash a character array to integer value between 0 and buckets-1.
// See here for more details: https://theartincode.stanis.me/008-djb2/
unsigned int djb2_word_to_bucket(char *word, int buckets) {
  if (!word) {
    printf("Invoked with null string");
    exit(EXIT_FAILURE);
  }
  unsigned long hash = 5381;
  uint32_t i;
// DO NOT ADD ANY NEW LINES BEFORE THIS POINT. DO NOT DELETE ANY LINES.
  for (i = 0; i < strlen(word); i++)
    hash = ((hash << 5) + hash) + word[i];

  return hash & (buckets - 1);
}
// ADD YOUR HELPER FUNCTIONS AFTER djb2

int myStrlen(const char *s) {
    int length = 0;
    while (s[length] != '\0') {
        length++;
    }
    return length;
}
char *myStrdup(const char *s) {
    size_t len = myStrlen(s) + 1;
    char *dup = malloc(len);
    if (dup != NULL) {
        memcpy(dup, s, len);
    }
    return dup;
}

/**
 * @brief Instantiate a table string
 *
 * @param buckets
 * @return table_string*
 */
void add_line(vs_entry_t *entry, int line) {
    if (entry->line_count >= entry->size_of_lines) {
        entry->size_of_lines *= 2;
        entry->lines = (int *)realloc(entry->lines, entry->size_of_lines * sizeof(int));
        if (!entry->lines) {
            fprintf(stderr, "Memory allocation failed for lines array\n");
            exit(EXIT_FAILURE);
        }
    }
    entry->lines[entry->line_count++] = line;
}
#include <stdio.h>
#include <stdlib.h>

int custom_strcmp(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        if (*s1 < *s2) return -1; // s1 is less than s2
        if (*s1 > *s2) return 1;  // s1 is greater than s2
        s1++;
        s2++;
    }
    // If one string ends before the other
    return (*s1 == '\0' && *s2 == '\0') ? 0 : (*s1 == '\0' ? -1 : 1);
}










void bubble_sort_entries(vs_entry_t **entries, int entry_count) {
    for (int i = 0; i < entry_count - 1; i++) {
        for (int j = 0; j < entry_count - i - 1; j++) {
            if (custom_strcmp(entries[j]->value, entries[j + 1]->value) > 0) {
                // Swap if out of order
                vs_entry_t *temp = entries[j];
                entries[j] = entries[j + 1];
                entries[j + 1] = temp;
            }
        }
    }
}






table_string *table_string_allocate(unsigned int buckets) {
  table_string *ts = malloc(sizeof(table_string));
    if (!ts) {
        perror("Unable to allocate memory for table_string");
        exit(EXIT_FAILURE);
    }

    // Allocate memory for the array of bucket heads (vs_entry_t* array)
    ts->heads = calloc(buckets, sizeof(vs_entry_t *));
    if (!ts->heads) {
        perror("Unable to allocate memory for bucket heads");
        free(ts);
        exit(EXIT_FAILURE);
    }

    ts->buckets = buckets;
    return ts;
  // Instantiate a bucket number of heads
  table_string *ts = (table_string *)malloc(sizeof(table_string));
    ts->heads = (vs_entry_t **)calloc(buckets, sizeof(vs_entry_t *));
    ts->buckets = buckets;
    return ts;
}

/**
 * @brief Insert the string pointed to by word into the table string.
 *   If word is already found increment count.
 *   If word is not found insert at the end of the corresponding bucket
 * @param ts - Pointer to table_string datastructure
 * @param word - Pointer to string to search for
 * @return * Find*
 */

int myStrCmp(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        if (*s1 < *s2) return -1; // s1 is less than s2
        if (*s1 > *s2) return 1;  // s1 is greater than s2
        s1++;
        s2++;
    }
    // If one string ends before the other
    return (*s1 == '\0' && *s2 == '\0') ? 0 : (*s1 == '\0' ? -1 : 1);
}
void table_string_insert_or_add(table_string *ts, char *word, int line) {
  // Find the bucket for word. djb2 will return a value between 0-buckets-1.
  // Rule: buckets can only be power of 2.
  int bucket = djb2_word_to_bucket(word, ts->buckets);
  // TODO:
  // Case head == NULL: bucket hasn't been initialized yet
  // Case word already in list, add to line array.
  // Case word not found, insert word and return.
}

void table_string_deallocate(table_string *ts) {
  // TODO:
  // Free the linked list of each bucket
  // Free the array of head pointers
  // Free the structure itself
  return;
}

void table_string_print(table_string *ts) {
  /** TODO:
   for each bucket
    for each entry in bucket
      print entry->word: line line line
  */
}
