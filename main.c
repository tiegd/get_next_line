#include "get_next_line.h"

int	main()
{
	int 	fd1;
	int		fd2;
	char	*result1;
	char	*result2;

	fd1 = open("test.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	while (1)
	{
		result1 = get_next_line(fd1);
		if (!result1)
			break ;
		printf("fd1 : %s\n", result1);
		free(result1);
		result2 = get_next_line(fd2);
		if (!result2)
			break ;
		printf("fd2 : %s\n", result2);
		free(result2);
	}
}
