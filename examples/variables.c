#include <poti.h>

int main (int argc, char **argv)
{
  poti_header (0, 0);
  poti_DefineContainerType ("PROCESS", "0", "PROCESS");
  poti_DefineVariableType ("VAR", "PROCESS", "VAR", "1 0 0");

  poti_CreateContainer (0, "p1", "PROCESS", "0", "p1");
  
  poti_SetVariable (0, "p1", "VAR", 10);
  poti_AddVariable (0.32, "p1", "VAR", 3);
  poti_SubVariable (0.53, "p1", "VAR", 2);

  poti_DestroyContainer (1.34, "PROCESS", "p1");

  return 0;
}
