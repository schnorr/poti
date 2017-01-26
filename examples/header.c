/*
    This file is part of Poti

    Poti is free software: you can redistribute it and/or modify
    it under the terms of the GNU Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Poti is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Public License for more details.

    You should have received a copy of the GNU Public License
    along with Poti. If not, see <http://www.gnu.org/licenses/>.
*/
#include <poti.h>

struct test {
 bool poti_basic_events;
 bool poti_legacy_header;
 bool poti_with_comments;
 bool poti_with_alias;
 bool poti_relative_timestamps;
};

/*
 * This program tests all combinations by which poti can be initialize.
 */
int main (int argc, char **argv)
{
  int tn;
  
  if (argc != 2){
    return 1;
  }else{
    tn = atoi(argv[1]);
  }

  struct test *tests = malloc(sizeof(struct test));
  int ntests = 1;

  for (int a = 0; a < 2; a++){
    for (int b = 0; b < 2; b++){
      for (int c = 0; c < 2; c++){
	for (int d = 0; d < 2; d++){
	  tests[ntests-1].poti_basic_events = a;
	  tests[ntests-1].poti_legacy_header = b;
	  tests[ntests-1].poti_with_comments = false;
	  tests[ntests-1].poti_with_alias = c;
	  tests[ntests-1].poti_relative_timestamps = d;
	  ntests++;
	  tests = realloc(tests, ntests * sizeof(struct test));
	}
      }
    }
  }

  if (tn < ntests){
    printf ("# Running test %d out of %d tests.\n", tn, ntests);
    poti_init_custom (NULL,
		      tests[tn].poti_basic_events,
		      tests[tn].poti_legacy_header,
		      tests[tn].poti_with_comments,
		      tests[tn].poti_with_alias,
		      tests[tn].poti_relative_timestamps);
  }else{
    //Unsupported test
    printf ("# Unsupported test %d.\n", tn);
    return 2;
  }

  printf("# This trace has been created with the following init configuration:\n");
  printf("# With basic events: %s\n", tests[tn].poti_basic_events ? "true" : "false");
  printf("# With legacy header: %s\n", tests[tn].poti_legacy_header ? "true" : "false");
  printf("# With comments: %s\n", tests[tn].poti_with_comments ? "true" : "false");
  printf("# With aliases: %s\n", tests[tn].poti_with_alias ? "true" : "false");
  printf("# With relative timestamps: %s\n", tests[tn].poti_relative_timestamps ? "true" : "false");
  
  poti_header();

  poti_DContainerType ("0", "PROCESS");
  poti_DStateType ("PROCESS", "VAR");
  poti_ECreateContainer (123, "PROCESS", "0", "p1");
  poti_ESetState (123.1, "p1", "VAR", "Inicio");
  poti_EPushState (123.2, "p1", "VAR", "Meio");
  poti_EPopState (123.3, "p1", "VAR");

  poti_close();
  free(tests);
  return 0;
}
