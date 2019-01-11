#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
int main()
{
	struct stat buf;

	if (access("/Library/Scripts/42/munki", X_OK) == 0)
		printf("munki size: %lld\n", buf.st_size);
	else
		perror("munki ");
}
