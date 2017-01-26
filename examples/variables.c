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

int main (int argc, char **argv)
{
  poti_init ();
  poti_header ();
  poti_DefineContainerType ("PROCESS", "0", "PROCESS");
  poti_DefineVariableType ("VAR", "PROCESS", "VAR", "1 0 0");

  poti_CreateContainer (0, "p1", "PROCESS", "0", "p1");
  
  poti_SetVariable (0, "p1", "VAR", 10);
  poti_AddVariable (0.32, "p1", "VAR", 3);
  poti_SubVariable (0.53, "p1", "VAR", 2);

  poti_DestroyContainer (1.34, "PROCESS", "p1");

  return 0;
}
