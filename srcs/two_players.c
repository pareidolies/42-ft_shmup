/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two_players.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 19:13:16 by ppajot            #+#    #+#             */
/*   Updated: 2022/08/28 16:51:18 by ppajot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shmup.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, 0);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

/*This function will send the enemies
according to a formula based on time with srand*/

void	send_enemies(t_game *game)
{
	int	i;

	i = rand() % 100;
	if (i < 20)
		game->grid[rand() % WIN_HEI][WIN_LEN - 1] = 'U';
	else if (i < 30)
		game->grid[rand() % WIN_HEI][WIN_LEN - 1] = 'V';
	else if (i < 40)
		game->grid[rand() % WIN_HEI][WIN_LEN - 1] = 'W';
	else if (i < 50)
		game->grid[rand() % WIN_HEI][WIN_LEN - 1] = 'X';
	//else if (i < 60)
		//game->grid[rand() % WIN_HEI][WIN_LEN - 1] = 'Y';
}

int	is_enemy(unsigned int id)
{
	if (id == 'U' || id == 'V' || id == 'W' || id == 'X' || id == 'Z' || id == ACS_DIAMOND)
		return (1);
	return (0);
}

int	is_player(unsigned int id)
{
	if (id == 'A' || id == 'S')
		return (1);
	return (0);
}

int	is_player_bullet(unsigned int id)
{
	if (id == ACS_BULLET || id == '-')
		return (1);
	return (0);
}

unsigned int	collision(t_game *game, unsigned int moving, unsigned int obst)
{
	//The second player can be killed by enemies
	//Why ACS_DIAMOND ?
	if ((is_player(moving) && is_enemy(obst)) || (is_player(obst) && is_enemy(moving)))
	{
		if (moving == 'A' || obst == 'A')
		{
			game->player.lives--;
			if (game->player.lives)
				return ('A');
			else
				return (' ');
		}
		else
		{
			game->second_player.lives--;
			if (game->second_player.lives)
				return ('S');
			else
				return (' ');
		}	
	}
	//The second player can kill enemies with '-'
	if ((is_player_bullet(moving) && is_enemy(obst)) || (is_player_bullet(obst) && is_enemy(moving)))
	{
		game->score++;
		return (' ');
	}
	if (is_enemy(moving) && is_enemy(obst))
		return (' ');
	if ((is_player(moving) && is_player_bullet(obst)) || (is_player(obst) && is_player_bullet(moving)))
	{
		if (moving == 'A' || obst == 'A')
			return ('A');
		else
			return ('S');
	}
	return (moving);
}

void	update_player_pos(t_game *game, int ch)
{
	if (ch == KEY_UP && game->player.y > 0 && !(game->player.y - 1 == game->second_player.y && game->player.x == game->second_player.x))
	{
		game->grid[game->player.y][game->player.x] = ' ';
		game->player.y--;
		game->grid[game->player.y][game->player.x] = collision(game, 'A', game->grid[game->player.y][game->player.x]);
	}	
	if (ch == KEY_DOWN && game->player.y < WIN_HEI - 1 && !(game->player.y + 1 == game->second_player.y && game->player.x == game->second_player.x))
	{
		game->grid[game->player.y][game->player.x] = ' ';
		game->player.y++;
		game->grid[game->player.y][game->player.x] = collision(game, 'A', game->grid[game->player.y][game->player.x]);
	}
	if (ch == KEY_LEFT && game->player.x > 0 && !(game->player.y == game->second_player.y && game->player.x == game->second_player.x - 1))
	{
		game->grid[game->player.y][game->player.x] = ' ';
		game->player.x--;
		game->grid[game->player.y][game->player.x] = collision(game, 'A', game->grid[game->player.y][game->player.x]);
	}	
	if (ch == KEY_RIGHT && game->player.x < WIN_LEN - 1 && !(game->player.y == game->second_player.y && game->player.x == game->second_player.x + 1))
	{
		game->grid[game->player.y][game->player.x] = ' ';
		game->player.x++;
		game->grid[game->player.y][game->player.x] = collision(game, 'A', game->grid[game->player.y][game->player.x]);
	}
}

void	update_second_player_pos(t_game *game, int ch)
{
	if (ch == SECOND_KEY_UP && game->second_player.y > 0 && !(game->player.y == game->second_player.y - 1 && game->player.x == game->second_player.x))
	{
		game->grid[game->second_player.y][game->second_player.x] = ' ';
		game->second_player.y--;
		game->grid[game->second_player.y][game->second_player.x] = collision(game, 'S', game->grid[game->second_player.y][game->second_player.x]);
	}	
	if (ch == SECOND_KEY_DOWN && game->second_player.y < WIN_HEI - 1 && !(game->player.y == game->second_player.y + 1 && game->player.x == game->second_player.x))
	{
		game->grid[game->second_player.y][game->second_player.x] = ' ';
		game->second_player.y++;
		game->grid[game->second_player.y][game->second_player.x] = collision(game, 'S', game->grid[game->second_player.y][game->second_player.x]);
	}
	if (ch == SECOND_KEY_LEFT && game->second_player.x > 0 && !(game->player.y == game->second_player.y && game->player.x == game->second_player.x - 1))
	{
		game->grid[game->second_player.y][game->second_player.x] = ' ';
		game->second_player.x--;
		game->grid[game->second_player.y][game->second_player.x] = collision(game, 'S', game->grid[game->second_player.y][game->second_player.x]);
	}	
	if (ch == SECOND_KEY_RIGHT && game->second_player.x < WIN_LEN - 1 && !(game->player.y == game->second_player.y && game->player.x == game->second_player.x + 1))
	{
		game->grid[game->second_player.y][game->second_player.x] = ' ';
		game->second_player.x++;
		game->grid[game->second_player.y][game->second_player.x] = collision(game, 'S', game->grid[game->second_player.y][game->second_player.x]);
	}
}

void	update_enemy_pos(t_game *game)
{
	int	i;
	int	j;

	j = -1;
	while (++j < WIN_HEI)
	{
		i = -1;
		while (++i < WIN_LEN)
		{
			if (j >= game->player.y && game->frame_time % 2 == 0 && game->grid[j][i] == 'X')
			{
				if (i > 0)
				{
					if (j > game->player.y)
						game->grid[j - 1][i - 1] = collision(game, 'X', game->grid[j - 1][i - 1]);
					else
						game->grid[j][i - 1] = collision(game, 'X', game->grid[j][i - 1]);
				}
				game->grid[j][i] = ' ';
			}
			if (game->frame_time % 2 == 0 && game->grid[j][i] == 'U')
			{
				if (i > 0)
					game->grid[j][i - 1] = collision(game, 'U', game->grid[j][i - 1]);
				game->grid[j][i] = ' ';
			}
			if (game->frame_time % 3 == 0 &&game->grid[j][i] == 'V')
			{
				if (i > 0 && j)
					game->grid[j - 1][i - 1] = collision(game, 'V', game->grid[j - 1][i - 1]);
				else if (i > 0 && j == 0)
					game->grid[j + 1][i - 1] = collision(game, 'W', game->grid[j + 1][i - 1]);
				game->grid[j][i] = ' ';
			}
			
		}
	}
	j = WIN_HEI;
	while (--j >= 0)
	{
		i = -1;
		while (++i < WIN_LEN)
		{
			if (j < game->player.y && game->frame_time % 2 == 0 && game->grid[j][i] == 'X')
			{
				if (i > 0)
					game->grid[j + 1][i - 1] = collision(game, 'X', game->grid[j + 1][i - 1]);
				game->grid[j][i] = ' ';
			}
			if (game->frame_time % 3 == 0 && game->grid[j][i] == 'W')
			{
				if (i > 0 && j < WIN_HEI - 1)
					game->grid[j + 1][i - 1] = collision(game, 'W', game->grid[j + 1][i - 1]);
				else if (i > 0 && j == WIN_HEI - 1)
					game->grid[j - 1][i - 1] = collision(game, 'V', game->grid[j - 1][i - 1]);
				game->grid[j][i] = ' ';
			}
		}
	}
}

void	update_player_bullet(t_game *game)
{
	int	i;
	int	j;

	j = WIN_HEI;
	while (--j >= 0)
	{
		i = WIN_LEN;
		while (--i >= 0)
		{
			if (game->grid[j][i] == ACS_BULLET || game->grid[j][i] == '-')
			{
				if (i < WIN_LEN - 1)
					game->grid[j][i + 1] = collision(game, game->grid[j][i], game->grid[j][i + 1]);
				game->grid[j][i] = ' ';
			}
		}
	}
}

void	update_enemy_bullet(t_game *game)
{
	int	i;
	int	j;

	j = -1;
	while (++j < WIN_HEI)
	{
		i = -1;
		while (++i < WIN_LEN)
		{
			if (game->grid[j][i] >= 'U' && game->grid[j][i] <= 'X' && i % 20 == 0 && (((game->grid[j][i] == 'V' || game->grid[j][i] == 'W') && game->frame_time % 3 == 0) || (game->grid[j][i] != 'V' && game->grid[j][i] != 'W' && game->frame_time % 2 == 0)))
			{
				if (i > 0)
					game->grid[j][i - 1] = collision(game, ACS_DIAMOND, game->grid[j][i - 1]);
			}
			if (game->grid[j][i] == ACS_DIAMOND)
			{
				if (i > 0)
					game->grid[j][i - 1] = collision(game, ACS_DIAMOND, game->grid[j][i - 1]);
				game->grid[j][i] = ' ';
			}
		}
	}
}

void	update_grid(t_game *game, int ch)
{
	if (game->player.lives)
		update_player_pos(game, ch);
	if (game->second_player.lives)
		update_second_player_pos(game, ch);
	update_enemy_pos(game);
	update_player_bullet(game);
	update_enemy_bullet(game);
	if (game->player.lives && ch == 32 && game->player.last_bullet >= game->player.bullet_delay && game->player.x < WIN_LEN - 1)
	{
		game->grid[game->player.y][game->player.x + 1] = collision(game, ACS_BULLET, game->grid[game->player.y][game->player.x + 1]);
		game->player.last_bullet = 0;
	}
	if (game->second_player.lives && ch == SECOND_PLAYER_KEY_X && game->second_player.last_bullet >= game->second_player.bullet_delay && game->second_player.x < WIN_LEN - 1)
	{
		game->grid[game->second_player.y][game->second_player.x + 1] = collision(game, '-', game->grid[game->second_player.y][game->second_player.x + 1]);
		game->second_player.last_bullet = 0;
	}
}

void	display_good(t_game *game, unsigned int c, int j, int i)
{
	wattron(game->win, A_BOLD);
	if (c == 'A')
		c = '>';
	//Vessel of the second player
	else if (c == 'S')
		c = 'D';
	else if (c == ACS_BULLET)
		c = '~';
	//Bullet of the second player
	else if (c == '-')
		c = '-';
	else if (c >= 'U' && c <= 'X')
		c = ACS_DIAMOND;
	else if (c == ACS_DIAMOND)
		c = ACS_BULLET;
	if (c == '>' || c == '~')
	{
		wattron(game->win, COLOR_PAIR(3));
		mvwaddch(game->win, j, i, c);
		wattroff(game->win, COLOR_PAIR(3));
	}
	//The second player is printed in yellow
	else if (c == 'D' || c == '-')
	{
		wattron(game->win, COLOR_PAIR(10));
		mvwaddch(game->win, j, i, c);
		wattroff(game->win, COLOR_PAIR(10));
	}
	else
	{
		wattron(game->win, COLOR_PAIR(2));
		mvwaddch(game->win, j, i, c);
		wattroff(game->win, COLOR_PAIR(2));
	}
	wattroff(game->win, A_BOLD);	
}

void	display_grid(t_game *game)
{
	int	i;
	int	j;

	j = -1;
	while (++j < WIN_HEI)
	{
		i = -1;
		while (++i < WIN_LEN)
		{
			if (game->grid[j][i] == ' ')
			{
					wattron(game->win, COLOR_PAIR(4));
					mvwprintw(game->win, j, i, "%c", game->scenery[j][i]);
					wattroff(game->win, COLOR_PAIR(4));
			}
			else
			{
				display_good(game, game->grid[j][i], j, i);
			}
		}
	}
}

int	end_menu(t_game *game, int won)
{
	int ret;
	int	ch;
	char game_over[6][90] = 
	{
	"   ______      _      ____    ____ ________        ___  ____   ____ ________ _______     ",
	" .' ___  |    / \\    |_   \\  /   _|_   __  |     .'   `|_  _| |_  _|_   __  |_   __ \\    ",
	"/ .'   \\_|   / _ \\     |   \\/   |   | |_ \\_|     /  .-.  \\ \\   / /   | |_ \\_| | |__) |   ",
	"| |   ____  / ___ \\    | |\\  /| |   |  _| _     | |   | | \\ \\ / /    |  _| _  |  __ /    ",
	"\\ `.___]  _/ /   \\ \\_ _| |_\\/_| |_ _| |__/ |    \\  `-'  /  \\ ' /    _| |__/ |_| |  \\ \\_  ",
	" `._____.|____| |____|_____||_____|________|     `.___.'    \\_/    |________|____| |___| "
	};
	char you_won[6][80] = 
	{
	" ____  ____   ___   _____  _____   ____      ____   ___   ____  _____   _  ",
	"|_  _||_  _|.'   `.|_   _||_   _| |_  _|    |_  _|.'   `.|_   \\|_   _| | | ",
	"  \\ \\  / / /  .-.  \\ | |    | |     \\ \\  /\\  / / /  .-.  \\ |   \\ | |   | | ",
	"   \\ \\/ /  | |   | | | '    ' |      \\ \\/  \\/ /  | |   | | | |\\ \\| |   | | ",
	"   _|  |_  \\  `-'  /  \\ \\__/ /        \\  /\\  /   \\  `-'  /_| |_\\   |_  |_| ",
	"  |______|  `.___.'    `.__.'          \\/  \\/     `.___.'|_____|\\____| (_) "                                                                           
	};
	ret = 1;
	int	i = -1;
	wattron(game->win, A_BOLD);
	wattron(game->win, COLOR_PAIR(9));
	while (++i < 6)
	{
		if (!won)
			mvwprintw(game->win, 5 + i, 30, "%s", game_over[i]);
		else
			mvwprintw(game->win, 5 + i, 37, "%s", you_won[i]);
	}
	mvwprintw(game->win, WIN_HEI / 2 + 5, 65, "FINAL SCORE : %i", game->score);
	wattron(game->win, COLOR_PAIR(8));
	mvwprintw(game->win, WIN_HEI / 2 + 10, 68, "PLAY AGAIN");
	wattron(game->win, COLOR_PAIR(9));
	mvwprintw(game->win, WIN_HEI / 2 + 15, 71, "EXIT");
	wattroff(game->win, COLOR_PAIR(9));
	wrefresh(game->win);
	while (1)
	{
		ch = getch();
		if (ch == KEY_UP || ch == KEY_DOWN)
		{
			ret = (ret + 1) % 2;
			wattron(game->win, COLOR_PAIR(9 - ret));
			mvwprintw(game->win, WIN_HEI / 2 + 10, 68, "PLAY AGAIN");
			wattron(game->win, COLOR_PAIR(8 + ret));
			mvwprintw(game->win, WIN_HEI / 2 + 15, 71, "EXIT");
			wattroff(game->win, COLOR_PAIR(8 + ret));
		}
		wrefresh(game->win);
		if (ch == 10)
			break ;
	}
	wattroff(game->win, A_BOLD);
	return (ret);
}

void	display_score(t_game *game)
{
	attron(A_BOLD);
	if (game->player_nbr == 1)
		mvprintw(game->lines / 2 - WIN_HEI / 2 - 1, game->cols / 2 - WIN_LEN / 2,  "LIVES : %-60i SCORE : %-58i TIME : %7.2f", game->player.lives, game->score, (float)game->frame_time * 0.03);
	else
		mvprintw(game->lines / 2 - WIN_HEI / 2 - 1, game->cols / 2 - WIN_LEN / 2,  "P1 LIVES : %-5i P2 LIVES : %-41i SCORE : %-58i TIME : %7.2f", game->player.lives, game->second_player.lives, game->score, (float)game->frame_time * 0.03);
	attroff(A_BOLD);
	refresh();
}

void	game_loop(t_game *game)
{
	int	ch;
	int	y;
	int	x;
	long	frame_start;
	long	frame_end;
	
	y = WIN_HEI - 2;
	x = WIN_LEN / 2 - 1;

	nodelay(stdscr, TRUE);
	nodelay(game->win, TRUE);
	//Now the player starts at the bottom center of the rectangle
	game->player.y = WIN_HEI - 2;
	game->player.x = WIN_LEN / 2 - 1;
	//The second player starts at the upper center of the rectangle
	
	game->frame_time = 0;
	game->player.bullet_delay = 5;
	game->player.last_bullet = 5;
	game->second_player.bullet_delay = 5;
	game->second_player.last_bullet = 5;
	game->score = 0;
	game->player.lives = 5;
	if (game->player_nbr == 2)
	{
		game->second_player.y = 2;
		game->second_player.x = WIN_LEN / 2 - 1;
		game->second_player.lives = 5;
	}
	else
	{
		game->second_player.lives = 0;
		game->second_player.y = 100000;
		game->second_player.x = 100000;
	}
	init_grid(game, game->player_nbr);
	while (game->player.lives || game->second_player.lives)
	{
		game->frame_time++;
		if (game->player.last_bullet < game->player.bullet_delay)
			game->player.last_bullet++;
		if (game->second_player.last_bullet < game->second_player.bullet_delay)
			game->second_player.last_bullet++;
		if (game->frame_time % 30 == 0)
			send_enemies(game);
		if (game->frame_time % SCENERY_TIME == 0)
			update_scenery(game);
		frame_start = get_time_ms();
		ch = getch();
		if (ch == 17)
			return ;
		if (ch == 410)
		{
			int test = -1;
			while (++test < COLS * LINES)
			printw(" ");
		}
		
		update_grid(game, ch);
		display_grid(game);
		wrefresh(game->win);
		//wrefresh(stdscr);
		display_score(game);
		frame_end = get_time_ms();
		while (frame_end - frame_start < 30)
			frame_end = get_time_ms();
	}
	if (end_menu(game, 0) == 0)
		return ;
	else
		game_loop(game);
}
