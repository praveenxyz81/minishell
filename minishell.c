#include"minishell.h"

void scan_input(char *prompt, char *input_string)
{

   scanf(" %[^\n]",input_string);
   if(strncmp(input_string,"PS1=",4) == 0)
   {
       if(strchr(input_string,' ') ==NULL)
       {
          strncpy(prompt,input_string+4,50-1); 
          prompt[50-1] = '\0';
          input_string[0] = '\0';
       }

   }
}
void extract_external_commands(char **external_commands)
{
      FILE *fp = fopen("external.txt","r");
      char str[50];
      int len,i=0;
      while(fgets(str,sizeof(str),fp) != NULL)
      {
         len = strlen(str);
         if(str[len-1] == '\n')
         {
            str[len-1] = '\0';
            external_commands[i] = malloc(len+1);
            strcpy(external_commands[i],str);
            i++;
         }    

      }
      external_commands[i] = NULL;
      fclose(fp);
}
char *get_command(char *input_string)
{
   char *cmd = malloc(50);
   int i =0;
   while(input_string[i] != ' ' && input_string != '\0')
   {

       cmd[i] = input_string[i];
       i++;

   }
   cmd[i] = '\0';
   return cmd;
}
int check_command_type(char *command , char **external)
{
   char *builtins[] = {"echo", "printf", "read", "cd", "pwd", "pushd", "popd", "dirs", "let", "eval",
						"set", "unset", "export", "declare", "typeset", "readonly", "getopts", "source",
						"exit", "exec", "shopt", "caller", "true", "type", "hash", "bind", "help", NULL};
   for(int i = 0 ; builtins[i] != NULL ;i++)
   {
       if(strcmp(builtins[i] , command) == 0)
       {
         return BUILTIN;
       }
   }
      for(int i = 0 ; external[i] != NULL ;i++)
   {
       if(strcmp(external[i] , command) == 0)
       {
         return EXTERNAL;
       }
   }

   return NO_COMMAND;


}
void splitstrings(char *input_string , char *args[])
{
   int i = 0;
   args[i] = strtok(input_string," ");
   while(args[i] != NULL)
   {
      args[i] = strtok(NULL," ");
      i++;
   }

}