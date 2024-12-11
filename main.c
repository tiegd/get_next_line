#include "get_next_line.h"
#include "get_next_line_bonus.h"

int	main()
{
	int fd;

	fd = open("test.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
}
