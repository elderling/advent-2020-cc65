#include <stdlib.h>
#include <stdio.h>
#include <cbm.h>

int main() {
  unsigned char string_position, lfn, open_result, chkin_result, bytes_read, data;
  unsigned char number_string[10];
  unsigned char** endptr;
  long int the_actual_number;
  long int the_long_total = 0;
  int total_lines_read = 0;
	long int *list_of_longs;
	long int *current_long;
	int i;

  const unsigned char* name = "advent-20-01,s,r";

	list_of_longs = (long int*)malloc(200 * sizeof(long int));

  printf("'%s'", name);
  lfn = 1;

  open_result = cbm_open( lfn, 8, 0, name );

  if ( open_result != 0 ) {
    printf("Error: %d", open_result);
    cbm_k_close( lfn );
    return -1;
  }

  chkin_result = cbm_k_chkin( lfn );

  printf("chkin_result = '%d'", chkin_result);

  number_string[0] = 0;
  string_position = 0;
	current_long = list_of_longs;
  do {
    
    bytes_read = cbm_read( lfn, &data, 1);

    if ( bytes_read ) {
      if ( data == 0x0d ) {
          //printf("\n");
          number_string[string_position] = 0;
          // printf("%s\n", number_string);
          the_actual_number = strtol(number_string, endptr, 0);
					*current_long = the_actual_number;
					current_long += sizeof(long int);

          the_long_total += the_actual_number;
          total_lines_read++;
          //printf("%ld\n", the_actual_number);

          string_position = 0;
      }
      else {
        //printf("%c", data);
        number_string[string_position++] = data;
      }
    }

  }
  while ( bytes_read > 0 );

	for(i=0; i < total_lines_read * sizeof(long int); i = i + sizeof(long int) ) {
		printf("%ld\n", *(list_of_longs + i) );
	}
	

  cbm_k_close( lfn );

  printf("\n");
  printf("'%s'", name);
  printf("The Long Total = %ld", the_long_total);
  printf("Total lines read = %d", total_lines_read);

  return 0;
}
