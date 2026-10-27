#include"minishell.h"

void  execute_external_commands(char **args)
{
   
  int pipe_count = 0;
  int args_size = 0;
  for(int i=0 ; args[i]!=NULL;i++)
  {
     args_size++;
  }
  int pipe_pos[args_size];
  for(int i = 0 ; i< args_size;i++)
  {
    if(strcmp(args[i],"|") == 0)
    {
         if (i == 0)
        {
            printf("Error: Missing command before pipe\n");
            return ;
        }
        if (i == args_size - 1)
        {
            printf("Error: Missing command after pipe\n");
            return ;
        }
        if (strcmp(args[i - 1], "|") == 0)
        {
            printf("Error: Consecutive pipes are not allowed\n");
            return ;
        }
           pipe_pos[pipe_count] = i;
           pipe_count++;
    }
  }

  if(pipe_count == 0)
  {
     execvp(args[0] , args);
     exit(0);
  }
  else
  {
    for (int i = 0; i < pipe_count; i++)
    {
        args[pipe_pos[i]] = NULL;
    }

    int fd[pipe_count][2];
    for(int i =0 ;i<pipe_count;i++)
    {
        if(pipe(fd[i]) == -1)
        {
            perror("pipe");
            return ;
        }
    }

    pid_t pid;
    int start = 0;

    for (int i = 0; i <= pipe_count; i++)
    {
        pid = fork();

        if (pid == -1)
        {
            perror("fork");
            return ;
        }

        if (pid == 0)
        {
            if (i > 0)
            {
                if (dup2(fd[i - 1][0], STDIN_FILENO) == -1)
                {
                    perror("dup2 input");
                    _exit(1);
                }
            }
            if (i < pipe_count)
            {
                if (dup2(fd[i][1], STDOUT_FILENO) == -1)
                {
                    perror("dup2 output");
                }
            }
            for (int j = 0; j < pipe_count; j++)
            {
                close(fd[j][0]);
                close(fd[j][1]);
            }

            execvp(args[start], &args[start]);

        }
        if (i < pipe_count)
        {
            start = pipe_pos[i] + 1;
        }
    }
    for (int i = 0; i < pipe_count; i++)
    {
        close(fd[i][0]);
        close(fd[i][1]);
    }
    for (int i = 0; i <= pipe_count; i++)
    {
        wait(NULL);
    }
    }


  }

 
    








//     int main(int argc, char *argv[])
// {
//    if(argc == 1)
//    {
//       printf("No arguments passed \n");
//       return 1;
//    }
//    int pipe_count = 0;
//    int pipe_pos[argc];
//    for(int i =0 ;i< argc ;i++)
//    {
//        if(strcmp(argv[i],"|") == 0)
//        {
//            if (i == 1)
//         {
//             printf("Error: Missing command before pipe\n");
//             return 1;
//         }
//         if (i == argc - 1)
//         {
//             printf("Error: Missing command after pipe\n");
//             return 1;
//         }
//         if (strcmp(argv[i - 1], "|") == 0)
//         {
//             printf("Error: Consecutive pipes are not allowed\n");
//             return 1;
//         }
//            pipe_pos[pipe_count] = i;
//            pipe_count++;
//        }
//    }
//    if (pipe_count == 0)
//     {
//         printf("Error: At least one pipe is required\n");
//         return 1;
//     }

