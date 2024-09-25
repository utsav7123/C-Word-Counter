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
    vs_entry_t *current = ts->heads[bucket];
    vs_entry_t *prev = NULL;

    // Traverse the linked list to find if the word exists
    while (current != NULL) {
        if (myStrCmp(current->value, word) == 0) {
            // Word found, add the line number to the lines array
            current->lines = realloc(current->lines, (current->size_of_lines + 1) * sizeof(int));
            if (!current->lines) {
                perror("Unable to allocate memory for line numbers");
                exit(EXIT_FAILURE);
            }
            current->lines[current->size_of_lines] = line;
            current->size_of_lines++;
            return;
        }
        prev = current;
        current = current->next;
    }

    // Word not found, create a new entry and add it at the end of the list
    vs_entry_t *new_entry = malloc(sizeof(vs_entry_t));
    new_entry->value = myStrdup(word); // Ensure word is duplicated correctly
    new_entry->lines = malloc(sizeof(int)); // Start with one line entry
    new_entry->lines[0] = line;
    new_entry->size_of_lines = 1;
    new_entry->next = NULL;

    // Insert the new entry
    if (prev == NULL) {
        // Bucket was empty, insert at head
        ts->heads[bucket] = new_entry;
    } else {
        // Append to the end of the bucket
        prev->next = new_entry;
    }
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
  for (int i = 0; i < ts->buckets; i++) {
        vs_entry_t *current = ts->heads[i];
        while (current != NULL) {
            vs_entry_t *next = current->next;
            free(current->value);      // Free the word string
            free(current->lines);      // Free the lines array
            free(current);             // Free the entry itself
            current = next;
        }
    }
    free(ts->heads);  // Free the array of bucket heads
    free(ts);         // Free the table_string struct
  //return;
}

#include <stdlib.h>

// Compare function for qsort to sort alphabetically by value (word)
int compare_entries(const void *a, const void *b) {
    vs_entry_t *entryA = *(vs_entry_t **)a;
    vs_entry_t *entryB = *(vs_entry_t **)b;
    return myStrCmp(entryA->value, entryB->value);
}

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

void table_string_insert(table_string *ts, char *word) {
    // Create new entry for the word
    vs_entry_t *new_entry = malloc(sizeof(vs_entry_t));
    new_entry->value = strdup(word);  // Use strdup to duplicate the word
    new_entry->next = NULL;
    
    // Determine which bucket to place the word into (simple hash function)
    int bucket_index = (int)(word[0] % ts->buckets);  // Simple mod hashing by first character
    
    // Insert the word at the head of the corresponding bucket
    if (ts->heads[bucket_index] == NULL) {
        ts->heads[bucket_index] = new_entry;
    } else {
        // Insert at the head of the linked list (collision resolution by chaining)
        new_entry->next = ts->heads[bucket_index];
        ts->heads[bucket_index] = new_entry;
    }
}