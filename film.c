#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef enum rating_t
{
  R_NONE = 0,
  APPROVED,
  G,
  M,
  N_A,
  NOT_RATED,
  PASSED,
  PG,
  PG_13,
  R,
  TV_14,
  UNRATED
} Rating;

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

const char* const rating_toString(const Rating r)
{
  return rating_n[r];
}

typedef enum category_t
{
  C_NONE = 0,
  ACTION,
  ADVENTURE,
  ANIMATION,
  BIOGRAPHY,
  COMEDY,
  CRIME,
  DRAMA,
  FAMILY,
  FANTASY,
  FILM_NOIR,
  HISTORY,
  HORROR,
  MUSIC,
  MUSICAL,
  MYSTERY,
  ROMANCE,
  SCI_FI,
  SHORT,
  SPORT,
  THRILLER,
  WAR,
  WESTERN
} Category;

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

const char* const category_toString(const Category c)
{
  return category_n[c];
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
  Film* film = (Film*)malloc(sizeof(Film));

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
  free(film); // free(NULL) is no-op
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

int main()
{
  Category cats[4] = {COMEDY, HISTORY, WAR};
  Film* f = film_new("Blackadder, the Film", 1986, PG_13, cats, 32, 9.8);
  film_print(f);
  film_delete(f);

  return 0;
}
