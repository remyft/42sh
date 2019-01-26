/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 05:48:08 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/25 12:55:35 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	put_prompt(char *prompt)
{
	ft_putstr(RESET);
	ft_putstr_cl(prompt, RED);
	ft_putstr(RESET);
}

char	*get_line(int fd)
{
	char	buff[4097];
	int		nb_read;
	int		i;

	nb_read = read(fd, buff, 4097);
	buff[nb_read] = '\0';
	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	buff[i] = '\0';
	if (buff[0])
		return (ft_strdup(buff));
	else
		return (NULL);
}

void	free_tab(char ***tabl)
{
	int i;

	i = -1;
	while ((*tabl)[++i])
		free((*tabl)[i]);
	free(*tabl);
}

char	**ft_ralloc(char ***env, int len)
{
	char	**tmp;
	int		i;
	int		max;

	max = get_tab_len(*env);
	if (!(tmp = (char**)malloc(sizeof(char*) * (max + len + 1))))
		return (NULL);
	i = -1;
	while ((*env)[++i] && i < max + len)
		tmp[i] = ft_strdup((*env)[i]);
	tmp[i] = NULL;
	free_tab(env);
	return (tmp);
}

int		get_tab_len(char **tabl)
{
	int i;

	i = 0;
	while (tabl[i])
		i++;
	return (i);
}