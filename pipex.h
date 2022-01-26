#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdio.h>
# include <memory.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

typedef struct s_pipex
{
	int		in;
	int		out;
	int		fd[2];
	char	**cmd;
	char	**cmdd;
	char	**path;
	int		child2;
	int		child;
	char	**argv;
	char	**envp;
}				t_pipex;

int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_calloc(size_t count, size_t size);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_getenv(char **env);
void	ft_execv(char **path, char **envp, char **argv);
void	freeall(char **str);
void	checkerror(int argc, t_pipex *p, char **envp);

#endif