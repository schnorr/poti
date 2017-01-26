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
  poti_DefineEventType ("EV", "PROCESS", "EV");

  poti_CreateContainer (0, "p1", "PROCESS", "0", "p1");

  poti_NewEvent(2.43, "p1", "EV", "PrimeiroEvento");
  poti_NewEvent(2.87, "p1", "EV", "SegundoEvento");

  //change the timestamp of destroy to be larger than that of latest NewEvent
  poti_DestroyContainer (1.34, "PROCESS", "p1");

  poti_close();
  return 0;
}
