#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	char *test = getcwd(NULL, 0);
	printf("%s", test);
	return(0);
}
