/**
 * @author Nicholas Sardo <gcc.programmer@gmail.com>
 * @copyright ©2019 Nicholas Sardo
 * @license MIT
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int main() {
  pid_t child, cpid;
  int status;
  
  if ( (child = fork()) < 0 ) {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  
  cpid = child;
  printf("%d is created child\n", child);
  
  if ( waitpid(child, &status, WNOHANG) == 0) {
    puts( "parent...");
    printf( "\tParent PID: %d\n", getpid());
    printf( "\tParent PPID: %d\n", getppid());
    int retval = kill( child, SIGKILL );
    if ( retval ) {
      /* KILL FAILED, WAIT FOR CHILD TO EXIT */
      puts("Kill Failed\n");
      perror("kill");
      waitpid(child, &status, 0);
      printf( "\tChild exited with: %d\n", status );
    } else
      printf("%d killed\n", child);
  }
  exit(EXIT_SUCCESS);
}