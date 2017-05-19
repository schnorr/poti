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

/*
 * Event names: these are the ones supported by Paje
 */
static char const *PajeEventNames[] = {
  "PajeDefineContainerType",
  "PajeDefineVariableType",
  "PajeDefineStateType",
  "PajeDefineEventType",
  "PajeDefineLinkType",
  "PajeDefineEntityValue",
  "PajeCreateContainer",
  "PajeDestroyContainer",
  "PajeSetVariable",
  "PajeAddVariable",
  "PajeSubVariable",
  "PajeSetState",
  "PajePushState",
  "PajePopState",
  "PajeResetState",
  "PajeStartLink",
  "PajeEndLink",
  "PajeNewEvent",
};

/*
 * Event (entry and closure)
 */
int poti_default_event_Entry (int type)
{
  static int identifier_generator = 0;
  fprintf(paje_file, "%%EventDef %s %d\n", PajeEventNames[type], identifier_generator);
  return identifier_generator++;
}

void poti_default_event_Closure (void)
{
  fprintf(paje_file, "%%EndEventDef\n");
}

/*
 * Type
 */

void poti_default_fields_DefineContainerType (void)
{
  if (poti_with_alias){
    fprintf(paje_file, "%%       Alias string\n");
  }
  fprintf(paje_file, "%%       Type string\n");
  fprintf(paje_file, "%%       Name string\n");
}

void poti_default_fields_DefineVariableType (void)
{
  if (poti_with_alias){
    fprintf(paje_file, "%%       Alias string\n");
  }
  fprintf(paje_file, "%%       Type string\n");
  fprintf(paje_file, "%%       Name string\n");
  fprintf(paje_file, "%%       Color color\n");

}

void poti_default_fields_DefineStateType (void)
{
  poti_default_fields_DefineContainerType();
}

void poti_default_fields_DefineEventType (void)
{
  poti_default_fields_DefineContainerType();
}

void poti_default_fields_DefineLinkType (void)
{
  if (poti_with_alias){
    fprintf(paje_file, "%%       Alias string\n");
  }
  fprintf(paje_file, "%%       Type string\n");
  fprintf(paje_file, "%%       StartContainerType string\n");
  fprintf(paje_file, "%%       EndContainerType string\n");
  fprintf(paje_file, "%%       Name string\n");

}

void poti_default_fields_DefineEntityValue (void)
{
  poti_default_fields_DefineVariableType();
}

/*
 * Container
 */

void poti_default_fields_CreateContainer (void)
{
  fprintf(paje_file, "%%       Time date\n");
  if(poti_with_alias){
    fprintf(paje_file, "%%       Alias string\n");
  }
  fprintf(paje_file, "%%       Container string\n");
  fprintf(paje_file, "%%       Type string\n");
  fprintf(paje_file, "%%       Name string\n");
}

void poti_default_fields_DestroyContainer (void)
{
  fprintf(paje_file, "%%       Time date\n");
  fprintf(paje_file, "%%       Type string\n");
  fprintf(paje_file, "%%       Name string\n");
}

/*
 * Variable
 */

void poti_default_fields_SetVariable (void)
{
  fprintf(paje_file, "%%       Time date\n");
  fprintf(paje_file, "%%       Container string\n");
  fprintf(paje_file, "%%       Type string\n");
  fprintf(paje_file, "%%       Value double\n");
}

void poti_default_fields_AddVariable (void)
{
  poti_default_fields_SetVariable();
}

void poti_default_fields_SubVariable (void)
{
  poti_default_fields_SetVariable();
}

/*
 * State
 */

void poti_default_fields_SetState (void)
{
  fprintf(paje_file, "%%       Time date\n");
  fprintf(paje_file, "%%       Container string\n");
  fprintf(paje_file, "%%       Type string\n");
  fprintf(paje_file, "%%       Value string\n");
}

void poti_default_fields_PushState (void)
{
  poti_default_fields_SetState();
}

void poti_default_fields_PopState (void)
{
  fprintf(paje_file, "%%       Time date\n");
  fprintf(paje_file, "%%       Container string\n");
  fprintf(paje_file, "%%       Type string\n");
}

void poti_default_fields_ResetState (void)
{
  poti_default_fields_SetState();
}

/*
 * Link
 */

void poti_default_fields_StartLink (void)
{
  fprintf(paje_file, "%%       Time date\n");
  fprintf(paje_file, "%%       Container string\n");
  fprintf(paje_file, "%%       Type string\n");
  fprintf(paje_file, "%%       StartContainer string\n");
  fprintf(paje_file, "%%       Value string\n");
  fprintf(paje_file, "%%       Key string\n");
}

void poti_default_fields_EndLink (void)
{
  fprintf(paje_file, "%%       Time date\n");
  fprintf(paje_file, "%%       Container string\n");
  fprintf(paje_file, "%%       Type string\n");
  fprintf(paje_file, "%%       EndContainer string\n");
  fprintf(paje_file, "%%       Value string\n");
  fprintf(paje_file, "%%       Key string\n");
}

/*
 * Event
 */

void poti_default_fields_NewEvent (void)
{
  fprintf(paje_file, "%%       Time date\n");
  fprintf(paje_file, "%%       Container string\n");
  fprintf(paje_file, "%%       Type string\n");
  fprintf(paje_file, "%%       Value double\n");
}
