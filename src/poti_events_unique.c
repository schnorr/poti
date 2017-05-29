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
#include <stdarg.h>
#include <ctype.h>
#include "poti_private.h"

static inline void print_event_type (int unique)
{
  fprintf(paje_file, "%d", unique);
}

#define EXTRAFIELDS()                           \
  if(extra == 0){ \
    fprintf(paje_file, "\n"); \
  }else{ \
    int i; \
    va_list arguments; \
    va_start (arguments, extra); \
    for (i = 0; i < extra; i++){ \
      fprintf(paje_file, " %s", va_arg (arguments, char*)); \
    } \
    va_end (arguments); \
    fprintf(paje_file, "\n"); \
  }

static int has_spaces (const char *s)
{
  while (*s != '\0') {
    if (isspace(*s)) return 1;
    s++;
  }
  return 0;
}

#define PFS(A,BUF,LEN) protect_from_spaces(A,BUF,LEN)
static const char *protect_from_spaces (const char *field, char *buffer, int bufferlen)
{
  if (!has_spaces(field)) return field;
  int len = strlen(field);
  buffer[0] = '\"';
  strncpy(buffer+1, field, POTI_STR_SIZE);
  buffer[len+1] = '\"';
  buffer[len+1+1] = '\0';
  return buffer;
}

void poti_user_DefineContainerType (const int unique, const char *alias, const char *containerType, const char *name, int extra, ...)
{
  char buffer[POTI_STR_SIZE];
  print_event_type (unique);
  if (poti_with_alias){
    fprintf(paje_file," %s", alias);
  }
  fprintf(paje_file, " %s", containerType);
  fprintf(paje_file, " %s", PFS(name, buffer, POTI_STR_SIZE));
  EXTRAFIELDS();
}

void poti_user_DefineVariableType (const int unique, const char *alias, const char *containerType, const char *name, const char *color, int extra, ...)
{
  char buffer[POTI_STR_SIZE];
  print_event_type (unique);
  if (poti_with_alias){
    fprintf(paje_file," %s", alias);
  }
  fprintf(paje_file, " %s", containerType);
  fprintf(paje_file, " %s", PFS(name, buffer, POTI_STR_SIZE));
  fprintf(paje_file, " %s", PFS(color, buffer, POTI_STR_SIZE));
  EXTRAFIELDS();
}

void poti_user_DefineStateType (const int unique, const char *alias, const char *containerType, const char *name, int extra, ...)
{
  char buffer[POTI_STR_SIZE];
  print_event_type (unique);
  if (poti_with_alias){
    fprintf(paje_file," %s", alias);
  }
  fprintf(paje_file, " %s", containerType);
  fprintf(paje_file, " %s", PFS(name, buffer, POTI_STR_SIZE));
  EXTRAFIELDS();
}

void poti_user_DefineEventType (const int unique, const char *alias, const char *containerType, const char *name, int extra, ...)
{
  char buffer[POTI_STR_SIZE];
  print_event_type (unique);
  if (poti_with_alias){
    fprintf(paje_file," %s", alias);
  }
  fprintf(paje_file, " %s", containerType);
  fprintf(paje_file, " %s", PFS(name, buffer, POTI_STR_SIZE));
  EXTRAFIELDS();
}

void poti_user_DefineLinkType (const int unique, const char *alias, const char *containerType, const char *startContainerType, const char *endContainerType, const char *name, int extra, ...)
{
  char buffer[POTI_STR_SIZE];
  print_event_type (unique);
  if (poti_with_alias){
    fprintf(paje_file," %s", alias);
  }
  fprintf(paje_file, " %s", containerType);
  fprintf(paje_file, " %s", startContainerType);
  fprintf(paje_file, " %s", endContainerType);
  fprintf(paje_file, " %s", PFS(name, buffer, POTI_STR_SIZE));
  EXTRAFIELDS();
}

void poti_user_DefineEntityValue (const int unique, const char *alias, const char *entityType, const char *name, const char *color, int extra, ...)
{
  char buffer[POTI_STR_SIZE];
  print_event_type (unique);
  if (poti_with_alias){
    fprintf(paje_file," %s", alias);
  }
  fprintf(paje_file, " %s", entityType);
  fprintf(paje_file, " %s", PFS(name, buffer, POTI_STR_SIZE));
  fprintf(paje_file, " %s", PFS(color, buffer, POTI_STR_SIZE));
  EXTRAFIELDS();
}

void poti_user_CreateContainer (const int unique, double timestamp, const char *alias, const char *type, const char *container, const char *name, int extra, ...)
{
  char buffer[POTI_STR_SIZE];
  print_event_type (unique);
  fprintf(paje_file, " %.9f", paje_event_timestamp(timestamp));
  if (poti_with_alias){
    fprintf(paje_file," %s", alias);
  }
  fprintf(paje_file, " %s", container);
  fprintf(paje_file, " %s", type);
  fprintf(paje_file, " %s", PFS(name, buffer, POTI_STR_SIZE));
  EXTRAFIELDS();
}

void poti_user_DestroyContainer (const int unique, double timestamp, const char *type, const char *container, int extra, ...)
{
  print_event_type (unique);
  fprintf(paje_file, " %.9f", paje_event_timestamp(timestamp));
  fprintf(paje_file, " %s", type);
  fprintf(paje_file, " %s", container);
  EXTRAFIELDS();
}

void poti_user_SetVariable (const int unique, double timestamp, const char *container, const char *type, double value, int extra, ...)
{
  print_event_type (unique);
  fprintf(paje_file, " %.9f", paje_event_timestamp(timestamp));
  fprintf(paje_file, " %s", container);
  fprintf(paje_file, " %s", type);
  fprintf(paje_file, " %f", value);
  EXTRAFIELDS();
}

void poti_user_AddVariable (const int unique, double timestamp, const char *container, const char *type, double value, int extra, ...)
{
  print_event_type (unique);
  fprintf(paje_file, " %.9f", paje_event_timestamp(timestamp));
  fprintf(paje_file, " %s", container);
  fprintf(paje_file, " %s", type);
  fprintf(paje_file, " %f", value);
  EXTRAFIELDS();
}

void poti_user_SubVariable (const int unique, double timestamp, const char *container, const char *type, double value, int extra, ...)
{
  print_event_type (unique);
  fprintf(paje_file, " %.9f", paje_event_timestamp(timestamp));
  fprintf(paje_file, " %s", container);
  fprintf(paje_file, " %s", type);
  fprintf(paje_file, " %f", value);
  EXTRAFIELDS();
}

void poti_user_SetState (const int unique, double timestamp, const char *container, const char *type, const char *value, int extra, ...)
{
  char buffer[POTI_STR_SIZE];
  print_event_type (unique);
  fprintf(paje_file, " %.9f", paje_event_timestamp(timestamp));
  fprintf(paje_file, " %s", container);
  fprintf(paje_file, " %s", type);
  fprintf(paje_file, " %s", PFS(value, buffer, POTI_STR_SIZE));
  EXTRAFIELDS();
}

void poti_user_PushState (const int unique, double timestamp, const char *container, const char *type, const char *value, int extra, ...)
{
  char buffer[POTI_STR_SIZE];
  print_event_type (unique);
  fprintf(paje_file, " %.9f", paje_event_timestamp(timestamp));
  fprintf(paje_file, " %s", container);
  fprintf(paje_file, " %s", type);
  fprintf(paje_file, " %s", PFS(value, buffer, POTI_STR_SIZE));
  EXTRAFIELDS();
}

void poti_user_PopState (const int unique, double timestamp, const char *container, const char *type, int extra, ...)
{
  print_event_type (unique);
  fprintf(paje_file, " %.9f", paje_event_timestamp(timestamp));
  fprintf(paje_file, " %s", container);
  fprintf(paje_file, " %s", type);
  EXTRAFIELDS();
}

void poti_user_ResetState (const int unique, double timestamp, const char *container, const char *type, int extra, ...)
{
  print_event_type (unique);
  fprintf(paje_file, " %.9f", paje_event_timestamp(timestamp));
  fprintf(paje_file, " %s", container);
  fprintf(paje_file, " %s", type);
  EXTRAFIELDS();
}

void poti_user_StartLink (const int unique, double timestamp, const char *container, const char *type, const char *sourceContainer, const char *value, const char *key, int extra, ...)
{
  char buffer[POTI_STR_SIZE];
  print_event_type (unique);
  fprintf(paje_file, " %.9f", paje_event_timestamp(timestamp));
  fprintf(paje_file, " %s", container);
  fprintf(paje_file, " %s", type);
  fprintf(paje_file, " %s", sourceContainer);
  fprintf(paje_file, " %s", PFS(value, buffer, POTI_STR_SIZE));
  fprintf(paje_file, " %s", key);
  EXTRAFIELDS();
}

void poti_user_EndLink (const int unique, double timestamp, const char *container, const char *type, const char *endContainer, const char *value, const char *key, int extra, ...)
{
  char buffer[POTI_STR_SIZE];
  print_event_type (unique);
  fprintf(paje_file, " %.9f", paje_event_timestamp(timestamp));
  fprintf(paje_file, " %s", container);
  fprintf(paje_file, " %s", type);
  fprintf(paje_file, " %s", endContainer);
  fprintf(paje_file, " %s", PFS(value, buffer, POTI_STR_SIZE));
  fprintf(paje_file, " %s", key);
  EXTRAFIELDS();
}

void poti_user_NewEvent (const int unique, double timestamp, const char *container, const char *type, const char *value, int extra, ...)
{
  char buffer[POTI_STR_SIZE];
  print_event_type (unique);
  fprintf(paje_file, " %.9f", paje_event_timestamp(timestamp));
  fprintf(paje_file, " %s", container);
  fprintf(paje_file, " %s", type);
  fprintf(paje_file, " %s", PFS(value, buffer, POTI_STR_SIZE));
  EXTRAFIELDS();
}

