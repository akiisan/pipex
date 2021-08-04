#include <stdio.h>
#include <memory.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "Libft/libft.h"

int getpath(char **env)
{
  int i;

  i = 0;

  while (env[i] && ft_strncmp("PATH",env[i],4) != 0)


}

int main(int argc, char **argv, char **envp)
{
  int in;
  int out;
  int fd[2];
  pid_t child;

  in = 0;
  out = 0;
  
  if ((in = open(argv[1],O_RDONLY)) >= 1)
    write(1,"SUCCESS OPEN IN FILE\n",22);
  else
    write(1,"ERROR OPEN IN FILE",9);

  if (pipe(fd) == -1)
    {
      write(1,"failed pipe",12);
      return (1);
    }
  if ((child = fork()) < 0)
  {
    write(1,"error fork",11);
    return (1);
  }
  else if (child > 0) // Parent
  {
    close(fd[0]);
    dup2(in,STDIN_FILENO);
    dup2(fd[1],STDOUT_FILENO);
    close(fd[1]);
    execlp("cat", "cat", (char *)0);
  }
  else // Child
  {
    if ((out = open(argv[4],O_WRONLY | O_CREAT,0777)) <= 1)
      write(1,"ERROR",6);
    close(fd[1]);
    dup2(fd[0],0);
    dup2(out,1);
    close(fd[0]);

    execlp("wc", "wc", (char *)0);
  }










  return (1);
}




