#include <stdlib.h>
#include <stdio.h>
#include <cbm.h>

long int get_nth_long( long int *the_longs, int n );

long int get_nth_long( long int *the_longs, int n ) {
  return *(the_longs + n * sizeof(long int));
}

int main() {
  unsigned char string_position, lfn, open_result, chkin_result, bytes_read, data;
  unsigned char number_string[10];
  unsigned char** endptr;
  long int the_actual_number;
  int total_lines_read = 0;
	long int *list_of_longs;
	long int *current_long;
	int i,j,k;
  long int first, second, third;

  const unsigned char* name = "advent-20-01,s,r";

	list_of_longs = (long int*)malloc(200 * sizeof(long int));

  lfn = 1;

  open_result = cbm_open( lfn, 8, 0, name );

  if ( open_result != 0 ) {
    printf("Error: %d", open_result);
    cbm_k_close( lfn );
    return -1;
  }

  chkin_result = cbm_k_chkin( lfn );

  //printf("chkin_result = '%d'", chkin_result);

  number_string[0] = 0;
  string_position = 0;
	current_long = list_of_longs;
  do {
    
    bytes_read = cbm_read( lfn, &data, 1);

    if ( bytes_read ) {
      if ( data == 0x0d ) {
          number_string[string_position] = 0;
          the_actual_number = strtol(number_string, endptr, 0);
					*current_long = the_actual_number;
					current_long += sizeof(long int);

          total_lines_read++;

          string_position = 0;
      }
      else {
        number_string[string_position++] = data;
      }
    }

  }
  while ( bytes_read > 0 );

  cbm_k_close( lfn );

	for(i=0; i < total_lines_read; i++ ) {
		printf( "%ld\n", get_nth_long(list_of_longs, i) );
    first = get_nth_long(list_of_longs, i);
    for (j=0; j < total_lines_read; j++) {
      second = get_nth_long(list_of_longs, j);
      for (k=0; k < total_lines_read; k++ ) {
        third = get_nth_long(list_of_longs, k);
        if (first + second + third == 2020) {
          printf("%ld,%ld,%ld,%ld\n", first, second, third, first * second * third);
        }
      }
    }
	}

  printf("\n");
  printf("'%s'", name);
  printf("Total lines read = %d", total_lines_read);

  return 0;
}
