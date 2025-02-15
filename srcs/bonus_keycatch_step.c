/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_keycatch_step.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:27:00 by lcalvie           #+#    #+#             */
/*   Updated: 2022/06/08 13:38:58 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	wall_collison_w(t_graph *graph)
{
	double	step;
	double	d_wall;
	int		save_face;

	save_face = graph->face;
	if ((save_face == 0 || save_face == 2)
		&& graph->game.angle_vision >= 90 && graph->game.angle_vision <= 270)
		d_wall = collision(graph, 180.0);
	else if (save_face == 0 || save_face == 2)
		d_wall = collision(graph, 0.0);
	else if (graph->game.angle_vision <= 180)
		d_wall = collision(graph, 90.0);
	else
		d_wall = collision(graph, 270.0);
	if (d_wall <= IN_WALL)
		return (0);
	step = dmin(STEP, d_wall - IN_WALL);
	if (save_face == 0 || save_face == 2)
		graph->game.player_x += step * cos(rad(graph->game.angle_vision));
	else
		graph->game.player_y -= step * sin(rad(graph->game.angle_vision));
	print_game(graph);
	return (0);
}

static void	make_step(int keycode, t_graph *graph, double step)
{
	if (keycode == KEY_W)
	{
		graph->game.player_x += step * cos(rad(graph->game.angle_vision));
		graph->game.player_y -= step * sin(rad(graph->game.angle_vision));
	}
	else if (keycode == KEY_A)
	{
		graph->game.player_x -= step * sin(rad(graph->game.angle_vision));
		graph->game.player_y -= step * cos(rad(graph->game.angle_vision));
	}
	else if (keycode == KEY_S)
	{
		graph->game.player_x -= step * cos(rad(graph->game.angle_vision));
		graph->game.player_y += step * sin(rad(graph->game.angle_vision));
	}
	else
	{
		graph->game.player_x += step * sin(rad(graph->game.angle_vision));
		graph->game.player_y += step * cos(rad(graph->game.angle_vision));
	}
}

int	keycatch_step(int keycode, t_graph *graph)
{
	double	step;
	double	d_wall;

	if (keycode == KEY_W)
		d_wall = collision(graph,
				graph->game.angle_vision);
	else if (keycode == KEY_A)
		d_wall = collision(graph,
				fmod(graph->game.angle_vision + 90, 360.0));
	else if (keycode == KEY_S)
		d_wall = collision(graph,
				fmod(graph->game.angle_vision + 180, 360.0));
	else
		d_wall = collision(graph,
				fmod(graph->game.angle_vision + 270, 360.0));
	if (d_wall - IN_WALL <= 0.001)
		return (keycode == KEY_W && wall_collison_w(graph));
	step = dmin(STEP * graph->is_boost, d_wall - IN_WALL);
	make_step(keycode, graph, step);
	print_game(graph);
	return (0);
}
