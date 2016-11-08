#ifndef CSV_H_INCLUDE
#define CSV_H_INCLUDE

#include "llist.h"

/**
 * Reads the given file and interprets the data as a CSV file
 * Each line is read into a linked list of the values (stored as strings).
 * @param  filename File to read data from
 * @param  c        How many entries were created
 * @return          An array of linked lists of char*
 */
LinkedList** csv_read(const char* const filename, size_t* const c);

#endif
