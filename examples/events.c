#include <poti.h>

int main (int argc, char **argv)
{
  poti_header (0, 0);
  poti_DefineContainerType ("PROCESS", "0", "PROCESS");
  poti_DefineEventType ("EV", "PROCESS", "EV");

  poti_CreateContainer (0, "p1", "PROCESS", "0", "p1");

  poti_NewEvent(2.43, "p1", "EV", "PrimeiroEvento");
  poti_NewEvent(2.87, "p1", "EV", "SegundoEvento");

  //change the timestamp of destroy to be larger than that of latest NewEvent
  poti_DestroyContainer (1.34, "PROCESS", "p1");

  return 0;
}
