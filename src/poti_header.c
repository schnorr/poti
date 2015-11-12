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
int disable_comments = 0;

static char const *X[] = {
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
  "PajePushState",
  "PajePopState",
  "PajeResetState",
  "PajeStartLink",
  "PajeStartLink",
  "PajeStartLink",
  "PajeEndLink",
  "PajeNewEvent",
};

extern FILE *paje_file;
extern int paje_extended;

static int poti_event_def_start (int type)
{
  static int type_generator = 0;
  fprintf(paje_file, "%%EventDef %s %d\n", X[type], type_generator);
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

static void poti_h_YYY_create_container (bool alias)
{
  fprintf(paje_file, "%%       Time date\n");
  if(alias){
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
  
static void poti_h_YYY_link (bool legacy, bool start)
{
  const char *kind_str;
  if (start){
    if (legacy){
      kind_str = "SourceContainer";
    }else{
      kind_str = "StartContainer";
    }
  }else{
    if (legacy){
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



static void poti_h_YYY_def_container_type (bool legacy, bool alias)
{
  if (alias){
    fprintf(paje_file, "%%       Alias string\n");
  }
  if (legacy){
    fprintf(paje_file, "%%       ContainerType string\n");
  }else{
    fprintf(paje_file, "%%       Type string\n");
  }
  fprintf(paje_file, "%%       Name string\n");
}

static void poti_h_YYY_def_variable_type (bool legacy, bool alias)
{
  if (alias){
    fprintf(paje_file, "%%       Alias string\n");
  }
  if (legacy){
    fprintf(paje_file, "%%       ContainerType string\n");
  }else{
    fprintf(paje_file, "%%       Type string\n");
  }
  fprintf(paje_file, "%%       Name string\n");
  fprintf(paje_file, "%%       Color color\n");
}

static void poti_h_YYY_def_state_event_type (bool legacy, bool alias)
{
  if (alias){
    fprintf(paje_file, "%%       Alias string\n");
  }
  if (legacy){
    fprintf(paje_file, "%%       ContainerType string\n");
  }else{
    fprintf(paje_file, "%%       Type string\n");
  }
  fprintf(paje_file, "%%       Name string\n");
}

static void poti_h_YYY_def_link_type (bool legacy, bool alias)
{
  if (alias){
    fprintf(paje_file, "%%       Alias string\n");
  }
  if (legacy){
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

static void poti_h_YYY_def_entity_value (bool legacy, bool alias)
{
  if (alias){
    fprintf(paje_file, "%%       Alias string\n");
  }
  if (legacy){
    fprintf(paje_file, "%%       EntityType string\n");
  }else{
    fprintf(paje_file, "%%       Type string\n");
  }
  fprintf(paje_file, "%%       Name string\n");
  fprintf(paje_file, "%%       Color color\n");
}

int poti_header_event (int type, bool legacy, bool alias, int num_extras, ...)
{
  /* Start of event definition */
  int identifier = poti_event_def_start (type);
  identifiers[type] = identifier;
  
  /* Required args */
  switch (type){
  case PAJE_DefineContainerType: poti_h_YYY_def_container_type (legacy, alias); break;
  case PAJE_DefineVariableType:  poti_h_YYY_def_variable_type (legacy, alias); break;
  case PAJE_DefineStateType:  
  case PAJE_DefineEventType:     poti_h_YYY_def_state_event_type (legacy, alias); break;
  case PAJE_DefineLinkType:      poti_h_YYY_def_link_type (legacy, alias); break;
  case PAJE_DefineEntityValue:
  
  case PAJE_CreateContainer: poti_h_YYY_create_container (alias); break;
  case PAJE_DestroyContainer: poti_h_YYY_destroy_container (); break;

  case PAJE_NewEvent: //event fields are the same as variable
  case PAJE_SetVariable: 
  case PAJE_AddVariable: 
  case PAJE_SubVariable: poti_h_YYY_variable (); break;
    
  case PAJE_SetState:  
  case PAJE_PushState: poti_h_YYY_set_push_state (); break;
  
  case PAJE_PopState:   
  case PAJE_ResetState: poti_h_YYY_pop_reset_state (); break;
  
  case PAJE_StartLink: poti_h_YYY_link (legacy, POTI_TRUE); break;
  case PAJE_EndLink:   poti_h_YYY_link (legacy, POTI_FALSE); break;

  //events with extra fields, should be removed
  case PAJE_PushStateMark: poti_h_YYY_set_push_state (); break;
  case PAJE_StartLinkSize: 
  case PAJE_StartLinkSizeMark: poti_h_YYY_link (legacy, POTI_TRUE); break;
    
  default: break;
  }

  /* Extra args (user responsibility) */
  va_list arguments;
  va_start (arguments, num_extras);
  for (int i = 0; i < num_extras; i++){
    fprintf(paje_file, "%%       %s\n", va_arg (arguments, char*));
  }
  va_end (arguments);

  /* End of event definition */
  poti_event_def_end ();
  return identifier;
}

/* entry point */
void _poti_header(int basic, int old_header)
{
  poti_header_event (PAJE_DefineContainerType, old_header, poti_alias, 0);
  poti_header_event (PAJE_DefineVariableType, old_header, poti_alias, 0);
  poti_header_event (PAJE_DefineStateType, old_header, poti_alias, 0);
  poti_header_event (PAJE_DefineEventType, old_header, poti_alias, 0);
  poti_header_event (PAJE_DefineLinkType, old_header, poti_alias, 0);
  poti_header_event (PAJE_DefineEntityValue, old_header, poti_alias, 0);
  poti_header_event (PAJE_CreateContainer, old_header, poti_alias, 0);
  poti_header_event (PAJE_DestroyContainer, old_header, poti_alias, 0);
  poti_header_event (PAJE_SetVariable, old_header, poti_alias, 0);
  poti_header_event (PAJE_AddVariable, old_header, poti_alias, 0);
  poti_header_event (PAJE_SubVariable, old_header, poti_alias, 0);
  poti_header_event (PAJE_SetState, old_header, poti_alias, 0);
  poti_header_event (PAJE_PushState, old_header, poti_alias, 0);
  poti_header_event (PAJE_PopState, old_header, poti_alias, 0);
  poti_header_event (PAJE_ResetState, old_header, poti_alias, 0);
  poti_header_event (PAJE_StartLink, old_header, poti_alias, 0);
  poti_header_event (PAJE_EndLink, old_header, poti_alias, 0);
  poti_header_event (PAJE_NewEvent, old_header, poti_alias, 0);

  if (basic){
    paje_extended = 0;
    if (!disable_comments){
      fprintf (paje_file,
               "#\n"
               "# Trace created without extended events\n"
               "#\n");
    }
    return;
  }else{
    paje_extended = 1;
  }

  if (!disable_comments){
    fprintf(paje_file,
            "#\n"
            "# Extended events with additional information\n"
            "# Note that not all paje file format parsers support this\n"
            "# If you have problems parsing this file with your visualization tool\n"
            "#\n");
  }
  
  poti_header_event (PAJE_PushStateMark, old_header, poti_alias, 1, "Mark string");
  poti_header_event (PAJE_StartLinkSize, old_header, poti_alias, 1, "Size double");
  poti_header_event (PAJE_StartLinkSizeMark, old_header, poti_alias, 2, "Size double", "Mark string");
}
