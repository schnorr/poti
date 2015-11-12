#include <poti.h>

int main (int argc, char **argv)
{
  poti_header (0, 0);
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

  return 0;
}
