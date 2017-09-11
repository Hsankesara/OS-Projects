#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<sys/types.h>
#include<dirent.h>
//prototype of the function needs to be defined above 
int Isinteractive(char *dir);
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
    //checking whether the directory is empty or non empty
	while(d=readdir(directory)!=NULL){
		
		if(++n>2)
			break;
    }
	//if directory is null
	if(directory == NULL){
			printf("directory does not exists\n");
			exit(0);
    }
    //if directory is empty
    else if(n<=2){
			rmdir(dir);
    }
    //if directory is non empty,then gives error
    else{
			printf("error deleting directory\n");
            exit(0);

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
	chdir(path);
	// error handling required
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
	//finally it makes the directory empty and deletes the directory the directory itself

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

 // function to check whether the given entry is a file or directory
int Isinteractive(char *dir){
   //creates a directory by using inbuilt opendir function
	DIR *directory = opendir(dir);
	struct dirent *d;
	int n=0;
    //checking if directory is empty or not by reading the directory using rmdir function
	while(d=readdir(directory)!=NULL){
	  //if n is greater than 2 ,leaves the loop
		if(++n>2)
			break;
    }
    //empty directory
    if(n<=2){
    	
        rmdir(dir);
    
    }
     //if directory does not exists
    else if(directory == NULL){
		printf("directory does not exists\n");
	
		exit(0);
    }
       
     else{
			printf("are u sure u want to delete this non empty directory(y/n)?");
			char ch;
			scanf("%c",&ch);
			
			//if y , then call the function
			if(ch == 'y'){
				nonemptydirectoryrecursively(dir);
            }
            //else return
			else if(ch == 'n'){
     
				return 0;
            } // no other tags included
			else{
				printf("invalid character\n");
            }
    }
	return 0;
      
}
