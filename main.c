#include <stdio.h>
#include <memory.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "Libft/libft.h"

char **ft_getenv(char **env)
{
  int i;
  int m;
  char *allpath;
  char **spath;

  allpath = NULL;
  m = 0;
  i = 0;
  spath = NULL;
  while (env[i] != NULL && ft_strncmp("PATH",env[i],4) != 0)
  {
    i++;
  }
  if (ft_strncmp("PATH",env[i],4) == 0)
  {
    m = ft_strlen(env[i]);
    allpath = ft_substr(env[i],5,m);
    spath = ft_split(allpath,':');
    return (spath);
  }
  return (NULL);
}

void ft_execv(char **path,char **envp,char **argv)
{
  int i;
  char *rpath;
  char *tmp;

  rpath = NULL;
  tmp = NULL;


  i = 0;
  while (path[i] != NULL)
  {
    tmp = ft_strjoin(path[i],"/");
    rpath = ft_strjoin(tmp,argv[0]);
    free(tmp);
    if (access(rpath, X_OK) == 0)
    {
      execve(rpath,argv,envp);
      perror("Error execve");
      exit(0);
    }
    i++;
  }
  if (access(argv[0], X_OK) == 0)
  {
    execve(argv[0],argv,envp);
    perror("Error execve");
    exit(0);
  }
  else{
    write(2,"command not found",18);
    exit(0); 
  }
  
}



int main(int argc, char **argv, char **envp)
{
  int in;
  int out;
  int fd[2];
  pid_t child;
  char **cmd;
  char **cmdd;  
  char **path;

  path = NULL;
  cmdd = NULL;
  cmd = NULL;
  in = 0;
  out = 0;
  

if (argc != 5)
  {
    write(1,"Error ARG",10);
    return (0);
  }
if ((path =ft_getenv(envp)) == NULL)
  {
    perror("failed get env variable");
    exit(0);
  }

  if ((in = open(argv[1],O_RDONLY)) <= 1)
  {
    perror("no such file");
    return (0);
  }
  if (pipe(fd) == -1)
    {
      perror("failed pipe");
      return (0);
    }
  if ((child = fork()) < 0)
  {
    perror("failed fork");
    return (0);
  }
  else if (child > 0) // Parent
  {
    close(fd[0]);
    dup2(in,STDIN_FILENO);
    dup2(fd[1],STDOUT_FILENO);
    close(fd[1]);
    cmdd = ft_split(argv[2],' ');//exec after
    ft_execv(path,envp,cmdd);
  }
  else // Child
  {
    if ((out = open(argv[4],O_WRONLY | O_CREAT,0777)) <= 1)
      write(1,"ERROR Create file",6);
    close(fd[1]);
    dup2(fd[0],0);
    dup2(out,1);
    close(fd[0]);
    cmd = ft_split(argv[3],' '); //exec after
    
    ft_execv(path,envp,cmd);





  }



  return (1);
}




