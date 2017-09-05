#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void cd(char cd_dir[]) {
	
	 int n = chdir(cd_dir);
	 if( n == 0 )
		 printf("Current Directory: %s\n",cd_dir);
	 else
		 printf("bash: cd: cn: No such file or directory\n");
 }
 
void cd_e(char cd_dir[]) {
 
	 int n = chdir(cd_dir);
	 if( n == 0 )
		 printf("Current Directory: %s\n",cd_dir);
	 else
	 {
	printf("bash: cd: cn: No such file or directory\n");
		 exit(1);
	 }
 }
 


int main() {
	char cd_dir[100] ;
 	scanf("%s",cd_dir);
 	cd(cd_dir);  
 	return(0);
}
