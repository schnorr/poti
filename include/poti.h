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
#ifndef __POTI_H
#define __POTI_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__cplusplus)
extern "C" {
#endif

typedef enum {
  PAJE_DefineContainerType,
  PAJE_DefineVariableType,
  PAJE_DefineStateType,
  PAJE_DefineEventType,
  PAJE_DefineLinkType,
  PAJE_DefineEntityValue,
  PAJE_CreateContainer,
  PAJE_DestroyContainer,
  PAJE_SetVariable,
  PAJE_AddVariable,
  PAJE_SubVariable,
  PAJE_SetState,
  PAJE_PushState,
  PAJE_PushStateMark,
  PAJE_PopState,
  PAJE_ResetState,
  PAJE_StartLink,
  PAJE_StartLinkSize,
  PAJE_StartLinkSizeMark,
  PAJE_EndLink,
  PAJE_NewEvent,
  PAJE_FinalMarker //add new events above if necessary
} e_event_type;
  
/*
 * Function to open output into a file, else output to stdout
 */
int poti_open (const char* filename);

/*
 * Function to init poti with an external file descriptor
 */
int poti_init (FILE *file);

/*
 * Function to close opened file
 */
void poti_close (void);

/*
 * Function to generate the header 
 */
void poti_header (int basic, int old_header);

/*
 * poti_header_event: defines a new event, see examples/eventdef.c for details
 */
int poti_header_event (int type, int legacy, int alias, int num_extras, ...);

/*
 * poti_set_alias: control if aliases are used or not in events
 */
void poti_set_alias (int alias);
  
/*
 * Main API: functions to define the type hierarchy and raise events
 */
void poti_DefineContainerType (const char *alias, const char *containerType, const char *name);
void poti_DefineVariableType (const char *alias, const char *containerType, const char *name, const char *color);
void poti_DefineStateType (const char *alias, const char *containerType, const char *name);
void poti_DefineEventType (const char *alias, const char *containerType, const char *name);
void poti_DefineLinkType (const char *alias, const char *containerType, const char *startContainerType, const char *endContainerType, const char *name);
void poti_DefineEntityValue (const char *alias, const char *entityType, const char *name, const char *color);
void poti_CreateContainer (double timestamp, const char *alias, const char *type, const char *container, const char *name);
void poti_DestroyContainer (double timestamp, const char *type, const char *container);
void poti_SetVariable (double timestamp, const char *container, const char *type, double value);
void poti_AddVariable (double timestamp, const char *container, const char *type, double value);
void poti_SubVariable (double timestamp, const char *container, const char *type, double value);
void poti_SetState (double timestamp, const char *container, const char *type, const char *value);
void poti_PushState (double timestamp, const char *container, const char *type, const char *value);
void poti_PopState (double timestamp, const char *container, const char *type);
void poti_ResetState (double timestamp, const char *container, const char *type);
void poti_StartLink (double timestamp, const char *container, const char *type, const char *sourceContainer, const char *value, const char *key);
void poti_EndLink (double timestamp, const char *container, const char *type, const char *endContainer, const char *value, const char *key);
void poti_NewEvent (double timestamp, const char *container, const char *type, const char *value);

/*
 * Main API with unique identifiers exposed and optional extra fields: functions to define the type hierarchy and raise events
 */
void poti_UDefineContainerType (const int unique, const char *alias, const char *containerType, const char *name, int extra, ...);
void poti_UDefineVariableType (const int unique, const char *alias, const char *containerType, const char *name, const char *color, int extra, ...);
void poti_UDefineStateType (const int unique, const char *alias, const char *containerType, const char *name, int extra, ...);
void poti_UDefineEventType (const int unique, const char *alias, const char *containerType, const char *name, int extra, ...);
void poti_UDefineLinkType (const int unique, const char *alias, const char *containerType, const char *startContainerType, const char *endContainerType, const char *name, int extra, ...);
void poti_UDefineEntityValue (const int unique, const char *alias, const char *entityType, const char *name, const char *color, int extra, ...);
void poti_UCreateContainer (const int unique, double timestamp, const char *alias, const char *type, const char *container, const char *name, int extra, ...);
void poti_UDestroyContainer (const int unique, double timestamp, const char *type, const char *container, int extra, ...);
void poti_USetVariable (const int unique, double timestamp, const char *container, const char *type, double value, int extra, ...);
void poti_UAddVariable (const int unique, double timestamp, const char *container, const char *type, double value, int extra, ...);
void poti_USubVariable (const int unique, double timestamp, const char *container, const char *type, double value, int extra, ...);
void poti_USetState (const int unique, double timestamp, const char *container, const char *type, const char *value, int extra, ...);
void poti_UPushState (const int unique, double timestamp, const char *container, const char *type, const char *value, int extra, ...);
void poti_UPopState (const int unique, double timestamp, const char *container, const char *type, int extra, ...);
void poti_UResetState (const int unique, double timestamp, const char *container, const char *type, int extra, ...);
void poti_UStartLink (const int unique, double timestamp, const char *container, const char *type, const char *sourceContainer, const char *value, const char *key, int extra, ...);
void poti_UEndLink (const int unique, double timestamp, const char *container, const char *type, const char *endContainer, const char *value, const char *key, int extra, ...);
void poti_UNewEvent (const int unique, double timestamp, const char *container, const char *type, const char *value, int extra, ...);
  
/*
 * Unalised API: without alias parameters
 */
void poti_DContainerType (const char *containerType, const char *name);
void poti_DVariableType  (const char *containerType, const char *name, const char *color);
void poti_DStateType     (const char *containerType, const char *name);
void poti_DEventType     (const char *containerType, const char *name);
void poti_DLinkType      (const char *containerType, const char *startContainerType, const char *endContainerType, const char *name);
void poti_DEntityValue   (const char *entityType, const char *name, const char *color);
void poti_ECreateContainer   (double timestamp, const char *type, const char *container, const char *name);
void poti_EDestroyContainer  (double timestamp, const char *type, const char *container);
void poti_ESetVariable   (double timestamp, const char *container, const char *type, double value);
void poti_EAddVariable   (double timestamp, const char *container, const char *type, double value);
void poti_ESubVariable   (double timestamp, const char *container, const char *type, double value);
void poti_ESetState      (double timestamp, const char *container, const char *type, const char *value);
void poti_EPushState     (double timestamp, const char *container, const char *type, const char *value);
void poti_EPopState      (double timestamp, const char *container, const char *type);
void poti_EResetState    (double timestamp, const char *container, const char *type);
void poti_EStartLink     (double timestamp, const char *container, const char *type, const char *sourceContainer, const char *value, const char *key);
void poti_EEndLink       (double timestamp, const char *container, const char *type, const char *endContainer, const char *value, const char *key);

  
#if defined(__cplusplus)
}
#endif

#endif
