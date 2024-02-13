/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:11:46 by vphilipp          #+#    #+#             */
/*   Updated: 2024/02/13 19:12:01 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*get_next_line(int fd);

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		i;

	if (argc != 2)
	{
		if (argc == 1)
			write(1, "File name missing.\n", 19);
		else if (argc > 2)
			write(1, "Too many arguments.\n", 20);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	// line = get_next_line(fd);
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		// printf("|%d line : %s",i, line);
		// get_next_line(fd);
		printf("%s", line);
		free(line);
		i++;
	}
	// system("leaks a.out");
	close(fd);
	return (0);
}
