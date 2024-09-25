#include "dedup.h"
#include "table_string.h"
#include "vector_char.h"
#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void dedup(table_string *ts1, char* file1, table_string *ts2, char* file2) {
  // Find common strings between ts1 and ts2
  // Store in array and print them
  // You can make use of dedup_entry_t (if you want; you can also ignore if you wish)
    // Print them.
    // printf("\n%s", word);
    // printf("\n%s ", file1);
    // Print all lines in file1 with word , separated
    // printf("%d,", entry[i].lines1[j]);
    // printf("\n%s", file2);
    // printf("%d,", entry[i].lines2[j]);
}

void unique(table_string *ts1, char *file1, table_string *ts2, char *file2) {
  // Find unique strings between ts1 and ts2
  // Store in array and print them
  // Print all strings in ts1 that are not in ts2 followed by
  // Print all strings in ts2 that are not in ts1
  // You can make use of dedup_entry_t (if you want; you can also ignore if you
  // wish) Print them. printf("\n%s", word); printf("\n%s ", file1); Print all
  // lines in file1 with word , separated printf("%d,", entry[i].lines1[j]);
  // printf("\n%s", file2);
  // printf("%d,", entry[i].lines2[j]);
  }

 void unify(table_string * ts1, char *file1, table_string *ts2, char *file2) {
    // Find union of strings between ts1 and ts2
    // Store in array and print them
    // Print all strings in ts1 (even those with entries in ts2) followed by
    // Print all strings in ts2 that are not in ts1
    // You can make use of dedup_entry_t (if you want; you can also ignore if
    // you wish) Print them. 
    // print all references for entry. If in ts1 and ts2 print both
    // If only in ts1 print only ts1
    // If only in ts2 print only ts2
    // printf("\n%s", word); printf("\n%s ", file1); Print
    // all lines in file1 with word , separated printf("%d,",
    // entry[i].lines1[j]); printf("\n%s", file2); printf("%d,",
    // entry[i].lines2[j]);}
 }
 int myStrcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}
unsigned long hash(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash;
}

void subtract(table_string *ts1, char *file1, table_string *ts2, char *file2) {
    int dedup_length = 0;
    dedup_entry_t **entries = malloc(sizeof(dedup_entry_t *));
    if (entries == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < ts1->buckets; i++) {
        vs_entry_t *ptr1 = ts1->heads[i];
        while (ptr1 != NULL) {
            vs_entry_t *ptr2 = ts2->heads[i]; // Reset ptr2 for each new ptr1

            while (ptr2 != NULL) {
                if (myStrcmp(ptr1->value, ptr2->value) == 0) {
                    dedup_length++;
                    entries = realloc(entries, dedup_length * sizeof(dedup_entry_t *));
                    if (entries == NULL) {
                        fprintf(stderr, "Memory reallocation failed\n");
                        exit(1);
                    }

                    entries[dedup_length - 1] = malloc(sizeof(dedup_entry_t));
                    if (entries[dedup_length - 1] == NULL) {
                        fprintf(stderr, "Memory allocation failed\n");
                        exit(1);
                    }

                    entries[dedup_length - 1]->value = ptr1->value;
                    entries[dedup_length - 1]->lines1 = ptr1->lines;
                    entries[dedup_length - 1]->lines2 = ptr2->lines;
                    entries[dedup_length - 1]->size_of_lines1 = ptr1->size_of_lines;
                    entries[dedup_length - 1]->size_of_lines2 = ptr2->size_of_lines;
                    entries[dedup_length - 1]->file1 = file1;
                    entries[dedup_length - 1]->file2 = file2;
                }
                ptr2 = ptr2->next;
            }
            ptr1 = ptr1->next; // Move to the next entry in ts1
        }
    }

    // Printing unique entries in ts1
    for (int j = 0; j < ts1->buckets; j++) {
        vs_entry_t *ptr = ts1->heads[j];
        while (ptr != NULL) {
            bool only_in_ts1 = true;
            for (int i = 0; i < dedup_length; i++) {
                if (myStrcmp(entries[i]->value, ptr->value) == 0) {
                    only_in_ts1 = false;
                    break; // Found in entries, no need to continue checking
                }
            }
            if (only_in_ts1) {
                printf("%s\n", ptr->value);
                printf("%s ", file1);
                // Print all line numbers for this word
                for (int r = 0; r < ptr->size_of_lines; r++) {
                    printf("%d,", ptr->lines[r]);
                }
                printf("\n"); // New line after each word's lines
            }
            ptr = ptr->next;
        }
    }

    // Free memory for entries
    for (int y = 0; y < dedup_length; y++) {
        free(entries[y]);
    }
    free(entries);
}
