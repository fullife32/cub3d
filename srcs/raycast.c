/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 15:25:24 by eassouli          #+#    #+#             */
/*   Updated: 2020/09/25 21:27:25 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "raycast.h"

void	rc_dir(t_a *a)
{
	a->dir.cam_x = 2 * a->mlx.x / (double)a->res.w - 1;
	a->dir.ray_x = a->dir.x + a->dir.plane_x * a->dir.cam_x;
	a->dir.ray_y = a->dir.y + a->dir.plane_y * a->dir.cam_x;
	a->map.x = (int)a->plr.pos_x;
	a->map.y = (int)a->plr.pos_y;
	if (a->dir.ray_y == 0)
		a->dst.delta_x = 0;
	else if (a->dir.ray_x == 0)
		a->dst.delta_x = 1;
	else
		a->dst.delta_x = fabs(1 / a->dir.ray_x);
	if (a->dir.ray_x == 0)
		a->dst.delta_y = 0;
	else if (a->dir.ray_y == 0)
		a->dst.delta_y = 1;
	else
		a->dst.delta_y = fabs(1 / a->dir.ray_y);
}

void	rc_dst(t_a *a)
{
	if (a->dir.ray_x < 0)
	{
		a->dst.step_x = -1;
		a->dst.side_x = a->plr.pos_x - (double)a->map.x;
		a->dst.side_x *= a->dst.delta_x;
	}
	else
	{
		a->dst.step_x = 1;
		a->dst.side_x = (double)a->map.x + 1.0 - a->plr.pos_x;
		a->dst.side_x *= a->dst.delta_x;
	}
	if (a->dir.ray_y < 0)
	{
		a->dst.step_y = -1;
		a->dst.side_y = a->plr.pos_y - (double)a->map.y;
		a->dst.side_y *= a->dst.delta_y;
	}
	else
	{
		a->dst.step_y = 1;
		a->dst.side_y = (double)a->map.y + 1.0 - a->plr.pos_y;
		a->dst.side_y *= a->dst.delta_y;
	}
}

void	rc_hit(t_a *a)
{
	a->map.hit = 0;
	while (a->map.hit == 0)
	{
		if (a->dst.side_x < a->dst.side_y)
		{
			a->dst.side_x += a->dst.delta_x;
			a->map.x += a->dst.step_x;
			a->map.side = 0;
		}
		else
		{
			a->dst.side_y += a->dst.delta_y;
			a->map.y += a->dst.step_y;
			a->map.side = 1;
		}
		if (a->map.map[a->map.y][a->map.x] == '1')
			a->map.hit = 1;
	}
}

void	rc_line(t_a *a)
{
	if (a->map.side == 0)
		a->dst.wall = ((double)a->map.x - a->plr.pos_x + (1.0 - a->dst.step_x) / 2) / a->dir.ray_x;
	else
		a->dst.wall = ((double)a->map.y - a->plr.pos_y + (1.0 - a->dst.step_y) / 2) / a->dir.ray_y;
	a->img.line_h = (int)(a->res.h / a->dst.wall);
	a->img.px_start = -a->img.line_h / 2 + a->res.h / 2;
	if (a->img.px_start < 0)
		a->img.px_start = 0;
	a->img.px_end = a->img.line_h / 2 + a->res.h / 2;
	if (a->img.px_end >= a->res.h)
		a->img.px_end = a->res.h - 1;
	wall_set(a); // Supprimer quand texture pretes
	// Ajout texture par position du mur et orientation
	
	a->test.texNum = a->map.map[a->map.y][a->map.x];
	if (a->map.side == 0)
		a->test.wallX = a->plr.pos_y + a->dst.wall * a->dir.y;
	else
		a->test.wallX = a->plr.pos_x + a->dst.wall * a->dir.x;
	a->test.wallX -= floor(a->test.wallX);
	a->test.texX = (int)(a->test.wallX * (double)a->test.texWidth);
	if (a->map.side == 0 && a->dir.ray_x > 0)
		a->test.texX = a->test.texWidth - a->test.texX - 1;
	if (a->map.side == 1 && a->dir.ray_y < 0)
		a->test.texX = a->test.texWidth - a->test.texX - 1;
	a->test.step = 1.0 * a->test.texHeight / a->img.line_h;
	a->test.texPos = (a->img.px_start - a->res.h / 2 + a->img.line_h / 2) * a->test.step;
}

           // How much to increase the texture coordinate per screen pixel
      double step = 1.0 * texHeight / lineHeight;
      // Starting texture coordinate
      double texPos = (drawStart - h / 2 + lineHeight / 2) * step;
      for(int y = drawStart; y<drawEnd; y++)
      {
        // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
        int texY = (int)texPos & (texHeight - 1);
        texPos += step;
        Uint32 color = texture[texNum][texHeight * texY + texX];
        //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
        if(side == 1) color = (color >> 1) & 8355711;
        buffer[y][x] = color;
      }
    }