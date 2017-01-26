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
#include <stdlib.h>
#include <argp.h>

static char doc[] = "Generates Paje Trace FILENAME, with a limite size of SIZE";
static char args_doc[] = "FILENAME [SIZE]";

static struct argp_option options[] = {
  {"size", 's', "SIZE", 0, "The target size of the file in bytes.", 0},
  {"filename", 'f', "FILENAME", 0, "The filename of the output.", 0},
  { 0 }
};

struct arguments {
  char *filename;
  int targetSize;
};

static error_t parse_options (int key, char *arg, struct argp_state *state)
{
  struct arguments *arguments = (struct arguments*)(state->input);
  switch (key){
  case 's': arguments->targetSize = atoi(arg); break;
  case 'f': arguments->filename = strdup(arg); break;
  case ARGP_KEY_ARG:
    argp_usage (state);
    break;
  case ARGP_KEY_END:
    if (!arguments->filename) {
      argp_usage (state);
    }
    break;
  default: return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static struct argp argp = { options, parse_options, args_doc, doc, NULL, NULL, NULL };

#define INCREASE ((double)((double)rand()/(double)RAND_MAX))
#define MINIMAL 2407

int main (int argc, char **argv)
{
  struct arguments arguments;
  bzero (&arguments, sizeof(struct arguments));
  arguments.targetSize = 0;
  if (argp_parse (&argp, argc, argv, 0, 0, &arguments) == ARGP_KEY_ERROR){
    fprintf(stderr, "%s, error during the parsing of parameters.\n", argv[0]);
    return 1;
  }
  
  srand(1);

  //open file for writing
  FILE *file = fopen(arguments.filename, "w");
  if (!file){
    fprintf(stderr, "%s, can't open file %s for writing.\n", argv[0], arguments.filename);
    return 1;
  }
  
  poti_init_filename (arguments.filename);

  poti_header ();
  poti_DefineContainerType ("P", "0", "P");
  poti_DefineStateType ("S", "P", "S");

  poti_CreateContainer (0, "p1", "P", "0", "p1");
  poti_SetState (0, "p1", "S", "I");

  double timestamp = INCREASE;
  
  while (ftell(file) < arguments.targetSize){
    //The size in bytes of these two events is 
    poti_PushState (timestamp, "p1", "S", "M");
    timestamp += INCREASE;
    poti_PopState (timestamp, "p1", "S");
    timestamp += INCREASE;
  }
  poti_DestroyContainer (timestamp, "P", "p1");
  printf ("Output is %ld bytes (target was %d; %ld bytes more).\n", ftell(file), arguments.targetSize, ftell(file)-arguments.targetSize);
  poti_close();
  free(arguments.filename);
  return 0;
}
