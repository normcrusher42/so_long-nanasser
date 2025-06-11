#include "so_long.h"

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		int fd;

		fd = open(av[1], O_RDONLY);
		if (fd < 0)
		{
			perror("Map failed to open. Bad input? Typo? Perhaps a SKILL ISSUE")
			exit(1);
		}
		
	}
}
