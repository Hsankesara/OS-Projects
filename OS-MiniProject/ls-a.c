#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include<string.h>

 // Define the color codes as macros
 #define RESET "\e[m"
 #define GREEN "\e[32m"
 #define BLUE "\e[36m"

int main()
{
   int i,j,num_files;
  char *curr=NULL;
  DIR *dir=NULL;
  struct dirent *dirptr=NULL;
  long *ptr=NULL;

  curr=getenv("PWD");
  if(NULL==curr)
  {
    printf("Could not get current directory!");
    return -1;
  }

  dir=opendir((const char*)curr);
  while(NULL!=(dirptr=readdir(dir)))
  {
    
    num_files++;
  }
  closedir(dir);

  dir=NULL;
  dirptr=NULL;

  if(!num_files)   //if number of files is zero,return
  {
    return 0;
  }
  else        //else allocate required memory
  {
    ptr=malloc(num_files*8);
    if(NULL==ptr)
    {
      printf("Memory allocation failed!");
    }
    else
    {
        memset(ptr,0,num_files*8);
    }
    dir=opendir((const char*)curr);
    if(NULL==dir)
    {
        printf("Could not open the working directory");
        free(ptr);
        return -1;
    }
    i=0;
    for(j=0;NULL!=(dirptr=readdir(dir));j++)
    {
      
      {
        ptr[i]=(long)dirptr->d_name;
        i++;
      }
    }
  }
  int count;
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
               // the same ASCII set then make them same and then
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
       // Check if the file/folder is executable.
       if(!access((const char*)ptr[count],X_OK))
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

               fstat(fd, &st);
               if(S_ISDIR(st.st_mode))
               {
                   // If folder, print in blue
                   printf(BLUE"%s     \n"RESET,(char*)ptr[count]);
               }
               else
               {
                   // If executable file, print in green
                   printf(GREEN"%s     \n"RESET,(char*)ptr[count]);
               }
               close(fd);
           }
           else
           {
               // If normal file, print by the default way(black color)
               printf("%s     \n",(char*)ptr[count]);
           }
   }
   printf("\n");

   //Free the allocated memory
   free(ptr);
 return 0;
}
