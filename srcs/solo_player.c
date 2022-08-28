/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 19:13:16 by ppajot            #+#    #+#             */
/*   Updated: 2022/08/27 22:04:47 by ppajot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shmup.h"

//ASCII art

/*    /\
     ( o)
	 |  |
    /|/\|\
   /_||||_\
*/

/*

        |
       / \
      / _ \
     |.o '.|
     |'._.'|
     |     |
   ,'|  |  |`.
  /  |  |  |  \
  |,-'--|--'-.|


*/

/*
     ___
 ___/   \___
/   '---'   \
'--_______--'
     / \
    /   \
    
*/


/*
     ▀▄   ▄▀     
    ▄█▀███▀█▄    
   █▀███████▀█   
   █ █▀▀▀▀▀█ █   
      ▀▀ ▀▀      

*/
/*
     ◆◆   ◆◆     
    ◆◆ ◆◆◆ ◆◆    
   ◆◆◆◆◆◆◆◆◆▀█   
   ◆ █▀▀▀▀▀█ █   
      ▀▀ ▀▀      

*/

/*

◆◆◆
◆◆◆
◆◆◆

*/

/*
 ◆◆
◆◆◆
 ◆◆

*/

//Enemy type 1

/*
     ,--.    
    |  oo|
    |  ~~|
    |/\/\| 

*/

//Enemy type 2

//

/*
       ___
      /o o\
      |   |
      |,,,|

*/

//Player

/*

      __
            \ \_____
         ###[==_____>
            /_/

*/
/*
              __
            _|  |_
          _|      |_ 
	     |  _    _  |
         | |_|  |_| |
      _  |  _    _  |  _
     |_|_|_| |__| |_|_|_|
       |_|_        _|_|
         |_|      |_|

*/

/*


            ====
           (o o")
           _\- /_
          / \  / \
         /   \/   \
        / /| |  |\ |
        || | |  | ||
        (` | |  | `)
           | |  |
           | |\ |
          /  || \
         /   ||_|\
________/____|[_]_\__

*/


/*
.             .  .       .    .     ___        .     .
    .   .              .     .    . /   \                 .    .
                 .              .  |  o  |.      .     .
     .      .        .   .   _____  \___/     .             .
                   .________|_____|__/_\___      .   .         .
  .   .    _ ___ ------------------------------__
    .    ./+\   |         |  |   |  |         |  |      .    .    .
 .       |-O-|  |         |##|   |##|         |  |.
       .  \_/___|_________|__|___|__|_________|__|     .     .   .
.   .      .       ---------|_____|---------     .
   .            .   .        .     .       .        .   .         .
      .     .                       .   .    .    .         .
                 .      .     .       .      .       .         .
*/

/*

                                                               .
|           |                      .                     O
| .     .   |              .                        .
|     _     |  .                            .                     .
|    /'\    |        .
|>=<|-O-|>=<|                                      .
| .  \_/    |             .            .                       .
|           |  .
|        .  |
|  .        |    

*/

/*
       _________
      /___   ___\
     //@@@\ /@@@\\
     \\@@@/ \@@@//
      \___ " ___/
         | - |
          \_/

		  */

/*

    .  .
     \/
    (@@)
 g/\_)(_/\e
g/\(=--=)/\e
    //\\
   _|  |_ 

*/

/*                _____
             ,-"     "-.
            / o       o \
           /   \     /   \
          /     )-"-(     \
         /     ( 6 6 )     \
        /       \ " /       \
       /         )=(         \
      /   o   .--"-"--.   o   \
     /    I  /  -   -  \  I    \
 .--(    (_}y/\       /\y{_)    )--.
(    ".___l\/__\_____/__\/l___,"    )
 \                                 /
  "-._      o O o O o O o      _,-"
      `--Y--.___________.--Y--'
         |==.___________.==| 
         `==.___________.==' 

		 */

static long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, 0);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

static void	send_enemies(t_game *game)
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

static unsigned int	collision(t_game *game, unsigned int moving, unsigned int obst)
{
	if ((moving == 'A' && (obst == 'U' || obst == 'V' || obst == 'W' || obst == 'X' || obst == 'Z' || obst == ACS_DIAMOND)) ||
		((moving == 'U' || moving == 'V' || moving == 'W' || moving == 'X' || moving == 'Z' || moving == ACS_DIAMOND) && obst == 'A'))
	{
			game->lives--;
			if (game->lives)
				return ('A');
			else
				return (' ');
	}
	if (((moving == 'U' || moving == 'V' || moving == 'W' || moving == 'X' || moving == 'Z') && obst == ACS_BULLET) || (moving == ACS_BULLET && (obst == 'U' || obst == 'V' || obst == 'W' || obst == 'X' || obst == 'Z')))
	{
		game->score++;
		return (' ');
	}
	if (moving == 'U' || moving == 'V' || moving == 'W' || moving == 'X' || moving == 'Z')
		if (obst == 'U' || obst == 'V' || obst == 'W' || obst == 'X' || obst == 'Z')
			return (' ');
	return (moving);
}

static void	update_player_pos(t_game *game, int ch)
{
	if (ch == KEY_UP && game->player.y > 0)
	{
		game->grid[game->player.y][game->player.x] = ' ';
		game->player.y--;
		game->grid[game->player.y][game->player.x] = collision(game, 'A', game->grid[game->player.y][game->player.x]);
	}	
	if (ch == KEY_DOWN && game->player.y < WIN_HEI - 1)
	{
		game->grid[game->player.y][game->player.x] = ' ';
		game->player.y++;
		game->grid[game->player.y][game->player.x] = collision(game, 'A', game->grid[game->player.y][game->player.x]);
	}
	if (ch == KEY_LEFT && game->player.x > 0)
	{
		game->grid[game->player.y][game->player.x] = ' ';
		game->player.x--;
		game->grid[game->player.y][game->player.x] = collision(game, 'A', game->grid[game->player.y][game->player.x]);
	}	
	if (ch == KEY_RIGHT && game->player.x < WIN_LEN - 1)
	{
		game->grid[game->player.y][game->player.x] = ' ';
		game->player.x++;
		game->grid[game->player.y][game->player.x] = collision(game, 'A', game->grid[game->player.y][game->player.x]);
	}
}

static void	update_enemy_pos(t_game *game)
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

static void	update_player_bullet(t_game *game)
{
	int	i;
	int	j;

	j = WIN_HEI;
	while (--j >= 0)
	{
		i = WIN_LEN;
		while (--i >= 0)
		{
			if (game->grid[j][i] == ACS_BULLET)
			{
				if (i < WIN_LEN - 1)
					game->grid[j][i + 1] = collision(game, ACS_BULLET, game->grid[j][i + 1]);
				game->grid[j][i] = ' ';
			}
		}
	}
}

static void	update_enemy_bullet(t_game *game)
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

static void	update_grid(t_game *game, int ch, int boss)
{
	//update_scenery(game);
	update_player_pos(game, ch);
	update_enemy_pos(game);
	update_player_bullet(game);
	update_enemy_bullet(game);
	if (boss)
		return;
	if (ch == 32 && game->player.last_bullet >= game->player.bullet_delay && game->player.x < WIN_LEN - 1)
	{
		game->grid[game->player.y][game->player.x + 1] = collision(game, ACS_BULLET, game->grid[game->player.y][game->player.x + 1]);
		game->player.last_bullet = 0;
	}	
}

static void	display_good(t_game *game, unsigned int c, int j, int i)
{
	if (c == 'A')
		c = '>';
	else if (c == ACS_BULLET)
		c = '~';
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
	else
	{
		wattron(game->win, COLOR_PAIR(2));
		mvwaddch(game->win, j, i, c);
		wattroff(game->win, COLOR_PAIR(2));
	}	
}

static void	display_grid(t_game *game)
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

static int	end_menu(t_game *game, int won)
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

void	game_loop1(t_game *game)
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
	game->frame_time = 0;
	game->player.bullet_delay = 5;
	game->player.last_bullet = 5;
	game->score = 0;
	game->lives = 5;
	while (game->lives)
	{
		game->frame_time++;
		if (game->player.last_bullet < game->player.bullet_delay)
			game->player.last_bullet++;
		if (game->frame_time % 30 == 0)
			send_enemies(game);
		if (game->frame_time % SCENERY_TIME == 0)
			update_scenery(game);
		frame_start = get_time_ms();
		ch = getch();
		if (ch == 17)
			break ;
		update_grid(game, ch, boss);
		display_grid(game);
		wrefresh(game->win);
		attron(A_BOLD);
		mvprintw(LINES / 2 - WIN_HEI / 2 - 1, COLS / 2 - WIN_LEN / 2,  "LIVES : %-60i SCORE : %-58i TIME : %7.2f", game->lives, game->score, (float)game->frame_time * 0.03);
		attroff(A_BOLD);
		refresh();
		frame_end = get_time_ms();
		while (frame_end - frame_start < 30)
			frame_end = get_time_ms();
	}
	if (end_menu(game, 0) == 0)
		return ;
	else
		game_loop1(game);
}