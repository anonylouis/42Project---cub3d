/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_graph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:05:15 by lcalvie           #+#    #+#             */
/*   Updated: 2022/06/13 12:17:05 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_graph	*new_graph(void)
{
	t_graph	*graph;

	graph = malloc(sizeof(t_graph));
	if (graph == NULL)
		return (NULL);
	graph->mlx_ptr = mlx_init();
	if (graph->mlx_ptr == NULL)
	{
		free(graph);
		return (NULL);
	}
	graph->win_ptr = mlx_new_window(graph->mlx_ptr, WIDTH, HEIGHT, "CUB'3D");
	init_img_addr(graph, &(graph->img), WIDTH, HEIGHT);
	graph->door = NULL;
	graph->hit_door = NULL;
	graph->is_boost = 1.0;
	mlx_set_font(graph->mlx_ptr, graph->win_ptr,
		"-sony-*-*-*-*-*-24-230-*-*-*-*-*-1");
	return (graph);
}

void	safe_destroy_image(void *mlx_ptr, void *img_ptr)
{
	if (img_ptr != NULL)
		mlx_destroy_image(mlx_ptr, img_ptr);
}

void	free_graph(t_graph *graph)
{
	if (graph)
	{
		safe_destroy_image(graph->mlx_ptr, graph->texture_door.img_ptr);
		safe_destroy_image(graph->mlx_ptr, graph->boost1.img_ptr);
		safe_destroy_image(graph->mlx_ptr, graph->boost2.img_ptr);
		safe_destroy_image(graph->mlx_ptr, graph->boost3.img_ptr);
		safe_destroy_image(graph->mlx_ptr, graph->boost4.img_ptr);
		safe_destroy_image(graph->mlx_ptr, graph->wall_no.img_ptr);
		safe_destroy_image(graph->mlx_ptr, graph->wall_ea.img_ptr);
		safe_destroy_image(graph->mlx_ptr, graph->wall_so.img_ptr);
		safe_destroy_image(graph->mlx_ptr, graph->wall_we.img_ptr);
		safe_destroy_image(graph->mlx_ptr, graph->img.img_ptr);
		mlx_clear_window(graph->mlx_ptr, graph->win_ptr);
		mlx_destroy_window(graph->mlx_ptr, graph->win_ptr);
		mlx_destroy_display(graph->mlx_ptr);
		free(graph->mlx_ptr);
		special_block_clear(&graph->door);
		free(graph);
	}
}
