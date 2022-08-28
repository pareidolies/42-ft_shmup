/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shmup.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 19:09:28 by ppajot            #+#    #+#             */
/*   Updated: 2022/08/27 20:17:11 by ppajot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHMUP_H
# define FT_SHMUP_H

# include <stdlib.h>
# include <ncurses.h>
# include <sys/time.h>
# include <time.h>
# include <string.h>

# define WIN_HEI 40
# define WIN_LEN 150
# define COLOR_GREY 8

# define SECOND_KEY_DOWN 115
# define SECOND_KEY_UP 119
# define SECOND_KEY_LEFT 97
# define SECOND_KEY_RIGHT 100
# define SECOND_PLAYER_KEY_X 120

# define SCENERY_TIME 5

# define L0 " .                           +   .                                       .   .                       .                         .  .   .. . +  .     .                           +   .                            "
# define L1 "                                                                                                                                                                                                                 "
# define L2 "                                        .                          .       .                                                *           .. .    +                          .                      .              "
# define L3 "  .       *                        . .           .                     .  .                                     .  + . ..                         .                        .                      ;              "
# define L4 "                                                                                                                                                                           :                  - --+- -           "
# define L5 "                                        .  .                               +                                .           .                       ..                         !           .          !              "
# define L6 ".                                        .  .                                 .     .                           . .                  .   .                                 |        .             .              "
# define L7 "                                                                                                                                                                           |_         +                          "
# define L8 "                             .     .                                                   . +.    +  . .                                                                   ,  | `.                                  "
# define L9 "                             .                                   .                   .                                   .                   .                    --- --+-<#>-+- ---  --  -                      "
# define L10 "                                                                                                                                                                        `._|_,'                                  "
# define L11 "                                                                                                                                                                           T                                     "
# define L12 "                             . .                                      .                            * . .                     .  .           + .    *                       |                                     "
# define L13 "                                                                                                                                                                           !                                     "
# define L14 "                                                                                                                                                                           :         . :                         "
# define L15 "                                   +      .                                 .   .                          +                               .+                              .       *                             "
# define L16 "                                                                                                                                                                                                                 "
# define L17 "                                                                                                                                                                                                                 "
# define L18 "                                                       .                                              . +  .   +                 . .               .                  .        *              :          ..      "
# define L19 "                                                                                                                                                                                                                 "
# define L20 "  .                                       .     .                                                       +           .               . .     .      ..                -                  ::         .             "
# define L21 "                        .                                                            .              .         . .   . . .        ! /                ...               * *                                        "
# define L22 "      *             .                                                        .                              .  +    .  .       - O -                         .                                                   "
# define L23 "          .                      .    .                           +                  . .  *                          .       . / |         .                                           ;            ...          "
# define L24 "                                                                                                                                                                                                                 "
# define L25 "                                                                                                                                                                                                                 "
# define L26 "                                                                                                                                                                                                                 "
# define L27 "               .                                    +                                     .  .                    .          ..          +  .       . .              ..              .           . +             "
# define L28 "                                                                                                                                                                                                                 "
# define L29 "                                                                                                                                                                                                                 "
# define L30 "                                                                                                                                                                                                                 "
# define L31 ".                                                     .                  .                .         *      .  *  .       +. .  .            *       + . *          *             . .               .             "
# define L32 " .      .                    . .                                            .                .   .                        .  +   .     .            ..               +                                           "
# define L33 "                                                                                                                                                                                                                 "
# define L34 "                                   +      .                                 .   .                          +                               .+        . *             +                +        . ....             "
# define L35 "                                                       .                                              . +  .   +                 . .               .                  .        *              :          ..      "
# define L36 " .      .                    . .                                            .                .   .                        .  +   .     .            ..               +                                           "
# define L37 " .      .                    . .                                            .                .   .                        .  +   .     .            ..               +                                           "
# define L38 "                                        .                          .       .                                                *           .. .    +                          .                      .              "
# define L39 "  .       *                        . .           .                     .  .                                     .  + . ..                         .                        .                      ;              "


typedef	struct s_enemy
{
	int		x;
	int		y;
	char	type;
}		t_enemy;

typedef struct s_player
{
	int	x;
	int	y;
	int	bullet_delay;
	int	last_bullet;
}		t_player;

typedef struct	s_game
{
	WINDOW			*win;
	unsigned int	grid[WIN_HEI][WIN_LEN];
	char	scenery[WIN_HEI][WIN_LEN];
	char	*whole_scenery[40];
	t_player		player;
	t_player		second_player;
	int				frame_time;
	int				score;
	int				lives;
}		t_game;

void	game_loop1(t_game *game);
void	game_loop2(t_game *game);
void	update_scenery(t_game *game);
void    create_scenery(t_game *game);

#endif