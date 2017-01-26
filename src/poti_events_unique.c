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

void poti_UDefineContainerType (const int unique, const char *alias, const char *containerType, const char *name, int extra, ...)
{
  print_event_type (unique);
  if (poti_with_alias){
    fprintf(paje_file," %s", alias);
  }
  fprintf(paje_file, " %s", containerType);
  fprintf(paje_file, " \"%s\"", name);
  EXTRAFIELDS();
}

void poti_UDefineVariableType (const int unique, const char *alias, const char *containerType, const char *name, const char *color, int extra, ...)
{
  print_event_type (unique);
  if (poti_with_alias){
    fprintf(paje_file," %s", alias);
  }
  fprintf(paje_file, " %s", containerType);
  fprintf(paje_file, " \"%s\"", name);
  fprintf(paje_file, " \"%s\"", color);
  EXTRAFIELDS();
}

void poti_UDefineStateType (const int unique, const char *alias, const char *containerType, const char *name, int extra, ...)
{
  print_event_type (unique);
  if (poti_with_alias){
    fprintf(paje_file," %s", alias);
  }
  fprintf(paje_file, " %s", containerType);
  fprintf(paje_file, " \"%s\"", name);
  EXTRAFIELDS();
}

void poti_UDefineEventType (const int unique, const char *alias, const char *containerType, const char *name, int extra, ...)
{
  print_event_type (unique);
  if (poti_with_alias){
    fprintf(paje_file," %s", alias);
  }
  fprintf(paje_file, " %s", containerType);
  fprintf(paje_file, " \"%s\"", name);
  EXTRAFIELDS();
}

void poti_UDefineLinkType (const int unique, const char *alias, const char *containerType, const char *startContainerType, const char *endContainerType, const char *name, int extra, ...)
{
  print_event_type (unique);
  if (poti_with_alias){
    fprintf(paje_file," %s", alias);
  }
  fprintf(paje_file, " %s", containerType);
  fprintf(paje_file, " %s", startContainerType);
  fprintf(paje_file, " %s", endContainerType);
  fprintf(paje_file, " \"%s\"", name);
  EXTRAFIELDS();
}

void poti_UDefineEntityValue (const int unique, const char *alias, const char *entityType, const char *name, const char *color, int extra, ...)
{
  print_event_type (unique);
  if (poti_with_alias){
    fprintf(paje_file," %s", alias);
  }
  fprintf(paje_file, " %s", entityType);
  fprintf(paje_file, " %s", name);
  fprintf(paje_file, " \"%s\"", color);
  EXTRAFIELDS();
}

void poti_UCreateContainer (const int unique, double timestamp, const char *alias, const char *type, const char *container, const char *name, int extra, ...)
{
  print_event_type (unique);
  fprintf(paje_file, " %.9f", paje_event_timestamp(timestamp));
  if (poti_with_alias){
    fprintf(paje_file," %s", alias);
  }
  fprintf(paje_file, " %s", container);
  fprintf(paje_file, " %s", type);
  fprintf(paje_file, " \"%s\"", name);
  EXTRAFIELDS();
}

void poti_UDestroyContainer (const int unique, double timestamp, const char *type, const char *container, int extra, ...)
{
  print_event_type (unique);
  fprintf(paje_file, " %.9f", paje_event_timestamp(timestamp));
  fprintf(paje_file, " %s", type);
  fprintf(paje_file, " %s", container);
  EXTRAFIELDS();
}

void poti_USetVariable (const int unique, double timestamp, const char *container, const char *type, double value, int extra, ...)
{
  print_event_type (unique);
  fprintf(paje_file, " %.9f", paje_event_timestamp(timestamp));
  fprintf(paje_file, " %s", container);
  fprintf(paje_file, " %s", type);
  fprintf(paje_file, " %f", value);
  EXTRAFIELDS();
}

void poti_UAddVariable (const int unique, double timestamp, const char *container, const char *type, double value, int extra, ...)
{
  print_event_type (unique);
  fprintf(paje_file, " %.9f", paje_event_timestamp(timestamp));
  fprintf(paje_file, " %s", container);
  fprintf(paje_file, " %s", type);
  fprintf(paje_file, " %f", value);
  EXTRAFIELDS();
}

void poti_USubVariable (const int unique, double timestamp, const char *container, const char *type, double value, int extra, ...)
{
  print_event_type (unique);
  fprintf(paje_file, " %.9f", paje_event_timestamp(timestamp));
  fprintf(paje_file, " %s", container);
  fprintf(paje_file, " %s", type);
  fprintf(paje_file, " %f", value);
  EXTRAFIELDS();
}

void poti_USetState (const int unique, double timestamp, const char *container, const char *type, const char *value, int extra, ...)
{
  print_event_type (unique);
  fprintf(paje_file, " %.9f", paje_event_timestamp(timestamp));
  fprintf(paje_file, " %s", container);
  fprintf(paje_file, " %s", type);
  fprintf(paje_file, " %s", value);
  EXTRAFIELDS();
}

void poti_UPushState (const int unique, double timestamp, const char *container, const char *type, const char *value, int extra, ...)
{
  print_event_type (unique);
  fprintf(paje_file, " %.9f", paje_event_timestamp(timestamp));
  fprintf(paje_file, " %s", container);
  fprintf(paje_file, " %s", type);
  fprintf(paje_file, " %s", value);
  EXTRAFIELDS();
}

void poti_UPopState (const int unique, double timestamp, const char *container, const char *type, int extra, ...)
{
  print_event_type (unique);
  fprintf(paje_file, " %.9f", paje_event_timestamp(timestamp));
  fprintf(paje_file, " %s", container);
  fprintf(paje_file, " %s", type);
  EXTRAFIELDS();
}

void poti_UResetState (const int unique, double timestamp, const char *container, const char *type, int extra, ...)
{
  print_event_type (unique);
  fprintf(paje_file, " %.9f", paje_event_timestamp(timestamp));
  fprintf(paje_file, " %s", container);
  fprintf(paje_file, " %s", type);
  EXTRAFIELDS();
}

void poti_UStartLink (const int unique, double timestamp, const char *container, const char *type, const char *sourceContainer, const char *value, const char *key, int extra, ...)
{
  print_event_type (unique);
  fprintf(paje_file, " %.9f", paje_event_timestamp(timestamp));
  fprintf(paje_file, " %s", container);
  fprintf(paje_file, " %s", type);
  fprintf(paje_file, " %s", sourceContainer);
  fprintf(paje_file, " %s", value);
  fprintf(paje_file, " %s", key);
  EXTRAFIELDS();
}

void poti_UEndLink (const int unique, double timestamp, const char *container, const char *type, const char *endContainer, const char *value, const char *key, int extra, ...)
{
  print_event_type (unique);
  fprintf(paje_file, " %.9f", paje_event_timestamp(timestamp));
  fprintf(paje_file, " %s", container);
  fprintf(paje_file, " %s", type);
  fprintf(paje_file, " %s", endContainer);
  fprintf(paje_file, " %s", value);
  fprintf(paje_file, " %s", key);
  EXTRAFIELDS();
}

void poti_UNewEvent (const int unique, double timestamp, const char *container, const char *type, const char *value, int extra, ...)
{
  print_event_type (unique);
  fprintf(paje_file, " %.9f", paje_event_timestamp(timestamp));
  fprintf(paje_file, " %s", container);
  fprintf(paje_file, " %s", type);
  fprintf(paje_file, " %s", value);
  EXTRAFIELDS();
}

