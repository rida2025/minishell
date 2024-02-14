#include "../minishell.h"

typedef struct s_cmd
{
	char			**cmd;
	int				fd[2];
	char			*path;
	struct s_cmd	*next;
}	t_cmd;

int main(int argc, char **agrv, char **envp)
{


    t_cmd cmd1;
    t_cmd cmd2;
    t_cmd cmd3;

    char **cmd = malloc(sizeof(char *) * 2);


    cmd[0] = "ls";
    cmd[2] = 0;

    // char **cmd22 = {"echo", "hi", 0};
    char **cmd22 = malloc(sizeof(char *) * 3);
    cmd22[0] = "wc";
    cmd22[1] = "-l";
    cmd22[2] = 0;
    char **cmd33 = malloc(sizeof(char *) * 3);
    cmd33[0] = "wc";
    cmd33[1] = "-c";
    cmd33[2] = 0;
    cmd1.cmd = cmd;
    cmd1.fd[0] = -1;
    cmd1.fd[1] = -1;
    cmd1.path = "/bin/ls";
    cmd1.next = &cmd2;

    cmd2.cmd = cmd22;
    cmd2.fd[0] = -1;
    cmd2.fd[1] = -1;
    cmd2.path = "/usr/bin/wc";
    cmd2.next = &cmd3;

    cmd3.cmd = cmd33;
    cmd3.fd[0] = -1;
    cmd3.fd[1] = -1;
    cmd3.path = "/usr/bin/wc";
    cmd3.next = 0;
    int pid;
    t_cmd *p = &cmd1;
    int fd[2];
    int i = 0;
    // sleep (10);
    while (p)
    {
        if (p->next)
        {
            if (i == 0)
            {
                pipe(fd);
                if (p->fd[1] == -1)
                    p->fd[1] = fd[1];
            }
            else
            {
                if (p->fd[0] == -1)
                    p->fd[0] = fd[0];
                close (fd[1]);
                pipe(fd);
                if (p->fd[1] == -1)
                    p->fd[1] = fd[1];
            }
        }
        else
        {
            if (p->fd[0] == -1)
                p->fd[0] = fd[0];
            close(fd[1]);
            if (p->fd[1] == -1)
                p->fd[1] = 1;
        }

        pid = fork();
        if (!pid)
        {
            if (p->fd[0] != -1)
            {
                dup2(p->fd[0], 0);
                close(p->fd[0]);

            }
            if ((p->fd[1] != -1) && (p->fd[1] != 1))
            {
                dup2(p->fd[1], 1);
                close(p->fd[1]);

            }
            execve(p->path, p->cmd, envp);
            printf("eqwe");
        }
        i++;
        p = p->next;
    }
    while (waitpid(-1, 0, 0) != -1)
        ;
    close(fd[0]);
}