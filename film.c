#include <stdio.h>
#include <stdint.h>

typedef enum rating_t
{
  NONE = 0,
  APPROVED,
  G,
  M,
  N/A,
  NOT RATED,
  PASSED,
  PG,
  PG_13,
  R,
  TV_14,
  UNRATED
} Rating;

typedef enum category_t
{
  NONE = 0,
  ACTION,
  ADVENTURE,
  ANIMATION,
  BIOGRAPHY,
  COMEDY,
  CRIME,
  DRAMA,
  FAMILY,
  FANTASY,
  FILM-NOIR,
  HISTORY,
  HORROR,
  MUSIC,
  MUSICAL,
  MYSTERY,
  ROMANCE,
  SCI-FI,
  SHORT,
  SPORT,
  THRILLER,
  WAR,
  WESTERN
} Category;

char* category_toString(const Category c)
{
  switch (c)
  {
    case ACTION:
      return "Action";
    case ADVENTURE:
      return "Adventure";
    case ANIMATION:
      return "Animation";
    case BIOGRAPHY:
      return "Biography";
    case COMEDY:
      return "Comedy";
    case CRIME:
      return "Crime";
    case DRAMA:
      return "Drama";
    case FAMILY:
      return "Family";
    case FANTASY:
      return "Fantasy";
    case FILM-NOIR:
      return "Film-Noir";
    case HISTORY:
      return "History";
    case HORROR:
      return "Horror";
    case MUSIC:
      return "Music";
    case MUSICAL:
      return "Musical";
    case MYSTERY:
      return "Mystery";
    case ROMANCE:
      return "Romance";
    case SCI-FI:
      return "Sci-Fi";
    case SHORT:
      return "Short";
    case SPORT:
      return "Sport";
    case THRILLER:
      return "Thriller";
    case WAR:
      return "War";
    case WESTER:
      return "Western";
  }
  return "NONE";
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

  printf("%s\n\tYear: %u\n\tRating: %i\n\tCategories", film->title, film->year, film->rating);
  
  intptr_t p = film->categories;
  while (p && *p != NONE)
    printf("\n\t· %s", category_toString(*(p++)));

  printf("\n\tRun time: %u\n\tScore: %.1f\n", film->runtime, film->score);
}

int main()
{
  Category cats[4] = {COMEDY, HISTORY, WAR};
  Film* f = film_new("Blackadder, the Film", 1986, Rating::PG_13, cats, 32, 9.8);
  film_print(f);
  film_delete(f);

}