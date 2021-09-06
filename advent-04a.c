#include <stdlib.h>
#include <stdio.h>
#include <cbm.h>
#include <string.h>
#include <stdint.h>

typedef struct {
  char * key;
  char * value;
} Key_Value_Pair_t;

char * themStrings[8];
uint8_t themStringsDepth = 0;

void gimme_a_line( char lfn, char *put_it_here, char *how_many );

char aoc_open_file(const char name[], unsigned int lfn);

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

int main() {
  char lfn, result;
  char the_string[128];
  int total_lines_read = 0;
  char how_many = 0;
  char * the_token;
  char * delimiter = " ";
  uint8_t i;
  char * new_string;

  const char* name = "advent-20-04,s,r";

  lfn = 1;

  result = aoc_open_file( name, lfn );

  do {
    gimme_a_line( lfn, the_string, &how_many );
    if ( how_many > 0) {
      total_lines_read++;

      if ( how_many > 1 ) {
        the_token = strtok( the_string, delimiter );

        new_string = malloc( strlen( the_token ) );
        strcpy(new_string, the_token);
        themStrings[themStringsDepth] = new_string;
        themStringsDepth++;
        while ( the_token = strtok( NULL, delimiter ) )  {
          //printf("%s\n", the_token);
          new_string = malloc( strlen( the_token ) );
          strcpy(new_string, the_token);
          themStrings[themStringsDepth] = new_string;
          themStringsDepth++;
        }
      } else {
        //do something with themStrings
        for (i = 0; i < themStringsDepth; i++ ) {
          printf("%s\n", themStrings[i]);
          free( themStrings[i] );
        }
        themStringsDepth = 0;
        printf("\n");
      }
    } else {
        //do something with themStrings
        for (i = 0; i < themStringsDepth; i++ ) {
          printf("%s\n", themStrings[i]);
          free( themStrings[i] );
        }
        themStringsDepth = 0;
        printf("\n");
    }
  }
  while ( how_many > 0 );

  cbm_k_close( lfn );

  printf("Total lines read = %d", total_lines_read);

  return 0;
}
