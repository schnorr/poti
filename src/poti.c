/*
    This file is part of Poti

    Poti is free software: you can redistribute it and/or modify it
    under the terms of the GNU Lesser Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Poti is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser Public License for more details.

    You should have received a copy of the GNU Lesser Public License
    along with Poti. If not, see <http://www.gnu.org/licenses/>.
*/
#include "poti_private.h"

bool poti_alias = false;
bool disable_comments = false;
FILE* paje_file = 0;
bool paje_extended = false;
bool relative_timestamps = true;
static bool poti_alias_initialized = false;

int poti_open (const char* filename)
{
  FILE* fout = fopen(filename,"w");
  if (fout ==0) return -1;
  paje_file = fout;
  return 0;
}

int poti_init (FILE *file)
{
  /* allocate identifiers list */
  if (!identifiers){
    identifiers = (int*) malloc (PAJE_FinalMarker * sizeof(int));
  }

  if (file){
    paje_file = file;
    return 0;
  }else{
    return -1;
  }
}

void poti_close ()
{
  /* deallocate identifiers list */
  free(identifiers);

  if (paje_file != stdout)
  {
    fclose( paje_file );
  }
  paje_file = 0;
}

void poti_header (int basic, int old_header)
{
  if (getenv("POTI_DISABLE_COMMENTS")){
    disable_comments = true;
  }

  if (paje_file == 0)
  {
    paje_file=stdout;
  }

  poti_init (paje_file);

  if (!disable_comments){
    fprintf(paje_file,"#POTI_GIT_VERSION %s\n", POTI_GITVERSION);
    fprintf(paje_file,"#POTI_GIT_DATE (date of the cmake configuration) %s\n", POTI_GITDATE);
  }
  poti_header_only (basic, old_header);
  poti_alias_initialized = true;
}

void poti_header_only (int basic, int old_header)
{
  _poti_header (basic, old_header);
}

void poti_set_alias (bool alias)
{
  if (!poti_alias_initialized){
    poti_alias = alias;
    poti_alias_initialized = true;
  }else{
    fprintf (stderr, "#Poti Warning Message: %s should be called once and before header.\n", __FUNCTION__);
  }
}
