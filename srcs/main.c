#include "../ft_shmup.h"

WINDOW	*win_create(int heigth, int width, int winy, int winx)
{
	WINDOW	*win;

	win = newwin(heigth, width, winy, winx);
	box(win, 0, 0);
	wrefresh(win);
	return (win);
}

/*This function checks if the size of the terminal
is big enough to start the game*/

int right_size(WINDOW *win)
{
	int	term_x;
	int	term_y;

	getmaxyx(win, term_y, term_x);

	return ((term_x >= WIN_LEN)&&(term_y >= WIN_HEI));
}

/*
     ,--.    
    |  oo|
    |  ~~|
    |/\/\| 

*/

int	start_menu(t_game *game)
{
	int ret = 1;
	int	ch;
    char say_hello[4][30] = 
    {
"     ,--.     Welcome     ",
"    |  oo|                ",
"    |  ~~|                ",
"    |/\\/\\|                "
};
	char welcome_shmup[9][70] = 
	{
/*"            _|                                               ",
"   _|_|_|   _|_|_|     _|_|_|  _|_|     _|    _|   _|_|_|    ",
" _|_|       _|    _|   _|    _|    _|   _|    _|   _|    _|  ",
"     _|_|   _|    _|   _|    _|    _|   _|    _|   _|    _|  ",
" _|_|_|     _|    _|   _|    _|    _|     _|_|_|   _|_|_|    ",
"                                                   _|        ",
"                                                   _|        "*/

/*" ::::::::  :::    ::: ::::    ::::  :::    ::: :::::::::  ",
":+:    :+: :+:    :+: +:+:+: :+:+:+ :+:    :+: :+:    :+: ",
"+:+        +:+    +:+ +:+ +:+:+ +:+ +:+    +:+ +:+    +:+ ",
"+#++:++#++ +#++:++#++ +#+  +:+  +#+ +#+    +:+ +#++:++#+  ",
"       +#+ +#+    +#+ +#+       +#+ +#+    +#+ +#+        ",
"#+#    #+# #+#    #+# #+#       #+# #+#    #+# #+#        ",
" ########  ###    ### ###       ###  ########  ###        "*/

"        |                                      ",
"       / \\           _                           ",
"      / _ \\         | |                          ",
"     |.o '.|     ___| |__  _ __ ___  _   _ _ __  ",
"     |'._.'|    / __| '_ \\| '_ ` _ \\| | | | '_ \\ ",
"     |     |    \\__ \\ | | | | | | | | |_| | |_) |",
"   ,'|  |  |`.  |___/_| |_|_| |_| |_|\\__,_| .__/ ",
"  /  |  |  |  \\                           | |    ",
"  |,-'--|--'-.|                           |_|    "
};

	int	i = -1;
	wattron(game->win, A_BOLD);
	wattron(game->win, COLOR_PAIR(4));
	while (++i < 9)
	{
		mvwprintw(game->win, 7 + i, 45, "%s", welcome_shmup[i]);
	}
    i = -1;
    //red say hello
	wattron(game->win, COLOR_PAIR(2));
	while (++i < 4)
	{
		mvwprintw(game->win, 32 + i, 5, "%s", say_hello[i]);
	}
	wattron(game->win, COLOR_PAIR(9));
	mvwprintw(game->win, WIN_HEI / 2 + 5, 66, "SELECT MODE");
	wattron(game->win, COLOR_PAIR(8));
	mvwprintw(game->win, WIN_HEI / 2 + 10, 66, "SOLO PLAYER");
	wattron(game->win, COLOR_PAIR(9));
	mvwprintw(game->win, WIN_HEI / 2 + 15, 70, "DUO");
	wattroff(game->win, COLOR_PAIR(9));
	wrefresh(game->win);
	while (1)
	{
		ch = getch();
		if (ch == KEY_UP || ch == KEY_DOWN)
		{
			ret = (ret + 1) % 2;
			wattron(game->win, COLOR_PAIR(9 - ret));
			mvwprintw(game->win, WIN_HEI / 2 + 10, 66, "SOLO PLAYER");
			wattron(game->win, COLOR_PAIR(8 + ret));
			mvwprintw(game->win, WIN_HEI / 2 + 15, 70, "DUO");
			wattroff(game->win, COLOR_PAIR(8 + ret));
		}
		wrefresh(game->win);
		if (ch == 10)
			break ;
	}
	wattroff(game->win, A_BOLD);
	return (2 - ret);
}

void	init_grid(t_game *game, int mode)
{
	int	i;
	int	j;

	j = -1;
	while (++j < WIN_HEI)
	{
		i = -1;
		while (++i < WIN_LEN)
		{
			if (mode && j == game->player.y && i == game->player.x)
				game->grid[j][i] = 'A';
			else if (mode == 2 && j == game->second_player.y && i == game->second_player.x)
				game->grid[j][i] = 'S';	
			else
				game->grid[j][i] = ' ';
		}
	}
}

int	main (void)
{
	int		winx;
	int 	winy;
	t_game	game;
	
	initscr();
	raw();
	keypad(stdscr, TRUE);
	winy = (LINES - WIN_HEI) / 2;
	winx = (COLS - WIN_LEN) / 2;

	start_color();
	curs_set(0);
	noecho();
	
	//Color initialization
	init_pair(1, COLOR_GREY, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_WHITE, COLOR_GREY);
	init_pair(6, COLOR_GREY, COLOR_MAGENTA);
	init_pair(7, COLOR_GREY, COLOR_CYAN);
	init_pair(8, COLOR_BLACK, COLOR_WHITE);
	init_pair(9, COLOR_WHITE, COLOR_BLACK);
	init_pair(10, COLOR_CYAN, COLOR_BLACK);
	init_color(COLOR_BLACK, 0, 0, 0);
	init_color(COLOR_YELLOW, 0, 0, 800);
	init_color(COLOR_GREY, 100, 100, 100);
	init_color(COLOR_CYAN, 800, 800, 100);
	//Rand initialization
	srand(time(NULL));

	//ch = getch();
	//printw("%i", ch);
	//refresh();
	//getch();
	refresh();
	game.win = win_create(WIN_HEI, WIN_LEN, winy, winx);
	if (!right_size(stdscr))
	{
		endwin();
		fprintf(stderr,"\x1b[91mTerminal is too small! Please increase the size of your terminal.\n\x1b[0m");
		return (0);
	}
	create_scenery(&game);
	update_scenery(&game);
	//Do we have to keep the lines below ?
	/*wattron(game.win, COLOR_PAIR(5));
	mvwprintw(game.win, game.player.y, game.player.x, "A");
	wattroff(game.win, COLOR_PAIR(5));
	wattrset(game.win, COLOR_PAIR(1));*/
	game.cols = COLS;
	game.lines = LINES;
	wattrset(stdscr, COLOR_PAIR(5));
	int test = -1;
	while (++test < COLS * LINES)
		printw(" ");
	init_grid(&game, 0);
	display_grid(&game);
	wrefresh(stdscr);
	wrefresh(game.win);
	//Adding a start menu
	game.player_nbr = start_menu(&game);
	game_loop(&game);
	endwin();
	return (0);
}

/*TODO :level increase
		multiplayer - OK
        start menu to select mode - OK
		new enemies
		resize
		new art/collision
		boss
		new weapons
		manual of the game*/