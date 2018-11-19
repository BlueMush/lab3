#include<stdio.h>
#include<fcntl.h>
#include<termios.h>
#include<time.h>
#include<sys/types.h>
#include<unistd.h>

#define PASSWORDSIZE 12

void typing(int time1, int time2){
  int time_tmp;
  float avg_input;

  time_tmp = time2 - time1;
  printf("시간: %dsec\n",time_tmp);
  avg_input = (74/time_tmp)*60;
  printf("타수: %.lf\n",avg_input);
}
int main(void)
{
int fd,fd1,fd2;
int nread, cnt=0, errcnt=0;
int nread1, cnt1=0, errcnt1=0;
int nread2, cnt2=0, errcnt2=0;
char ch, text[] = "BlueMushRoom";
char ch1, text1[] = "RedMushRoom";
char ch2, text2[] = "GreenMushRoom";

struct termios init_attr, new_attr;
time_t time1, time2;

fd = open(ttyname(fileno(stdin)), O_RDWR);
fd1 = open(ttyname(fileno(stdin)), O_RDWR);
fd2 = open(ttyname(fileno(stdin)), O_RDWR);

tcgetattr(fd, &init_attr);
new_attr = init_attr;
new_attr.c_lflag &= ~ICANON;
new_attr.c_lflag &= ~ECHO;
new_attr.c_cc[VMIN] = 1;
new_attr.c_cc[VTIME] = 0;

if (tcsetattr(fd, TCSANOW, &new_attr) != 0) {
  fprintf(stderr, "터미널 속성을 설정할 수 없음.\n");
}
if (tcsetattr(fd1, TCSANOW, &new_attr) != 0) {
  fprintf(stderr, "터미널 속성을 설정할 수 없음.\n");
}
if (tcsetattr(fd2, TCSANOW, &new_attr) != 0) {
  fprintf(stderr, "터미널 속성을 설정할 수 없음.\n");
}

fd1 = open(ttyname(fileno(stdin)), O_RDWR);
tcgetattr(fd, &init_attr);
new_attr = init_attr;
new_attr.c_lflag &= ~ICANON;
new_attr.c_lflag &= ~ECHO;
new_attr.c_cc[VMIN] = 1;
new_attr.c_cc[VTIME] = 0;
fd2 = open(ttyname(fileno(stdin)), O_RDWR);
tcgetattr(fd, &init_attr);
new_attr = init_attr;
new_attr.c_lflag &= ~ICANON;
new_attr.c_lflag &= ~ECHO;
new_attr.c_cc[VMIN] = 1;
new_attr.c_cc[VTIME] = 0;
  time(&time1);
  
printf("다음 문장을 그대로 입력하세요.\n%s\n", text);
while ((nread=read(fd, &ch, 1)) > 0 && ch != '\n') {
  if (ch == text[cnt++])
  write(fd, &ch, 1);
  else {
    write(fd, "*", 1);
    errcnt++;
  }
}

printf("\n다음 문장을 그대로 입력하세요.\n%s\n", text1);
while ((nread=read(fd1, &ch1, 1)) > 0 && ch1 != '\n') {
  if (ch1 == text1[cnt++])
  write(fd1, &ch1, 1);
  else {
    write(fd1, "*", 1);
    errcnt++;
  }
}

printf("\n다음 문장을 그대로 입력하세요.\n%s\n", text2);
while ((nread=read(fd2, &ch2, 1)) > 0 && ch2 != '\n') {
  if (ch2 == text2[cnt++])
  write(fd2, &ch2, 1);
  else {
    write(fd2, "*", 1);
    errcnt++;
  }
}




printf("\n타이핑 오류의 횟수는 %d\n", errcnt);
time(&time2);
typing(time1,time2);

tcsetattr(fd, TCSANOW, &init_attr);
tcsetattr(fd1, TCSANOW, &init_attr);
tcsetattr(fd2, TCSANOW, &init_attr);
close(fd);
close(fd1);
close(fd2);

}
