
//Implementing cd Command in C

#include<unistd.h>

#include<stdio.h>

#include<string.h>

#include<stdlib.h>

#include<sys/types.h>

#include<pwd.h>



void cd(char cd_dir[]) {



	// chdir command is used to make cd_dir as the present directory

	 int n = chdir(cd_dir);

	 if( n == 0 )

	 	//If directory exists and is changed succesfully

		 printf("Current Directory: %s\n",cd_dir);

	 else

	 	//If directory doesn't exist

		 printf("bash: cd: cn: No such file or directory\n");

 }

 //the current working directory cannot be determined successfully, exit with a non-zero status



void cd_e(char cd_dir[]) {

 

	 int n = chdir(cd_dir);

	 if( n == 0 )

	 	//If directory exists and is changed succesfully

		 printf("Current Directory: %s\n",cd_dir);

	 else

	 	////If directory doesn't exist

	 {

		printf("bash: cd: cn: No such file or directory\n");

		exit(1); // exits with a non zero status

	 }

 }

 

void cd_t() {

	//getenv searches for the environment string pointed to by name and returns the associated value to the string

	char *homedir = getenv("HOME");
	//uid_t is an integer data type used to represent group IDs
        uid_t uid = getuid();
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
