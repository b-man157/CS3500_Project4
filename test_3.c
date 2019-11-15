#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int *arr = (int*) malloc (4096 * sizeof(int)); 
  printf(1, "# Before page access\n");
  printf(1, "\n Virtual pages: %d\nPhysical pages: %d\n", count_virtual_pages(), count_physical_pages());

  for(int i = 0; i < 4096; ++i){
    arr[i] = 0;
  }
  printf(1, "\n# After page access\n");
  printf(1, "\n Virtual pages: %d\nPhysical pages: %d\n", count_virtual_pages(), count_physical_pages());

  exit();
}
