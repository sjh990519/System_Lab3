#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#define BUF_SIZE 512 

char ex_1[BUF_SIZE] = "How many times do I have to say?";
char ex_2[BUF_SIZE] = "Would you mind sending me the program draft you mentioned?";
char ex_3[BUF_SIZE] = "I’m afraid we need to delay our meeting. ";

int main(){
    time_t start_time, end_time;
    char a[20];
    char buffer[BUF_SIZE]; // 타자수 확인 버퍼
    char buf_1[BUF_SIZE]; // 파일 입력 버퍼
    char buf_2[BUF_SIZE]; // 파일 입력 버퍼
    char buf_3[BUF_SIZE]; // 파일 입력 버퍼
    int wrong_count=0;
    int n;
    int filedes;
    int fd;
    int sum = 0;
    double total = 0;

    //시작
    printf("\n         [ 타자 연습 프로그램 ] \n");
    printf("             Start -> (Enter) \n");
    gets(a);
    start_time = time(NULL);

    // 주어진 문장 입력 
    fprintf(stderr, "\n%s\n", ex_1);
    gets(buf_1);

    fprintf(stderr,"\n%s\n", ex_2);
    gets(buf_2);

    fprintf(stderr, "\n%s\n", ex_3);
    gets(buf_3);
    end_time = time(NULL);


    // 걸린 시간
    total = difftime(end_time, start_time);

    // 입력한 타이핑 전체 글자수
    sum = strlen(buf_1) + strlen(buf_2) + strlen(buf_3);
    sum /= total/60; 

    // 오타 체크
    for(int i = 0; i < strlen(ex_1); i++) if(buf_1[i] != ex_1[i]) wrong_count++;
    for(int i = 0; i < strlen(ex_2); i++) if(buf_2[i] != ex_2[i]) wrong_count++;
    for(int i = 0; i < strlen(ex_3); i++) if(buf_3[i] != ex_3[i]) wrong_count++;
    

    printf("타이핑 오류 횟수: %d\n",wrong_count); 
    printf("분당 타자수: %ld\n", sum);
    printf("총 걸린시간: %f\n", total);

    exit(0);

    return 0;
}
