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

int *identifiers = NULL;

int poti_header_DeclareEvent (int type, int num_extras, ...)
{
  /* Entry of event declaration */
  int identifier = poti_default_event_Entry (type);

  if (num_extras == 0) {
    /* Save the new identifier only if we are in default decl. (no extras) */
    identifiers[type] = identifier;
  }

  /* Default fields declaration */
  switch (type){
  case PAJE_DefineContainerType: poti_default_fields_DefineContainerType (); break;
  case PAJE_DefineVariableType:  poti_default_fields_DefineVariableType (); break;
  case PAJE_DefineStateType:     poti_default_fields_DefineStateType (); break;
  case PAJE_DefineEventType:     poti_default_fields_DefineEventType (); break;
  case PAJE_DefineLinkType:      poti_default_fields_DefineLinkType (); break;
  case PAJE_DefineEntityValue:   poti_default_fields_DefineEntityValue (); break;

  case PAJE_CreateContainer:     poti_default_fields_CreateContainer (); break;
  case PAJE_DestroyContainer:    poti_default_fields_DestroyContainer (); break;

  case PAJE_SetVariable:         poti_default_fields_SetVariable (); break;
  case PAJE_AddVariable:         poti_default_fields_AddVariable (); break;
  case PAJE_SubVariable:         poti_default_fields_SubVariable (); break;

  case PAJE_SetState:            poti_default_fields_SetState (); break;
  case PAJE_PushState:           poti_default_fields_PushState (); break;
  case PAJE_PopState:            poti_default_fields_PopState (); break;
  case PAJE_ResetState:

  case PAJE_StartLink:           poti_default_fields_StartLink (); break;
  case PAJE_EndLink:             poti_default_fields_EndLink (); break;

  case PAJE_NewEvent:            poti_default_fields_NewEvent (); break;

  default:
    fprintf(stderr, "%s: Type %d given is unknown\n", __func__, type);
    abort();
  }

  /* Extra args (user responsibility) */
  int i;
  va_list arguments;
  va_start (arguments, num_extras);
  for (i = 0; i < num_extras; i++){
    fprintf(paje_file, "%%       %s\n", va_arg (arguments, char*));
  }
  va_end (arguments);

  /* End of event declaration */
  poti_default_event_Closure ();
  return identifier;
}

/* Default event declaration order */
void poti_default_header_order()
{
  /* Put more frequent events first */
  poti_header_DeclareEvent (PAJE_PushState, 0);
  poti_header_DeclareEvent (PAJE_PopState, 0);
  poti_header_DeclareEvent (PAJE_SetState, 0);
  poti_header_DeclareEvent (PAJE_ResetState, 0);

  poti_header_DeclareEvent (PAJE_AddVariable, 0);
  poti_header_DeclareEvent (PAJE_SubVariable, 0);
  poti_header_DeclareEvent (PAJE_SetVariable, 0);

  poti_header_DeclareEvent (PAJE_StartLink, 0);
  poti_header_DeclareEvent (PAJE_EndLink, 0);
  poti_header_DeclareEvent (PAJE_NewEvent, 0);

  poti_header_DeclareEvent (PAJE_CreateContainer, 0);
  poti_header_DeclareEvent (PAJE_DestroyContainer, 0);
  
  poti_header_DeclareEvent (PAJE_DefineContainerType, 0);
  poti_header_DeclareEvent (PAJE_DefineVariableType, 0);
  poti_header_DeclareEvent (PAJE_DefineStateType, 0);
  poti_header_DeclareEvent (PAJE_DefineEventType, 0);
  poti_header_DeclareEvent (PAJE_DefineLinkType, 0);
  poti_header_DeclareEvent (PAJE_DefineEntityValue, 0);
}
