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

void subtract(table_string *t1, char *f1, table_string *t2) {
    printf("\n");
    for (int i = 0; i < t1->buckets; i++) {
        vs_entry_t *entry_t1 = t1->heads[i];
        while (entry_t1 != NULL) {
            // Check if this word exists in t2
            int found_in_t2 = 0;
            int bucket_t2 = djb2_word_to_bucket(entry_t1->value, t2->buckets);
            vs_entry_t *entry_t2 = t2->heads[bucket_t2];
            
            // Search for the word in t2's bucket
            while (entry_t2 != NULL) {
                if (custom_Strcmp(entry_t1->value, entry_t2->value) == 0) {
                    found_in_t2 = 1;
                    break;
                }
                entry_t2 = entry_t2->next;
            }

            // If not found in t2, print the word and its line numbers from t1
            if (!found_in_t2) {
    printf("%s\n", entry_t1->value);  // Print the word
    printf("%s ", f1);  // Print the filename
    for (int j = 0; j < entry_t1->line_count; j++) {
        printf("%d", entry_t1->lines[j]);  // Print line numbers
        if (j < entry_t1->line_count - 1) {
            printf(",");  // Add comma between line numbers
        }
    }
    printf(",\n");  // Newline after each entry
}

            entry_t1 = entry_t1->next;
        }
    }
}


