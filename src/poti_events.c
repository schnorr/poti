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
  if (!poti_relative_timestamps) {
    return timestamp;
  }
  if (first_timestamp == -1) {
    first_timestamp = timestamp;
  }
  return timestamp - first_timestamp;
}

void poti_DefineContainerType (const char *alias, const char *containerType, const char *name)
{
  poti_user_DefineContainerType (identifiers[PAJE_DefineContainerType], alias, containerType, name, 0);
}

void poti_DefineVariableType (const char *alias, const char *containerType, const char *name, const char *color)
{
  poti_user_DefineVariableType (identifiers[PAJE_DefineVariableType], alias, containerType, name, color, 0);
}

void poti_DefineStateType (const char *alias, const char *containerType, const char *name)
{
  poti_user_DefineStateType (identifiers[PAJE_DefineStateType], alias, containerType, name, 0);
}

void poti_DefineEventType (const char *alias, const char *containerType, const char *name)
{
  poti_user_DefineEventType (identifiers[PAJE_DefineEventType], alias, containerType, name, 0);
}

void poti_DefineLinkType (const char *alias, const char *containerType, const char *startContainerType, const char *endContainerType, const char *name)
{
  poti_user_DefineLinkType (identifiers[PAJE_DefineLinkType], alias, containerType, startContainerType, endContainerType, name, 0);
}

void poti_DefineEntityValue (const char *alias, const char *entityType, const char *name, const char *color)
{
  poti_user_DefineEntityValue (identifiers[PAJE_DefineEntityValue], alias, entityType, name, color, 0);
}

void poti_CreateContainer (double timestamp, const char *alias, const char *type, const char *container, const char *name)
{
  poti_user_CreateContainer (identifiers[PAJE_CreateContainer], timestamp, alias, type, container, name, 0);
}

void poti_DestroyContainer (double timestamp, const char *type, const char *container)
{
  poti_user_DestroyContainer (identifiers[PAJE_DestroyContainer], timestamp, type, container, 0);
}

void poti_SetVariable (double timestamp, const char *container, const char *type, double value)
{
  poti_user_SetVariable (identifiers[PAJE_SetVariable], timestamp, container, type, value, 0);
}

void poti_AddVariable (double timestamp, const char *container, const char *type, double value)
{
  poti_user_AddVariable (identifiers[PAJE_AddVariable], timestamp, container, type, value, 0);
}

void poti_SubVariable (double timestamp, const char *container, const char *type, double value)
{
  poti_user_SubVariable (identifiers[PAJE_SubVariable], timestamp, container, type, value, 0);
}

void poti_SetState (double timestamp, const char *container, const char *type, const char *value)
{
  poti_user_SetState (identifiers[PAJE_SetState], timestamp, container, type, value, 0);
}

void poti_PushState (double timestamp, const char *container, const char *type, const char *value)
{
  poti_user_PushState (identifiers[PAJE_PushState], timestamp, container, type, value, 0);
}

void poti_PopState (double timestamp, const char *container, const char *type)
{
  poti_user_PopState (identifiers[PAJE_PopState], timestamp, container, type, 0);
}

void poti_ResetState (double timestamp, const char *container, const char *type)
{
  poti_user_ResetState (identifiers[PAJE_ResetState], timestamp, container, type, 0);
}

void poti_StartLink (double timestamp, const char *container, const char *type, const char *sourceContainer, const char *value, const char *key)
{
  poti_user_StartLink (identifiers[PAJE_StartLink], timestamp, container, type, sourceContainer, value, key, 0);
}

void poti_EndLink (double timestamp, const char *container, const char *type, const char *endContainer, const char *value, const char *key)
{
  poti_user_EndLink (identifiers[PAJE_EndLink], timestamp, container, type, endContainer, value, key, 0);
}

void poti_NewEvent (double timestamp, const char *container, const char *type, const char *value)
{
  poti_user_NewEvent (identifiers[PAJE_NewEvent], timestamp, container, type, value, 0);
}
