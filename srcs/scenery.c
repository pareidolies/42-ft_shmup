/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scenery.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 14:54:03 by smostefa          #+#    #+#             */
/*   Updated: 2022/08/27 14:54:51 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shmup.h"
#include <stdio.h>

void	update_scenery(t_game *game)
{
	static int offset = 0;
	
	int	i;
	int	j;

	j = WIN_HEI;
	while (--j >= 0)
	{
		i = WIN_LEN;
		while (--i >= 0)
		{
			game->scenery[j][i] = game->whole_scenery[j][(i + offset) % 210];
		}
	}
	offset++;
}

void    create_scenery(t_game *game)
{
    game->whole_scenery[0] = L0;
    game->whole_scenery[1] = L1;
    game->whole_scenery[2] = L2;
    game->whole_scenery[3] = L3;
    game->whole_scenery[4] = L4;
    game->whole_scenery[5] = L5;
    game->whole_scenery[6] = L6;
    game->whole_scenery[7] = L7;
    game->whole_scenery[8] = L8;
    game->whole_scenery[9] = L9;
    game->whole_scenery[10] = L10;
    game->whole_scenery[11] = L11;
    game->whole_scenery[12] = L12;
    game->whole_scenery[13] = L13;
    game->whole_scenery[14] = L14;
    game->whole_scenery[15] = L15;
    game->whole_scenery[16] = L16;
    game->whole_scenery[17] = L17;
    game->whole_scenery[18] = L18;
    game->whole_scenery[19] = L19;
    game->whole_scenery[20] = L20;
    game->whole_scenery[21] = L21;
    game->whole_scenery[22] = L22;
    game->whole_scenery[23] = L23;
    game->whole_scenery[24] = L24;
    game->whole_scenery[25] = L25;
    game->whole_scenery[26] = L26;
    game->whole_scenery[27] = L27;
    game->whole_scenery[28] = L28;
    game->whole_scenery[29] = L29;
    game->whole_scenery[30] = L30;
    game->whole_scenery[31] = L31;
    game->whole_scenery[32] = L32;
    game->whole_scenery[33] = L33;
    game->whole_scenery[34] = L34;
    game->whole_scenery[35] = L35;
    game->whole_scenery[36] = L36;
    game->whole_scenery[37] = L37;
    game->whole_scenery[38] = L38;
    game->whole_scenery[39] = L39;
 
/*    j = 0;
    while (j < 40)
    {
        i = 0;
        while (i < 150)
        {
            printf("%c", scenery[j][i]);
            i++;
        }
        printf("\n");
        j++;
    }
*/
}
