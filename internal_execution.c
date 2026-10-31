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
 else if(strcmp(args[0],"exit") == 0)
 {
    exit(0);
 }
 else if(strcmp(args[0], "cd") == 0)
 {
    char *path = args[1];
     if(path == NULL || chdir(path) != 0)
     {
        perror("cd");
     }
 }
else if (strcmp(args[0], "echo") == 0)
{
    extern int exit_status;
    int i = 1;
    while (args[i])
    {
        if (strcmp(args[i], "$?") == 0)
           printf("%d", exit_status);
        else if (strcmp(args[i], "$$") == 0)
            printf("%d", getpid());
        else if (args[i][0] == '$' && args[i][1])
        {
            char *val = getenv(args[i] + 1);
            if (val)
                printf("%s", val);
        }
        else
            printf("%s", args[i]);
        if (args[i + 1])
            printf(" ");
        i++;
    }
    printf("\n");
}
else if (strcmp(args[0], "fg") == 0)
{
    extern job_t *head;
    extern int status;

    if (head == NULL)
    {
        printf("No stopped jobs\n");
    }
    else
    {
        job_t *temp = head;

        if (kill(temp->pid, SIGCONT) == -1)
        {
            perror("fg");
        }
        else
        {
            waitpid(temp->pid, &status, WUNTRACED);

            if (WIFSTOPPED(status))
            {
                printf("\n[%d] Stopped %s\n",temp->pid, temp->input);
            }
            else
            {
                head = temp->link;
                free(temp);
            }
        }
    }
}
else if (strcmp(args[0], "bg") == 0)
{
    extern job_t *head;

    if (head == NULL)
    {
        printf("No stopped jobs\n");
    }
    else
    {
        if (kill(head->pid, SIGCONT) == -1)
        {
            perror("bg");
        }
        else
        {
            printf("[%d] Running %s\n",head->pid, head->input);
        }
    }
}
else if (strcmp(args[0], "jobs") == 0)
{
    extern job_t *head;

    if (head == NULL)
    {
        printf("No jobs\n");
    }
    else
    {
        job_t *temp = head;

        while (temp != NULL)
        {
            printf("[%d] Stopped    %s\n", temp->pid, temp->input);
            temp = temp->link;
        }
    }
}

}