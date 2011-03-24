
#include "string_score.h"
#include <string.h>
#include <stdio.h>

int main(int argc, char** argv)
{
  char* a = argv[1];
  char* b = argv[2];
  printf( "Normal match: %f\n", string_score(a,b) );
  return 0;
}
