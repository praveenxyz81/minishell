#include"minishell.h"

int exit_status = 0;
int main()
{
   system("clear");
   char *external[153];
   char *args[50];
   int status;
    pid_t pid;
   extract_external_commands(external);
   char prompt_string[50] = "minishell";
   char input_string[50];
   while(1)
   {
     printf("%s$ ",prompt_string);
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
          execute_external_commands(args);
          exit(0);
        }
        else if(pid > 0)
        {
            waitpid(pid,&status,0);
            if(WIFEXITED(status))
            {
                exit_status = WEXITSTATUS(status);
            }
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