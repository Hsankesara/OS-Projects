/*#include <unistd.h>
#include <stdio.h>

*/
#define RESET	"\x1b[0m"
#define YELLOW  "\x1b[33m"
int pwd() {
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	printf(YELLOW"Current working directory >> %s\n", cwd);
	printf(RESET);
}