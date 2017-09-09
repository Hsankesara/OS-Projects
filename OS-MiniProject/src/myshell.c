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
	struct base line = {NULL, NULL, NULL};
	char *output = strtok(str, " "); //splits the string
	line.command = (char *) malloc(sizeof(char) * strlen(output));
	strcpy(line.command, output);	//store command given by user
	output = strtok (NULL, " ");		//just to jump from one substring to another
	if(output == NULL){	// if next substring is null i.e no tags and no directory
		//printf("%s\n",line.dir );
		return line;
	}
	char *temp = malloc(sizeof(char) * strlen(output));
	strcpy(temp, output);
	// cheacking whether tag exist or not. 
	if(temp[0] == '-') {
		line.tags = (char *)malloc(sizeof(char)*strlen(output));
		strcpy(line.tags, output);
		printf("%s\n", line.tags);
		output= strtok (NULL, " ");
	}
	else{
			line.tags = NULL;
	}
	// stores directory given by user
	if(output != NULL){
		line.dir = (char *)malloc(sizeof(char)*strlen(output));
		strcpy(line.dir, output);
		output= strtok (NULL, " ");
	}
	else{
		line.dir = NULL;
	}
	return line;
}

int main() {
	char curr_dir[100];
	char arg[1000];
	do{
		getcwd(curr_dir, sizeof(char) * 100);	//return current directory and saved it in curr_dirr
		printf("bash@%s$", curr_dir);
		scanf ("%[^\n]%*c", arg);	//for scanning the whole string
		struct base command_line = {NULL, NULL, NULL};
		command_line = parse_string(arg);
		printf("%s %s %s\n",command_line.command, command_line.tags, command_line.dir);
		switch(command_line.command[0]){
			// swich case to determine what was the command user typed.
			// And do appropriate job using that command
			case 'l':
				if(strcmp("ls",command_line.command) == 0){
					if(command_line.tags == NULL){
						ls();
					}
					else if(strcmp(command_line.tags,"-a") == 0){
						lsa();
					}
					else if(strcmp(command_line.tags,"-l") == 0){
						lsl();
					}
					else{
						printf("%s does not exist please try -l or -a\n",command_line.tags );
					}
				}
				else{
					printf("Sorry command does not found\nplease try from cd, ls, mkdir, rmdir, pwd and exit commands\n");
				}
				break;
			case 'm':
				if(strcmp("mkdir",command_line.command) == 0){
					if(command_line.tags == NULL && command_line.dir != NULL)
						make_dir(command_line.dir);
					else{
						printf("Invalid command try \"mkdir DIRECTORY_NAME\"\n");
					}
				}
				else{
					printf("Sorry command does not found\nplease try from cd, ls, mkdir, rmdir, pwd and exit commands\n");
				}
				break;
			case 'r':
				if(strcmp("rmdir",command_line.command) == 0){
					if(command_line.tags == NULL){
						//Create rmdir method for non empty file
					}
					else if(strcmp(command_line.tags, "-i") == 0){
						is_interactive(command_line.dir);
					}
					else if(strcmp(command_line.tags,"-r") == 0){
						nonemptydirectoryrecursively(command_line.dir);
					}
				}
				else{
					printf("Sorry command does not found\nplease try from cd, ls, mkdir, rmdir, pwd and exit commands\n");
				}
				break;
			case 'c':
				printf("1\n");
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
						printf("please insert directory\n");
					}
					else if(strcmp(command_line.tags, "-e") == 0){
						cd_e(command_line.dir);
					}
					else{
						printf("%s does not exist please try -e\n",command_line.tags );
					}
				}
				else{
					printf("Sorry command does not found\nplease try from cd, ls, mkdir, rmdir, pwd and exit commands\n");
				}
				break;
			case 'p':
				if(strcmp("pwd",command_line.command) == 0){
					if(command_line.tags == NULL && command_line.dir == NULL){
						pwd();
					}
					else{
						printf("invalid format, please write \"pwd\" only\n");
					}
				}
				else{
					printf("Sorry command does not found\nplease try from cd, ls, mkdir, rmdir, pwd and exit commands\n");
				}
			case 'e':
				break;
			default :
				printf("Sorry command does not found\nplease try from cd, ls, mkdir, rmdir, pwd and exit commands\n");
		}
		
		free(command_line.command);
		command_line.command = NULL;
		free(command_line.tags);
		command_line.tags = NULL;
		free(command_line.dir);
		command_line.dir = NULL;
	} while(strcmp(arg,"exit")!=0);

	return 0;
}