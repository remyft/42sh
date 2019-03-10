/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_complet_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 02:17:24 by rfontain          #+#    #+#             */
/*   Updated: 2019/03/10 14:15:39 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"
#include "shell_lib.h"

char	*replace_tilde(const char *path, const char *replace)
{
	int		j;
	int		k;
	int		l;
	char	*str;

	if (!(str = ft_memalloc(sizeof(char) * (ft_strlen(path)
						+ ft_strlen(replace)))))
		return (NULL);
	k = -1;
	while (path[++k] != '~')
		str[k] = path[k];
	l = -1;
	while (replace[++l])
		str[k + l] = replace[l];
	k--;
	j = 1;
	while (path[++k + j])
		str[k + l] = path[k + j];
	str[k + l] = '\0';
	return (str);
}

int		inprint(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (ft_isprint(str[i]))
			return (1);
	return (0);
}

char	*chr_beg_glob(char *buff)
{
	char	*ptr;
	int		i;

	ptr = buff;
	i = -1;
	while (buff[++i])
		if (buff[i] == '/')
			ptr = &buff[i];
		else if (ft_strchr("*[?", buff[i]))
			break ;
	return (ptr);
}

#include "stdio.h"

t_tree	*set_tmp(char *buff, int glob)
{
	t_tree	*file;
	char	*stmp;
	char	*tmp;
	char	*flag;

	//	stmp = sh_strrchr(buff, ' ') + 1;
	if (!(stmp = sh_strrchr(buff, ' ')))
		stmp = buff;
	else
		stmp += 1;
	tmp = NULL;
	//	if (!ft_strchr(stmp, '/'))
	//		return (NULL);
	if (*stmp != '/')
	{
		if (*stmp == '~')
		{
			tmp = replace_tilde(stmp, getenv("HOME"));
			if (glob)
				flag = chr_beg_glob(tmp);
			else if (!(flag = sh_strrchr(tmp, '/')))
				flag = ft_strchr(tmp, 0);
			stmp = ft_strndup(tmp, flag - tmp);
			ft_putstr("flag : ");
			ft_putendl(flag);
			ft_putstr("tmp : ");
			ft_putendl(tmp);
			ft_putstr("stmp : ");
			ft_putendl(stmp);
			printf("flag - tmp : %ld\n", flag - tmp);
		}
		else
		{
			if (glob)
				flag = chr_beg_glob(stmp);
			else if (!(flag = sh_strrchr(stmp, '/')))
				flag = ft_strchr(stmp, 0);
			stmp = ft_strndup(stmp, flag - stmp);
		}
	}
	else
	{
		if (glob)
			flag = chr_beg_glob(stmp);
		else if (!(flag = sh_strrchr(stmp, '/')))
			flag = ft_strchr(stmp, 0);
		stmp = ft_strndup(stmp, flag - stmp + 1);
	}
//	ft_putendl(stmp);
	file = create_file_tree(stmp, NULL);
	free(stmp);
	if (tmp)
		free(tmp);
	return (file);
}

/*t_tree	*set_glob_tmp(char *buff)
{
	char	*tmp;
	char	*stmp;
	t_tree	*file;

	if (!(tmp = sh_strrchr(buff, ' ')))
		tmp = buff;
	else
		stmp += 1;
	tmp = chr_beg_glob(stmp);
	if (*stmp != '/')
	{
		if (*stmp == '~')
		{
			tmp = replace_tilde(stmp, getenv("HOME"));
			stmp = ft_strndup(tmp, ft_strrchr(tmp, '/') - tmp);
		}
		else
			stmp = ft_strndup(stmp, ft_strrchr(stmp, '/') - stmp);
	}
	else
		stmp = ft_strndup(stmp, ft_strrchr(stmp, '/') - stmp + 1);
	file = create_file_tree(stmp, NULL);
	free(stmp);
	if (tmp)
		free(tmp);
	return (file);
}*/

int		str_chrglob(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*' || str[i] == '[' || str[i] == '?')
			return (1);
		i++;
	}
	return (0);
}

void	free_select(t_slct *select)
{
	if (select->next)
		free_select(select->next);
	if (select->down)
		free_select(select->down);
	if (select)
		free(select);
}
