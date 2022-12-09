#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/sem.h>
#define SHMSIZE 1024
#define SHMKEY (key_t)0111
#define SEMKEY (key_t)0111

static int sem;

union semapore{
	int value;
	struct sem_ds *buf;
	unsigned short int *array;
};

static int sem;

int parent_process_read(char *filename){
	int shm, len;
	void *shmaddr;
	FILE *fp = fopen(filename, "r");
	int size = strlen((char *)shmaddr);

	printf("parent process start.\n");
	sleep(3);
	if((shm = shmget(SHMKEY, SHMSIZE, IPC_CREAT|0666)) == -1) {
		perror("shmget failed");
		exit(1);
	}
	if((shmaddr = shmat(shm, NULL, 0)) == (void *)-1) {
		perror("shmat failed");
		exit(1);
	}

	fgets((char *)shmaddr, size, fp);

	if(shmdt(shmaddr) == -1){
		perror("shmdt failed");
		exit(1);
	}

	printf("read Success\n");
	fclose(fp);
	printf("parent process finish. \n");
}

int child_process(char *filename){
	int shm,len;
	void *shmaddr;
	FILE *fp = fopen(filename, "w");

	printf("child process start. \n");
	sleep(2);

	if((shm = shmget(SHMKEY, SHMSIZE,IPC_CREAT|0666)) == -1){
		perror("shmget failed");
		exit(1);
	}
	if((shmaddr = shmat(shm, NULL, 0)) == (void *)-1){
		perror("shmat failed");
		exit(1);
	}

	fputs((char *)shmaddr, fp);
	printf("copy Success \n");

	if(shmdt(shmaddr) == -1){
		perror("shmdt failed");
		exit(1);
	}
	if(shmctl(shm, IPC_RMID, 0) == -1){
		perror("shmctl failed");
		exit(1);
	}
	fclose(fp);
	printf("child process finish. \n");
}

int main(int argc, char **argv){
	FILE *fp;
	union semapore semapore;

	struct sembuf mysem_open = {0,-1, SEM_UNDO};



	struct sembuf mysem_close = {0,1, SEM_UNDO};

	if(argc !=3){
		fprintf(stderr, "Using : %s <original file name> <create file name>\n", 	argv[0]);
		exit(1);
	}

	sem = semget((key_t)234, 1, 0660|IPC_CREAT);

	if(sem == -1){
		perror("semget error");
		exit(0);
	}
	semapore.value = 1;

	if(semctl(sem, 0, SETVAL, semapore) == -1){
		perror("semctl error");
		exit(1);
	}
	if(semop(sem, &mysem_open, 1) == -1){
		perror("semop error");
		exit(0);
	}
	if((fp = fopen(argv[1], "r+")) == NULL){
		perror("fopen error");
		exit(0);
	}
	parent_process_read(argv[1]);
	rewind(fp);

	sleep(2);

	child_process(argv[2]);
	fclose(fp);

	semop(sem, &mysem_close, 1);
	printf("check your %s file.\n", argv[2]);

	return 0;
}


