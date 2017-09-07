#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<sys/types.h>
#include<dirent.h>


int Isinteractive(char *dir,char *pathname);
void nonemptydirectoryrecursively(char *dir);
int isfile(char *filename);


//argc-counts the no of lines till the input is taken
//argv-stores the input in form of an array
int main(int argc,char *argv[])
{
    //if no input given by user then error arises
    if(argv[1] == NULL){
    
		fprintf(stderr,"out of memory\n");
    
    }
   //if no tag given then simply remove the directory using the inbuilt function rmdir
   // taking the input as pathname
   if(argv[2] == NULL){
     
		char *pathname=argv[1];
		char *dir=pathname;
		rmdir(dir);
   
   }
	else{
		char *pathname=argv[2];
		char *dir=pathname;
		char *tag =argv[1];
      
    // -i is the interactive tag confirming the user to delete the directory ot not
    //if it is not empty
    //compares the tag by the given string 
      if(strcmp(tag, "-i") == 0) {
        
			return Isinteractive(dir,pathname);
        
      }
    //-r  deletes the directory if it is not empty
    // i.e if it contains multiple directories within or multiple files 
    
      else if(strcmp(tag,"-r") == 0){
        
			nonemptydirectoryrecursively(dir);
        
      }
     // no other tags 
      else{
           
			printf("invalid tag\n");
            exit(0); 
     
     }

   }
  
  
  
}
 // function to be called in main
int Isinteractive(char *dir,char *pathname){
   //creates a directory by using inbuilt opendir function
	DIR *directory = opendir(dir);
    
    //if directory is not empty ,it confirms again to delete it or not 
     if(directory!=NULL){
            printf("Are u sure u want to delete the non empty directory(y/n)?");
       
		int a;
		scanf("%s",a);
       
        if(a == "y"){
           
			nonemptydirectoryrecursively(dir);
                
        }
       
       else{
       
			exit(0);
       
       }
    }
       
       //if empty directory then it deletes simply by using rmdir function
    else{
		char *pathname=argv[2];
        char *dir=pathname;
        rmdir(dir);
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
    }
	else if(errno == ENOTDIR){

      return 1;
    }
   
   //if it is not a file or a directory
	else {
      return -1;
  } 
}
