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

void poti_DContainerType (const char *containerType, const char *name)
{
  poti_DefineContainerType (NULL, containerType, name);
}

void poti_DVariableType  (const char *containerType, const char *name, const char *color)
{
  poti_DefineVariableType (NULL, containerType, name, color);
}

void poti_DStateType     (const char *containerType, const char *name)
{
  poti_DefineStateType (NULL, containerType, name);
}

void poti_DEventType     (const char *containerType, const char *name)
{
  poti_DefineEventType (NULL, containerType, name);
}

void poti_DLinkType      (const char *containerType, const char *startContainerType, const char *endContainerType, const char *name)
{
  poti_DefineLinkType (NULL, containerType, startContainerType, endContainerType, name);
}

void poti_DEntityValue   (const char *entityType, const char *name, const char *color);
{
  poti_DefineEntityValue (NULL, entityType, name, color);
}

void poti_ECreateContainer    (double timestamp, const char *type, const char *container, const char *name)
{
  poti_CreateContainer (timestamp, NULL, type, container, name);
}

void poti_EDestroyContainer  (double timestamp, const char *type, const char *container)
{
  poti_DestroyContainer (timestamp, type, container);
}

void poti_ESetVariable   (double timestamp, const char *container, const char *type, double value)
{
  poti_SetVariable (timestamp, container, type, value);
}

void poti_EAddVariable   (double timestamp, const char *container, const char *type, double value)
{
  poti_AddVariable (timestamp, container, type, value);
}

void poti_ESubVariable   (double timestamp, const char *container, const char *type, double value)
{
  poti_SubVariable (timestamp, container, type, value);
}

void poti_ESetState      (double timestamp, const char *container, const char *type, const char *value)
{
  poti_SetState (timestamp, container, type, value);
}

void poti_EPushState     (double timestamp, const char *container, const char *type, const char *value)
{
  poti_PushState (timestamp, container, type, value);
}

void poti_EPopState      (double timestamp, const char *container, const char *type)
{
  poti_PopState (timestamp, container, type, value);
}

void poti_EResetState    (double timestamp, const char *container, const char *type)
{
  poti_ResetState (timestamp, container, type, value);
}

void poti_EStartLink     (double timestamp, const char *container, const char *type, const char *sourceContainer, const char *value, const char *key)
{
  poti_StartLink (timestamp, container, type, sourceContainer, value, key);
}

void poti_EEndLink       (double timestamp, const char *container, const char *type, const char *endContainer, const char *value, const char *key)
{
  poti_EndLink (timestamp, container, type, endContainer, value, key);
}
  

