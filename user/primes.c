#include "kernel/types.h"
#include "user/user.h"

static const int N = 35;

int check(int divider, int *left_pipe) {
  int n, right_pipe[2];

  close(left_pipe[1]);
  if (read(left_pipe[0], &n, sizeof(int)) != 0) {
    fprintf(1, "prime %d\n", n);
  } else {
    close(left_pipe[0]);
    exit(0);
  }

  if (divider+1 > N) {
    close(left_pipe[0]);
    exit(0);
  }

  pipe(right_pipe);
  if (fork() != 0) {
    // Parent
    while(read(left_pipe[0], &n, sizeof(int)) == sizeof(int)) {
      if (n % divider != 0) {
        write(right_pipe[1], &n, sizeof(int));
      }
    }
    close(right_pipe[1]);
    close(left_pipe[0]);
    wait((int *) 0);
    exit(0);
  } else {
    // Child
    close(left_pipe[0]);
    check(divider+1, right_pipe);
    exit(0);
  }
}

int main(int argc, char *argv[]) {
  int right_pipe[2];
  pipe(right_pipe);
  for (int i = 2; i < N; i++) {
    write(right_pipe[1], &i, sizeof(int));
  }
  close(right_pipe[1]);
  check(2, right_pipe);
  wait((int *) 0);
  exit(0);
}
