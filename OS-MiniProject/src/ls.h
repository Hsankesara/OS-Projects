#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include<string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#define RESET "\x1b[0m"
#define RED   "\x1b[31m"
#define RESET_COLOR "\e[m"
#define MAKE_GREEN "\e[32m"
#define MAKE_BLUE "\e[36m"
// Define the color codes as macros

int ls(char *path) 					//main ls function.Pass path to the ls fuction.
{
	char *curr_dir = NULL;				//declare curr_dir to store current directory
	DIR *dp = NULL;					//declare directory stream pointer
	struct dirent *dptr = NULL;			//declare directory pointer which will store names of files/directories
	unsigned int count = 0;
	
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	char * initial_path = (char *) malloc(sizeof(cwd));
	strcpy(initial_path, cwd);	// stores initial path for later uses
	if(NULL!=path){
		if(path[0] == '/')
			curr_dir=path;
		else{
			curr_dir = strcat(cwd,"/");
			curr_dir = strcat(curr_dir, path);
		}					//get current directory and check path is given.If path is given change directory to path
	}
	else{
		curr_dir=cwd;
	}
	int n = chdir(curr_dir);
	if(n != 0){
		printf(RED"bash: cd: cn: No such file or directory\n"RESET);
		return -1;
	}
	dp = opendir((const char*)curr_dir);			//open directory stream for reading files/directories
	for(count = 0; NULL != (dptr = readdir(dp)); count++) 
        {
        if(dptr->d_name[0] != '.') 				//read files/directories that does not start with '.' 
        { 
            // Check if the file is executable 
            if(!access(dptr->d_name,X_OK)) 
            { 
                int fd = -1; 	
                struct stat st; 				//declare file descriptor and structure variable st.
  
                fd = open(dptr->d_name, O_RDONLY, 0); 
                if(-1 == fd) 
                { 
                    printf("\n Opening file/Directory failed\n"); 
                    return -1; 
                } 
                 
                fstat(fd, &st); 				//Use fstat function to get details about files.
                // Check if it actaully was a directory with execute 
                // permissions on it. 
                if(S_ISDIR(st.st_mode)) 
                { 
                    // If it was a directory, print it in Blue 
                    printf(MAKE_BLUE"%10s     "RESET_COLOR,dptr->d_name); 
                } 
                else 
                {                                   
                    // If it was a normal executable 
                    // Print it in green 
                    printf(MAKE_GREEN"%10s     "RESET_COLOR,dptr->d_name); 
                } 
                close(fd); 
            } 
            else 
            { 
                // No executable flag ON
                printf("%10s     ",dptr->d_name); 
            } 
          }
	}
	int n2 = chdir(initial_path);
	printf("\n");
	free(initial_path);
	initial_path = NULL;
 return 0;
} 

int lsa(char *path)					//ls -a function.Pass path to the ls fuction.
{
	
	char *curr_dir = NULL;
	DIR *dp = NULL;
	struct dirent *dptr = NULL;			//define current directory,DIRECTORY stream and directory pointer.
	unsigned int count = 0;
	
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	char * initial_path = (char *) malloc(sizeof(cwd));
	strcpy(initial_path, cwd);	// stores initial path for later uses 
	if(NULL!=path)
		{if(path[0] == '/')
			curr_dir=path;
		else{
			curr_dir = strcat(cwd,"/");
			curr_dir = strcat(curr_dir, path);
		}}					//get current directory and check path is given.If path is given change directory to path}
	else
		curr_dir=cwd;				//get current directory and check path is given.If path is given change directory to path
	int n = chdir(curr_dir);
	if(n != 0){
		printf(RED"bash: cd: cn: No such file or directory\n"RESET);
		return -1;
	}
	dp = opendir((const char*)curr_dir);		//open directory stream for reading files/directories
	for(count = 0; NULL != (dptr = readdir(dp)); count++) 
        { 
        { 
            // Check if the file is executable 
            if(!access(dptr->d_name,X_OK)) 
            { 
                int fd = -1; 
                struct stat st; 				//declare file descriptor and structure variable st.
  
                fd = open(dptr->d_name, O_RDONLY, 0); 
                if(-1 == fd) 
                { 
                    printf("\n Opening file/Directory failed\n"); 
                    return -1; 
                } 
                 
                fstat(fd, &st); 					//Use fstat function to get details about files.
                // Check if it actaully was a directory with execute 
                // permissions on it. 
                if(S_ISDIR(st.st_mode)) 
                { 
                    // If it was a directory, print it in Blue 
                    printf(MAKE_BLUE"%10s     "RESET_COLOR,dptr->d_name); 
                } 
                else 
                {                                   
                    // If it was a normal executable 
                    // Print it in green 
                    printf(MAKE_GREEN"%10s     "RESET_COLOR,dptr->d_name); 
                } 
                close(fd); 
            } 
            else 
            { 
                // No executable flag ON 
                // Print it in black(default) 
                printf("%10s     ",dptr->d_name); 
            } 
          }
	}
	int n2=chdir(initial_path);
	printf("\n");
	free(initial_path);
	initial_path = NULL;
 return 0;
} 

int lsl(char *path)
{ 
   	char *curr_dir = NULL; 
   	DIR *dp = NULL; 
   	struct dirent *dptr = NULL; 		//define current directory,DIRECTORY stream and directory pointer.
   	unsigned int count = 0; 
   	long *ptr = NULL; 
   	char cwd2[1024];
   	getcwd(cwd2, sizeof(cwd2));
   	char * initial_path = (char *) malloc(sizeof(cwd2));
	strcpy(initial_path, cwd2);	// stores initial path for later uses
	if(path!=NULL)
		{if(path[0] == '/')
			curr_dir=path;
		else{
			curr_dir = strcat(cwd2,"/");
			curr_dir = strcat(curr_dir, path);
		}}					
	else
		curr_dir = cwd2;	//get current directory and check path is given.If path is given change directory to path
	int n = chdir(curr_dir);
	if(n != 0){
		printf(RED"bash: cd: cn: No such file or directory\n"RESET);
		return -1;
	}
	if(NULL == curr_dir) { 
		printf(RED"\n ERROR : Could not get the working directory\n"RESET); 
		return -1; 
	}
   // Variable to hold number of files inside the directory 
	int num_files = 0; 
	dp = opendir((const char*)curr_dir);   
	// Start reading the directory contents 
	while(NULL != (dptr = readdir(dp))){ 
		// Do not count the files beginning with '.'
		if(dptr->d_name[0] != '.') 
		num_files++; 				//read the files and increase count
	} 
	// Our aim was to count the number of files/folders  
	// inside the current working directory. Since its  
	// done so close the directory. 
	closedir(dp); 
 
	// Restore the values back as we will be using them 
	// later again 
	dp = NULL; 
	dptr = NULL; 
 
	// Check that we should have at least one file/folder 
	// inside the current working directory 
	if(!num_files) { 
	   return 0; 
	} 
	else { 
		// Allocate memory to hold the addresses of the  
		// names of contents in current working directory 
		ptr = malloc(num_files*8); 
		if(NULL == ptr) { 
		   printf(RED"\n Memory allocation failed\n"RESET); 
		   return -1; 
	   } 
		else { 
			// Initialize the memory by zeros 
			memset(ptr,0,num_files*8); 
		} 
	}  
 
	// Open the directory again 
	dp = opendir((const char*)curr_dir);    
	if(NULL == dp) { 
		printf(RED"\n ERROR : Could not open the working directory\n"RESET); 
		free(ptr); 
		return -1; 
	} 
  
	// Start iterating the directory and read all its contents 
	// inside an array allocated above. 
	unsigned int j = 0; 
	for(count = 0; NULL != (dptr = readdir(dp)); count++) { 
		if(dptr->d_name[0] != '.') { 
			ptr[j] = (long)dptr->d_name; 
			j++;  
		} 
	} 
   for(count = 0; count< num_files; count++) { 
		int fd = -1; 
		struct stat st;  
		fd = open((char*)ptr[count], O_RDONLY, 0); 
		if(-1 == fd) { 
		   printf(RED"\n Opening file/Directory failed\n"RESET); 
		   free(ptr); 
		   return -1; 
	   } 
 
	  // Call fstat to get the stat info about the file 
	  if(fstat(fd, &st)) { 
		  // If fstat() fails 
			printf(RED"\n Fstat() failed\n"RESET); 
			close(fd); 
			free(ptr); 
			return -1; 
		} 
 
		//Check st_mode variable in st to check whether it is file or directory.
		if(S_ISDIR(st.st_mode)) { 
			printf("d"); 
		} 
		else {     
			printf("-"); 
		} 
 
		// Check the owner permission 
		mode_t permission = st.st_mode & S_IRWXU; //mode_t stores permission and check if read/write/exec by user
 
		if(permission & S_IRUSR){ 
			printf("r"); 
		} 
		else { 
			printf("-"); 
		} 
 
		if(permission & S_IWUSR) { 
		  printf("w"); 
	  } 
		else { 
			printf("-"); 
		} 
 
	  if(permission & S_IXUSR) { 
			printf("x"); 
		} 
		else { 
			printf("-"); 
		}	 
 
 
	  // CHeck the group permission 
		permission = st.st_mode & S_IRWXG; 
 
		if(permission & S_IRGRP) { 
			printf("r"); 
		} 
		else { 
			printf("-"); 
		} 
 
		if(permission & S_IWGRP) { 
		  printf("w"); 
		} 
		else { 
			printf("-"); 
		} 
 
		if(permission & S_IXGRP) { 
			printf("x"); 
		} 
		else { 
		  printf("-"); 
		} 
 
 
		// CHeck other's permission 
		permission = st.st_mode & S_IRWXO; 

		if(permission & S_IROTH) { 
			printf("r"); 
		} 
		else { 
			printf("-"); 
		} 

		if(permission & S_IWOTH) { 
			printf("w"); 
		} 
		else { 
			printf("-"); 
		} 
		if(permission & S_IXOTH) { 
			printf("x"); 
		} 
		else { 
		  printf("-"); 
		} 
 		//use st to acces number of links to files,user name,group name,size
		// Print the number of hard links 
		printf(" %d ", (int)st.st_nlink); 
 
		// Get the user name 
		struct passwd *pt = getpwuid(st.st_uid); 
		printf("%s ",pt->pw_name); 
 
		// Get the group name 
		struct group *p = getgrgid(st.st_gid); 
		printf("%s ",p->gr_name); 
 
		// Get the file size 
		printf("%lld ",(long long) st.st_size); 
 
		// Get the date and time 
		// Note that some logic is applied here 
		// so as to remove the trailing newline. 
		char date_time[100]; 
		memset(date_time,0,sizeof(date_time)); 
		strncpy(date_time, ctime(&st.st_ctime), sizeof(date_time)); //declare time array and copy time from st_ctime to time.
		int c = 0; 
		while(date_time[c] != '\0') { 
			if(date_time[c] == '\n') 
				date_time[c] = '\0'; 
			c++; 
		} 
		printf("%s ", date_time); 
		// Check if the file/folder is executable. 
		if(!access((const char*)ptr[count],X_OK)) { 
			if(S_ISDIR(st.st_mode)) { 
				// If folder, print in blue 
				printf(MAKE_BLUE"%s\n"RESET_COLOR,(char*)ptr[count]); 
			} 
			else {        
				// If executable file, print in green                            
				printf(MAKE_GREEN"%s\n"RESET_COLOR,(char*)ptr[count]); 
			} 
		} 
		else { 
			// If normal file, print by the default way(black color) 
			printf("%s\n",(char*)ptr[count]); 
		} 
		close(fd); 
	}
	printf("\n");
 	chdir(cwd2);
	//Free the allocated memory 
	free(ptr); 
	int n2=chdir(initial_path);
	free(initial_path);
	initial_path = NULL;
	return 0; 
}

