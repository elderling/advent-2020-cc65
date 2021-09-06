#include <stdlib.h>
#include <stdio.h>
#include <cbm.h>
#include <string.h>

#define TREE '#'
#define NO_TREE '.'

void gimme_a_line( char lfn, char *put_it_here, char *how_many );

char aoc_open_file(const char name[], unsigned int lfn);
char wraparound_char_at(unsigned int index, char *theString);

char aoc_open_file(const char name[], unsigned int lfn) {
 char open_result,chkin_result;

  open_result = cbm_open( lfn, 8, 0, name );

  if ( open_result != 0 ) {
    printf("Error: %d", open_result);
    cbm_k_close( lfn );
    return -1;
  }

  chkin_result = cbm_k_chkin( lfn );

  //printf("chkin_result = '%d'", chkin_result);
  return 0;
}

void gimme_a_line( char lfn, char *put_it_here, char *how_many ) {
   char data, bytes_read;
   char string_position = 0;
   *how_many = 0;
   put_it_here[0] = 0;

  do {
    
    bytes_read = cbm_read( lfn, &data, 1);

    if ( bytes_read ) {
      if ( data == 0x0d ) {
          put_it_here[string_position] = 0;

          *how_many = string_position + 1;
          return;
          string_position = 0;
      }
      else {
        put_it_here[string_position++] = data;
        *how_many = string_position + 1;
      }
    }

  }
  while ( bytes_read > 0 );

  return;
}

char wraparound_char_at(unsigned int index, char *theString)
{
  return theString[index % 31];
}

int main() {
  char lfn, result;
  char the_string[32];
  int total_lines_read = 0;
  char how_many;
  unsigned int total_trees = 0;
  unsigned int x_axis = 0;

  const char* name = "advent-20-03,s,r";

  lfn = 1;

  result = aoc_open_file( name, lfn );

  do {
    gimme_a_line( lfn, the_string, &how_many );
    if (strlen(the_string) > 0) {
      total_lines_read++;
      if ( wraparound_char_at(x_axis, the_string) == TREE ) {
        printf("TREE at %d!\n", x_axis);
        total_trees++;
      }
      else {
        printf("NO_TREE at %d!\n", x_axis);
      }
      x_axis = x_axis + 3;
      //printf( "%s\n", the_string );
    }
  }
  while ( strlen(the_string) > 0 );

  cbm_k_close( lfn );

  printf("Total lines read = %d", total_lines_read);
  printf("Total trees = %d", total_trees);

  return 0;
}
