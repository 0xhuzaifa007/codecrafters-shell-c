#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  // Flush after every printf
  setbuf(stdout, NULL);

  // TODO: Uncomment the code below to pass the first stage
  char command[30]; 
 
  while (1){
    printf("$ ");
    //scanf("%s", command);
    fgets(command,sizeof(command), stdin);
    command[strlen(command) - 1 ] = '\0';
    char *token = strtok(command, " ");
    //printf("%s\n", command);
    if ( strcmp(command,"exit") == 0){
      return 0;
    }
    
    else if (strcmp(command,"echo") == 0){
      printf("%s\n",strtok(NULL,""));
    }

    else if (strcmp(command, "type") == 0){
      char *token2 = strtok(NULL,"");    
      //printf("%s is a shell command\n", token2);
      if (token2 != NULL && strcmp(token2,"echo") == 0 ||
                            strcmp(token2,"exit") == 0 ||
                            strcmp(token2,"type") == 0 )
{
              printf("%s is a shell builtin\n", token2);
           }
      else {
        printf("%s: not found\n", token2);
      }
    }

    else {
      printf("%s: command not found\n", command);
    } 
}
  return 0;
}
