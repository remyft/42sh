/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 04:57:17 by rfontain          #+#    #+#             */
/*   Updated: 2018/11/22 04:58:00 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static int	ft_strspace(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (!ft_isspace(str[i]))
			return (0);
	return (1);
}

int			get_typing(int *index, char *buff, char *tmp, int nb_read, char *buff_tmp)
{
	int		len;
	int		cp;
	int		j;
	char	cbis;
	char	tchar;

	cp = 0;
	len = ft_strlen(buff);
	if (ft_isprint(tmp[0]))
		ft_bzero(buff_tmp, 8194);
	while (cp < nb_read && (ft_isprint(tmp[cp]) || ft_isspace(tmp[cp])) && (tmp[0] != 9 || ft_strspace(buff)))
	{
		tchar = buff[*index + 1];
		if (*index != len)
			buff[*index + 1] = buff[*index];
		buff[(*index)++] = tmp[cp];
		len++;
		j = 1;
		ft_putchar(tmp[cp++]);
		if (*index != len)
		{
			while (*index + j < len)
			{
				cbis = buff[*index + j];
				buff[*index + j] = tchar;
				tchar = cbis;
				j++;
			}
			tputs(tgetstr("sc", NULL), 1, ft_pchar);
			ft_putstr(&buff[*index]);
			tputs(tgetstr("rc", NULL), 1, ft_pchar);
		}
	}
	return (len);
}
