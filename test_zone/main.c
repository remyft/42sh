#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

static void change_fds(int fds[3])
{
	fds[0] = 1;
	fds[1] = 2;
	fds[2] = 3;
}

#define DECAL (1 << 16)

int main()
{
	struct stat buf;
	int			fds[3];

	if (access("/Library/Scripts/42/munki", X_OK) == 0)
		printf("munki size: %lld\n", buf.st_size);
	else
		perror("munki ");

	printf("TEST fds copy\n");
	fds[0] = 0;
	fds[1] = 0;
	fds[2] = 0;
	printf("AFTER [0]=%d [1]=%d [2]=%d\n", fds[0], fds[1], fds[2]);
	change_fds(fds);
	printf("BEFORE [0]=%d [1]=%d [2]=%d\n", fds[0], fds[1], fds[2]);

	printf("TESTING BITS\n");
	int test = 2;

	test |= DECAL;
	printf("test = %d %d\n", test, test & ~DECAL);
	if (test & DECAL)
		printf("bit set\n");
	else
		printf("bit not set\n");
	test = 2;
	printf("test = %d %d\n", test, test & ~DECAL);
	test = -1;
	printf("test = %d %d\n", test, test & ~DECAL);
}
