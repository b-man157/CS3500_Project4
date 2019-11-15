#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  printf(1, " Virtual pages: %d\nPhysical pages: %d\n", count_virtual_pages(), count_physical_pages());
  exit();
}
