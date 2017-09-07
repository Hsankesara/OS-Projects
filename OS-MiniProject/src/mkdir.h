#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

void make_dir(char *path){
    int ret;
    char cwd[1024];
    //S_IRWXU is the bitwise-inclusive OR of S_IRUSR, S_IWUSR, and S_IXUSR.
    //S_IRUSR=Read Permission,owner.
    //S_IWUSR=Write Permission,owner.
    //S_IXUSR=Execute/search permission,owner.
    //S_IRWXG is the bitwise-inclusive OR of S_IRGRP, S_IWGRP, and S_IXGRP.
    //S_IRGRP=Read Permission,group.
    //S_IWGRP=Write Permission,group.
    //S_IXGRP=Execute/search,group.    
    //S_IRWXO is the bitwise-inclusive OR of S_IROTH, S_IWOTH, and S_IXOTH.
    //S_IROTH=Read permission,others.
    //S_IWOTH=Write permission,others.
    //S_IXOTH=Execute/Search permission,others.
    if (mkdir(path,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)==-1){
        printf("Cannot create directory, path is incorrect\n");
    }
    //If here any type of error will result to ret = -1; Error are Checking the Path ;If the There is any Folder made at the           Same Location then it will return -1.
    else {
        ret = mkdir(path,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }    
}