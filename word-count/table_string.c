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
void table_string_insert_or_add(table_string *ts, char *word, int line) {
    int bucket = djb2_word_to_bucket(word, ts->buckets);

    //////////printf("Inserting '%s' into bucket %d\n", word, bucket);/////////////////

    vs_entry_t *current = ts->heads[bucket];

    // Check if word already exists
    while (current != NULL) {
        if (custom_strcmp(current->value, word) == 0) { // Use custom_strcmp here
            add_line(current, line);
            return;
        }
        current = current->next;
    }

    // Word not found, create new entry
    vs_entry_t *new_entry = (vs_entry_t *)malloc(sizeof(vs_entry_t));
    new_entry->value = malloc(strlen(word) + 1); // Use malloc instead of strdup
    strcpy(new_entry->value, word); // Use strcpy for safe copying
    new_entry->lines = (int *)malloc(2 * sizeof(int)); // Initial capacity for 2 lines
    new_entry->line_count = 0;
    new_entry->size_of_lines = 2;
    add_line(new_entry, line);
    new_entry->next = NULL;

    // Insert at the tail of the linked list
    if (ts->heads[bucket] == NULL) {
        ts->heads[bucket] = new_entry; // First entry in bucket
    } else {
        current = ts->heads[bucket];
        while (current->next != NULL) {
            current = current->next; // Traverse to the end
        }
        current->next = new_entry; // Link the new entry
    }

   //////////// printf("after Inserting '%s' into bucket %d\n", word, bucket);//////////////////////

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
            free(current->value);

            // Free the lines array if it was allocated
            if (current->lines != NULL) {
                free(current->lines);
            }

            free(current);
            current = next;
        }
    }
    // Free the array of head pointers
    free(ts->heads);
    // Free the structure itself
    free(ts);
  return;
}

void table_string_print(table_string *ts) {
    int entry_count = 0;
    vs_entry_t *entries[1000];

    bubble_sort_entries(entries, entry_count);

    for (int i = 0; i < ts->buckets; i++) {
        vs_entry_t *current = ts->heads[i];
        while (current != NULL) {
            entries[entry_count++] = current;
            current = current->next;
        }
    }
  
    //bubble_sort_entries(entries, entry_count);

    for (int i = 0; i < entry_count; i++) {
        vs_entry_t *entry = entries[i];
        printf("%s: ", entry->value);
        for (int j = 0; j < entry->line_count; j++) {
            printf("%d ", entry->lines[j]);
        }
        printf("\n");
    }
}
