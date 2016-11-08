#ifndef MOVIEDATABASE_H_INCLUDE
#define MOVIEDATABASE_H_INCLUDE

/**
 * Loads the movie database from the given CSV file.
 * If there are already loaded films, then the films in the CSV file are
 * appended to the current set of films.
 * @param path CSV file to read film data from
 */
void mdb_loadDB(const char* const path);

/**
 * Frees all the memory allocated by the movie database, use on exit to
 * clean up
 */
void mdb_freeDB();

/**
 * Prints all the films in the database
 */
void mdb_printAll();

/**
 * Does task 1 of the assignment, print all the films in chronological order
 */
void task1();
/**
 * Does task 2 of the assignment, finds the 3rd longest film noir film
 */
void task2();
/**
 * Does task 3 of the assignment, finds the 10th highest scoring scifi film
 */
void task3();
/**
 * Does task 4 of the assignment, finds the highest scoring film
 */
void task4();
/**
 * Does task 5 of the assignment, finds the film with the shortest title
 */
void task5();
/**
 * Does task 6 of the assignment, removes all R rated films and then prints
 * the number of films remaining
 */
void task6();

#endif
