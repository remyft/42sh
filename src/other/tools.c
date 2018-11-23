/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 05:48:08 by rfontain          #+#    #+#             */
/*   Updated: 2018/11/23 09:27:38 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	put_prompt(char *prompt)
{
	ft_putstr(RESET);
	ft_putend_cl(prompt, RED,  " $> ", BLUE);
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

char	*replace_str(char *path, char *src, char *replace)
{
	int		i;
	int		j;
	int		k;
	int		l;
	char	*str;

	if (!ft_strstr(path, src))
		return (NULL);
	i = 0;
	j = 0;
	ft_find(path, src, &i, &j);
	if (!(str = malloc(sizeof(char) * (ft_strlen(path) - ft_strlen(src)
						+ ft_strlen(replace) + 1))))
		return (NULL);
	k = -1;
	while (++k < i)
		str[k] = path[k];
	str[k] = '\0';
	l = -1;
	while (replace[++l])
		str[k + l] = replace[l];
	k--;
	while (path[++k + j])
		str[k + l] = path[k + j];
	str[k + l] = '\0';
	return (str);
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
