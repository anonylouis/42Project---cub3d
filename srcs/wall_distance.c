/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_distance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:22:57 by lcalvie           #+#    #+#             */
/*   Updated: 2022/05/30 18:26:53 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	is_a_wall(t_graph *graph, double x, double y, double angle)
{
	int	i;
	int	j;

	if (angle <= 90)
	{
		i = ceil(y - 1);
		j = floor(x);
	}
	else if (angle <= 180)
	{
		i = ceil(y - 1);
		j = ceil(x - 1);
	}
	else if (angle <= 270)
	{
		i = floor(y);
		j = ceil(x - 1);
	}
	else
	{
		i = floor(y);
		j = floor(x);
	}
	return (graph->game.map[i][j] == '1');
}

double	wall_distance(t_graph *graph, double angle)
{
	double	x;
	double	y;
	double	d;

	x = graph->game.player_x;
	y = graph->game.player_y;
	graph->face = -1;
	while (graph->face == -1 || !is_a_wall(graph, x, y, angle))
		graph->face = find_next_border(&x, &y, angle);
	d = distance(graph->game.player_x, graph->game.player_y, x, y);
	if (graph->face == 0)
		graph->percent_face = x;
	else if (graph->face == 1)
		graph->percent_face = 1 - y;
	else if (graph->face == 2)
		graph->percent_face = 1 - x;
	else
		graph->percent_face = y;
	return (d);
}
