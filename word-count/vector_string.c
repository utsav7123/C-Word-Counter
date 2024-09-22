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
vector_string *vector_string_allocate()
{
    vector_string *vs = (vector_string *)malloc(sizeof(vector_string));
    if (vs != NULL) {
        vs->head = NULL;
        vs->tail = NULL;
    }
    return vs;
}
bool vector_string_find(vector_string *vs, char *key)
{

    vs_entry_t *current = vs->head;
    while (current != NULL) {
        if (strcmp(current->value, key) == 0) {
            return true;
        }
        current = current->next;
    }
    return false;
}
void vector_string_insert(vector_string *vs, char *key) {
 
vs_entry_t *new_entry = (vs_entry_t *)malloc(sizeof(vs_entry_t));
    if (!new_entry) {
        printf("Memory allocation failed for new entry\n");
        exit(1);
    }
    new_entry->value = strdup(key);
    new_entry->next = NULL;

    if (vs->tail) {
        vs->tail->next = new_entry;
    } else {
        vs->head = new_entry;
    }
    vs->tail = new_entry;
}
void vector_string_deallocate(vector_string *vs) {
    vs_entry_t *current = vs->head;
    while (current) {
        vs_entry_t *temp = current;
        current = current->next;
        free(temp->value);
        free(temp);
    }
    free(vs);
}
void vector_string_print(vector_string *vs) {

  int count = 1;
    vs_entry_t *current = vs->head;
    while (current != NULL) {
        printf("%d. %s\n", count++, current->value);
        current = current->next;
    }
}