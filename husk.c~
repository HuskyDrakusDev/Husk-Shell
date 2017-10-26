/***************************************\
*	Husk Command Shell V 0.0.1	*
*	Sean Vactor			*
*					*
*	10/25/2017			*
*					*
*	credit to brennan.io for help	*
*					*
\***************************************/


#include <stdlib.h>
#include <stdio.h>

void shellLoop();
char *shellReadLine();
char **shellSplitLine(char *line);

const int RL_BUFFER_SIZE = 100;

int main(int argc, char **argv) {


	shellLoop();

	exit(EXIT_SUCCESS);
}

void shellLoop() {

	char *line;
	char **args;
	int status = 0;
	
	do {
	
		printf("husk:$ ");	
		line = shellReadLine();
		args = shellSplitLine(line);
		status = shellExecute(args);
		
		/* free the line buffer created by malloc in shellReadLine() */
		free(line);
		free(args);
	
	} while (status);
	
	return;
}

char *shellReadLine() {

	int bufferSize = RL_BUFFER_SIZE;
	int pos = 0;
	char *buffer = malloc(sizeof(char) * bufferSize);
	int c;
	int done = 0; /* flag for exiting loop */
	
	if(buffer == 0) {
		fprintf(stderr, "husk: allocation error (m line buffer)\n");
		exit(EXIT_FAILURE);
	}
	
	while (!done) {
	
		c = getchar();
		
		if (c == EOF || c == '\n') {
			buffer[pos] = '\0';
			done = 1;		
		} else {
			buffer[pos] = c;
		}
		pos += 1;
	
		/* reallocate more buffer space if necessary */
		if (!done && pos >= bufferSize) {
			bufferSize += RL_BUFFER_SIZE;
			buffer = realloc(buffer, bufferSize);
			if(buffer == 0) {
				fprintf(stderr, "husk: allocation error (r line buffer)\n");
				exit(EXIT_FAILURE);
			}
		}
	
	}
	
	return(buffer);
}

char **shellSplitLine(char *line) {

	



}
