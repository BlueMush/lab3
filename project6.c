#include<stdio.h>
#include<fcntl.h>
#include<dirent.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<time.h>
#include<sys/types.h>
#include<grp.h>
#include<pwd.h>
 
void fatal(char *);
void print_filename(char *);
void print_fileformat(int);
void print_filetime(time_t);
void print_filesize(off_t);
void print_inode(ino_t);
void print_gid(gid_t);
void print_uid(uid_t);
void print_linkcnt(nlink_t);
void print_type(mode_t);
void print_per(mode_t);
int main(int argc,char *argv[])
{
        void fatal(char*);
        DIR *dir;
        char file[BUFSIZ+1];
        struct dirent *directory;
        struct stat file_stat;
        if(argc!=2)
        {
                printf("Usage: lsp directory_name");
                exit(0);
        }
        if((dir=opendir(argv[1]))==NULL)
                        fatal("open error");
        while(directory=readdir(dir))
        {
                if(strcmp(directory->d_name,".")==0||strcmp(directory->d_name,"..")==0)
                        continue;
                if(directory->d_ino==0)
                        continue;
                sprintf(file,"%s/%s",argv[1],directory->d_name);
                if(lstat(file,&file_stat)<0)
                        fatal("latat error");
                print_inode(file_stat.st_ino);          //inode
                print_type(file_stat.st_mode);          //파일타입
                print_per(file_stat.st_mode);  //권한보기
                print_linkcnt(file_stat.st_nlink);      //링크수
                print_uid(file_stat.st_uid);            //유저아이디
                print_gid(file_stat.st_gid);            //그룹아이디
                print_filesize(file_stat.st_size);      //파일사이즈
                print_filetime(file_stat.st_mtime);     //파일접근시간
                print_filename(directory->d_name);      //파일명
                print_fileformat(file_stat.st_mode);    //파일포맷
                putchar('\n');
        }
        closedir(dir);
        return 0;
}
void print_per(mode_t pmode)
{
        /////Usr permission//////////
        if(pmode&S_IRUSR)
                putchar('r');
        else
                putchar('-');
        if(pmode&S_IWUSR)
                putchar('w');
        else
                putchar('-');
        if(pmode&S_IXUSR)
                putchar('x');
        else
                putchar('-');
        ////Group permission////////
         if(pmode&S_IRGRP)
                putchar('r');
         else
                putchar('-');
         if(pmode&S_IWGRP)
                 putchar('w');
         else
                 putchar('-');
         if(pmode&S_IXGRP)
                 putchar('x');
         else
                 putchar('-');
        ////Other permission////////
        if(pmode&S_IROTH)
                putchar('r');
        else
                putchar('-');
        if(pmode&S_IWOTH)
                putchar('w');
        else
                putchar('-');
        if(pmode&S_IXOTH)
                putchar('x');
        else
                putchar('-');
}
void print_type(mode_t mmode)
{
        printf("  ");
        if(S_ISREG(mmode))
                putchar('-');
        else if(S_ISDIR(mmode))
                putchar('d');
        else if(S_ISCHR(mmode))
                putchar('c');
        else if(S_ISBLK(mmode))
                putchar('b');
        else if(S_ISFIFO(mmode))
                putchar('p');
        else if(S_ISLNK(mmode))
                putchar('l');
        else if(S_ISSOCK(mmode))
                putchar('s');
}
void print_uid(uid_t uid)
{
        struct passwd *uuid=(struct passwd*)malloc(sizeof(struct passwd));
        uuid=getpwuid(uid);
        printf("  %s",uuid->pw_name);
}
void print_linkcnt(nlink_t lcnt)
{
        printf("  %d",lcnt);
}
void print_gid(gid_t gid)
{
        struct group* grp=(struct group*)malloc(sizeof(struct group));
        grp=getgrgid(gid);
        printf("  %s",grp->gr_name);
}
void print_inode(ino_t inonum)
{
        printf("%-10ld",inonum);
}
void print_filesize(off_t sz)
{
        printf("%10ld",sz);
}
void print_filetime(time_t ttime)
{
        struct tm *tm_ptr;
        tm_ptr=localtime(&ttime);
        printf("  ");
        printf("%02d월 %02d %02d:%02d",tm_ptr->tm_mon+1,tm_ptr->tm_mday,tm_ptr->tm_hour,tm_ptr->tm_min);
}
void print_fileformat(int st_mode)
{
        switch(st_mode&S_IFMT)
        {
                case S_IFDIR:
                        putchar('/');
                        break;
                case S_IFIFO:
                        putchar('|');
                        break;
                case S_IFLNK:
                        putchar('@');
                        break;
        }
        if((st_mode&S_IFMT)==S_IFREG)
                if(st_mode&S_IEXEC)
                {
                        putchar('*');
                }
}
void print_filename(char *s)
{
        printf("\t%s",s);
}
void fatal(char *error_name)
{
        perror(error_name);
}
