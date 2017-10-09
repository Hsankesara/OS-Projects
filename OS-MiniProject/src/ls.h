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


  
int ls(char *path)
{
	
	char *curr_dir = NULL;
	DIR *dp = NULL;
	struct dirent *dptr = NULL;
	unsigned int count = 0;
	long *ptr = NULL;
	
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	if(NULL!=path)
		curr_dir=path;
	else
		curr_dir=cwd;
	int n = chdir(curr_dir);
	if(n != 0){
		printf(RED"bash: cd: cn: No such file or directory\n"RESET);
		return -1;
	}

	if(NULL == curr_dir)
	{
		printf(RED"\n ERROR : Could not get the working directory\n"RESET);
		return -1;
	}

	// Variable to hold number of files inside the directory
	int num_files = 0;
	dp = opendir((const char*)curr_dir);
	// Start reading the directory contents
	while(NULL != (dptr = readdir(dp)))
	{
		// Do not count the files begining with '.'
		if(dptr->d_name[0] != '.')
			num_files++;
	}
  
	// close the directory.
	closedir(dp);

	// Restore the values 
	dp = NULL;
	dptr = NULL;

	// Check that we should have at least one file/folder
	// inside the current working directory
	if(!num_files)
	{
		return 0;
	}
	else
	{
		// Allocate memory to hold the addresses of the
		// names of contents in current working directory
		ptr = malloc(num_files*8);
		if(NULL == ptr)
		{
			printf(RED"\n Memory allocation failed\n"RESET);
			return -1;
		}
		else
		{
			// Initialize the memory by zeros
			memset(ptr,0,num_files*8);
		}
	}
   

	// Open the directory again
	dp = opendir((const char*)curr_dir);
	if(NULL == dp)
	{
		printf(RED"\n ERROR : Could not open the working directory\n"RESET);
		free(ptr);
		return -1;
	}

	// Start iterating the directory and read all its contents
	// inside an array allocated above.
	unsigned int j = 0;
	for(count = 0; NULL != (dptr = readdir(dp)); count++)
	{
		if(dptr->d_name[0] != '.')
		{
		   ptr[j] = (long)dptr->d_name;
		   j++;
		}
	}


	
	
	for(count = 0; count< num_files; count++)
	{
		// Check if the file/folder is executable.
		if(!access((const char*)ptr[count],X_OK))
			{
				int fd = -1;
				struct stat st;

				fd = open((char*)ptr[count], O_RDONLY, 0);
				if(-1 == fd)
				{
					printf(RED"\n Opening file/Directory failed\n"RESET);
					free(ptr);
					return -1;
				}

				fstat(fd, &st);
				if(S_ISDIR(st.st_mode))
				{
					// If folder, print in blue
					printf(MAKE_BLUE"%s     "RESET_COLOR,(char*)ptr[count]);
				}
				else
				{
					// If executable file, print in green
					printf(MAKE_GREEN"%s     "RESET_COLOR,(char*)ptr[count]);
				}
				close(fd);
		   }
			else
			{
				// If normal file, print by the default way(black color)
				printf("%s     ",(char*)ptr[count]);
			}
	}
	printf("\n");
	chdir(cwd);
	//Free the allocated memory
	free(ptr);
	return 0;

}

int lsa(char *path)
{
	char *curr_dir = NULL;
	DIR *dp = NULL;
	struct dirent *dptr = NULL;
	unsigned int count = 0;
	long *ptr = NULL;
	char cwd1[1024];
	getcwd(cwd1, sizeof(cwd1));
	if(path!=NULL)
	 curr_dir=path;
	else
	curr_dir=cwd1;
	int n = chdir(curr_dir);
	if(n != 0){
		printf(RED"bash: cd: cn: No such file or directory\n"RESET);
		return -1;
	}
	if(NULL == curr_dir)
	{
		printf(RED"\n ERROR : Could not get the working directory\n"RESET);
		return -1;
	}

	// Variable to hold number of files inside the directory
	int num_files = 0;
	dp = opendir((const char*)curr_dir);
	// Start reading the directory contents
	while(NULL != (dptr = readdir(dp)))
	{
		num_files++;
	}
  
	// close the directory.
	closedir(dp);

	// Restore the values 
	dp = NULL;
	dptr = NULL;

	// Check that we should have at least one file/folder
	// inside the current working directory
	if(!num_files)
	{
		return 0;
	}
	else
	{
		// Allocate memory to hold the addresses of the
		// names of contents in current working directory
		ptr = malloc(num_files*8);
		if(NULL == ptr)
		{
			printf(RED"\n Memory allocation failed\n"RESET);
			return -1;
		}
		else
		{
			// Initialize the memory by zeros
			memset(ptr,0,num_files*8);
		}
	}
   
	// Open the directory again
	dp = opendir((const char*)curr_dir);
	if(NULL == dp)
	{
		printf(RED"\n ERROR : Could not open the working directory\n"RESET);
		free(ptr);
		return -1;
	}

	// Start iterating the directory and read all its contents
	// inside an array allocated above.
	unsigned int j = 0;
	for(count = 0; NULL != (dptr = readdir(dp)); count++)
	{
		
		{
		   ptr[j] = (long)dptr->d_name;
		   j++;
		}
	}

	for(count = 0; count< num_files; count++)
	{
		// Check if the file/folder is executable.
		if(!access((const char*)ptr[count],X_OK))
			{
				int fd = -1;
				struct stat st;

				fd = open((char*)ptr[count], O_RDONLY, 0);
				if(-1 == fd)
				{
					printf(RED"\n Opening file/Directory failed\n"RESET);
					free(ptr);
					return -1;
				}

				fstat(fd, &st);
				if(S_ISDIR(st.st_mode))
				{
					// If folder, print in blue
					printf(MAKE_BLUE"%s     "RESET_COLOR,(char*)ptr[count]);
				}
				else
				{
					// If executable file, print in green
					printf(MAKE_GREEN"%s     "RESET_COLOR,(char*)ptr[count]);
				}
				close(fd);
		   }
			else
			{
				// If normal file, print by the default way(black color)
				printf("%s     ",(char*)ptr[count]);
			}
	}
	printf("\n");
	chdir(cwd1);
	//Free the allocated memory
	free(ptr);
	return 0;

}

int lsl(char *path)
{ 
   char *curr_dir = NULL; 
   DIR *dp = NULL; 
   struct dirent *dptr = NULL; 
   unsigned int count = 0; 
   long *ptr = NULL; 
   char cwd2[1024];
   getcwd(cwd2, sizeof(cwd2));
	if(path!=NULL)
		curr_dir = path;
	else
		curr_dir = cwd2;
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
		num_files++; 
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
 
		// Check if a directory 
		if(S_ISDIR(st.st_mode)) { 
			printf("d"); 
		} 
		else {     
			printf("-"); 
		} 
 
		// Check the owner permission 
		mode_t permission = st.st_mode & S_IRWXU; 
 
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
		strncpy(date_time, ctime(&st.st_ctime), sizeof(date_time)); 
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
 	chdir(cwd2);
	//Free the allocated memory 
	free(ptr); 
	return 0; 
}
