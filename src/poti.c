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

bool poti_basic_events = false;
bool poti_legacy_header = false;
bool poti_with_comments = true;
bool poti_with_alias = true;
bool poti_relative_timestamps = true;

FILE* paje_file = NULL;

static void _init (void)
{
  /* allocate identifiers list */
  if (!identifiers){
    identifiers = (int*) malloc (PAJE_FinalMarker * sizeof(int));
  }
}

static bool poti_getenv (const char *name, bool default_value)
{
  char *value = getenv(name);
  if (value == NULL){
    return default_value;
  }else{
    if (atoi(value) == 0){
      return false;
    }
  }
  return true;
}

static void poti_header_envs (void)
{
  /* No additional fields for events */
  poti_basic_events = poti_getenv("POTI_BASIC_EVENTS", poti_basic_events);
  
  /* Support for old header names (vite-support) */
  poti_legacy_header = poti_getenv("POTI_LEGACY_HEADER", poti_legacy_header);

  /* Comments are not show in the output */
  poti_with_comments = poti_getenv("POTI_WITH_COMMENTS", poti_with_comments);

  /* If events have aliases, this might reduce trace size */
  poti_with_alias = poti_getenv("POTI_WITH_ALIAS", poti_with_alias);

  /* Absolute timestamps */
  poti_relative_timestamps = poti_getenv("POTI_RELATIVE_TIMESTAMPS", poti_relative_timestamps);
}

bool poti_init ()
{
  poti_init_filename (NULL);
  poti_header_envs ();
  return true;
}

bool poti_init_filename (const char *filename)
{
  return poti_init_custom (filename, poti_basic_events, poti_legacy_header, poti_with_comments, poti_with_alias, poti_relative_timestamps);
}

bool poti_init_custom (const char* filename, bool basic_events, bool legacy_header, bool with_comments, bool with_alias, bool relative_timestamps)
{
  if (filename == NULL){
    paje_file = stdout;
  }else{
    paje_file = fopen(filename, "w");
    if (!paje_file){
      return false;
    }
  }

  poti_basic_events = basic_events;
  poti_legacy_header = legacy_header;
  poti_with_comments = with_comments;
  poti_with_alias = with_alias;
  poti_relative_timestamps = relative_timestamps;

  _init();
  return true;
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

void poti_header ()
{
  poti_comment("POTI_GIT_VERSION %s", POTI_GITVERSION);
  poti_comment("POTI_GIT_DATE (date of the cmake configuration) %s", POTI_GITDATE);
  _poti_header();
}

void poti_comment (const char *format, ...)
{
  if (!poti_with_comments) return;
  
  va_list arg;

  fprintf(paje_file, "# ");
  va_start(arg, format);
  vfprintf(paje_file, format, arg);
  va_end(arg);
  fprintf(paje_file, "\n");
}
