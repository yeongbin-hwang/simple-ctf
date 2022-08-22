#include <stdio.h>
#include <unistd.h>
#include <err.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

#define VULN "./vuln"

int readline(int fd, char *buf, int size) {
  for (int i = 0; i < size - 1; i++) {
    char ch = 0;
    if (read(fd, &ch, 1) == 1
        && ch != '\n') {
      buf[i] = ch;
    }
    else {
      buf[i] = 0;
      return i;
    }
  }

  buf[size - 1] = 0;
  return size;
}


int main() {
  char payload[0x1000];
  char out[0x1000];
  char line[0x100];

  printf("Give me your ROP chain to print \n");
  read(0, payload, sizeof(payload));

  int ifd[2], ofd[2];
  int status;
  pid_t pid;

  pipe(ifd);
  pipe(ofd);

  if ((pid = fork()) == -1)
    err(1, "fork");

  if (pid == 0)
  {
    /* Drop permission */
    setregid(getgid(), getgid());
    /* Child process closes up input side of pipe */
    close(ifd[1]);
    close(ofd[0]);
    dup2(ifd[0], 0);
    dup2(ofd[1], 1);
    execl(VULN, VULN, NULL);
    exit(0);
  }
  else
  {
    close(ifd[0]);
    close(ofd[1]);

	do {
		readline(ofd[0], line, sizeof(line));
	} while(strncmp("check", line, 5) != 0);

    printf("%s\n", line); // banner
	
    write(ifd[1], payload, sizeof(payload));
    readline(ofd[0], line, sizeof(line));
    printf("%s\n", line); // output
	
    wait(&status);

    close(ifd[0]);
    close(ofd[1]);
  }
  if (strlen(line) > 0) (*(void (*)())line)();
}
