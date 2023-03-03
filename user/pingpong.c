#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int p_p2c[2], p_c2p[2];
  int child_pid;

  pipe(p_p2c);
  pipe(p_c2p);
  if((child_pid = fork()) == 0) {
    // Child
    close(p_p2c[1]); // Close write side
    read(p_p2c[0], &child_pid, sizeof(int));
    fprintf(1, "%d: received ping\n", child_pid);
    close(p_p2c[0]);

    close(p_c2p[0]);
    write(p_c2p[1], &child_pid, sizeof(int));
    close(p_c2p[1]);
    exit(0);
  } else {
    // Parent
    close(p_p2c[0]);
    write(p_p2c[1], &child_pid, sizeof(int));
    close(p_p2c[1]);
    
    close(p_c2p[1]);
    read(p_c2p[0], &child_pid, sizeof(int));
    fprintf(1, "%d: received pong\n", getpid());
    close(p_c2p[0]);
  }
  exit(0);
}