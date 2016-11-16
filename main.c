#include "moviedatabase.h"

int main()
{
  mdb_loadDB("films.txt");

  task1();
  task2();
  task3();
  task4();
  task5();
  task6();
  mdb_freeDB();
}
