#include <stdio.h>
#include <memory.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>



int main(int argc, char **argv)
{
  int in, out;
  char *cat_args[] = {"cat", NULL};

  // open input and output files

  in = open("in.txt", O_RDONLY);
  out = open("out", O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);

  // replace standard input with input file

  dup2(in, 0);

  // replace standard output with output file

  dup2(out, 1);

  // close unused file descriptors

  close(in);
  close(out);

  // execute grep

  execvp("cat", cat_args);
}









/*
int main(int argc, char **argv)
  {
   // Crée le pipe avec tableau de 2 fd 
   int pfd[2];
   //Alloue les deux fd du pipe
    if (pipe(pfd) == -1)
    {
      printf("PIPE FAILED");
      return (-1);
    }

    //Crée le processus enfant avec fonction fork 
    int pid;
    if ((pid = fork()) < 0)
    {
      printf("FORK FAILED");
      return(-2);
    } 

    //Condition si je suis dans le processus enfant 
    if (pid == 0)
    {
      char buffer[BUFSIZ];
      close(pfd[1]); // Ferme l'entré du pipe enfant
      if (read(pfd[0],buffer,BUFSIZ) != 0) //Lis la sortie pipe de l'enfant
        printf("CHILD READ %s",buffer);
      close(pfd[0]); // Ferme la sortie pipe enfant
      exit(0);
    }
    else{
      int fd;
      char buffer[BUFSIZ];
      close(pfd[0]);
      fd = open("in.txt",O_RDONLY);
      dup2(pfd[1],fd);
      close(pfd[1]);

    }
    return (0);

   
  }*/