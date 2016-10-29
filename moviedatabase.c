#include "moviedatabase.h"

#include <stdio.h>
#include <string.h> // strcmp

#include "alloc.h"
#include "csv.h"
#include "film.h"
#include "llist.h"

LinkedList* films = NULL;

void mdb_loadDB(const char* const path)
{
  size_t entries;
  LinkedList** csv = csv_read(path, &entries);

  if (!csv)
  {
    fprintf(stderr, "Failed to read database file\n");
    return;
  }

  if (!films)
    films = ll_new();

  for (size_t i = 0; i < entries; ++i)
  {
    LinkedList* entry = csv[i];
    LinkedIterator it = ll_it_begin(entry);
    char* title = (char*)ll_it_data(&it);
    uint16_t year = atoi((char*)ll_it_next(&it));
    char* rating = (char*)ll_it_next(&it);
    char* categories = (char*)ll_it_next(&it);
    uint16_t runtime = atoi((char*)ll_it_next(&it));
    double score = atof((char*)ll_it_next(&it));
    Film* film = film_new(title, year, rating_fromString(rating),
                          category_fromStrings(categories), runtime, score);
    ll_delete(entry);

    ll_push_back(films, film);
  }
  mt_free(csv);
}

void mdb_freeDB()
{
  if (!films) // No films? No work
    return;

  // delete each film manually
  for (LinkedIterator it = ll_it_begin(films);
       ll_it_valid(&it); ll_it_next(&it))
    film_delete(ll_it_data(&it));
  // purge the linked list, all the data pointers are invalid now
  ll_purge(films);
}

void mdb_printAll()
{
  if (!films)
    return;

  for (LinkedIterator it = ll_it_begin(films);
       ll_it_valid(&it); ll_it_next(&it))
    film_print(ll_it_data(&it));
}

int32_t alphanumeric(const void* const a, const void* const b)
{
  return strcmp(film_getTitle((Film*)a), film_getTitle((Film*)b)) < 0;
}
int32_t chronological(const void* const a, const void* const b)
{
  return film_getYear((Film*)a) > film_getYear((Film*)b) ? 1 : 0;
}
int32_t runtime(const void* const a, const void* const b)
{
  return film_getRuntime((Film*)a) < film_getRuntime((Film*)b) ? 1 : 0;
}
int32_t score(const void* const a, const void* const b)
{
  int32_t s = film_getScore((Film*)a) < film_getScore((Film*)b) ? 1 : 0;
  return s;// ? s : alphanumeric(a, b);
}

void task1()
{
  ll_bsort(films, chronological);
  mdb_printAll();
}


void task2()
{
  LinkedList* noir = ll_new();

  for (LinkedIterator it = ll_it_begin(films);
       ll_it_valid(&it); ll_it_next(&it))
  {
    Film* f = (Film*)ll_it_data(&it);
    if (film_hasCategory(f, FILM_NOIR))
      ll_push_front(noir, f);
  }

  ll_bsort(noir, runtime);
  LinkedIterator third = ll_at(noir, 2);
  film_print((Film*)ll_it_data(&third));
  ll_purge(noir);
}

void task3()
{
  LinkedList* scifi = ll_new();

  for (LinkedIterator it = ll_it_begin(films);
       ll_it_valid(&it); ll_it_next(&it))
  {
    Film* f = (Film*)ll_it_data(&it);
    if (film_hasCategory(f, SCI_FI))
    {
      film_print(f);
      ll_push_front(scifi, f);
    }
  }

  ll_bsort(scifi, score);
  LinkedIterator tenth = ll_at(scifi, 9);
  film_print(ll_it_data(&tenth));
  ll_purge(scifi);
}

void task4()
{
  Film* highest = NULL;

  for (LinkedIterator it = ll_it_begin(films);
       ll_it_valid(&it); ll_it_next(&it))
  {
    Film* f = (Film*)ll_it_data(&it);
    if (!highest || film_getScore(f) > film_getScore(highest))
      highest = f;
  }

  if (highest)
    film_print(highest);
}
void task5()
{
  Film* shortest = NULL;

  for (LinkedIterator it = ll_it_begin(films);
       ll_it_valid(&it); ll_it_next(&it))
  {
    Film* f = (Film*)ll_it_data(&it);
    if (!shortest || strlen(film_getTitle(f)) < strlen(film_getTitle(shortest)))
      shortest = f;
  }

  if (shortest)
    film_print(shortest);
}

void task6()
{
  LinkedIterator itp;
  for (LinkedIterator it = ll_it_begin(films);
       ll_it_valid(&it); ll_it_next(&it))
  {
    Film* f = (Film*)ll_it_data(&it);
    if (film_getRating(f) == R)
    {
      ll_erase(&it);
      film_delete(f);
      it = itp;
    }
    else
    {
      itp = it;
    }
  }

  printf("After deleting all R rated films, there are %zu films.\n",
         ll_size(films));
}

void task(const int n)
{
  switch (n)
  {
    case 1:
      task1();
    break;
    case 2:
      task2();
    break;
    case 3:
      task3();
    break;
    case 4:
      task4();
    break;
    case 5:
      task5();
    break;
    case 6:
      task6();
    break;
  }
  return;
}
