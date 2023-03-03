#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc != 2){
    fprintf(2, "usage: sleep [time]\n");
    exit(1);
  }

  int sleep_time;
  if ((sleep_time = atoi(argv[1])) == -1){
    fprintf(2, "input value cannot be recognized as integer");
    exit(1);
  }

  sleep(sleep_time * 10);
  exit(0);
}
