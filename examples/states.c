#include <poti.h>

int main (int argc, char **argv)
{
  poti_header (0, 0);
  poti_DefineContainerType ("PROCESS", "0", "PROCESS");
  poti_DefineStateType ("VAR", "PROCESS", "VAR");

  poti_CreateContainer (0, "p1", "PROCESS", "0", "p1");
  
  poti_SetState (0, "p1", "VAR", "Inicio");
  poti_PushState (0.32, "p1", "VAR", "Meio");
  poti_PopState (0.53, "p1", "VAR");
  poti_PushState (0.86, "p1", "VAR", "Fim");
  poti_PopState (0.99, "p1", "VAR");

  poti_DestroyContainer (1.34, "PROCESS", "p1");

  return 0;
}
