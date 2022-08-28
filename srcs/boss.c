#include "../ft_shmup.h"

void	boss_script(t_game *game)
{
    (void) game;

}

int	move_boss(t_game *game)
{
	int	i = 0;
	int	j = 0;
	static int cinematic = 0;

	if (cinematic == 14)
		return (0);
	while (i < 28)
	{
		j = 0;
		while (j < 6)
		{
			game->grid[WIN_HEI / 2 + j][WIN_LEN + i - 14] = game->grid[WIN_HEI / 2 + j][WIN_LEN + i - 14 + 1];
			j++;
		}
		i++;
	}
	cinematic++;
	return (1);
}

void	create_boss(t_game *game)
{
	char boss1[6][14] = 
	{
"     ___     ",
" ___/   \\___ ",
"/   '###'   \\",
"'##_______##'",
"     / \\      ",
"    /   \\    "
	};
	int	i = 0;
	int j = 0;

	while (i < 13)
	{
		j = 0;
		while (j < 6)
		{
			game->grid[WIN_HEI / 2 + j][WIN_LEN + i] = boss1[j][i];
			j++;
		}
		i++;
	}
	/*int	cinematic = 0;
	while (cinematic < 13)
	{
		move_boss(game);
		update_grid(game, 0);
		display_grid(game);
		wrefresh(game->win);
		usleep(500000);
		cinematic++;
	}*/
}