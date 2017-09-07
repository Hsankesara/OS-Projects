#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include <sys/types.h> 
#include <dirent.h> 
#include <sys/stat.h> 
#include <unistd.h> 
#include <fcntl.h> 
#include <sys/ioctl.h> 
#include <pwd.h> 
#include <grp.h> 
#include <time.h> 
 
 
 
#define RESET "\e[m" 
#define GREEN "\e[32m" 
#define BLUE "\e[36m" 
 
 
int main(void) 
{ 
   char *curr_dir = NULL; 
   DIR *dp = NULL; 
   struct dirent *dptr = NULL; 
   unsigned int count = 0; 
   long *ptr = NULL; 
   struct winsize w; 
 
   curr_dir = getenv("PWD"); 
   if(NULL == curr_dir) 
   { 
       printf("\n ERROR : Could not get the working directory\n"); 
       return -1; 
   } 
 
   // Variable to hold number of files inside the directory 
   int num_files = 0; 
   // opne the directory 
   dp = opendir((const char*)curr_dir);   
   // Start reading the directory contents 
   while(NULL != (dptr = readdir(dp)))  
   { 
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
           printf("\n Memory allocation failed\n"); 
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
       printf("\n ERROR : Could not open the working directory\n"); 
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
 
   // Start sorting the names alphabetically 
   // Using bubble sorting here 
   for(count = 0; count< num_files-1;count++) 
   { 
       for(j=count+1; j< (num_files);j++) 
       { 
           char *c = (char*)ptr[count]; 
           char *d = (char*)ptr[j]; 
            
           // Check that the two characters should be from same set 
           if( ((*c >= 'a') && (*d >= 'a')) || ((*c <='Z') && (*d <='Z')) ) 
           { 
               int i = 0; 
               // If initial characters are same, continue comparing 
               // the characters until a difference is found 
               if(*c == *d) 
               { 
                   while(*(c+i)==*(d+i)) 
                   { 
                       i++; 
                   } 
               } 
               // Check if the earlier stored value is alphabetically 
               // higher than the next value 
               if(*(c+i) > *(d+i)) 
               { 
                   // If yes, then swap the values 
                   long temp = 0; 
                   temp = ptr[count]; 
                   ptr[count] = ptr[j]; 
                   ptr[j] = temp; 
               } 
 
           } 
           else 
           { 
               // if the two beginning characters are not from 
               // the same ascii set then make them same and then 
               // compare. 
               int off_1=0, off_2=0; 
               if(*c <= 'Z') 
               { 
                   off_1 = 32; 
               } 
               if(*d <= 'Z') 
               { 
                   off_2 = 32; 
               } 
 
               int i = 0; 
               // After the character set are made same, check if the 
               // beginning characters are same. If yes, then continue  
               // searching until we find some difference. 
               if(*c+ off_1 == *d + off_2) 
               { 
                   while(*(c+off_1+i)==*(d+off_2+i)) 
                   { 
                       i++; 
                   } 
               } 
               // After difference is found, check if a swap is required. 
               if((*c + off_1+i) > (*d + off_2+i)) 
               { 
                   // If yes, go ahead and do the swap 
                   long temp = 0; 
                   temp = ptr[count]; 
                   ptr[count] = ptr[j]; 
                   ptr[j] = temp; 
               } 
           } 
       } 
    } 
 
   // Now the names are sorted alphabetically 
   // Start displaying on console. 
   for(count = 0; count< num_files; count++) 
   { 
       int fd = -1; 
       struct stat st; 
 
       fd = open((char*)ptr[count], O_RDONLY, 0); 
       if(-1 == fd) 
       { 
           printf("\n Opening file/Directory failed\n"); 
           free(ptr); 
           return -1; 
       } 
 
      // Call fstat to get the stat info about the file 
      if(fstat(fd, &st)) 
      { 
          // If fstat() fails 
          printf("\n Fstat() failed\n"); 
          close(fd); 
          free(ptr); 
          return -1; 
      } 
 
      // Check if a directory 
      if(S_ISDIR(st.st_mode)) 
      { 
      printf("d"); 
      } 
      else 
      {     
          printf("-"); 
      } 
 
      // Check the owner permission 
      mode_t permission = st.st_mode & S_IRWXU; 
 
      if(permission & S_IRUSR) 
      { 
          printf("r"); 
      } 
      else 
      { 
          printf("-"); 
      } 
 
      if(permission & S_IWUSR) 
      { 
          printf("w"); 
      } 
      else 
      { 
          printf("-"); 
      } 
 
      if(permission & S_IXUSR) 
      { 
          printf("x"); 
      } 
      else 
      { 
          printf("-"); 
      } 
 
 
      // CHeck the group permission 
      permission = st.st_mode & S_IRWXG; 
 
      if(permission & S_IRGRP) 
      { 
          printf("r"); 
      } 
      else 
      { 
          printf("-"); 
      } 
 
      if(permission & S_IWGRP) 
      { 
          printf("w"); 
      } 
      else 
      { 
          printf("-"); 
      } 
 
      if(permission & S_IXGRP) 
      { 
          printf("x"); 
      } 
      else 
      { 
          printf("-"); 
      } 
 
 
      // CHeck other's permission 
      permission = st.st_mode & S_IRWXO; 
 
      if(permission & S_IROTH) 
      { 
          printf("r"); 
      } 
      else 
      { 
          printf("-"); 
      } 
 
      if(permission & S_IWOTH) 
      { 
          printf("w"); 
      } 
      else 
      { 
          printf("-"); 
      } 
 
      if(permission & S_IXOTH) 
      { 
          printf("x"); 
      } 
      else 
      { 
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
      while(date_time[c] != '\0') 
      { 
          if(date_time[c] == '\n') 
              date_time[c] = '\0'; 
          c++; 
      } 
      printf("%s ", date_time); 
 
       // Check if the file/folder is executable. 
      if(!access((const char*)ptr[count],X_OK)) 
      { 
          if(S_ISDIR(st.st_mode)) 
          { 
              // If folder, print in blue 
              printf(BLUE"%s\n"RESET,(char*)ptr[count]); 
          } 
          else 
          {        
              // If executable file, print in green                            
              printf(GREEN"%s\n"RESET,(char*)ptr[count]); 
          } 
      } 
      else 
      { 
          // If normal file, print by the default way(black color) 
          printf("%s\n",(char*)ptr[count]); 
      } 
      close(fd); 
   } 
 
   //Free the allocated memory 
   free(ptr); 
   return 0; 
}
