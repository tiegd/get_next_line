#include "get_next_line.h"

int	main()
{
	int 	fd;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("fd non valid\n");
		return (0);
	}
	printf("Line 1 : %s\n", get_next_line(fd));
	printf("\n");
	printf("Line 2 : %s\n", get_next_line(fd));
	printf("\n");
	printf("Line 3 : %s\n", get_next_line(fd));
	printf("\n");
	printf("Line 4 : %s\n", get_next_line(fd));
	printf("\n");
	printf("Line 5 : %s\n", get_next_line(fd));
	printf("\n");
	printf("Line 6 : %s\n", get_next_line(fd));
	printf("\n");
	printf("Line 7 : %s\n", get_next_line(fd));
	printf("\n");
	printf("Line 8 : %s\n", get_next_line(fd));
	printf("\n");
}
