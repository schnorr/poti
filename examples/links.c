#include <poti.h>

int main (int argc, char **argv)
{
  poti_header (0, 0);
  poti_DefineContainerType ("PROCESS", "0", "PROCESS");
  poti_DefineLinkType("LINK", "0", "PROCESS", "PROCESS", "LINK");

  poti_CreateContainer (0, "p1", "PROCESS", "0", "p1");
  poti_CreateContainer (0, "p2", "PROCESS", "0", "p2");
  poti_CreateContainer (0, "p3", "PROCESS", "0", "p3");

  poti_StartLink (0.24, "0", "LINK", "p1", "c", "myKey-001");
  poti_EndLink (1.02, "0", "LINK", "p2",   "c", "myKey-001");


  poti_StartLink (1.04, "0", "LINK", "p1", "c", "myKey-002");
  poti_EndLink (2.10, "0", "LINK", "p3",   "c", "myKey-002");

  return 0;
}
