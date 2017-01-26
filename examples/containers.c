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
  poti_DefineContainerType ("ROOT", "0", "ROOT");
  poti_DefineContainerType ("PROCESS", "ROOT", "PROCESS");
  poti_DefineContainerType ("THREAD", "PROCESS", "THREAD");


  poti_CreateContainer (0, "root", "ROOT", "0", "root");
  poti_CreateContainer (0, "p1", "PROCESS", "root", "p1");
  poti_CreateContainer (0, "p2", "PROCESS", "root", "p2");
  poti_CreateContainer (0, "p3", "PROCESS", "root", "p3");

  poti_CreateContainer (0, "1t1", "THREAD", "p1", "t1");
  poti_CreateContainer (0, "1t2", "THREAD", "p1", "t2");
  poti_CreateContainer (0, "1t3", "THREAD", "p1", "t3");

  poti_CreateContainer (0, "2t1", "THREAD", "p2", "t1");
  poti_CreateContainer (0, "2t2", "THREAD", "p2", "t2");

  poti_CreateContainer (0, "3t1", "THREAD", "p3", "t1");

  poti_DestroyContainer (0.76, "PROCESS", "p2");
  
  poti_DestroyContainer (1.34, "ROOT", "root");

  poti_close();
  return 0;
}
