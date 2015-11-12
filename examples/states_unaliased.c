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
  poti_set_alias (0);
  poti_header (0, 0);
  poti_DContainerType ("0", "PROCESS");
  poti_DStateType ("PROCESS", "VAR");

  poti_ECreateContainer (0, "PROCESS", "0", "p1");
  poti_ESetState (0, "p1", "VAR", "Inicio");
  poti_EPushState (0.32, "p1", "VAR", "Meio");
  poti_EPopState (0.53, "p1", "VAR");
  poti_EPushState (0.86, "p1", "VAR", "Fim");
  poti_EPopState (0.99, "p1", "VAR");
  poti_EDestroyContainer (1.34, "PROCESS", "p1");

  return 0;
}
