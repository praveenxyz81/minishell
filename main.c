#include"minishell.h"


int main()
{
   system("clear");
   char *external[152];
   char *args[50];
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
     
    



   }
}