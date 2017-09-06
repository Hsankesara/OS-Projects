#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
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
	struct base line;
	char *output = strtok(str, " "); //splits the string
	while(output != NULL){
		bool istag = false;	//for knowing whether or not tag exist
		line.command = (char *) malloc(sizeof(char) * strlen(output));
		strcpy(line.command, output);	//store command given by user
		output= strtok (NULL, " ");		//just to jump from one substring to another
		if(output == NULL)	// if next substring is null i.e no tags and no directory
			return line;
		char *temp = malloc(sizeof(char) * strlen(output));
		strcmp(output, temp);
		// cheacking whether tag exist or not. 
		if(temp[0] == "-") {
			istag = true;
			line.tags = (char *)malloc(sizeof(char)*strlen(output));
			strcpy(line.tags, output);
			output= strtok (NULL, " ");
		}
		else{
			line.tags = NULL;
		}
		// stores directory given by user
		line.dir = (char *)malloc(sizeof(char)*strlen(output));
		strcpy(line.dir, output);
		output= strtok (NULL, " ");
	}
	return line;
}

int main() {
	char curr_dir[100];
	getcwd(curr_dir, sizeof(char) * 100);	//return current directory and saved it in curr_dirr
	char arg[1000];
	do{
		printf("bash@%s$", curr_dir);
		scanf ("%[^\n]%*c", arg);	//for scanning the whole string
		struct base command_line = parse_string(arg);
		switch(command_line.command[0]){
			// swich case to determine what was the command user typed.
			// And do appropriate job using that command
			case 'l':
				if(strcmp("ls",command_line.command) == 0){
					printf("ls command\n");
				}
				else{
					printf("Sorry command does not found\nplease try from cd, ls, mkdir, rmdir, pwd and exit commands\n");
				}
				break;
			case 'm':
				if(strcmp("mkdir",command_line.command) == 0){
					printf("mkdir command\n");
				}
				else{
					printf("Sorry command does not found\nplease try from cd, ls, mkdir, rmdir, pwd and exit commands\n");
				}
				break;
			case 'r':
				if(strcmp("rmdir",command_line.command) == 0){
					printf("rmdir command\n");
				}
				else{
					printf("Sorry command does not found\nplease try from cd, ls, mkdir, rmdir, pwd and exit commands\n");
				}
				break;
			case 'c':
				if(strcmp("cd",command_line.command) == 0){
					printf("cd command\n");
				}
				else{
					printf("Sorry command does not found\nplease try from cd, ls, mkdir, rmdir, pwd and exit commands\n");
				}
				break;
			case 'p':
				if(strcmp("pwd",command_line.command) == 0){
					printf("pwd command\n");
				}
				else{
					printf("Sorry command does not found\nplease try from cd, ls, mkdir, rmdir, pwd and exit commands\n");
				}
			case 'e':
				break;
			default :
				printf("Sorry command does not found\nplease try from cd, ls, mkdir, rmdir, pwd and exit commands\n");
		}
	} while(strcmp(arg,"exit")!=0);

	return 0;
}