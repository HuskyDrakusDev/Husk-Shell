/***********************************************\
*	Husk Command Shell V 0.0.1		*
*	Sean Vactor				*
*						*
*	10/25/2017				*
*						*
*	credit to Stephen Brennan for help	*
\***********************************************/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void shellLoop();
char *shellReadLine();
char **shellSplitLine(char *line);
int shellLaunch(char ** args);

/*
 * Number of chars allowed in a single command
 * before realloc is needed to expand buffer.
 */
const int RL_BUFFER_SIZE = 100;

/*
 * Number of tokens allowed in a single command
 * before realloc is needed to expand buffer.
 * NOTE: the tokens buffer will be null terminated,
 * so for a buffer size of 7, only 6 tokens can fit,
 * plus a null.
 */
const int TOKEN_BUFFER_SIZE = 7;

/*
 * Set of chars that delimit tokens in a command.
 */
const char TOKEN_DELIM[9] = " \t\r\n\a";


/*
 * Main function.
 */
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
			if(buffer == NULL) {
				fprintf(stderr, "husk: allocation error (r line buffer)\n");
				exit(EXIT_FAILURE);
			}
		}
	
	}
	
	return(buffer);
}

char **shellSplitLine(char *line) {

	/* size of the tokens buffer */
	int bufferSize = TOKEN_BUFFER_SIZE;
	int pos = 0;

	/* array of tokens (will be null terminated) */
	char **tokens = malloc(bufferSize * sizeof(char*));
	
	/* a string to store each token as line is tokenized */
	char *token;
	
	/* test for malloc failure */
	if (tokens == NULL) {
		fprintf(stderr, "husk: allocation error (m token buffer)\n");
		exit(EXIT_FAILURE);
	}
	
	/*
	 * First call to strtok, line is passed, since we want
	 * to tokenize the string passed to shellSplitLine.
	 * This also gets the first token in line.
	 */
	token = strtok(line, TOKEN_DELIM);
	
	/* loop until strtok returns NULL, indicating no more tokens */
	while (token != NULL) {
	
		tokens[pos] = token;
		pos += 1;
		
		if(pos >= bufferSize) {
		
			bufferSize += TOKEN_BUFFER_SIZE;
			tokens = realloc(tokens, bufferSize * sizeof(char*));
			if(tokens == NULL) {
				fprintf(stderr, "husk: allocation error (r token buffer)\n");
				exit(EXIT_FAILURE);
			}
		}
		
		/* get the next token from line */
		token = strtok(NULL, TOKEN_DELIM);	
	}
	
	/* null terminate the tokens buffer */	
	tokens[pos] = NULL;
	return(tokens);
}

int shellLaunch(char ** args) {

}
