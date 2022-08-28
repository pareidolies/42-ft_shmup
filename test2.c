#include <ncurses.h>
#include <stdio.h>

int main()
{	
	int	ch;

	initscr();			/* Start curses mode 		  */
	printw("Hello World !!!");	/* Print Hello World		  */
	refresh();			/* Print it on to the real screen */
	ch = getch();			/* Wait for user input */
	printw("%i\n", ch);
	ch = getch();			/* Wait for user input */
	printw("%i\n", ch);
	ch = getch();			/* Wait for user input */
	printw("%i\n", ch);
	endwin();			/* End curses mode		  */

	return 0;
}
