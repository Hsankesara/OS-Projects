#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<sys/types.h>
#include<dirent.h>
#define RESET	"\x1b[0m"
#define RED		"\x1b[31m"
#define BLUE	"\x1b[34m"
//prototype of the function needs to be defined above 
void Isinteractive(char *dir);
void nonemptydirectoryrecursively(char *dir);
int isfile(char *filename);
int emptydirectory(char *dir);



//argc-counts the no of lines till the input is taken
//argv-stores the input in form of an array


int emptydirectory(char *dir){
     //opens the directory
	DIR *directory = opendir(dir);
	struct dirent *d;
	int n=0;

	//if directory is null
    if(directory == NULL){
    	printf(RED"directory does not exists\n"RESET);
    	return 0;
    }
    //checking whether the directory is empty or non empty
	while((d = readdir(directory))!=NULL){
		
		if(++n>2)
			break;
    }
    //if directory is empty
    if(n<=2){
		rmdir(dir);
    }
    //if directory is non empty,then gives error
    else{
		printf(RED"error deleting directory\n"RESET);
        return -1;

	}
	return 0;        
}
       
// function for deleting a non empty directory 
void nonemptydirectoryrecursively(char *dir){
	DIR *dirname;	
	struct dirent **entry;
	char *path = dir;
	int count = 0;
	//counts the no of files and directory in a given directory 
	//using the scandir function
	count = scandir(dir, &entry, NULL, alphasort); 
	//changes the path of directory after every recursive call         
	int n = chdir(path);
	if( n != 0 ){
		//If directory doesn't exist
		printf(RED"bash: cd: cn: No such file or directory\n"RESET);
		return;
	}

	for(int i=0;i<count;i++){
	   //checks whether the given entry is a file or a directory
		if(isfile(entry[i]->d_name) == 0){
		    //recursive call to get into the directory
			nonemptydirectoryrecursively(entry[i]->d_name);
		}
		else{
		    //removes or deletes if the entry is a file using remove function
            remove(entry[i]->d_name);
       	}
	}
	//finally it makes the directory empty and deletes the directory itself

	chdir("..");
	rmdir(path);
}
 //function to check whether the given entry is a file or directory
int isfile(char *filename){
     //creates a directory
	DIR* directory = opendir(filename);
    // considers filenames ".",".." as a directory 
	if(directory!=NULL&&strcmp(filename,".")!=0&&strcmp(filename,"..")!=0){
    // close the directory stream
     closedir(directory);
      return 0;
    }//if the given entry is a file
	else if(errno == ENOTDIR){

      return 1;
    }
   
   //if it is not a file or a directory
	else {
      return -1;
  } 
}