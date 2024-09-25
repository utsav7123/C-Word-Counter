#include "vector_string.h"
#include "str_cmp.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
/////////////////////////////////////////

*/
/**
 * @brief Memory allocate a vector string so that we can start inserting entries
 * into it.
 *
 */
vector_string *vector_string_allocate() {
   vector_string *vs = (vector_string *)malloc(sizeof(vector_string));
    if (!vs) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    vs->head = NULL;
    vs->tail = NULL;
    return vs;
}

/**
 * @brief Search the vector string pointed to by vs and return true if the
 * vs_entry.value == key, else return false.
 * TODO:
 * @param vs - Pointer to vector_string datastructure
 * @param key - Pointer to string to search for
 * @return * Find*
 */
int myStrcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

bool vector_string_find(vector_string *vs, char *key) { vs_entry_t *current = vs->head;
    while (current != NULL) {
        if (myStrcmp(current->value, key) == 0) {
            return true;
        }
        current = current->next;
    }
    return false;
  }

/**
 * @brief TODO: Insert the string pointed to by key into the vector string.
 *  char* is externally allocated. You do not have to allocate internally
 *
 * @param vs - Pointer to vector_string datastructure
 * @param key - Pointer to string to search for
 * @return * Find*
 */

char *myStrdup(const char *src) {
    size_t len = 0;
    while (src[len] != '\0') {
        len++;  // Calculate the length of the string
    }

    char *dup = (char *)malloc((len + 1) * sizeof(char));  // Allocate memory for the copy
    if (!dup) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    for (size_t i = 0; i < len; i++) {
        dup[i] = src[i];  // Copy each character
    }
    dup[len] = '\0';  // Null-terminate the new string
    return dup;
}
void vector_string_insert(vector_string *vs, char *key) {
  // Insert the string into the tail of the list.
  vs_entry_t *new_entry = (vs_entry_t *)malloc(sizeof(vs_entry_t));
    if (!new_entry) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    new_entry->value = myStrdup(key);//////////////////////////////////////////////////////////////////////

    new_entry->next = NULL;
    
    if (vs->tail != NULL) {
        vs->tail->next = new_entry;
    }
    vs->tail = new_entry;

    if (vs->head == NULL) {
        vs->head = new_entry;
    }
}
/**
 * @brief Remove all entries and cleanup vector string
 * TODO: Remove all entries. Remember head and tail are pointers.
 * Remember to remove vs as well; not just entries. or you will have memory
 * leaks.
 * @param vs: Pointer to vector_string struct
 */
void vector_string_deallocate(vector_string *vs) {
   vs_entry_t *current = vs->head;
    while (current != NULL) {
        vs_entry_t *next = current->next;
        free(current);
        current = next;
    }
    free(vs);
}

/**
 * @brief Print all value in each entry of the vector string, in the following
 * format. In this case hello and world are the unique words in the file.
 * 1. hello
 * 2. world
 * @param vs
 */
void vector_string_print(vector_string *vs) {

  int count = 1;
    vs_entry_t *entry = vs->head;
    while (entry != NULL) {
        printf("%d. %s\n", count, entry->value);
        entry = entry->next;
        count++;
    }
}