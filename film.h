#ifndef FILM_H_INCLUDE
#define FILM_H_INCLUDE

#include <stdint.h>
#include <stdbool.h>

#include "llist.h"

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
  UNRATED,
  NUM_RATINGS
} Rating;
typedef enum category_t
{
  C_NONE    = 0x000001,
  ACTION    = 0x000002,
  ADVENTURE = 0x000004,
  ANIMATION = 0x000008,
  BIOGRAPHY = 0x000010,
  COMEDY    = 0x000020,
  CRIME     = 0x000040,
  DRAMA     = 0x000080,
  FAMILY    = 0x000100,
  FANTASY   = 0x000200,
  FILM_NOIR = 0x000400,
  HISTORY   = 0x000800,
  HORROR    = 0x001000,
  MUSIC     = 0x002000,
  MUSICAL   = 0x004000,
  MYSTERY   = 0x008000,
  ROMANCE   = 0x010000,
  SCI_FI    = 0x020000,
  SHORT     = 0x040000,
  SPORT     = 0x080000,
  THRILLER  = 0x100000,
  WAR       = 0x200000,
  WESTERN   = 0x400000,
  NUM_CATEGORIES = 22
} Category;
typedef uint_least32_t CategoryType;
const char* rating_toString(const Rating r);
const char* category_toString(const Category c);
Rating rating_fromString(const char* const str);
Category category_fromString(const char* const str);
Category category_fromStrings(const char* const str);


typedef struct film_t Film;

Film* film_new(const char* title, uint16_t year, Rating rating,
               CategoryType categories, uint16_t runtime, double score);
void film_delete(Film* film);
void film_print(Film* film);

const char* film_getTitle(const Film* const film);
uint16_t film_getYear(const Film* const film);
Rating film_getRating(const Film* const film);
uint16_t film_getRuntime(const Film* const film);
double film_getScore(const Film* const film);

bool film_hasCategory(const Film* const film, const Category cat);

#endif
