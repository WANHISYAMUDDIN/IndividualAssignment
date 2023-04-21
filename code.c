#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void sigint_handler(int sig){
	printf("interruption\n");
	exit(EXIT_SUCCESS);
}

int main(void){
	void sigint_handler(int sig);

	int pipefds[2];
	char space[200];
	char enter[200];

	pipe(pipefds);

	pid_t pid = fork();

	if(pid==0){

		for(int i=0;i<3;i++){
			close(pipefds[1]);
			read(pipefds[0], &space, sizeof(space));
			close(pipefds[0]);
			printf("receive message: %s", space);
		}
	exit(EXIT_SUCCESS);
	}
	else{
		close(pipefds[0]);
		printf("Enter input: ");
		fgets(enter, sizeof(enter), stdin);
		write(pipefds[1], &enter, sizeof(enter));
		close(pipefds[1]);
		wait(NULL);
	}
	return EXIT_SUCCESS;
}
