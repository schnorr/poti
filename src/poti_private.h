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
#ifndef __POTI_PRIVATE_H__
#define __POTI_PRIVATE_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <poti.h>
#include <stdbool.h>
#include <poti_config.h>

extern int *identifiers;
extern FILE *paje_file;
extern bool poti_basic_events;
extern bool poti_legacy_header;
extern bool poti_with_comments;
extern bool poti_with_alias;
extern bool poti_relative_timestamps;

double paje_event_timestamp(double timestamp);
void poti_default_header_order (void);

/* poti_header_default.c */
int poti_default_event_Entry (int type);
void poti_default_event_Closure (void);

void poti_default_fields_DefineContainerType (void);
void poti_default_fields_DefineVariableType (void);
void poti_default_fields_DefineStateType (void);
void poti_default_fields_DefineEventType (void);
void poti_default_fields_DefineLinkType (void);
void poti_default_fields_DefineEntityValue (void);
void poti_default_fields_CreateContainer (void);
void poti_default_fields_DestroyContainer (void);
void poti_default_fields_SetVariable (void);
void poti_default_fields_AddVariable (void);
void poti_default_fields_SubVariable (void);
void poti_default_fields_SetState (void);
void poti_default_fields_PushState (void);
void poti_default_fields_PopState (void);
void poti_default_fields_ResetState (void);
void poti_default_fields_StartLink (void);
void poti_default_fields_EndLink (void);
void poti_default_fields_NewEvent (void);

#endif
