#include <stdlib.h>
#include <stdio.h>
#include <cbm.h>
#include <string.h>

long int get_nth_long( long int *the_longs, int n );

long int get_nth_long( long int *the_longs, int n ) {
  return *(the_longs + n * sizeof(long int));
}

int main() {
  unsigned char string_position, lfn, open_result, chkin_result, bytes_read, data;
  unsigned char the_string[32];
  int total_lines_read = 0;
  signed char min, max, count, the_rest;
  unsigned char *min_str, *max_str, *count_str, *the_rest_str, *the_range_str, *the_letter_str, *the_password_str, the_letter;

  const unsigned char* name = "advent-20-02,s,r";

  lfn = 1;

  open_result = cbm_open( lfn, 8, 0, name );

  if ( open_result != 0 ) {
    printf("Error: %d", open_result);
    cbm_k_close( lfn );
    return -1;
  }

  chkin_result = cbm_k_chkin( lfn );

  //printf("chkin_result = '%d'", chkin_result);

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
          printf("range: %d-%d", min, max);
          the_letter = the_letter_str[0];
          printf(" letter: %c\n", the_letter);
          printf("password: %s\n", the_password_str);
          printf("\n");



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

  return 0;
}
