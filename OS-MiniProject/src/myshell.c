#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include "cd.h"	
#include "ls.h"
#include "mkdir.h"
#include "rmdir.h"
#include "pwd.h"
/*
Unix Shell interface 
*/
#define clear() printf("\033[H\033[J")
#define BLUE	"\x1b[34m"
#define GREEN	"\x1b[32m"
#define CYAN	"\x1b[36m"
#define RESET	"\x1b[0m"
#define RED		"\x1b[31m"
#define MAGENTA	"\x1b[35m"
struct base	
{
	//for taking string input from user and divide them into those character arrays.
	char *command;	//stores command insert by user
	char *tags;		//stores tags i.e -l -e etc if inserted
	char *dir;		//stores directory if inserted
};
struct base parse_string(char * str){
	/*
	parse string basically returns base structure
	which contains parsed string.
	It splits the string and divide into structure accordingly
	*/
	struct base line = {NULL, NULL, NULL};	//Initialize structure with NULL
	char *output = strtok(str, " "); //splits the string and stores each part in buffer, the we can call buffer string by string
	if (output ==NULL){
		// If first output is NULL means user only presses enter button
		return line;
	}
	line.command = (char *) malloc(sizeof(char) * strlen(output));	// Assign some memory to line.command
	strcpy(line.command, output);	//store command given by user
	output = strtok (NULL, " ");		//just to jump from one substring to another
	if(output == NULL){	// if next substring is null i.e no tags and no directory
		//printf("%s\n",line.dir );
		return line;	// if now output it NULL then it have no tag or directory
	}
	char *temp = malloc(sizeof(char) * strlen(output));	// Assign some memory to tag
	strcpy(temp, output);	// copy output to temp to decide whether it is tag or directory
	// checking whether tag exist or not. 
	if(temp[0] == '-') {
		// to check tag i have to check whether first char of output in hyphen or not
		line.tags = (char *)malloc(sizeof(char)*strlen(output));	// Assign memory to line.tags
		strcpy(line.tags, output);	// copy output to line.tags
		output= strtok (NULL, " ");	// push next string from buffer
	}
	else{
			line.tags = NULL;	// if tag does not exist then line.tags is NULL
	}
	// stores directory given by user
	free(temp);	// freeing temp
	temp = NULL;// assign temp to NULL	
	if(output != NULL){
		line.dir = (char *)malloc(sizeof(char)*strlen(output)); // Assign some memory to line.dir
		strcpy(line.dir, output);	// copy output to line.dir
		output= strtok (NULL, " ");	//  push next string from buffer just to clear buffer
	}
	else{
		line.dir = NULL;
	}
	return line;
}

int main() {
	char curr_dir[1000];	// stores current directory
	char arg[10000];		// stores user input
	do{
		getcwd(curr_dir, sizeof(char) * 100);	//return current directory and saved it in curr_dirr
		printf(GREEN"bash:", curr_dir);
		printf(BLUE"%s$ ", curr_dir);
		printf(RESET);
		scanf("\n"); 	// Just to ignore '\n' input
		scanf ("%[^\n]%*c", arg);	//for scanning the whole string
		struct base command_line = {NULL, NULL, NULL}; // initialize structure with NULl
		command_line = parse_string(arg);	// function call which returns appropriate structure
		switch(command_line.command[0]){
			// swich case to determine what was the command user typed.
			// And do appropriate job using that command
			case 'l':
				if(strcmp("ls",command_line.command) == 0){
					if(command_line.tags == NULL){
						ls(command_line.dir);
					}	
					else if(strcmp(command_line.tags,"-a") == 0){
						lsa(command_line.dir);
					}
					else if(strcmp(command_line.tags,"-l") == 0){
						lsl(command_line.dir);
					}
					else{
						printf(RED "%s does not exist please try -l or -a\n",command_line.tags);
						printf(RESET);
					}
				}
				else{
					printf(RED "Sorry command does not found\nplease try from cd, ls, mkdir, rmdir, pwd and exit commands\n" RESET);
				}
				break;
			case 'm':
				if(strcmp("mkdir",command_line.command) == 0){
					if(command_line.tags == NULL && command_line.dir != NULL)
						make_dir(command_line.dir);
					else{
						printf(RED "Invalid command try \"mkdir DIRECTORY_NAME\"\n" RESET);
					}
				}
				else{
					printf(RED"Sorry command does not found\nplease try from cd, ls, mkdir, rmdir, pwd and exit commands\n"RESET);
				}
				break;
			case 'r':
				if(strcmp("rmdir",command_line.command) == 0){
					if(command_line.tags == NULL && command_line.dir != NULL){
						emptydirectory(command_line.dir);
					}
					else if(command_line.dir == NULL){
						printf(RED"please insert directory\n"RESET);
					}
					else if(strcmp(command_line.tags,"-r") == 0){
						nonemptydirectoryrecursively(command_line.dir);
					}
					else{
						printf(RED"Invalid Tag please use -r\n"RESET);		
					}
				}
				else{
					printf(RED"Sorry command does not found\nplease try from cd, ls, mkdir, rmdir, pwd and exit commands\n"RESET);
				}
				break;
			case 'c':
				if(strcmp("cd",command_line.command) == 0){
					if(command_line.tags == NULL && command_line.dir != NULL){
						if(strcmp(command_line.dir,"~") == 0){
							cd_t();
						}
						else{
							cd(command_line.dir);
						}
					}
					else if(command_line.dir == NULL){
						printf(RED "please insert directory\n" RESET);
					}
					else if(strcmp(command_line.tags, "-e") == 0){
						cd_e(command_line.dir);
					}
					else{
						printf(RED"%s does not exist please try -e\n",command_line.tags );
						printf(RESET);
					}
				}
				else if(strcmp(command_line.command,"cls") == 0){
					clear();
				}
				else{
					printf(RED"Sorry command does not found\nplease try from cd, ls, mkdir, rmdir, pwd and exit commands\n"RESET);
				}
				break;
			case 'p':
				if(strcmp("pwd",command_line.command) == 0){
					if(command_line.tags == NULL && command_line.dir == NULL){
						pwd();
					}
					else{
						printf(RED"invalid format, please write \"pwd\" only\n"RESET);
					}
				}
				else{
					printf(RED"Sorry command does not found\nplease try from cd, ls, mkdir, rmdir, pwd and exit commands\n"RESET);
				}
				break;
			case 'e':
				if (strcmp("exit", command_line.command) != 0){
					printf(RED"Sorry command does not found\nplease try from cd, ls, mkdir, rmdir, pwd and exit commands\n"RESET);
				}
				else if(command_line.tags != NULL || command_line.dir !=  NULL){
					printf(RED"Use valid command\n"RESET);
				}

				break;
			default :
				printf(RED"Sorry command does not found\nplease try from cd, ls, mkdir, rmdir, pwd, cls and exit commands\n"RESET);
		}
		// Free all the struct pointer
		// And then declare them NULL
		// Just to be on a safe side
		free(command_line.command);
		command_line.command = NULL;
		free(command_line.tags);
		command_line.tags = NULL;
		free(command_line.dir);
		command_line.dir = NULL;
	} while(strcmp(arg,"exit")!=0);

	return 0;
}
