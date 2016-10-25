#include "film.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "alloc.h"

const char* const rating_n[] = {
  "NONE",
  "APPROVED",
  "G",
  "M",
  "N/A",
  "NOT RATED",
  "PASSED",
  "PG",
  "PG-13",
  "R",
  "TV-14",
  "UNRATED",
  "X"
};

const char* rating_toString(const Rating r)
{
  return rating_n[r];
}
Rating rating_fromString(const char* const str)
{
  for (size_t i = 0; i < sizeof(rating_n); ++i)
  {
    if (strcmp(str, rating_n[i]) == 0)
      return (Rating)i;
  }
  return R_NONE;
}

const char* const category_n[] = {
  "None",
  "Action",
  "Adventure",
  "Animation",
  "Biography",
  "Comedy",
  "Crime",
  "Drama",
  "Family",
  "Fantasy",
  "Film-Noir",
  "History",
  "Horror",
  "Music",
  "Musical",
  "Mystery",
  "Romance",
  "Sci-Fi",
  "Short",
  "Sport",
  "Thriller",
  "War",
  "Western"
};

const char* category_toString(const Category c)
{
  return category_n[c];
}
Category* category_fromString(const char* const str)
{
  size_t cats = 0;
  for (size_t i = 0; i < strlen(str); ++i)
  {
    if (str[i] == '/')
      ++cats;
  }
  if (cats)
    ++cats;
  else
    return NULL;

  Category* c = (Category*)mt_malloc(sizeof(Category) * cats);

  size_t n = 0;
  size_t p = 0;
  for (size_t i = p; i < strlen(str)+1; ++i)
  {
    if (str[i] == '/' || i == strlen(str))
    {
      char buf[64];
      memcpy(buf, str+p, i-p);
      buf[i-p+1] = '\0';
      p = i+1;
      printf("%s\n", buf);
      ++n;
    }
  }

  return c;
}

typedef struct film_t
{
  const char* title;
  uint16_t year; // assuming 32k years is enough?
  Rating rating;
  Category* categories; // for now, allocated array
  uint16_t runtime; // in minutes
  double score; // how good (or bad) is this film
} Film;

Film* film_new(const char* title, uint16_t year, Rating rating, Category* categories, uint16_t runtime, double score)
{
  Film* film = (Film*)mt_malloc(sizeof(Film));

  if (film)
  {
    film->title = title;
    film->year = year;
    film->rating = rating;
    film->categories = categories;
    film->runtime = runtime;
    film->score = score;
  }

  return film;
}

void film_delete(Film* film)
{
  mt_free(film); // free(NULL) is no-op
}

void film_print(Film* film)
{
  if (!film)
    return;

  printf("%s\n\tYear: %u\n\tRating: %s\n\tCategories:", film->title, film->year, rating_toString(film->rating));

  Category* p = film->categories;
  while (p && *p != C_NONE)
    printf("\n\t· %s", category_toString(*(p++)));

  printf("\n\tRun time: %u minutes\n\tScore: %.1f\n", film->runtime, film->score);
}
