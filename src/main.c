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
char *path_copy;
char file[256];
char cmd_copy[256];
void full_path(char *file_path, char *command){
  
  sprintf(file,"%s/%s" ,file_path,command);
  //printf("PATH: %s is %s\n",command,file);
  return;
}
void check_x(char *command, char *token2){
  int flag = 0;
  char *ptr2;
  char *file_path = strtok_r(path_copy, PATH_LIST_SEPARATOR, &ptr2);
  while(file_path != NULL){
        //printf("PATH: %s\n",file_path);
        //sprintf(file,"%s/%s" ,file_path,token2);
        //printf("%s", command);
        //printf("PATH: %s is %s\n",token2,file);
        if(strcmp(command, "type") == 0){
          full_path(file_path, token2);
        }
        else{
          full_path(file_path,command);
        }
        //printf("%d\n%d\n",access(file,F_OK),access(file,X_OK));
        if (access(file,F_OK) == 0){
          if (access(file,X_OK) == 0){
            flag = 1;
            printf("TEST");
            if(strcmp(command, "type") == 0){
              printf("%s is %s\n",token2,file);
              break;
            }
            else{
              //printf("TEST\n");
              //execvp(file,args);
              system(cmd_copy);
              break;
            }
          }
        }
        file_path = strtok_r(NULL,":", &ptr2);
      }
  if (!flag){printf("%s: not found\n", token2);}
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
    strcpy(cmd_copy,command);
    char *ptr1;
    char *token = strtok_r(command, " ", &ptr1);
    path_copy = strdup(path);
    int execute = 0;
    //printf("ERR: %s\n", file_path);
    // printf("ERR: %s\n", token);
    if ( strcmp(command,"exit") == 0){
      return 0;
    }
    else if (strcmp(command,"echo") == 0){
      // printf("ERR: %s\n", file_path);
      printf("%s\n",strtok_r(NULL,"",&ptr1));
    }
    //printf("%s\n", command);
    else if (strcmp(command, "type") == 0){
      char *token2 = strtok_r(NULL,"",  &ptr1);    
      
      if (token2 != NULL && strcmp(token2,"echo") == 0 ||
                            strcmp(token2,"exit") == 0 ||
                            strcmp(token2,"type") == 0 ){
              printf("%s is a shell builtin\n", token2);
           }
      else {
          //int flag = 0;
        check_x(command,token2);  
      }
    }

    else if (strcmp(command, "type") != 0){
      char *args = strtok_r(NULL, "", &ptr1);
      check_x(command,args);
    }
    else {
      //system(command);
      printf("%s: command not found\n", command);
    }
    free(path_copy);
  }
  return 0;
}
