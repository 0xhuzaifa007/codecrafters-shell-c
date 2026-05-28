#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#ifdef _WIN32
#define PATH_LIST_SEPARATOR ";"
#else
#define PATH_LIST_SEPARATOR ":"
#endif

void check_x(char *file_path,char *token2){
  int flag = 0;
  while(file_path != NULL){
        //printf("PATH: %s\n",file_path);
        char file[256];
        sprintf(file,"%s/%s" ,file_path,token2);
        //printf("PATH: %s is %s\n",token2,file);
        if (access(file,F_OK) == 0){
          if (access(file,X_OK) == 0){
            printf("%s is %s\n",token2,file);
            flag = 1; 
            break;
          }
        }
        file_path = strtok(NULL,":");
      }
  if (!flag){printf("%s: not found\n", token2);}
  return;
}

void execute_command(char *command, char *path){
  char *token = strtok(command, " ");
  char *path_copy = strdup(path);
  int executable = 0;

    
    

    if (strcmp(command, "type") == 0){
      char *token2 = strtok(NULL,"");    
      char *file_path = strtok(path_copy, ":");
      if (token2 != NULL && strcmp(token2,"echo") == 0 ||
                            strcmp(token2,"exit") == 0 ||
                            strcmp(token2,"type") == 0 ){
              printf("%s is a shell builtin\n", token2);
           }
      else {
  
        //int flag = 0;
        check_x(file_path, token2);  
      }
    }

    // else if (strcmp(command))

    else {
      system(command);
      printf("%s: command not found\n", command);
    }
    free(path_copy);
    return;
}

int main(int argc, char *argv[]) {
  // Flush after every printf
  setbuf(stdout, NULL);
  // printf("arg0:%s",argv[0]);
  // printf("arg1:%s",argv[1]);
  // printf("arg2:%s",argv[2]);


  // TODO: Uncomment the code below to pass the first stage
  char command[256]; 
  char *path = getenv("PATH");
  // if (path != NULL){
  //   printf("%s", path);
  // }

  while (1){
    printf("$ ");
    //scanf("%s", command);
    fgets(command,sizeof(command), stdin);
    command[strlen(command) - 1 ] = '\0';
    
    if ( strcmp(command,"exit") == 0){
      return 0;
    }
    if (strcmp(command,"echo") == 0){
      printf("%s\n",strtok(NULL,""));
    }
    //printf("%s\n", command);
    execute_command(command, path);
  }
  return 0;
}
