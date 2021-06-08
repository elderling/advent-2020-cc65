#include <stdlib.h>
#include <stdio.h>
#include <cbm.h>
#include <string.h>

unsigned char is_char_at_index( unsigned char the_char, unsigned char index, unsigned char the_string[] );

unsigned char is_char_at_index( unsigned char the_char, unsigned char index, unsigned char the_string[] ) {
  if ( the_string[index] == the_char ) {
    return 1;
  }

  return 0;
}

unsigned char aoc_open_file(const unsigned char name[], unsigned int lfn);

unsigned char aoc_open_file(const unsigned char name[], unsigned int lfn) {
  unsigned char open_result,chkin_result;

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

int main() {
  unsigned char string_position, lfn, bytes_read, data, result;
  unsigned char the_string[32];
  int total_lines_read = 0;
  int total_valid_passwords = 0;
  signed char min, max, count;
  unsigned char *min_str, *max_str, *the_range_str, *the_letter_str, *the_password_str, the_letter;

  const unsigned char* name = "advent-20-02,s,r";

  lfn = 1;

  result = aoc_open_file( name, lfn );

  count = 0;
  the_string[0] = 0;
  string_position = 0;
  do {
    
    bytes_read = cbm_read( lfn, &data, 1);

    if ( bytes_read ) {
      if ( data == 0x0d ) {
          the_string[string_position] = 0;

          the_range_str = strtok(the_string, " ");
          //printf("Range: %s\n", the_range_str);
          the_letter_str = strtok(NULL, " ");
          the_password_str = strtok(NULL, " ");

          min_str = strtok(the_range_str, "-");
          max_str = strtok(NULL, "-");

          min = atoi(min_str);
          max = atoi(max_str);
          printf("range: %d-%d\n", min, max);
          the_letter = the_letter_str[0];

          //printf("password: %s\n", the_password_str);
          printf("letter %c appears in %s %d times", the_letter, the_password_str, count);
          printf("\n");
          if ( count >= min && count <= max ) {
            total_valid_passwords++;
          }

          total_lines_read++;
          //printf("%s\n", the_string);
          //printf("min is %s\n", min_str);
          //printf("the_rest is %s\n", the_rest_str);

          //max_str = strtok(the_rest_str, " ");

          //the_rest_str =  strtok(NULL, "-");


          string_position = 0;
      }
      else {
        the_string[string_position++] = data;
      }
    }

  }
  while ( bytes_read > 0 );

  cbm_k_close( lfn );

  printf("\n");
  printf("Total lines read = %d", total_lines_read);
  printf("Total valid passwords = %d", total_valid_passwords);

  return 0;
}
