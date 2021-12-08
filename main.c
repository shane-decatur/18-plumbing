#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define READ 0
#define WRITE 1

int main(){
  int fds1[2];
  pipe(fds1);

  int fds2[2];
  pipe(fds2);

  int f = fork();

  while(1){
    if (f){
      char line[100];
      close(fds1[READ]);
      close(fds2[WRITE]);

      printf("input message: ");
      fgets(line, sizeof(line),stdin);
      write(fds1[WRITE],line,sizeof(line));

      read(fds2[READ],line,sizeof(line));
      printf("your message but loud: %s\n",line);
    }
    else{
      char line[100];
      close(fds1[WRITE]);
      close(fds2[READ]);

      read(fds1[READ],line,sizeof(line));

      int i = 0;
      for (i = 0; i < strlen(line); i++) {
  				if (line[i] >= 97 && line[i] <= 122) line[i] -= 32;
  		}
      write(fds2[WRITE],line,sizeof(line));
    }
  }

  return 0;
}
