//Implementing cd Command in C

#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

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
 