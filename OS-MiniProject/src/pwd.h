/*#include <unistd.h>
#include <stdio.h>

*/
int pwd() {
    
	char cwd[1024];
    
	chdir("/path/to/change/directory/to");
    
	getcwd(cwd, sizeof(cwd));
    
	printf("Current working dir: %s\n", cwd);
}