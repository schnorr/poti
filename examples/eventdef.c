/*
    This file is part of Poti

    Poti is free software: you can redistribute it and/or modify
    it under the terms of the GNU Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Poti is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Public License for more details.

    You should have received a copy of the GNU Public License
    along with Poti. If not, see <http://www.gnu.org/licenses/>.
*/
#include <poti.h>

/*
 * This example shows you how to define events with extra fields.
 * See the Paje file format documentation for the theory.
 */
int main (int argc, char **argv)
{
  // Init the library
  poti_init ();

  //This is the way you do to declare a DefineContainerType
  //The first parameter is the type, one of these:
  /* PAJE_DefineContainerType, */
  /* PAJE_DefineVariableType, */
  /* PAJE_DefineStateType, */
  /* PAJE_DefineEventType, */
  /* PAJE_DefineLinkType, */
  /* PAJE_DefineEntityValue, */
  /* PAJE_CreateContainer, */
  /* PAJE_DestroyContainer, */
  /* PAJE_SetVariable, */
  /* PAJE_AddVariable, */
  /* PAJE_SubVariable, */
  /* PAJE_SetState, */
  /* PAJE_PushState, */
  /* PAJE_PopState, */
  /* PAJE_ResetState, */
  /* PAJE_StartLink, */
  /* PAJE_EndLink, */
  /* PAJE_NewEvent, */
  //The second parameter indicates if there are user extra fields.

  poti_header_DeclareEvent (PAJE_DefineContainerType, 0);
  poti_header_DeclareEvent (PAJE_DefineStateType, 0);
  poti_header_DeclareEvent (PAJE_CreateContainer, 0);

  int myPushStateMark = poti_header_DeclareEvent (PAJE_PushState, 1, "Mark string");

  //Each of the above functions return the unique identifier of the
  //event definition.  This unique identifier should be then used in
  //the events section.

  poti_DefineContainerType ("P", "0", "PROCESS");
  poti_DefineStateType ("S", "P", "STATE");
  poti_CreateContainer (0.0, "p1", "P", "0", "Process 1");

  //So, if you are handling with events with extra fields, you should
  //manage these unique identifiers yourself and generate events with
  //the following API:
  poti_UPushState (myPushStateMark, 0.32, "p1", "S", "Start", 1, "MyMark");

  // Close the library
  poti_close();
  return 0;
}
