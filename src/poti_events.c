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

double paje_event_timestamp(double timestamp)
{
  static double first_timestamp = -1;
  if (first_timestamp == -1) {
    first_timestamp = timestamp;
  }
  return timestamp - first_timestamp;
}

void poti_DefineContainerType (const char *alias, const char *containerType, const char *name)
{
  fprintf(paje_file, "%d", identifiers[PAJE_DefineContainerType]);
  if (poti_alias){
    fprintf(paje_file," %s", alias);
  }
  fprintf(paje_file, " %s", containerType);
  fprintf(paje_file, " \"%s\"\n", name);
}

void poti_DefineVariableType (const char *alias, const char *containerType, const char *name, const char *color)
{
  fprintf(paje_file, "%d", identifiers[PAJE_DefineVariableType]);
  if (poti_alias){
    fprintf(paje_file," %s", alias);
  }
  fprintf(paje_file, " %s", containerType);
  fprintf(paje_file, " \"%s\"", name);
  fprintf(paje_file, " \"%s\"\n", color);
}

void poti_DefineStateType (const char *alias, const char *containerType, const char *name)
{
  fprintf(paje_file, "%d", identifiers[PAJE_DefineStateType]);
  if (poti_alias){
    fprintf(paje_file," %s", alias);
  }
  fprintf(paje_file, " %s", containerType);
  fprintf(paje_file, " \"%s\"\n", name);
}

void poti_DefineEventType (const char *alias, const char *containerType, const char *name)
{
  fprintf(paje_file, "%d", identifiers[PAJE_DefineEventType]);
  if (poti_alias){
    fprintf(paje_file," %s", alias);
  }
  fprintf(paje_file, " %s", containerType);
  fprintf(paje_file, " \"%s\"\n", name);
}

void poti_DefineLinkType (const char *alias, const char *containerType, const char *startContainerType, const char *endContainerType, const char *name)
{
  fprintf(paje_file, "%d", identifiers[PAJE_DefineLinkType]);
  if (poti_alias){
    fprintf(paje_file," %s", alias);
  }
  fprintf(paje_file, " %s", containerType);
  fprintf(paje_file, " %s", startContainerType);
  fprintf(paje_file, " %s", endContainerType);
  fprintf(paje_file, " \"%s\"\n", name);
}

void poti_DefineEntityValue (const char *alias, const char *entityType, const char *name, const char *color)
{
  fprintf(paje_file, "%d", identifiers[PAJE_DefineEntityValue]);
  if (poti_alias){
    fprintf(paje_file," %s", alias);
  }
  fprintf(paje_file, " %s", entityType);
  fprintf(paje_file, " %s", name);
  fprintf(paje_file, " \"%s\"\n", color);
}

void poti_CreateContainer (double timestamp, const char *alias, const char *type, const char *container, const char *name)
{
  fprintf(paje_file, "%d", identifiers[PAJE_CreateContainer]);
  fprintf(paje_file, " %.9f", paje_event_timestamp(timestamp));
  if (poti_alias){
    fprintf(paje_file," %s", alias);
  }
  fprintf(paje_file, " %s", container);
  fprintf(paje_file, " %s", type);
  fprintf(paje_file, " \"%s\"\n", name);
}

void poti_DestroyContainer (double timestamp, const char *type, const char *container)
{
  fprintf(paje_file, "%d", identifiers[PAJE_DestroyContainer]);
  fprintf(paje_file, " %.9f", paje_event_timestamp(timestamp));
  fprintf(paje_file, " %s", type);
  fprintf(paje_file, " %s\n", container);
}

void poti_SetVariable (double timestamp, const char *container, const char *type, double value)
{
  fprintf(paje_file, "%d", identifiers[PAJE_SetVariable]);
  fprintf(paje_file, " %.9f", paje_event_timestamp(timestamp));
  fprintf(paje_file, " %s", container);
  fprintf(paje_file, " %s", type);
  fprintf(paje_file, " %f\n", value);
}

void poti_AddVariable (double timestamp, const char *container, const char *type, double value)
{
  fprintf(paje_file, "%d", identifiers[PAJE_AddVariable]);
  fprintf(paje_file, " %.9f", paje_event_timestamp(timestamp));
  fprintf(paje_file, " %s", container);
  fprintf(paje_file, " %s", type);
  fprintf(paje_file, " %f\n", value);
}

void poti_SubVariable (double timestamp, const char *container, const char *type, double value)
{
  fprintf(paje_file, "%d", identifiers[PAJE_SubVariable]);
  fprintf(paje_file, " %.9f", paje_event_timestamp(timestamp));
  fprintf(paje_file, " %s", container);
  fprintf(paje_file, " %s", type);
  fprintf(paje_file, " %f\n", value);
}

void poti_SetState (double timestamp, const char *container, const char *type, const char *value)
{
  fprintf(paje_file, "%d", identifiers[PAJE_SetState]);
  fprintf(paje_file, " %.9f", paje_event_timestamp(timestamp));
  fprintf(paje_file, " %s", container);
  fprintf(paje_file, " %s", type);
  fprintf(paje_file, " %s\n", value);
}

void poti_PushState (double timestamp, const char *container, const char *type, const char *value)
{
  fprintf(paje_file, "%d", identifiers[PAJE_PushState]);
  fprintf(paje_file, " %.9f", paje_event_timestamp(timestamp));
  fprintf(paje_file, " %s", container);
  fprintf(paje_file, " %s", type);
  fprintf(paje_file, " %s\n", value);
}

void poti_PushStateMark (double timestamp, const char *container, const char *type, const char *value, const int mark)
{
  if (paje_extended){
    fprintf(paje_file, "%d", identifiers[PAJE_PushStateMark]);
    fprintf(paje_file, " %.9f", paje_event_timestamp(timestamp));
    fprintf(paje_file, " %s", container);
    fprintf(paje_file, " %s", type);
    fprintf(paje_file, " %s", value);
    fprintf(paje_file, " %d\n", mark);
  }else{
    poti_PushState (timestamp, container, type, value);
  }
}

void poti_PopState (double timestamp, const char *container, const char *type)
{
  fprintf(paje_file, "%d", identifiers[PAJE_PopState]);
  fprintf(paje_file, " %.9f", paje_event_timestamp(timestamp));
  fprintf(paje_file, " %s", container);
  fprintf(paje_file, " %s\n", type);
}

void poti_ResetState (double timestamp, const char *container, const char *type)
{
  fprintf(paje_file, "%d", identifiers[PAJE_ResetState]);
  fprintf(paje_file, " %.9f", paje_event_timestamp(timestamp));
  fprintf(paje_file, " %s", container);
  fprintf(paje_file, " %s\n", type);
}

void poti_StartLink (double timestamp, const char *container, const char *type, const char *sourceContainer, const char *value, const char *key)
{
  fprintf(paje_file, "%d", identifiers[PAJE_StartLink]);
  fprintf(paje_file, " %.9f", paje_event_timestamp(timestamp));
  fprintf(paje_file, " %s", container);
  fprintf(paje_file, " %s", type);
  fprintf(paje_file, " %s", sourceContainer);
  fprintf(paje_file, " %s", value);
  fprintf(paje_file, " %s\n", key);
}

void poti_StartLinkSize (double timestamp, const char *container, const char *type, const char *sourceContainer, const char *value, const char *key, const int size)
{
  if (paje_extended){
    fprintf(paje_file, "%d", identifiers[PAJE_StartLinkSize]);
    fprintf(paje_file, " %.9f", paje_event_timestamp(timestamp));
    fprintf(paje_file, " %s", container);
    fprintf(paje_file, " %s", type);
    fprintf(paje_file, " %s", sourceContainer);
    fprintf(paje_file, " %s", value);
    fprintf(paje_file, " %s", key);
    fprintf(paje_file, " %d\n", size);
  }else{
    poti_StartLink (timestamp, container, type, sourceContainer, value, key);
  }
}

void poti_StartLinkSizeMark (double timestamp, const char *container, const char *type, const char *sourceContainer, const char *value, const char *key, const int size, const int mark)
{
  if (paje_extended){
    fprintf(paje_file, "%d", identifiers[PAJE_StartLinkSizeMark]);
    fprintf(paje_file, " %.9f", paje_event_timestamp(timestamp));
    fprintf(paje_file, " %s", container);
    fprintf(paje_file, " %s", type);
    fprintf(paje_file, " %s", sourceContainer);
    fprintf(paje_file, " %s", value);
    fprintf(paje_file, " %s", key);
    fprintf(paje_file, " %d", size);
    fprintf(paje_file, " %d\n", mark);
  }else{
    poti_StartLink (timestamp, container, type, sourceContainer, value, key);
  }
}

void poti_EndLink (double timestamp, const char *container, const char *type, const char *endContainer, const char *value, const char *key)
{
  fprintf(paje_file, "%d", identifiers[PAJE_EndLink]);
  fprintf(paje_file, " %.9f", paje_event_timestamp(timestamp));
  fprintf(paje_file, " %s", container);
  fprintf(paje_file, " %s", type);
  fprintf(paje_file, " %s", endContainer);
  fprintf(paje_file, " %s", value);
  fprintf(paje_file, " %s\n", key);
}

void poti_NewEvent (double timestamp, const char *container, const char *type, const char *value)
{
  fprintf(paje_file, "%d", identifiers[PAJE_NewEvent]);
  fprintf(paje_file, " %.9f", paje_event_timestamp(timestamp));
  fprintf(paje_file, " %s", container);
  fprintf(paje_file, " %s", type);
  fprintf(paje_file, " %s\n", value);
}

