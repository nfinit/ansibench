#include <unistd.h>
#include <stdio.h>
int main()
{
	printf("%d\n",sysconf(_SC_CLK_TCK));
	return 0;
}
