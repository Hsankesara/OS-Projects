//Implementing cd Command in C

#include<unistd.h>

#include<stdio.h>

#include<string.h>

#include<stdlib.h>

#include<sys/types.h>

#include<pwd.h>

#define RESET	"\x1b[0m"
#define RED		"\x1b[31m"

void cd(char cd_dir[]) {



	// chdir command is used to make cd_dir as the present directory

	 int n = chdir(cd_dir);

	 if( n != 0 )

		//If directory doesn't exist

		printf(RED"bash: cd: cn: No such file or directory\n"RESET);


 }

 //the current working directory cannot be determined successfully, exit with a non-zero status
void cd_e(char cd_dir[]) {

 

	 int n = chdir(cd_dir);

	 if( n != 0 ){

		printf(RED"bash: cd: cn: No such file or directory\n"RESET);
		exit(1); // exits with a non zero status
	 }
 }

void cd_t() {

	//getenv searches for the environment string pointed to by name and returns the associated value to the string

	char *homedir = getenv("HOME");
	//uid_t is an integer data type used to represent group IDs
	//getuid() returns the real user ID of the calling process
        uid_t uid = getuid();
    //The getpwuid() function shall search the user database for an entry with a matching uid
        struct passwd *pw = getpwuid(uid);
        if (pw == NULL) {
                printf("Failed\n");
                exit(EXIT_FAILURE);
        }
        //Prints the home directory with username
        printf("%s\n", pw->pw_dir);
        //Set current directory as /home/<username>
        cd(pw->pw_dir);

 }	

 