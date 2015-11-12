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
  int test_type;
  
  if (argc != 2){
    return 1;
  }else{
    test_type = atoi(argv[1]);
  }

  switch (test_type){
  case 1:
    poti_header (0, 0);
    break;
  case 2:
    poti_header (1, 0);
    break;
  case 3:
    poti_header (0, 1);
    break;
  case 4:
    poti_header (1, 1);
    break;
  case 5:
    poti_set_alias (0);
    poti_header (0, 0);
    break;
  case 6:
    poti_set_alias (0);
    poti_header (1, 0);
    break;
  case 7:
    poti_set_alias (0);
    poti_header (0, 1);
    break;
  case 8:
  default:
    poti_set_alias (0);
    poti_header (1, 1);
    break;
  }
  return 0;
}
