#ifndef FILM_H_INCLUDE
#define FILM_H_INCLUDE

#include <stdint.h>

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
const char* rating_toString(const Rating r);
const char* category_toString(const Category c);
Rating rating_fromString(const char* const str);
Category category_fromString(const char* const str);
Category* category_fromStrings(const char* const str);


typedef struct film_t Film;

Film* film_new(const char* title, uint16_t year, Rating rating,
               Category* categories, uint16_t runtime, double score);
void film_delete(Film* film);
void film_print(Film* film);

#endif
