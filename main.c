#include"minishell.h"

int exit_status = 0;
pid_t pid;
char *external[153];
char *args[50];
int status;
char prompt_string[50]= "Minishell";
char input_string[50];
job_t *head = NULL;

int main()
{
   system("clear");
   extract_external_commands(external);
   signal(SIGINT,signal_handler);
   signal(SIGTSTP,signal_handler);
   while(1)
   {
     printf("%s $",prompt_string);
     fflush(stdout);
     scan_input(prompt_string,input_string);
     if(input_string[0] == '\0')
      continue;
    splitstrings(input_string,args);
    char *cmd = get_command(input_string);
    int type = check_command_type(cmd,external);
    switch(type)
    {
       case EXTERNAL:
        pid = fork();
        if(pid == 0)
        {
           signal(SIGINT,  SIG_DFL);
           signal(SIGTSTP, SIG_DFL);
           signal(SIGCHLD, SIG_DFL);
          execute_external_commands(args);
          exit(0);
        }
        else if(pid > 0)
        {
            waitpid(pid, &status, WUNTRACED);

            if (WIFSTOPPED(status))
            {
                insert_first(&head, input_string, pid);
                printf("\n[%d] Stopped %s\n", pid, input_string);
            }
            else if (WIFEXITED(status))
            {
                exit_status = WEXITSTATUS(status);
            }
            else if (WIFSIGNALED(status))
            {
                printf("\n");
            }

            pid = 0;
        }
        break;

        case BUILTIN:
         execute_internal_commands(args);
          break;
        case NO_COMMAND:
          printf("Invalid input\n");
          break;





    }
     
    



   }
}