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

static int poti_event_def_start (int type)
{
  static int type_generator = 0;
  fprintf(paje_file, "%%EventDef %s %d\n", PajeEventNames[type], type_generator);
  return type_generator++;
}

static void poti_event_def_end ()
{
  fprintf(paje_file, "%%EndEventDef\n");
  return;
}

static void poti_h_YYY_set_push_state (void)
{
  fprintf(paje_file, "%%       Time date\n");
  fprintf(paje_file, "%%       Container string\n");
  fprintf(paje_file, "%%       Type string\n");
  fprintf(paje_file, "%%       Value string\n");
}

static void poti_h_YYY_pop_reset_state (void)
{
  fprintf(paje_file, "%%       Time date\n");
  fprintf(paje_file, "%%       Container string\n");
  fprintf(paje_file, "%%       Type string\n");
}

static void poti_h_YYY_variable (void)
{
  fprintf(paje_file, "%%       Time date\n");
  fprintf(paje_file, "%%       Container string\n");
  fprintf(paje_file, "%%       Type string\n");
  fprintf(paje_file, "%%       Value double\n");
}

static void poti_h_YYY_create_container (void)
{
  fprintf(paje_file, "%%       Time date\n");
  if(poti_with_alias){
    fprintf(paje_file, "%%       Alias string\n");
  }
  fprintf(paje_file, "%%       Container string\n");
  fprintf(paje_file, "%%       Type string\n");
  fprintf(paje_file, "%%       Name string\n");
}

static void poti_h_YYY_destroy_container (void)
{
  fprintf(paje_file, "%%       Time date\n");
  fprintf(paje_file, "%%       Type string\n");
  fprintf(paje_file, "%%       Name string\n");
}

static void poti_h_YYY_link (bool start)
{
  const char *kind_str;
  if (start){
    if (poti_legacy_header){
      kind_str = "SourceContainer";
    }else{
      kind_str = "StartContainer";
    }
  }else{
    if (poti_legacy_header){
      kind_str = "DestContainer";
    }else{
      kind_str = "EndContainer";
    }
  }

  fprintf(paje_file, "%%       Time date\n");
  fprintf(paje_file, "%%       Container string\n");
  fprintf(paje_file, "%%       Type string\n");
  fprintf(paje_file, "%%       %s string\n", kind_str);
  fprintf(paje_file, "%%       Value string\n");
  fprintf(paje_file, "%%       Key string\n");
}



static void poti_h_YYY_def_container_type (void)
{
  if (poti_with_alias){
    fprintf(paje_file, "%%       Alias string\n");
  }
  if (poti_legacy_header){
    fprintf(paje_file, "%%       ContainerType string\n");
  }else{
    fprintf(paje_file, "%%       Type string\n");
  }
  fprintf(paje_file, "%%       Name string\n");
}

static void poti_h_YYY_def_variable_type (void)
{
  if (poti_with_alias){
    fprintf(paje_file, "%%       Alias string\n");
  }
  if (poti_legacy_header){
    fprintf(paje_file, "%%       ContainerType string\n");
  }else{
    fprintf(paje_file, "%%       Type string\n");
  }
  fprintf(paje_file, "%%       Name string\n");
  fprintf(paje_file, "%%       Color color\n");
}

static void poti_h_YYY_def_state_event_type (void)
{
  if (poti_with_alias){
    fprintf(paje_file, "%%       Alias string\n");
  }
  if (poti_legacy_header){
    fprintf(paje_file, "%%       ContainerType string\n");
  }else{
    fprintf(paje_file, "%%       Type string\n");
  }
  fprintf(paje_file, "%%       Name string\n");
}

static void poti_h_YYY_def_link_type (void)
{
  if (poti_with_alias){
    fprintf(paje_file, "%%       Alias string\n");
  }
  if (poti_legacy_header){
    fprintf(paje_file, "%%       ContainerType string\n");
    fprintf(paje_file, "%%       SourceContainerType string\n");
    fprintf(paje_file, "%%       DestContainerType string\n");
  }else{
    fprintf(paje_file, "%%       Type string\n");
    fprintf(paje_file, "%%       StartContainerType string\n");
    fprintf(paje_file, "%%       EndContainerType string\n");
  }
  fprintf(paje_file, "%%       Name string\n");
}

static void poti_h_YYY_def_entity_value (void)
{
  if (poti_with_alias){
    fprintf(paje_file, "%%       Alias string\n");
  }
  if (poti_legacy_header){
    fprintf(paje_file, "%%       EntityType string\n");
  }else{
    fprintf(paje_file, "%%       Type string\n");
  }
  fprintf(paje_file, "%%       Name string\n");
  fprintf(paje_file, "%%       Color color\n");
}

int poti_header_event (int type, int num_extras, ...)
{
  /* Start of event definition */
  int identifier = poti_event_def_start (type);

  /* Save the new identifier, mapping to the type of event*/
  identifiers[type] = identifier;

  /* Required args */
  switch (type){
  case PAJE_DefineContainerType: poti_h_YYY_def_container_type (); break;
  case PAJE_DefineVariableType:  poti_h_YYY_def_variable_type (); break;
  case PAJE_DefineStateType:
  case PAJE_DefineEventType:     poti_h_YYY_def_state_event_type (); break;
  case PAJE_DefineLinkType:      poti_h_YYY_def_link_type (); break;
  case PAJE_DefineEntityValue:   poti_h_YYY_def_entity_value (); break;

  case PAJE_CreateContainer: poti_h_YYY_create_container (); break;
  case PAJE_DestroyContainer: poti_h_YYY_destroy_container (); break;

  case PAJE_NewEvent: //event fields are the same as variable
  case PAJE_SetVariable:
  case PAJE_AddVariable:
  case PAJE_SubVariable: poti_h_YYY_variable (); break;

  case PAJE_SetState:
  case PAJE_PushState: poti_h_YYY_set_push_state (); break;

  case PAJE_PopState:
  case PAJE_ResetState: poti_h_YYY_pop_reset_state (); break;

  case PAJE_StartLink: poti_h_YYY_link (true); break;
  case PAJE_EndLink:   poti_h_YYY_link (false); break;

  default: break;
  }

  /* Extra args (user responsibility) */
  int i;
  va_list arguments;
  va_start (arguments, num_extras);
  for (i = 0; i < num_extras; i++){
    fprintf(paje_file, "%%       %s\n", va_arg (arguments, char*));
  }
  va_end (arguments);

  /* End of event definition */
  poti_event_def_end ();
  return identifier;
}

static void _declare_default_event (int type)
{
  poti_header_event (type, 0);
}

/* entry point */
void _poti_header()
{
  _declare_default_event (PAJE_DefineContainerType);
  _declare_default_event (PAJE_DefineVariableType);
  _declare_default_event (PAJE_DefineStateType);
  _declare_default_event (PAJE_DefineEventType);
  _declare_default_event (PAJE_DefineLinkType);
  _declare_default_event (PAJE_DefineEntityValue);
  _declare_default_event (PAJE_CreateContainer);
  _declare_default_event (PAJE_DestroyContainer);
  _declare_default_event (PAJE_SetVariable);
  _declare_default_event (PAJE_AddVariable);
  _declare_default_event (PAJE_SubVariable);
  _declare_default_event (PAJE_SetState);
  _declare_default_event (PAJE_PushState);
  _declare_default_event (PAJE_PopState);
  _declare_default_event (PAJE_ResetState);
  _declare_default_event (PAJE_StartLink);
  _declare_default_event (PAJE_EndLink);
  _declare_default_event (PAJE_NewEvent);

  if (poti_basic_events){
    if (poti_with_comments){
      fprintf (paje_file,
               "#\n"
               "# Trace created without extended events\n"
               "#\n");
    }
    return;
  }
}
