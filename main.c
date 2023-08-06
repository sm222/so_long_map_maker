/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 10:23:53 by anboisve          #+#    #+#             */
/*   Updated: 2023/08/06 12:23:49 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

void	info(void)
{
	printf("./map_maker map_name x_size y_size nb_c (optional)\n");
}
void	print_map(int x, int y, int fd, int c)
{
	char	map[y + 1][x + 2];
	int		i = 0, j = 0;
	int		nb_c = 0, t = 0, w = 0;
	int	last_y = -1, last_x = 1;
	
	
	while (j < y)
	{
		i = 0;
		map[j][x + 1] = 0;
		if (j < y - 1)
			map[j][x] = '\n';
		else
			map[j][x] = 0;
	
		while (i < x)
		{
			if ((i == 0 || j == 0) || (i == x - 1 || j == y - 1))
			{
				map[j][i] = '1';
				w++;
			}
			else
			{
				last_x = random() % x;
				if (c && j != last_y && random() % 2 == 0 && last_x == i)
				{
					c--;
					last_y = j;
					map[j][i] = 'C';
					nb_c++;
					srandomdev();
				}
				else if (random() % 3 == 0)
				{
					map[j][i] = '1';
					w++;
				}
				else
				{
					map[j][i] = '0';
					t++;
				}
			}
			i++;
		}
		j++;
	}
	for (int k = 0; k < y; k++)
		write(fd, map[k], strlen(map[k]));
	close(fd);
	printf("wall %d, colectable %d, groud %d, plable zone %d\n", \
	w, nb_c, t, nb_c + t);
}

int main(int ac, char **av)
{
	int	i = 0, j = 0;
	int	fd;
	int	max_c =	10;

	if (ac < 5)
	{
		info();
		return (1);
	}
	fd = open(av[1], O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd == -1)
	{
		printf("fd err\n");
		return (1);
	}
	i = atoi(av[2]);
	j = atoi(av[3]);
	max_c = atoi(av[4]);
	if (i < 5 || j < 5 || max_c < 1)
	{
		printf("bad args\n");
		return (1);
	}
	print_map(i, j, fd, max_c);
	return (0);
}