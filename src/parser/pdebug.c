/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pdebug.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 14:52:10 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/15 18:05:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void		print_node(const char *buff, t_node *node)
{
	if (!node)
		return ;
	if (node->left)
		print_node(buff, node->left);
	t_token *token = node->token;
	if (node->token)
		printf("\t\t\tTOKEN %.*s\n", (int)(token->tail - token->head), buff);
	else
		printf("\t\t\tTOKEN null\n");
	if (node->right)
		print_node(buff, node);
}

void		debug_parser(const char *buff, t_m_list *list)
{
	printf("\nPARSER\n");
	for (t_m_list *ptr = list; ptr; ptr = ptr->next)
	{
		printf("----------------------------------\n");
		printf(" Main List (mode : %d)\n", ptr->mode);
		for (t_ao_list *ao = ptr->aolist; ao; ao = ao->next)
		{
			printf("\tAND OR LIST (mode : %d)\n", ao->mode);
			print_node(buff, ao->node);
		}
	}
}