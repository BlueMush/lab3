#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <sys/types.h>

int getargs(char *cmd, char *argv[]);

main ()

{ 

 char buf[256];

 char *argv[50];

 int narg;

 pid_t pid;

 while (1)

 {

  printf("shell>");

  fgets(buf,256,stdin);

  narg = getargs(buf, argv);

  pid=fork();

  if (strncmp (buf, "exit",4) == 0)

  {

   exit(0);

  }

  if(pid==0)

  {

   execvp(argv[0],argv);

   perror("Error:");       // 명령어 존재하지 않음

   exit(0);    // 자식 프로세스 종료

  }

  else if (pid>0)

  {

   if(narg>=0)   // 백그라운드 실행이 아니면

    wait(NULL); // 자식프로세스 기다림

   continue;  // 백그라운드 실행이면 바로 루프의 처음으로

  }

  else

  {

   perror("fork failed");

  }

 }

 return 1;

}

int getargs(char * cmd, char *argv[])

{

 int i = 0;

 char c;

 char * token;

 int len=strlen(cmd);

 for(i=0;i<len;i++)

 {

  if (cmd[i]=='\n')

   cmd[i]=' ';  // New Line 을 Blank로 변환

 }

 argv[0]=token=strtok(cmd," ");  // 첫번째 명령어 추출

 argv[1]=NULL;

 i=1;

 while (token!=NULL)

 {

  token=strtok(NULL," ");  // 다음 Argument 추출

  if(token!=NULL&&strcmp(token,"&")==0)     // 백그라운드 실행조건

  {

   argv[i]=NULL;

   return i*(-1);                           //음수를 리턴

  }

  argv[i]=token;

  i++; 

 }

 return i;

}
