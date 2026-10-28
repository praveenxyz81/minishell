#include"minishell.h"

void execute_internal_commands(char **args)
{
 if(strcmp(args[0],"pwd") == 0)
 {
    char cwd[1024];
    if(getcwd(cwd,sizeof(cwd))!=NULL)
    {
        printf("%s\n",cwd);
    }
    else
    {
        perror("pwd");
    }
 }
 else if(strcmp(args[0], "cd") == 0)
 {
    char *path = args[1];
    


 }

}